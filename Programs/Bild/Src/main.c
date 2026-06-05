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

		openNextFile(); //start der Uebertragunng

		lcdPrintlnS("taste druecken fuer naechstes Bild");

		//warten auf Taste
		while(!readButton()) {}

		lcdPrintlnS("naechstes Bild");

		if (processBMP())
		{
			
		};
	}
}

// EOF
