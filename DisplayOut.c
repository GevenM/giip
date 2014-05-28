#include "DisplayOut.h"

enum e_operations c_operation = Idle;
enum e_operations nextOperation = Idle;

const char* convertedValue;
unsigned int value = 0;
unsigned char tempValue[5];

void DisplayOut(void){
	switch(c_operation){
	case Idle:
		// Load idle screen into screen buffer and draw to screen
		PrintIdle();

		// Poll the UI buttons to check if any button (that has functionality) is being pressed
		// When pressed, record the action to take and when the button is released, perform this action.
		// if multiple buttons are pressed, it uses the last one that is released.
		if (SecondButtonPressed()){
			SetLED1();
			nextOperation = MMBasal;

		} else {
			ResetLED1();
			if(c_operation != nextOperation){
				GrClearDisplay(&g_sContext); // Clears the LCD
				c_operation = nextOperation;
			}

		}

		break;

	case MMBasal:

		// Load MainMenu screen with Basal highlighted into screen buffer and draw to screen
		PrintMMBasal();

		// Poll the UI buttons to check if any button (that has functionality) is being pressed
		// When pressed, record the action to take and when the button is released, perform this action.
		// if multiple buttons are pressed, it uses the last one that is released.
		if (FirstButtonPressed()){
			SetLED1();
			nextOperation = Idle;
		} else if (DownButtonPressed()){
			SetLED1();
			nextOperation = MMBolus;
		} else if (SecondButtonPressed()){
			SetLED1();
			nextOperation = BasMenu;
		}  else if (UpButtonPressed()){
			SetLED1();
			nextOperation = MMShutDown;
		} else {
			ResetLED1();
			if(c_operation != nextOperation){
				if (nextOperation == MMBolus || nextOperation == MMShutDown){
					ClearMM();
				}
				else{
					GrClearDisplay(&g_sContext); // Clears the screen
				}
				c_operation = nextOperation;
			}
		}
		break;

	case BasMenu:
		if (f_basalIsActive || f_temporaryBasalIsActive){
			nextOperation = BasMenuActiveA;

		} else {
			nextOperation = BasMenuInactiveA;
		}
		c_operation = nextOperation;
		break;

	case BasMenuActiveA:
		PrintBasMenuActiveA();

		// Poll the UI buttons to check if any button (that has functionality) is being pressed
		// When pressed, record the action to take and when the button is released, perform this action.
		// if multiple buttons are pressed, it uses the last one that is released.
		if (FirstButtonPressed()){
			SetLED1();
			nextOperation = MMBasal;
		} else if (DownButtonPressed()){
			SetLED1();
			nextOperation = BasMenuActiveB;
		} else if (SecondButtonPressed()){
			SetLED1();
			nextOperation = BasMenu;
		} else {
			ResetLED1();
			if(c_operation != nextOperation){
				if (nextOperation == BasMenuActiveB){
					ClearBasMenuActive();
				}
				else{
					GrClearDisplay(&g_sContext); // Clears the screen
				}
				c_operation = nextOperation;
			}
		}
		break;

	case BasMenuActiveB:
			PrintBasMenuActiveB();

			// Poll the UI buttons to check if any button (that has functionality) is being pressed
			// When pressed, record the action to take and when the button is released, perform this action.
			// if multiple buttons are pressed, it uses the last one that is released.
			if (FirstButtonPressed()){
				SetLED1();
				nextOperation = MMBasal;
			} else if (UpButtonPressed()){
				SetLED1();
				nextOperation = BasMenuActiveA;
			//} else if (SecondButtonPressed()){
			//	SetLED1();
			//	nextOperation = BasMenu;
			} else {
				ResetLED1();
				if(c_operation != nextOperation){
					if (nextOperation == BasMenuActiveA){
						ClearBasMenuActive();
					}
					else{
						GrClearDisplay(&g_sContext); // Clears the screen
					}
					c_operation = nextOperation;
				}
			}
			break;

	case BasMenuInactiveA:
		PrintBasMenuInactiveA();

		// Poll the UI buttons to check if any button (that has functionality) is being pressed
		// When pressed, record the action to take and when the button is released, perform this action.
		// if multiple buttons are pressed, it uses the last one that is released.
		if (FirstButtonPressed()){
			SetLED1();
			nextOperation = MMBasal;
		} else if (DownButtonPressed()){
			SetLED1();
			nextOperation = BasMenuInactiveB;
		} else {
			ResetLED1();
			if(c_operation != nextOperation){
				if (nextOperation == BasMenuInactiveB){
					ClearBasMenuInactive();
				}
				else{
					GrClearDisplay(&g_sContext); // Clears the screen
				}
				c_operation = nextOperation;
			}
		}
		break;
	case BasMenuInactiveB:
		PrintBasMenuInactiveB();

		// Poll the UI buttons to check if any button (that has functionality) is being pressed
		// When pressed, record the action to take and when the button is released, perform this action.
		// if multiple buttons are pressed, it uses the last one that is released.
		if (FirstButtonPressed()){
			SetLED1();
			nextOperation = MMBasal;
		} else if (UpButtonPressed()){
			SetLED1();
			nextOperation = BasMenuInactiveA;
		} else {
			ResetLED1();
			if(c_operation != nextOperation){
				if (nextOperation == BasMenuInactiveA){
					ClearBasMenuInactive();
				}
				else{
					GrClearDisplay(&g_sContext); // Clears the screen
				}
				c_operation = nextOperation;
			}
		}
		break;

	case MMBolus:

		// Load MainMenu screen with Bolus highlighted into screen buffer and draw to screen
		PrintMMBolus();

		// Poll the UI buttons to check if any button (that has functionality) is being pressed
		// When pressed, record the action to take and when the button is released, perform this action.
		// if multiple buttons are pressed, it uses the last one that is released.
		if (FirstButtonPressed()){
			SetLED1();
			nextOperation = Idle;
		} else if (UpButtonPressed()) {
			SetLED1();
			nextOperation = MMBasal;
		} else if (DownButtonPressed()){
			SetLED1();
			nextOperation = MMSchedule;
		} else if (SecondButtonPressed()){
			SetLED1();
			//nextOperation = BolMenu;
		} else {
			ResetLED1();
			if(c_operation != nextOperation){
				if (nextOperation == MMBasal || nextOperation == MMSchedule){
					ClearMM();
				} else {
					GrClearDisplay(&g_sContext); // Clears the screen
				}
				c_operation = nextOperation;
			}
		}

		break;
	//case BolMenu:
		//if
	case MMSchedule:

		// Load MainMenu screen with Schedule highlighted into screen buffer and draw to screen
		PrintMMSchedule();

		// Poll the UI buttons to check if any button (that has functionality) is being pressed
		// When pressed, record the action to take and when the button is released, perform this action.
		// if multiple buttons are pressed, it uses the last one that is released.
		if (FirstButtonPressed()){
			SetLED1();
			nextOperation = Idle;
		} else if (UpButtonPressed()) {
			SetLED1();
			nextOperation = MMBolus;
		} else if (DownButtonPressed()){
			SetLED1();
			nextOperation = MMSettings;
		} else {
			ResetLED1();
			if(c_operation != nextOperation){
				c_operation = nextOperation;
				if (nextOperation == MMBolus || nextOperation == MMSettings){
					ClearMM();
				} else {
					GrClearDisplay(&g_sContext); // Clears the screen
				}
				c_operation = nextOperation;
			}
		}

		break;

	case MMSettings:

		// Load MainMenu screen with Schedule highlighted into screen buffer and draw to screen
		PrintMMSettings();

		// Poll the UI buttons to check if any button (that has functionality) is being pressed
		// When pressed, record the action to take and when the button is released, perform this action.
		// if multiple buttons are pressed, it uses the last one that is released.
		if (FirstButtonPressed()){
			SetLED1();
			nextOperation = Idle;
		} else if (UpButtonPressed()) {
			SetLED1();
			nextOperation = MMSchedule;
		} else if (DownButtonPressed()){
			SetLED1();
			nextOperation = MMShutDown;
		} else {
			ResetLED1();
			if(c_operation != nextOperation){
				c_operation = nextOperation;
				if (nextOperation == MMSchedule || nextOperation == MMShutDown){
					ClearMM();
				} else {
					GrClearDisplay(&g_sContext); // Clears the screen
				}
				c_operation = nextOperation;
			}
		}

		break;

	case MMShutDown:

		// Load MainMenu screen with Schedule highlighted into screen buffer and draw to screen
		PrintMMShutDown();

		// Poll the UI buttons to check if any button (that has functionality) is being pressed
		// When pressed, record the action to take and when the button is released, perform this action.
		// if multiple buttons are pressed, it uses the last one that is released.
		if (FirstButtonPressed()){
			SetLED1();
			nextOperation = Idle;
		} else if (UpButtonPressed()) {
			SetLED1();
			nextOperation = MMSettings;
		} else if (DownButtonPressed()) {
			SetLED1();
			nextOperation = MMBasal;
		} else {
			ResetLED1();
			if(c_operation != nextOperation){
				c_operation = nextOperation;
				if (nextOperation == MMSettings || nextOperation == MMBasal){
					ClearMM();
				} else {
					GrClearDisplay(&g_sContext); // Clears the screen
				}
				c_operation = nextOperation;
			}
		}

		break;
	default:
		// All possibilities should be covered by the previous cases. Report an error if default executes.
		GrClearDisplay(&g_sContext); // Clears the screen
		GrStringDrawCentered(&g_sContext, "Error", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
		GrFlush(&g_sContext);
	}
}

void PrintIdle(){
	// Print basal status
	if (f_temporaryBasalIsActive){
		GrStringDrawCentered(&g_sContext, "Basal: " , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
	} else if(f_basalIsActive){
		GrStringDrawCentered(&g_sContext, "Temp Basal: " , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
	} else {
		GrStringDrawCentered(&g_sContext, "No Basal" , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
	}

	// Print bolus status
	if(f_bolusInProgress)
		GrStringDrawCentered(&g_sContext, "Bolus: " , AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
	else {
		GrStringDrawCentered(&g_sContext, "No Bolus" , AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
	}
	LoadBanner();
	// Load bottom buttons
	LoadLeftButton("");
	LoadMiddleButton("MENU");
	LoadRightButton("");
	GrFlush(&g_sContext);
}

void SetLED1(){
	P1OUT |= BIT0; // Set LED on P1.0
}
void ResetLED1(){
	P1OUT &= ~BIT0; // reset P1.0
}

void PrintMMBasal(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");


	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Basal Menu", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrStringDraw(&g_sContext, "Bolus Menu", AUTO_STRING_LENGTH, 5, 31, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Schedule", AUTO_STRING_LENGTH, 5, 44, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Settings", AUTO_STRING_LENGTH, 5, 57, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Shut Down", AUTO_STRING_LENGTH, 5, 70, TRANSPARENT_TEXT);
	GrFlush(&g_sContext);
}

void ClearMM(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");


	//GrContextForegroundSet(&g_sContext, ClrWhite);
	//GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Basal Menu", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	//GrContextForegroundSet(&g_sContext, ClrBlack);
	//GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrStringDraw(&g_sContext, "Bolus Menu", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Schedule", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Settings", AUTO_STRING_LENGTH, 5, 57, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Shut Down", AUTO_STRING_LENGTH, 5, 70, OPAQUE_TEXT);
	GrFlush(&g_sContext);
}

void PrintMMSchedule(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");



	GrStringDraw(&g_sContext, "Basal Menu", AUTO_STRING_LENGTH, 5, 18, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Bolus Menu", AUTO_STRING_LENGTH, 5, 31, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Schedule", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrStringDraw(&g_sContext, "Settings", AUTO_STRING_LENGTH, 5, 57, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Shut Down", AUTO_STRING_LENGTH, 5, 70, TRANSPARENT_TEXT);
	GrFlush(&g_sContext);
}

void PrintBasMenuActiveA(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Deactivate Basal", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 31, TRANSPARENT_TEXT);

	GrFlush(&g_sContext);
}
void PrintBasMenuActiveB(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");

	GrStringDraw(&g_sContext, "Deactivate Basal", AUTO_STRING_LENGTH, 5, 18, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

	GrFlush(&g_sContext);
}

void PrintBasMenuInactiveA(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Start Basal", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 31, TRANSPARENT_TEXT);
	GrFlush(&g_sContext);
}

void PrintBasMenuInactiveB(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");

	GrStringDraw(&g_sContext, "Start Basal", AUTO_STRING_LENGTH, 5, 18, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrFlush(&g_sContext);
}

void ClearBasMenuActive(){
	GrStringDraw(&g_sContext, "Deactivate Basal", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
}

void ClearBasMenuInactive(){
	GrStringDraw(&g_sContext, "Start Basal", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
}

void PrintMMSettings(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");

	GrStringDraw(&g_sContext, "Basal Menu", AUTO_STRING_LENGTH, 5, 18, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Bolus Menu", AUTO_STRING_LENGTH, 5, 31, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Schedule", AUTO_STRING_LENGTH, 5, 44, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Settings", AUTO_STRING_LENGTH, 5, 57, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrStringDraw(&g_sContext, "Shut Down", AUTO_STRING_LENGTH, 5, 70, TRANSPARENT_TEXT);
	GrFlush(&g_sContext);
}

void PrintMMShutDown(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");

	GrStringDraw(&g_sContext, "Basal Menu", AUTO_STRING_LENGTH, 5, 18, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Bolus Menu", AUTO_STRING_LENGTH, 5, 31, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Schedule", AUTO_STRING_LENGTH, 5, 44, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Settings", AUTO_STRING_LENGTH, 5, 57, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Shut Down", AUTO_STRING_LENGTH, 5, 70, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrFlush(&g_sContext);
}

void PrintMMBolus(){
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");



	GrStringDraw(&g_sContext, "Basal Menu", AUTO_STRING_LENGTH, 5, 18, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDraw(&g_sContext, "Bolus Menu", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrStringDraw(&g_sContext, "Schedule", AUTO_STRING_LENGTH, 5, 44, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Settings", AUTO_STRING_LENGTH, 5, 57, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Shut Down", AUTO_STRING_LENGTH, 5, 70, TRANSPARENT_TEXT);
	GrFlush(&g_sContext);
}
void LoadLeftButton(const char * text){
	GrRectFill(&g_sContext, &myRectangleBotLeft);

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDrawCentered(&g_sContext, text, AUTO_STRING_LENGTH, 14, 88, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
}

void LoadMiddleButton(const char * text){
	GrRectFill(&g_sContext, &myRectangleBotMid);

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDrawCentered(&g_sContext, text, AUTO_STRING_LENGTH, 49, 88, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
}

void LoadRightButton(const char * text){
	GrRectFill(&g_sContext, &myRectangleBotRight);

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDrawCentered(&g_sContext, text, AUTO_STRING_LENGTH, 72, 88, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
}

void LoadBanner(void){
	// Draw top banner
	GrRectFill(&g_sContext, &myRectangleTopBan);
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDrawCentered(&g_sContext, "hh:mm", AUTO_STRING_LENGTH, 80 , 7, TRANSPARENT_TEXT);
	GrStringDrawCentered(&g_sContext, "bat%", AUTO_STRING_LENGTH, 15, 7, TRANSPARENT_TEXT);
	GrStringDrawCentered(&g_sContext, "res%", AUTO_STRING_LENGTH, 48, 7, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
}

const char * convertToChar(unsigned int x){
	unsigned char count = 0;
	while(x>=10000){ // x may be 0..65535 here
		count++;
		x-=10000;
	}
	count += 0x30;
	tempValue[0] = count;
	count = 0;
	while(x>=1000){ // at this point, x is 9999 at max
		count++;
		x-=1000;
	}
	count += 0x30;
	tempValue[1] = count;
	count=0;
	while(x>=100){  // x is no more than 999 now
		count++;
		x-=100;
	}
	count += 0x30;
	tempValue[2] = count;
	count=0;

	while(x>=10){ // and here, x cannot be more than 99
		count++;
		x-=10;
	}
	count += 0x30;
	tempValue[3] = count;
	tempValue[4] = x + 0x30;
	return &tempValue;
}

bool UpButtonPressed(){
	if (BIT0 & P4IN){
		return false;
	} else {
		return true;
	}
}

bool DownButtonPressed(){
	if (BIT2 & P8IN){
		return false;
	} else {
		return true;
	}
}

bool LeftButtonPressed(){
	if (BIT3 & P4IN){
		return false;
	} else {
		return true;
	}
}

bool RightButtonPressed(){
	if (BIT7 & P3IN){
		return false;
	} else {
		return true;
	}
}

bool FirstButtonPressed(){
	if (BIT4 & P1IN){
		return false;
	} else {
		return true;
	}
}

bool SecondButtonPressed(){
	if (BIT3 & P1IN){
		return false;
	} else {
		return true;
	}
}

bool ThirdButtonPressed(){
	if (BIT2 & P1IN){
		return false;
	} else {
		return true;
	}
}
