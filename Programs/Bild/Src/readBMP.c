#include "BMP_types.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "input.h"
#include "errorhandler.h"
#include <stdint.h>
#include <stdio.h>
#include "lcd.h"
#include "readBMP.h"
#include "LCD_GUI.h"
#include "stm32f429xx.h"
#include <stdlib.h>
#include <string.h>


static uint16_t rgbQTo565(RGBQUAD c)
{
    return (((c.rgbRed >> 3) << 11) | ((c.rgbGreen >> 2) << 5) | (c.rgbBlue >> 3));
}
static uint16_t rgbTo565(RGBTRIPLE c)
{
    return ((c.rgbtRed >> 3) << 11) | ((c.rgbtGreen >> 2) << 5) | (c.rgbtBlue >> 3);
}
int processBMP()
{
    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBQUAD palette[MAX_COLOR_TABLE_SIZE];

    int result =0;
    //fileheader lesen 
    result = COMread((char *)&fileheader, sizeof(BITMAPFILEHEADER), 1);
    RETURN_NOK_ON_ERR(result == EOF, "kann nicht BMP fileheader lesen");
    //infoheader lesen
    result = COMread((char *)&infoheader, sizeof(BITMAPINFOHEADER), 1);
    RETURN_NOK_ON_ERR(result == EOF, "kann nicht BMP infoheader lesen");

    RETURN_NOK_ON_ERR(fileheader.bfType != BMP_SIGNATURE, "nicht BM Typ");
    RETURN_NOK_ON_ERR(infoheader.biBitCount != 8 && infoheader.biBitCount != 24, "nicht 8 Bit BMP");
    RETURN_NOK_ON_ERR(infoheader.biCompression != BI_RGB && infoheader.biCompression != BI_RLE8, "nicht richtige Format von Compression");
   
   // sprintf("H: %ld, W: %ld", infoheader.biHeight, infoheader.biWidth);
    
    if(infoheader.biCompression == BI_RLE8)
    {
        result = COMread((char *)palette, sizeof(RGBQUAD), infoheader.biClrUsed == 0 ? 256 : infoheader.biClrUsed);
        RETURN_NOK_ON_ERR(result == EOF, "kann nicht palette lesen");
        drawCompresedImage(palette,infoheader.biWidth,infoheader.biHeight);
    }else { //BI_RGB
        if(infoheader.biBitCount == 24)
            drawImage24Lines(infoheader.biWidth, infoheader.biHeight);
        else //8 Bit
            drawImage8Lines(infoheader.biWidth, infoheader.biHeight, infoheader.biClrUsed);
    }

    return EOK;
}

bool readButton()
{
    if((GPIOF->IDR&0xFF) != 0xFF) return 1;  // gpiof is 0-input
    return 0;
}
void drawCompresedImage(RGBQUAD* palette, uint32_t w,  uint32_t h)
{
    int c1 = 0; 
    int c2 = 0; 
    uint32_t i = 0;
    bool draw = 1;

    int x = 0, y = 0;
    uint16_t lcdColor;
    while(1)
    {
        c1 = nextChar();
        c2 = nextChar();
        if(c1 == 00) // EXIT, absolute mode or return! 
        {
            switch(c2)
            {
                case 0: //end of line, read padding
                    //COMread(temp, padding, 1); // y+= 1;
                    y+=1;
                    x = 0;
                break;
                case 1: 
                    return; // end of bitmap, return
                break;
                case 2: // delta, make xy offset and continue //
                    x += nextChar();
                    y += nextChar();
                break;
                default: 
                {// Absolut mode, read next bytes(Absolute){}
                    char align = 0; 
                    if(c2 % 2 != 0) align = 1;

                    uint16_t c[c2];
                    for(int i = 0; i < c2; i++)
                    {
                        char color = nextChar();
                        lcdColor = rgbQTo565(palette[color]);
                        c[i] = lcdColor;
                    }
                    GUI_WriteLine((Coordinate){x,h-1 - y}, c2, c);

                    if(align)
                    {
                        nextChar();
                    }
                    x += c2;
                }
            }
        }else // normal number, encoded mode
        {
            lcdColor = rgbQTo565(palette[c2]);
            uint16_t c[c1];
            for(int i = 0; i < c1; i++)
            {
                c[i] = lcdColor;
            }
            GUI_WriteLine((Coordinate){x,h-1 - y}, c1, c);
            /*
            while(c1 > 0)
            {
                
                
                if(draw && x < LCD_WIDTH && (h-1 - y) < LCD_HEIGHT) {
                GUI_drawPoint((Coordinate){x,h-1 - y}, lcdColor, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP);
                }
                x++;
                c1--;
            }*/
            x += c1;
        }
    }
} 

