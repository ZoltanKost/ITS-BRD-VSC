/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"

#include <stdio.h>

#include "input.h"
#include "state.h"
#include "update.h"
#include "zeit.h"
#include "output.h"
#include "error.h"
#include "pinoutput.h"


void lcdPrintlnInt(int zahl){
	 char txt[12];
	 sprintf( txt, "%d", zahl);
	 lcdPrintlnS(txt);
}

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	//TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  // Begruessungstext	
	lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	initTime();
	/*
		1. pins als input initialisieren.
		PORT->PIN |= PORT_READ_MASK
	*/
	// Test in Endlosschleife
	while(1)
	{
		// eingabe. 
		readValues();
		// update zustand. zeitmessung
		error = updateState();

		while(error != 0) 
		{
			readButtonInput();
			if(reset_button == 0)
			{
				error = 0;
				resetState();
				resetOutputTime();
				break;
			}
		}
		// berechnen neue werte bas. auf zustand
		updateValues();
		//ausgabe
		error = output();
		
		pinOutput();

		while(error != 0) 
		{
			readButtonInput();
			if(reset_button == 0)
			{
				error = 0;
				resetState();
				resetOutputTime();
				break;
			}
		}
		//HAL_Delay(10000);
	}
	return 0;
}

// EOF
