#include "BMP_types.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "input.h"
#include "errorhandler.h"
#include <stdio.h>
#include "lcd.h"
#include "readBMP.h"
#include "LCD_GUI.h"
#include <stdlib.h>


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
        result = COMread((char *)palette, sizeof(RGBQUAD), infoheader.biClrUsed == 0 ? 255 : infoheader.biClrUsed);
        RETURN_NOK_ON_ERR(result == EOF, "kann nicht palette lesen");
        drawCompresedImage(palette,infoheader.biWidth);
    }else {
        if(infoheader.biBitCount == 24)
            drawImage24(infoheader.biWidth, infoheader.biHeight);
        else 
            drawImage8(infoheader.biWidth, infoheader.biHeight, infoheader.biClrUsed);
    }

    return EOK;
}

void drawCompresedImage(RGBQUAD* palette, uint32_t w)
{
    int c = 0; uint32_t i = 0;
    while(1)
    {
        c = nextChar();
        if(c == EOF)
        {
            break;
        }
        RGBQUAD color = palette[c]; 
        uint16_t lcdColor = rgbQTo565(color);
        uint32_t x = i % w;
        uint32_t y = i / w;
        if(x >= LCD_WIDTH || y >= LCD_HEIGHT) continue;
        GUI_drawPoint((Coordinate){x,y}, lcdColor, 0, 0);
        i++;
    }
}

void drawImage8(int w, int h,int biClrUsed)
{
    RGBQUAD palette[256];
    int result = COMread((char *)palette, sizeof(RGBQUAD), biClrUsed == 0 ? 255 : biClrUsed);
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
        int wP = (((w * 8) + 31) / 32) * 4; // formula, gegeben - 1 byte pro pixel
        padding = (wP - w); // padding bytes per 1 pixel
        temp = malloc(padding);
    }
    lcdPrintInt(padding);
    for(int i = 0; i < w * h; i++)
    {
        int c = nextChar();
        //if(c == EOF) break;  // TODO
        lcdColor = rgbQTo565(palette[c]);
        int x = i % w;
        int y = h - i / w - 1;
        if(x >= LCD_WIDTH || y >= LCD_HEIGHT) continue;
        GUI_drawPoint((Coordinate){x,y}, lcdColor, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP);
        if(padding > 0 && i % w == 0 && i > 0)
        {
            COMread(temp, padding, 1);
        }
    }
    lcdPrintS("abc");
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
        COMread((char *)&color, sizeof(RGBTRIPLE), 1);
        lcdColor = rgbTo565(color);
        int x = i % w;
        int y = h - i / w - 1;
        if(x >= LCD_WIDTH || y >= LCD_HEIGHT) continue;
        GUI_drawPoint((Coordinate){x,y}, lcdColor, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP);

        if(padding > 0 && i % w == 0 && i > 0)
        {
            COMread(temp, padding, 1);
        }
    }
}