void drawImage8(int w, int h,int biClrUsed)
{
    RGBQUAD palette[256];
    int result = COMread((char *)palette, sizeof(RGBQUAD), biClrUsed == 0 ? 256 : biClrUsed);
    ERR_HANDLER(result == NOK, "falsche palette");
    uint16_t lcdColor = GREEN;
    /*
        1.calculate bytes w/padding 
        2.calculate bytes wo/padding
        3.padding = (w/wo) / byteProPixel
    */
    int padding = 0;
    char* temp;
    if(w % 4 != 0)
    {    
        int wP = ((w  + 31) / 32) * 4; // formula, gegeben - 1 byte pro pixel
        padding = (wP - w); // padding bytes per 1 pixel
        temp = malloc(padding);
    }
    lcdPrintInt(padding);
    for(int i = 0; i < w * h; i++)
    {
        if(readButton()) 
        {
            lcdPrintS("next image");
            return;
        }
        int c = nextChar();
        //if(c == EOF) break;  // TODO
        lcdColor = rgbQTo565(palette[c]);
        int x = i % w;
        int y = h-1 - i / w;
        if(x >= LCD_WIDTH  || y >= LCD_HEIGHT) continue;
        GUI_drawPoint((Coordinate){x,y}, lcdColor, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP);
        if(padding > 0 && i % w == 0 && i > 0)
        {
            COMread(temp, padding, 1);
        }
    }
    lcdPrintS("abc");
    free(temp);
}

void drawImage8Lines(int w, int h,int biClrUsed)
{
    RGBQUAD palette[256];
    int result = COMread((char *)palette, sizeof(RGBQUAD), biClrUsed == 0 ? 256 : biClrUsed);
    ERR_HANDLER(result == NOK, "falsche palette");

    uint16_t lcdColor = GREEN;

    char indicies[w]; // TODO: 4000 pixels wird overflowen spaetestens bei deklar. von colors[w]
    int benutzteFarbenLength = w > LCD_WIDTH?LCD_WIDTH:w;
    uint16_t colors[benutzteFarbenLength];
    
    /*
        1.calculate bytes w/padding 
        2.calculate bytes wo/padding
        3.padding = (w/wo) / byteProPixel
    */
    int padding = 0;
    char* temp;
    if(w % 4 != 0)
    {    
        int wP = ((w + 31) / 32) * 4; // formula, gegeben - 1 byte pro pixel
        padding = (wP - w); // padding bytes per 1 pixel
        temp = malloc(padding);
    }
    lcdPrintInt(padding);
    for(int i = 0; i < h; i++) //jede Reihe
    {
        COMread(indicies, 1, w);
        int y = h-1 - i;

        if(y < LCD_HEIGHT) 
        {
            for(int i = 0; i < benutzteFarbenLength; i++)
            {
                colors[i] = rgbQTo565(palette[indicies[i]]);
            }
            GUI_WriteLine((Coordinate){0,y}, benutzteFarbenLength, colors);
        }

        if(padding > 0)
        {
            COMread(temp, padding, 1);
        }
    }
    lcdPrintS("abc");
    free(temp);
}

void drawImage24(uint32_t w, uint32_t h)
{
    RGBTRIPLE color;
    uint16_t lcdColor = GREEN;
    
    int padding = 0;
    char* temp;
    if((w * 3) % 4 != 0)
    {    
        int wP = (((w)*(24) + 31) / 32) * 4; // formula, gegeben - 3 bytes pro pixel
        int woP = w * 3; // 3byte * 8bit * w = w * pixel = w * rgb 
        padding = (wP - woP); // padding bytes per 1 pixel
        temp = malloc(padding);
    }
    for(int i = 0; i < w * h; i++)
    {
        if(readButton()) 
        {
            lcdPrintS("next image");
            return;
        }
        COMread((char *)&color, sizeof(RGBTRIPLE), 1);
        uint32_t x = i % w;
        uint32_t y = h - i / w - 1;
        if(x < LCD_WIDTH && y < LCD_HEIGHT) 
        {
            lcdColor = rgbTo565(color);

            GUI_drawPoint((Coordinate){x,y}, lcdColor, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP);

        }

        if(padding > 0 && (i + 1) % w == 0)
        {
            COMread(temp, padding, 1);
        }
    }
    free(temp);
}

