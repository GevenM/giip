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

 //*****************************************************************************
//
// Sharp96x96.h - Prototypes for the Sharp96x96 LCD display driver
//
//*****************************************************************************


#ifndef __SHARPLCD_H__
#define __SHARPLCD_H__

//*****************************************************************************
//
// User Configuration for the LCD Driver
//
//*****************************************************************************
// LCD Screen Dimensions
#define LCD_VERTICAL_MAX    96
#define LCD_HORIZONTAL_MAX  96


// SYSTEM_CLOCK_SPEED (in Hz) allows to properly closeout SPI communication
#define SYSTEM_CLOCK_SPEED      8000000

// Define LCD Screen Orientation Here
#define LANDSCAPE

//Maximum Colors in an image color palette
#define MAX_PALETTE_COLORS  2

#define SHARP_SEND_TOGGLE_VCOM_COMMAND		0x01
#define SHARP_SKIP_TOGGLE_VCOM_COMMAND 		0x00

#define SHARP_LCD_TRAILER_BYTE				0x00

#define SHARP_VCOM_TOGGLE_BIT 		   		0x40

#define SHARP_LCD_CMD_CHANGE_VCOM			0x00
#define SHARP_LCD_CMD_CLEAR_SCREEN			0x20
#define SHARP_LCD_CMD_WRITE_LINE			0x80



// Ports from MSP430 connected to LCD
#define LCD_MOSI_PORT                       GPIO_PORT_P3
#define LCD_SCLK_PORT                       GPIO_PORT_P3
#define LCD_DISP_PORT                       GPIO_PORT_P1
#define LCD_POWER_PORT                      GPIO_PORT_P6
#define LCD_SCS_PORT	                    GPIO_PORT_P6


// Pins from MSP430 connected to LCD
#define LCD_MOSI_PIN                        GPIO_PIN0
#define LCD_MOSI_PIN_FUNCTION               GPIO_SECONDARY_MODULE_FUNCTION
#define LCD_SCLK_PIN                        GPIO_PIN2
#define LCD_SCLK_PIN_FUNCTION               GPIO_SECONDARY_MODULE_FUNCTION
#define LCD_POWER_PIN                       GPIO_PIN5
#define LCD_DISP_PIN                        GPIO_PIN6
#define LCD_SCS_PIN                         GPIO_PIN6




//*****************************************************************************
//
// Macros for the Display Driver
//
//*****************************************************************************

//*****************************************************************************
//
// Translates a 24-bit RGB color to a display driver-specific color.
//
// \param c is the 24-bit RGB color.  The least-significant byte is the blue
// channel, the next byte is the green channel, and the third byte is the red
// channel.
//
// This macro translates a 24-bit RGB color into a value that can be written
// into the display's frame buffer in order to reproduce that color, or the
// closest possible approximation of that color. This particular driver
// requires the 8-8-8 24 bit RGB color to convert into 5-6-5 16 bit RGB Color
//
// \return Returns the display-driver specific color
//
//*****************************************************************************

#define DPYCOLORTRANSLATE(c)    (((c) & 0xff))


//*****************************************************************************
//
// Waits until the SPI communication with the LCD is finished a command to
// the LCD Driver
//
// \param None
//
// \return None
//*****************************************************************************

#define WaitUntilLcdWriteFinished()                \
        while  (USCI_B_SPI_isBusy(USCI_B0_BASE))



//*****************************************************************************
//
// Writes command or data to the LCD Driver
//
// \param ucCmdData is the 8 or 16 bit command to send to the LCD driver
// Uses the SET_LCD_DATA macro
//
// \return None
//
//*****************************************************************************

#define WriteCmdData(ucCmdData)                    	                 \
        do                                         	                 \
        {                                                            \
			while (!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,    \
                    USCI_B_SPI_TRANSMIT_INTERRUPT));                \
            	USCI_B_SPI_transmitData(USCI_B0_BASE,ucCmdData);   \
        }                                                            \
        while(0)



//*****************************************************************************
//
// Sets the cursor to coordinates X, Y. Increment from Left to Right
//
// \param X and Y are the LCD pixel coordinates to place the cursor
//
// This macro sets the cursor location, and sets auto incrementing
// of the X value from left to right on the LCD screen. This is used
// when drawing rows of pixels in images or lines. Upon exiting this 
// macro, the LCD should be ready to accept a stream of data
//
// Note that left to right is relative to the screen orientation, but
// HORIZ_DIRECTION is defined depending on screen orientation to always
// be left to right. (See Coordinate Space and Mapping above)
//
// \return None
//
//*****************************************************************************

#define SetCursorLtoR(X, Y) \
    __no_operation();

//*****************************************************************************
//
// Sets the cursor to coordinates X, Y. Increment from Top to Bottom
//
// \param X and Y are the LCD pixel coordinates to place the cursor
//
// This macro sets the cursor location, and sets auto incrementing
// of the Y value from top to bottom on the LCD screen. This is used
// when drawing rows of pixels in images or lines. Upon exiting this 
// macro, the LCD should be ready to accept a stream of data
//
// Note that top to bottom is relative to the screen orientation, but
// VERT_DIRECTION is defined depending on screen orientation to always
// be top to bottom. (See Coordinate Space and Mapping above)
//
// \return None
//
//*****************************************************************************

#define SetCursorTtoB(X, Y) \
    __no_operation();




//*****************************************************************************
//
// Clears CS line
//
// This macro allows to clear the Chip Select (CS) line
//
// \return None
//
//*****************************************************************************

#define ClearCS()  GPIO_setOutputLowOnPin(LCD_SCS_PORT, LCD_SCS_PIN)

//*****************************************************************************
//
// Set CS line
//
// This macro allows to set the Chip Select (CS) line
//
// \return None
//
//*****************************************************************************

#define SetCS()    GPIO_setOutputHighOnPin(LCD_SCS_PORT, LCD_SCS_PIN)



//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************
extern void Sharp96x96_LCDInit(void);
extern const tDisplay g_sharp96x96LCD;
extern void Sharp96x96_SendToggleVCOMCommand();
#endif // __SHARPLCD_H__
