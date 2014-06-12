#include "msp430.h"

// Specify the input pins for push buttons
#define i_leftSelBtn 	!(P1IN & BIT4) // P1.4
#define i_middleSelBtn 	!(P1IN & BIT3) // P1.3
#define i_rightSelBtn 	!(P1IN & BIT2) // P1.2
#define i_leftDirBtn 	!(P4IN & BIT3) // P4.3
#define i_rightDirBtn 	!(P3IN & BIT7) // P3.7
#define i_upDirBtn 		!(P4IN & BIT0) // P4.0
#define i_downDirBtn 	!(P8IN & BIT2) // P8.2


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
