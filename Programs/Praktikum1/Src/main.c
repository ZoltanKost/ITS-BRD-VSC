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


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	initDisplay();

  // Begruessungstext	
	printStdout("Hallo liebes TI-Labor (c-project)");
	
	
	while(1) {
		T_token = nextToken();
		Stack s = 
	}
}


// EOF
