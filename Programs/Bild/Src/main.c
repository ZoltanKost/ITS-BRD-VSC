/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "input.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include <stdio.h>

#include "readBMP.h"


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	//TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  // Begruessungstext	
	
	
	initInput(); //Aufbau der Verbindung
	lcdPrintlnS("Input connected");
	// Test in Endlosschleife
	while(1) {
		//warten auf Taste
		openNextFile(); //start der Uebertragunng
		//lcdGotoXY(1, 1 );
		lcdPrintlnS("naechstes Bild");

		//int c = nextChar(); // naechste Byte

		if (processBMP())
		{
			
		};
	}
}

// EOF
