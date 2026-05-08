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

#include "token.h"
#include "scanner.h"
#include "display.h"
#include "reader.h"

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	initDisplay();

  // Begruessungstext	
	//printToEchoLine('1');
	
	Stack s = {0};
	stack_init(&s,16);
	
	while(1) {
		readToken(&s);
	}
}

// EOF
