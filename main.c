/* --COPYRIGHT--,BSD
 * Copyright (c) 2013, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/


// Basic MSP430 and driverLib #includes
#include "msp430.h"
#include "driverlib/MSP430F5xx_6xx/wdt_a.h"
#include "driverlib/MSP430F5xx_6xx/ucs.h"
#include "driverlib/MSP430F5xx_6xx/pmm.h"
#include "driverlib/MSP430F5xx_6xx/sfr.h"


#include "inc/hw_memmap.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include "images/images.h"
#include "driverlib.h"
#include "stdint.h"

#include "hardware.h" // File that contains information regarding hardware and its initializations

#include "DisplayOut.h"


void Delay(void);


//typedef int bool;
//#define true 1
//#define false 0

bool f_basalIsActive = false;
bool f_temporaryBasalIsActive = false;
bool f_bolusInProgress = false;


tContext g_sContext;
tRectangle myRectangleBotMid = { 33, 82, 63, 95};
tRectangle myRectangleBotRight = { 66, 82, 95, 95};
tRectangle myRectangleBotLeft = { 0, 82, 30, 95};
tRectangle myRectangleTopBan = { 0, 0, 95, 13};

tRectangle g_sRect;

uint8_t g_delayCounter = 0;

void main(void)
{
    // Stop WDT
    WDT_A_hold(WDT_A_BASE);

    // Basic GPIO initialization
    // initPorts();           // Config all the GPIOS for low-power (output low)
    //initButtons();         // Config the GPIOS for the buttons
    boardInit();
    timerInit();
    ledInit();
    buttonInit();

    clockInit(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz

    // Set up the LCD
    Sharp96x96_LCDInit();



    GrContextInit(&g_sContext, &g_sharp96x96LCD);
  	GrContextForegroundSet(&g_sContext, ClrBlack);
  	GrContextBackgroundSet(&g_sContext, ClrWhite);
  	GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
  	GrClearDisplay(&g_sContext);
  	GrFlush(&g_sContext);



	while(1){



		DisplayOut();
		/*// Intro Screen
		GrStringDrawCentered(&g_sContext,
							 "How to use",
							 AUTO_STRING_LENGTH,
							 48,
							 15,
							 TRANSPARENT_TEXT);
		GrStringDrawCentered(&g_sContext,
							 "the MSP430",
							 AUTO_STRING_LENGTH,
							 48,
							 35,
							 TRANSPARENT_TEXT);
		GrStringDraw(&g_sContext,
					 "Graphics Library",
					 AUTO_STRING_LENGTH,
					 1,
					 51,
					 TRANSPARENT_TEXT);
		GrStringDrawCentered(&g_sContext,
							 "Primitives",
							 AUTO_STRING_LENGTH,
							 48,
							 75,
							 TRANSPARENT_TEXT);

		GrFlush(&g_sContext);
		Delay();
		GrClearDisplay(&g_sContext);

		// Draw pixels and lines on the display
		GrStringDrawCentered(&g_sContext,
							 "Draw Pixels",
							 AUTO_STRING_LENGTH,
							 48,
							 5,
							 TRANSPARENT_TEXT);
		GrStringDrawCentered(&g_sContext,
							 "& Lines",
							 AUTO_STRING_LENGTH,
							 48,
							 15,
							 TRANSPARENT_TEXT);
		GrPixelDraw(&g_sContext, 30, 30);
		GrPixelDraw(&g_sContext, 30, 32);
		GrPixelDraw(&g_sContext, 32, 32);
		GrPixelDraw(&g_sContext, 32, 30);
		GrLineDraw(&g_sContext, 35, 35, 90, 90);
		GrLineDraw(&g_sContext, 5, 80, 80, 20);
		GrLineDraw(&g_sContext,
				   0,
				   GrContextDpyHeightGet(&g_sContext) - 1,
				   GrContextDpyWidthGet(&g_sContext) - 1,
				   GrContextDpyHeightGet(&g_sContext) - 1);
		GrFlush(&g_sContext);
		Delay();
		GrClearDisplay(&g_sContext);

		// Draw circles on the display
		GrStringDraw(&g_sContext,
					 "Draw Circles",
					 AUTO_STRING_LENGTH,
					 10,
					 5,
					 TRANSPARENT_TEXT);
		GrCircleDraw(&g_sContext,
					 30,
					 70,
					 20);
		GrCircleFill(&g_sContext,
					 60,
					 50,
					 30);
		GrFlush(&g_sContext);
		Delay();
		GrClearDisplay(&g_sContext);

		// Draw rectangles on the display
		GrStringDrawCentered(&g_sContext,
							 "Draw Rectangles",
							 AUTO_STRING_LENGTH,
							 48,
							 5,
							 TRANSPARENT_TEXT);
		GrRectDraw(&g_sContext, &myRectangle1);
		GrRectFill(&g_sContext, &myRectangle2);
		// Text below won't be visible on screen due to transparency
		// (foreground colors match)
		GrStringDrawCentered(&g_sContext,
							 "Normal Text",
							 AUTO_STRING_LENGTH,
							 50,
							 50,
							 TRANSPARENT_TEXT);
		// Text below draws foreground and background for opacity
		GrStringDrawCentered(&g_sContext,
							 "Opaque Text",
							 AUTO_STRING_LENGTH,
							 50,
							 65,
							 OPAQUE_TEXT);
		GrContextForegroundSet(&g_sContext, ClrWhite);
		GrContextBackgroundSet(&g_sContext, ClrBlack);
		GrStringDrawCentered(&g_sContext,
							 "Invert Text",
							 AUTO_STRING_LENGTH,
							 50,
							 80,
							 TRANSPARENT_TEXT);
		GrFlush(&g_sContext);
		Delay();

		// Invert the foreground and background colors
		GrContextForegroundSet(&g_sContext, ClrBlack);
		GrContextBackgroundSet(&g_sContext, ClrWhite);
		GrRectFill(&g_sContext, &myRectangle3);
		GrContextForegroundSet(&g_sContext, ClrWhite);
		GrContextBackgroundSet(&g_sContext, ClrBlack);
		GrStringDrawCentered(&g_sContext,
							 "Invert Colors",
							 AUTO_STRING_LENGTH,
							 48,
							 5,
							 TRANSPARENT_TEXT);
		GrRectDraw(&g_sContext, &myRectangle1);
		GrRectFill(&g_sContext, &myRectangle2);
		// Text below won't be visible on screen due to
		// transparency (foreground colors match)
		GrStringDrawCentered(&g_sContext,
							 "Normal Text",
							 AUTO_STRING_LENGTH,
							 50,
							 50,
							 TRANSPARENT_TEXT);
		// Text below draws foreground and background for opacity
		GrStringDrawCentered(&g_sContext,
							 "Opaque Text",
							 AUTO_STRING_LENGTH,
							 50,
							 65,
							 OPAQUE_TEXT);
		// Text below draws with inverted foreground color to become visible
		GrContextForegroundSet(&g_sContext, ClrBlack);
		GrContextBackgroundSet(&g_sContext, ClrWhite);
		GrStringDrawCentered(&g_sContext,
							 "Invert Text",
							 AUTO_STRING_LENGTH,
							 50,
							 80,
							 TRANSPARENT_TEXT);
		GrFlush(&g_sContext);
		Delay();
		GrContextForegroundSet(&g_sContext, ClrBlack);
		GrContextBackgroundSet(&g_sContext, ClrWhite);
		GrClearDisplay(&g_sContext);

		// Draw Images on the display
		GrImageDraw(&g_sContext, &LPRocket_96x37_1BPP_UNCOMP, 3, 28);
		GrFlush(&g_sContext);
		Delay();
		GrClearDisplay(&g_sContext);
		GrImageDraw(&g_sContext, &TI_Logo_69x64_1BPP_UNCOMP, 15, 15);
		GrFlush(&g_sContext);
		Delay();
		GrClearDisplay(&g_sContext);*/

		//__bis_SR_register(LPM0_bits+GIE); //enter low power mode 0 with interrupts
	}
}



void Delay(void){
	__delay_cycles(SYSTEM_CLOCK_SPEED*4);
}





