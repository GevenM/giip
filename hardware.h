#ifndef HARDWARE_H
#define HARDWARE_H

#include "msp430.h"

#define LEFT_SEL_BTN_PORT		GPIO_PORT_P1
#define LEFT_SEL_BTN_PIN  		BIT4
#define LEFT_SEL_BTN_INPUT 		P1IN

#define MIDDLE_SEL_BTN_PORT 	GPIO_PORT_P1
#define MIDDLE_SEL_BTN_PIN  	BIT3
#define MIDDLE_SEL_BTN_INPUT 	P1IN

#define RIGHT_SEL_BTN_PORT 		GPIO_PORT_P1
#define RIGHT_SEL_BTN_PIN 		BIT2
#define RIGHT_SEL_BTN_INPUT 	P1IN

#define LEFT_DIR_BTN_PORT 		GPIO_PORT_P4
#define LEFT_DIR_BTN_PIN 		BIT3
#define LEFT_DIR_BTN_INPUT 		P4IN

#define RIGHT_DIR_BTN_PORT 		GPIO_PORT_P3
#define RIGHT_DIR_BTN_PIN 		BIT7
#define RIGHT_DIR_BTN_INPUT 	P3IN

#define UP_DIR_BTN_PORT 		GPIO_PORT_P4
#define UP_DIR_BTN_PIN 			BIT0
#define UP_DIR_BTN_INPUT 		P4IN

#define DOWN_DIR_BTN_PORT 		GPIO_PORT_P8
#define DOWN_DIR_BTN_PIN 		BIT2
#define DOWN_DIR_BTN_INPUT 		P8IN

// Specify the input pins for push buttons
#define i_leftSelBtn 	!( LEFT_SEL_BTN_INPUT 	& LEFT_SEL_BTN_PIN )
#define i_middleSelBtn 	!( MIDDLE_SEL_BTN_INPUT & MIDDLE_SEL_BTN_PIN )
#define i_rightSelBtn 	!( RIGHT_SEL_BTN_INPUT 	& RIGHT_SEL_BTN_PIN )
#define i_leftDirBtn 	!( LEFT_DIR_BTN_INPUT 	& LEFT_DIR_BTN_PIN )
#define i_rightDirBtn 	!( RIGHT_DIR_BTN_INPUT	& RIGHT_DIR_BTN_PIN )
#define i_upDirBtn 		!( UP_DIR_BTN_INPUT 	& UP_DIR_BTN_PIN )
#define i_downDirBtn 	!( DOWN_DIR_BTN_INPUT 	& DOWN_DIR_BTN_PIN )


#define GPIO_ALL	GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3| \
					GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7


#define MSP430F5529LP      // F5529 LaunchPad (MSP-EXP430F5529LP)

#ifdef MSP430F5529LP
#define BUTTON1_PORT	GPIO_PORT_P2
#define BUTTON1_PIN		GPIO_PIN1
#define BUTTON1_VECTOR	PORT2_VECTOR

#define BUTTON2_PORT	GPIO_PORT_P1
#define BUTTON2_PIN		GPIO_PIN1
#define BUTTON2_VECTOR	PORT1_VECTOR
#endif

void clockInit(unsigned long mclkFreq);
void boardInit();
void timerInit();
void ledInit();
void buttonInit();


extern bool i_1_leftSelBtn;
extern bool i_1_middleSelBtn;
extern bool i_1_rightSelBtn;
extern bool i_1_leftDirBtn;
extern bool i_1_rightDirBtn;
extern bool i_1_upDirBtn;
extern bool i_1_downDirBtn;

extern bool I_leftSelBtn;
extern bool I_middleSelBtn;
extern bool I_rightSelBtn;
extern bool I_rightDirBtn;
extern bool I_leftDirBtn;
extern bool I_upDirBtn;
extern bool I_downDirBtn;

#endif