void drawImage24Lines(uint32_t w, uint32_t h)
{
    //RGBTRIPLE* color = malloc(w * sizeof(RGBTRIPLE));
    static RGBTRIPLE bmpColors[LCD_WIDTH]; // static damit es in statischer memory allociert wird:
                                        // auf dem stack gibt es sonst zu wenig platz!
    
    uint32_t padding = 0;
    char* temp;
    if((w * 3) % 4 != 0)
    {    
        uint32_t wP = (((w)*(24) + 31) / 32) * 4; // formula, gegeben - 3 bytes pro pixel
        uint32_t woP = w * 3; // 3byte * 8bit * w = w * pixel = w * rgb 
        padding = (wP - woP); // padding bytes per 1 pixel
        temp = malloc(padding);
    }
    //uint16_t *lcdColors = malloc(w * sizeof(uint16_t));
    //int benutzteFarbenLength =  w > LCD_WIDTH ? LCD_WIDTH : w;
    static uint16_t lcdColors[LCD_WIDTH] = {0};// static damit es in statischer memory allociert wird:
                                        // auf dem stack gibt es sonst zu wenig platz!

    for(uint32_t i = 0; i < h; i++)
    {
        uint32_t y =  h-1 - i;//
        if(w > LCD_WIDTH) // wenn es mehr als eine breite geben soll
        {
            COMread((char *)bmpColors, sizeof(RGBTRIPLE), LCD_WIDTH); // eine breite lesen
            for(uint32_t k = 0; k < LCD_WIDTH; k++) // farben vorbereiten
            {
                lcdColors[k] = rgbTo565(bmpColors[k]);
            }
            int temp = w;
            while((temp -= LCD_WIDTH) > LCD_WIDTH) // wenn es mehr als eine breite uebrig
            {
                COMread((char *)bmpColors, sizeof(RGBTRIPLE), LCD_WIDTH); // noch eine breite lesen
            }
            COMread((char *)bmpColors, sizeof(RGBTRIPLE), temp); // den rest auslesen
        }else // wenn es weniger/gleich einer breite gibt
        { 
            COMread((char *)bmpColors, sizeof(RGBTRIPLE), w); // alles lesen und direkt vorbereiten 
            for(uint32_t k = 0; k < LCD_WIDTH; k++)
            {
                lcdColors[k] = rgbTo565(bmpColors[k]);
            }
        }
        
        if(y < LCD_HEIGHT){
            GUI_WriteLine((Coordinate){0,y},LCD_WIDTH ,lcdColors);
        }

        if(padding > 0)
        {
            COMread(temp, padding, 1);
        }
    }
    free(temp);
    //free(color);
    //free(lcdColors);
}
/*
#define min(x,y) (x > y?) y : x
#define floor(x) (int) x
#define ceil(x) ((x - floor(x)) > 0) ? (floor(x) + 1) : (x)

void drawPixelsScaled(uint32_t w, uint32_t h)
{
    static uint16_t lcdColors[LCD_WIDTH];
    static RGBTRIPLE bmpColors[LCD_WIDTH * 5];

    uint16_t scale_x = LCD_WIDTH / w;
    uint16_t scale_y = LCD_HEIGHT / h;
    uint16_t scale = min(scale_y,scale_x); // # Damit keine Verzerrung auftritt
    uint16_t box_width = ceil(1/scale);
    uint16_t box_height = ceil(1/scale);
    //# Koordinaten im Bild
    for (int y = 0; y < 320; y++)
    {
        COMread((char*)bmpColors,sizeof(RGBTRIPLE),LCD_WIDTH * 5);
        
        for (int x = 0; x < 480; x++)
        {
            x_ = floor(x/scale_x);
            y_ = floor(y/scale_x);   
            x_end = min(x_ + box_width, LCD_WIDTH - 1); // # keine Bereichsüberschreitung
            y_end = min(y_ + box_height, LCD_HEIGHT - 1); //  # keine Bereichsüberschreitung
            //# Mittelwert der Pixel der Kachel (x_,y_) bis (x_end,y_end) bestimmen

        }
    }
    //# Gebe Farbwert an der Stelle (x,y) auf dem LCD Display aus

}*/