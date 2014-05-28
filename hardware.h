

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


