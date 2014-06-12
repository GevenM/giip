#include "DisplayOut.h"
#include <string.h>


tContext g_sContext;
tRectangle myRectangleBotMid = { 33, 82, 63, 95};
tRectangle myRectangleBotRight = { 66, 82, 95, 95};
tRectangle myRectangleBotLeft = { 0, 82, 30, 95};
tRectangle myRectangleTopBan = { 0, 0, 95, 13};
tRectangle myRectangleScreen = { 0, 14, 95, 81};

tRectangle g_sRect;
uint8_t g_delayCounter = 0;

y_basal p_inputProfile;
int segments[k_segDay] = {k_segDay, 0};


y_basalRate rates[k_segDay];
int rateIndex = 0;
int segmentIndex = 0;


int nameIndex = 0;
bool updateScreen = false;
bool basCreateStatus_NameEntered;

const char* convertedValue;
unsigned int value = 0;
unsigned char tempValue[5];
bool nextOption = false;
bool previousOption = false;

int f_numberOfBasProf = 0;

void PrintBasal_Manage();
void LoadBanner(void);
void LoadLeftButton(const char * text);
void LoadMiddleButton(const char * text);
void LoadRightButton(const char * text);
void LoadRates(y_basal *p_profile, int scollOffset);

void ClearBasNoActive();
void ClearBasBothActive();
void ClearBasTmpActive();
void ClearBasProfActive();
void ClearBasalMenu_Manage();
void ClearMainMenu();
void ClearCreateBasProf_Idle(y_basal *p_profile);

void PrintBolus_Manage();
void PrintBolus();
void PrintBolusAlreadyActive();
void PrintBolusCreateNotAllowed();
void PrintError();
void PrintNoBolusPreset();
void PrintNoRemind();
void PrintRemindCreateNotAllowed();
void PrintSchedule();
void PrintSettings();
void PrintIdle();
void PrintMainMenu();
void PrintBasNoActive();
void PrintBasBothActive();
void PrintBasTmpActive();
void PrintBasProfActive();
void PrintNoBasProf();
void PrintBasalMenu_Manage();
void PrintBasCreateNotAllowed();
void PrintCreateBasProf();
void PrintMessage(char outString[32]);
void PrintCreateBasProf_Idle(y_basal *p_profile);

void UpdateScreen();

int UnsignedInt_To_ASCII(unsigned int hex, char *ASCII);

void DisplayOut(void){
	switch(c_pwrStatus){
	case Standby:

		break;

	case POST:

		break;

	case Ready:
		UpdateScreen();
		//PrintScreen();
		break;

	case OffReq:

		break;

	case Error:

		break;

	default: break;


	}
}

void PrintScreen(){
	//ClearScreen();
	LoadBanner();
	switch(c_menuScreen){
	case None: PrintIdle(); break;
	case Main: PrintMainMenu(); break;

	case BasalBothActive: PrintBasBothActive(); break;
	case BasalProfActive: PrintBasProfActive(); break;
	case BasalTmpActive: PrintBasTmpActive(); break;
	case BasalNoActive: PrintBasNoActive(); break;

	case Bolus: PrintBolus(); break;
	case Schedule: PrintSchedule(); break;
	case Settings: PrintSettings(); break;

	case BolusAlreadyActive: PrintBolusAlreadyActive(); break;
	case Bolus_Manage: PrintBolus_Manage(); break;
	case RemindCreateNotAllowed: PrintRemindCreateNotAllowed(); break;
	case NoRemind: PrintNoRemind(); break;

	case NoBasProf: PrintNoBasProf(); break;
	case Basal_Manage: PrintBasal_Manage(); break;
	case BasCreateNotAllowed: PrintBasCreateNotAllowed(); break;
	case BolusCreateNotAllowed: PrintBolusCreateNotAllowed(); break;
	case NoBolusPreset: PrintNoBolusPreset(); break;

	case CreateBasProf_Idle:
		//ClearCreateBasProf_Idle(&p_inputProfile);
		PrintCreateBasProf_Idle(&p_inputProfile); break;

	case CreateBasProf_Confirm:
	case CreateBasProf_Invalid:
	case RemoveBasProf_Idle:PrintMessage("Remove Bas"); break;
	case RemoveBasProf_Confirm:
	case RemoveBasProf_Invalid:
	case StartBasProf_Idle:PrintMessage("Start Bas"); break;
	case StartBasProf_Confirm:
	case StartBasProf_Invalid:
	case StopBasProf_All:PrintMessage("Stop Bas"); break;
	case StartTmpBas_Idle:PrintMessage("Start Tmp"); break;
	case StartTmpBas_Confirm:
	case StartTmpBas_Invalid:
	case StopTmpBas_All:PrintMessage("Stop Tmp"); break;
	case CreateBolusPreset_Idle:PrintMessage("Create Bol"); break;
	case CreateBolusPreset_Confirm:
	case CreateBolusPreset_Invalid:
	case RemoveBolusPreset_Idle:PrintMessage("Remove Bol"); break;
	case RemoveBolusPreset_Confirm:
	case RemoveBolusPreset_Invalid:
	case StartBolus_Idle:PrintMessage("Start Bol"); break;
	case StartBolus_Calculator:
	case StartBolus_Preset:
	case StartBolus_Manual:
	case StartBolus_Confirm:
	case StartBolus_Invalid:
	case CreateReminder_Idle:PrintMessage("Create Remind"); break;
	case CreateReminder_Confirm:
	case CreateReminder_Invalid:
	case RemoveReminder_Idle:PrintMessage("Remove Remind"); break;
	case RemoveReminder_Confirm:



	default: PrintError(); break;
	}
}

void UpdateScreen(){
	switch (c_operation){
	case Idle:
		switch (c_menuScreen){
		case None:
			if (M_menuReq) {
				c_menuScreen = Main;
				f_menuChoice = Basal;
			}
			break;
		case Main:
			if (M_backReq){
				c_menuScreen = None;
			} else if (M_upReq){
				switch (f_menuChoice){
				case Basal: f_menuChoice = ShutDown;break;
				case Bolus: f_menuChoice = Basal;break;
				case Schedule: f_menuChoice = Bolus;break;
				case Settings: f_menuChoice = Schedule;break;
				case ShutDown: f_menuChoice = Settings;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Basal: f_menuChoice = Bolus;break;
				case Bolus: f_menuChoice = Schedule;break;
				case Schedule: f_menuChoice = Settings;break;
				case Settings: f_menuChoice = ShutDown;break;
				case ShutDown: f_menuChoice = Basal;break;
				default: break;
				}
			} else if (M_selReq){
				switch (f_menuChoice){
				case Basal:
					if(BasalIsActive() && TemporaryBasalIsActive()){
						c_menuScreen = BasalBothActive;
						f_menuChoice = Basal_StopProfile;
					} else if (BasalIsActive() && !TemporaryBasalIsActive()){
						c_menuScreen = BasalProfActive;
						f_menuChoice = Basal_StopProfile;
					} else if (!BasalIsActive() && TemporaryBasalIsActive()){
						c_menuScreen = BasalTmpActive;
						f_menuChoice = Basal_StartProfile;
					} else{
						c_menuScreen = BasalNoActive;
						f_menuChoice = Basal_StartProfile;
					}
					break;
				case Bolus:
					c_menuScreen = Bolus;
					f_menuChoice = Bolus_Start;
					break;
				case Schedule:
					c_menuScreen = Schedule;
					f_menuChoice = Schedule_Create;
					break;
				case Settings:
					c_menuScreen = Settings;
					//f_menuChoice = Settings_1;
					break;
				case ShutDown: break; // Shouldn't  need to do anything as this produces M_pwrReq.
				default: break;
				}
			}
			break;

		case Bolus:
			if (M_backReq){
				c_menuScreen = Main;
				f_menuChoice = Bolus;
			} else if (M_upReq){
				switch (f_menuChoice){
				case Bolus_Start: f_menuChoice = Bolus_Manage;break;
				case Bolus_Manage: f_menuChoice = Bolus_Start;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Bolus_Start: f_menuChoice = Bolus_Manage;break;
				case Bolus_Manage: f_menuChoice = Bolus_Start;break;
				default:  break;
				}
			} else if (M_selReq){
				switch (f_menuChoice){
				case Bolus_Start:
					if(BolusInProgress()){
						c_menuScreen = BolusAlreadyActive;
					} else{
						// should not happen as is indicates M_bolStartReq
					}
					break;
				case Bolus_Manage:
					c_menuScreen = Bolus_Manage;
					f_menuChoice = Bolus_Manage_Create;
					break;
				default: break;
				}
			}
			break;

		case Schedule:
			if (M_backReq){
				c_menuScreen = Main;
				f_menuChoice = Schedule;
			} else if (M_upReq){
				switch (f_menuChoice){
				case Schedule_Create: f_menuChoice = Schedule_Remove;break;
				case Schedule_Remove: f_menuChoice = Schedule_Create;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Schedule_Create: f_menuChoice = Schedule_Remove;break;
				case Schedule_Remove: f_menuChoice = Schedule_Create;break;
				default:  break;
				}
			} else if (M_selReq){
				switch (f_menuChoice){
				case Schedule_Create:
					if(ScheduleCreationAllowed()){
						// should not happen as it indicates M_ReminderCreateReq
					} else{
						c_menuScreen = RemindCreateNotAllowed;
					}
					break;
				case Schedule_Remove:
					if(ScheduleExists()){
						// should not happen as it indicates M_RemindRemoveReq
					} else{
						c_menuScreen = NoRemind;
					}
					break;
				default: break;
				}
			}
			break;

		case Settings: break; //?

		case BasalBothActive:
			if (M_backReq){
				c_menuScreen = Main;
				f_menuChoice = Basal;
			} else if (M_upReq){
				switch (f_menuChoice){
				case Basal_StopProfile: f_menuChoice = Basal_Manage;break;
				case Basal_StopTmp: f_menuChoice = Basal_StopProfile;break;
				case Basal_Manage: f_menuChoice = Basal_StopTmp;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Basal_StopProfile: f_menuChoice = Basal_StopTmp;break;
				case Basal_StopTmp: f_menuChoice = Basal_Manage;break;
				case Basal_Manage: f_menuChoice = Basal_StopProfile;break;
				default: break;
				}
			} else if (M_selReq){
				c_menuScreen = f_menuChoice;
				switch (f_menuChoice){
				case Basal_StopProfile: break;
				case Basal_StopTmp:break;
				case Basal_Manage: f_menuChoice = Basal_Manage_Create;break;
				default: break;
				}
			}
			break;
		case BasalNoActive:
			if (M_backReq){
				c_menuScreen = Main;
				f_menuChoice = Basal;
			} else if (M_upReq){
				switch (f_menuChoice){
				case Basal_StartProfile: f_menuChoice = Basal_Manage;break;
				case Basal_StartTmp: f_menuChoice = Basal_StartProfile;break;
				case Basal_Manage: f_menuChoice = Basal_StartTmp;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Basal_StartProfile: f_menuChoice = Basal_StartTmp;break;
				case Basal_StartTmp: f_menuChoice = Basal_Manage;break;
				case Basal_Manage: f_menuChoice = Basal_StartProfile;break;
				default: break;
				}
			} else if (M_selReq){
				c_menuScreen = f_menuChoice;
				switch (f_menuChoice){
				case Basal_StartProfile:
					if(BasalProfileExists()){
						; //?
					} else {
						c_menuScreen=NoBasProf;
					}
					break;
				case Basal_StartTmp: break;
				case Basal_Manage: f_menuChoice = Basal_Manage_Create;break;
				default: break;
				}
			}
			break;
		case BasalTmpActive:
			if (M_backReq){
				c_menuScreen = Main;
				f_menuChoice = Basal;
			} else if (M_upReq){
				switch (f_menuChoice){
				case Basal_StartProfile: f_menuChoice = Basal_Manage;break;
				case Basal_StopTmp: f_menuChoice = Basal_StartProfile;break;
				case Basal_Manage: f_menuChoice = Basal_StopTmp;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Basal_StartProfile: f_menuChoice = Basal_StopTmp;break;
				case Basal_StopTmp: f_menuChoice = Basal_Manage;break;
				case Basal_Manage: f_menuChoice = Basal_StartProfile;break;
				default: break;
				}
			} else if (M_selReq){
				c_menuScreen = f_menuChoice;
				switch (f_menuChoice){
				case Basal_StartProfile:
					if(BasalProfileExists()){
						;//?
					} else {
						c_menuScreen=NoBasProf;
					}
					break;
				case Basal_StopTmp: break;
				case Basal_Manage: f_menuChoice = Basal_Manage_Create;break;
				default: break;
				}
			}
			break;
		case BasalProfActive:
			if (M_backReq){
				c_menuScreen = Main;
				f_menuChoice = Basal;
			} else if (M_upReq){
				switch (f_menuChoice){
				case Basal_StopProfile: f_menuChoice = Basal_Manage;break;
				case Basal_StartTmp: f_menuChoice = Basal_StopProfile;break;
				case Basal_Manage: f_menuChoice = Basal_StartTmp;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Basal_StopProfile: f_menuChoice = Basal_StartTmp;break;
				case Basal_StartTmp: f_menuChoice = Basal_Manage;break;
				case Basal_Manage: f_menuChoice = Basal_StopProfile;break;
				default: break;
				}
			} else if (M_selReq){
				c_menuScreen = f_menuChoice;
				switch (f_menuChoice){
				case Basal_StopProfile: break;
				case Basal_StopTmp: break;
				case Basal_Manage: f_menuChoice = Basal_Manage_Create;break;
				default: break;
				}
			}
			break;
		case Basal_Manage:
			if (M_backReq){
				if(BasalIsActive() && TemporaryBasalIsActive()){
					c_menuScreen = BasalBothActive;
				} else if (BasalIsActive() && !TemporaryBasalIsActive()){
					c_menuScreen = BasalProfActive;
				} else if (!BasalIsActive() && TemporaryBasalIsActive()){
					c_menuScreen = BasalTmpActive;
				} else{
					c_menuScreen = BasalNoActive;
				}
				f_menuChoice = Basal_Manage;
			} else if (M_upReq){
				switch (f_menuChoice){
				case Basal_Manage_Create: f_menuChoice = Basal_Manage_Remove;break;
				case Basal_Manage_Remove: f_menuChoice = Basal_Manage_Create;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Basal_Manage_Create: f_menuChoice = Basal_Manage_Remove;break;
				case Basal_Manage_Remove: f_menuChoice = Basal_Manage_Create;break;
				default: break;
				}
			} else if (M_selReq){
				c_menuScreen = f_menuChoice;
				switch (f_menuChoice){
				case Basal_Manage_Create:
					if(BasalCreationAllowed()){
						;// M_basCreateReq
					} else {
						c_menuScreen = BasCreateNotAllowed;
					}
					break;
				case Basal_Manage_Remove:
					if(BasalProfileExists()){
						;//BasRemoveReq
					} else {
						c_menuScreen = NoBasProf;
					}
					break;
				default: break;
				}
			}
			break;

		case NoBasProf:
			if (M_backReq){
				if(BasalIsActive() && TemporaryBasalIsActive()){
					c_menuScreen = BasalBothActive;
					f_menuChoice = Basal_StopProfile;
				} else if (BasalIsActive() && !TemporaryBasalIsActive()){
					c_menuScreen = BasalProfActive;
					f_menuChoice = Basal_StopProfile;
				} else if (!BasalIsActive() && TemporaryBasalIsActive()){
					c_menuScreen = BasalTmpActive;
					f_menuChoice = Basal_StartProfile;
				} else{
					c_menuScreen = BasalNoActive;
					f_menuChoice = Basal_StartProfile;
				}
			}
			break;

		case BasCreateNotAllowed:
			if (M_backReq){
				c_menuScreen = Basal_Manage;
				f_menuChoice = Basal_Manage_Create;
			}
			break;

		case BolusAlreadyActive:
			if (M_backReq){
				c_menuScreen = Bolus;
			}
			break;

		case RemindCreateNotAllowed:
			if (M_backReq){
				c_menuScreen = Schedule;
			}
			break;

		case NoRemind:
			if (M_backReq){
				c_menuScreen = Schedule;
			}
			break;

		case BolusCreateNotAllowed:
			if (M_backReq){
				c_menuScreen = Bolus_Manage;
			}
			break;

		case NoBolusPreset:
			if (M_backReq){
				c_menuScreen = Bolus;
				f_menuChoice = Bolus_Start;
			}
			break;

		default: break;
		}
		break;

	case CreateBasProf:
		switch (c_basCreateStatus){
		case e_opStatus_idle:
			c_menuScreen = CreateBasProf_Idle;

			if(basCreateStatus_NameEntered == false){

				/** Allow user to enter a profile name, temporarily stores it in p_inputProfile.**/
				// Initialize the First letter of Profile Name to 'A'
				if(nameIndex == 0 && p_inputProfile.Name[0] == 0) {
					p_inputProfile.Name[nameIndex] = 65;
				}

				if (M_upReq){ // Increment current character by one and wrap around the alphabet if needed.
					if (nameIndex==0 && p_inputProfile.Name[nameIndex] == 90) p_inputProfile.Name[nameIndex] = 65; //ASCII 90 = Z, 65 = A
					else if (p_inputProfile.Name[nameIndex] == 122) p_inputProfile.Name[nameIndex] = 97; //ASCII 122 = z, 97 = a
					else p_inputProfile.Name[nameIndex]++;
					updateScreen = true;

				} else if(M_downReq){ // Decrement current character by one and wrap around the alphabet if needed.
					if (nameIndex==0 && p_inputProfile.Name[nameIndex] == 65) p_inputProfile.Name[nameIndex] = 90;
					else if (p_inputProfile.Name[nameIndex] == 97) p_inputProfile.Name[nameIndex] = 122;
					else p_inputProfile.Name[nameIndex]--;
					updateScreen = true;

				} else if(M_rightReq){ // Go to next character and initialize it to 'a'
					if(nameIndex<10){
						p_inputProfile.Name[++nameIndex] = 97;
						updateScreen = true;
					}

				} else if (M_leftReq){ // Go to previous character (if possible) and remove last character.
					if(nameIndex > 0){
						p_inputProfile.Name[nameIndex--] = 0;
						updateScreen = true;
					}
				} else if (M_nextReq){
					basCreateStatus_NameEntered = true;
					updateScreen = true;
				}

			} else {
				if (M_upReq){
					if (rateIndex == 0){
						if (segments[segmentIndex+1] > 1){
							segments[segmentIndex]++;
							segments[segmentIndex+1]--;
						}
					} else {
						p_inputProfile.Rate[segmentIndex]++;
					}
					updateScreen = true;

				} else if(M_downReq){
					if (rateIndex == 0){
						if (segments[segmentIndex]>1){
							segments[segmentIndex]--;
							segments[segmentIndex+1]++;
						}
					} else {
						if (p_inputProfile.Rate[segmentIndex] > 0){
							p_inputProfile.Rate[segmentIndex]--;
						}
					}
					updateScreen = true;

				} else if(M_rightReq){ // Go to next character and initialize it to 'a'
					if (rateIndex == 1){
						if (segments[segmentIndex+1]>0){
							segmentIndex++;
							rateIndex = 0;
						}
					} else{
						rateIndex = 1;
					}
					updateScreen = true;

				} else if (M_leftReq){ // Go to previous character (if possible) and remove last character.
					if (rateIndex == 1){
						rateIndex = 0;
					} else {
						if (segmentIndex > 0){
							segmentIndex--;
							rateIndex = 1;
						} else {
							basCreateStatus_NameEntered = false;
						}
					}
					updateScreen = true;

				} else if (M_addReq){
			//
			//		if (segments[segmentIndex]>1){
			//			segments[segmentIndex]--;
			//			segmentIndex++
			//			segments[segmentIndex] = 1;
			//		}

					;
				}
			}

			break;

		case e_opStatus_confirm: c_menuScreen = CreateBasProf_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = CreateBasProf_Invalid; break;
		}
		break;

	case RemoveBasProf:
		switch (c_basRemStatus){
		case e_opStatus_idle: c_menuScreen = RemoveBasProf_Idle; break;
		case e_opStatus_confirm: c_menuScreen = RemoveBasProf_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = RemoveBasProf_Invalid; break;
		}
		break;

	case StartBasProf:
		switch (c_basStartStatus){
		case e_opStatus_idle: c_menuScreen = StartBasProf_Idle; break;
		case e_opStatus_confirm: c_menuScreen = StartBasProf_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = StartBasProf_Invalid; break;
		}
		break;

	case StopBasProf:
		c_menuScreen = StopBasProf_All;
		break;

	case StartTmpBas:
		switch (c_tmpStartStatus){
		case e_opStatus_idle: c_menuScreen = StartTmpBas_Idle; break;
		case e_opStatus_confirm: c_menuScreen = StartTmpBas_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = StartTmpBas_Invalid; break;
		}
		break;

	case StopTmpBas:
		c_menuScreen = StopTmpBas_All;
		break;

	case CreateBolusPreset:
		switch (c_bolCreateStatus){
		case e_opStatus_idle: c_menuScreen = CreateBolusPreset_Idle; break;
		case e_opStatus_confirm: c_menuScreen = CreateBolusPreset_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = CreateBolusPreset_Invalid; break;
		}
		break;

	case RemoveBolusPreset:
		switch (c_bolRemStatus){
		case e_opStatus_idle: c_menuScreen = RemoveBolusPreset_Idle; break;
		case e_opStatus_confirm: c_menuScreen = RemoveBolusPreset_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = RemoveBolusPreset_Invalid; break;
		}
		break;

	case StartBolus:
		switch (c_bolStartStatus){
		case e_bolStatus_idle: c_menuScreen = StartBolus_Idle; break;
		case e_bolStatus_confirm: c_menuScreen = StartBolus_Confirm; break;
		case e_bolStatus_invalid: c_menuScreen = StartBolus_Invalid; break;
		case e_bolStatus_preset: c_menuScreen = StartBolus_Preset; break;
		case e_bolStatus_calculator: c_menuScreen = StartBolus_Calculator; break;
		case e_bolStatus_manual: c_menuScreen = StartBolus_Manual; break;
		}
		break;

	case CreateReminder:
		switch (c_remindCreateStatus){
		case e_opStatus_idle: c_menuScreen = CreateReminder_Idle; break;
		case e_opStatus_confirm: c_menuScreen = CreateReminder_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = CreateReminder_Invalid; break;
		}
		break;

	case RemoveReminder:
		switch (c_remindRemStatus){
		case e_opStatus_idle: c_menuScreen = RemoveReminder_Idle; break;
		case e_opStatus_confirm: c_menuScreen = RemoveReminder_Confirm; break;
		case e_opStatus_invalid: break; //do nothing, should not happen.
		}
		break;

	default:
		break;
	}
}



void ClearScreen(){
	GrClearDisplay(&g_sContext); // Clears the screen
}

void PrintBolus_Manage(){
	;
}
void PrintBolus(){
	;
}
void PrintBolusAlreadyActive(){
	;
}
void PrintBolusCreateNotAllowed(){
	;
}
void PrintError(){
	;
}
void PrintNoBolusPreset(){
	;
}
void PrintNoRemind(){
	;
}
void PrintRemindCreateNotAllowed(){
	;
}
void PrintSchedule(){
	;
}
void PrintSettings(){
	;
}

void ClearCreateBasProf_Idle(y_basal *p_profile){
	GrStringDraw(&g_sContext, p_profile->Name, AUTO_STRING_LENGTH, 5, 44, TRANSPARENT_TEXT);

	GrFlush(&g_sContext);
}

void LoadRates(y_basal *p_profile, int scrollOffset){

	char buffer[10] = "";
	char rateBuffer[10] = "";
	char outString[32] = "";
	int rateDigs, hours, halfs, digits, segCount = 0;
	int i = 0;


	strcpy(outString, "0000-");

	while(i<k_segDay && segments[i+1]!= 0)
	{
		segCount += segments[i];
		hours = segCount/2;
		halfs = segCount%2;
		digits = UnsignedInt_To_ASCII(hours, buffer);

		strncat(outString, buffer, digits);

		if (halfs == 1)	strncat(outString, "30", 2);
		else strncat(outString, "00", 2);

		if (digits == 1) strncat(outString, " ", 1);

		rateDigs = UnsignedInt_To_ASCII(p_profile->Rate[i], rateBuffer);
		strncat(outString, "|", 1);
		strncat(outString, rateBuffer, rateDigs);

		if (50+i*10-scrollOffset > 15 && 50 + i*10-scrollOffset < 80) GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, i*10+50 - scrollOffset, OPAQUE_TEXT);

		strcpy(outString, "");
		if (digits == 1) strncat(outString, " ", 1);

		strncat(outString, buffer,digits);

		if (halfs == 1)	strncat(outString, "30-", 3);
		else strncat(outString, "00-", 3);


		// Remove previously written underline
		GrContextForegroundSet(&g_sContext, ClrWhite);
		if (58 + i*10-scrollOffset > 15 && 58 + i*10-scrollOffset < 81) GrLineDrawH(&g_sContext, 35, 95, 58 + i*10 -scrollOffset);
		GrContextForegroundSet(&g_sContext, ClrBlack);

		i++;
	}

	// Remove previously written underline
	GrContextForegroundSet(&g_sContext, ClrWhite);
	if (58 + i*10-scrollOffset > 15 && 58 + i*10-scrollOffset < 81) GrLineDrawH(&g_sContext, 35, 95, 58 + i*10 - scrollOffset);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	segCount += segments[i];
	hours = segCount/2;
	halfs = segCount%2;
	digits = UnsignedInt_To_ASCII(hours, buffer);

	if (digits == 1) strncat(outString, " ", 1);

	strncat(outString, buffer,digits);

	if (halfs == 1)	strncat(outString, "30", 2);
	else strncat(outString, "00", 2);

	if (digits == 1) strncat(outString, " ", 1);

	rateDigs = UnsignedInt_To_ASCII(p_profile->Rate[i], rateBuffer);
	strncat(outString, "|", 1);
	strncat(outString, rateBuffer, rateDigs);

	if (50 + i*10-scrollOffset > 15 && 50+ i*10-scrollOffset < 80) GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 10*i+50 - scrollOffset, OPAQUE_TEXT);

}

void PrintCreateBasProf_Idle(y_basal *p_profile){
	int cursorY, cursorX, cursorW, scrollOffset=0;

	if (basCreateStatus_NameEntered == false){
		cursorY = 34;
		cursorX = nameIndex+(nameIndex+1)*5;
		cursorW = 4;
	} else {
		cursorY = 58 + segmentIndex*10 ;
		cursorX = 35 + rateIndex*30;
		cursorW = 23 - rateIndex*7;
	}

	if (cursorY > 80){
		scrollOffset = cursorY - 80;

		GrContextForegroundSet(&g_sContext, ClrWhite);
		GrRectFill(&g_sContext, &myRectangleScreen);
		GrContextForegroundSet(&g_sContext, ClrBlack);
	} else if (cursorY > 70){
		// takes care of clearing the screen when returning to the top of the page.
		GrContextForegroundSet(&g_sContext, ClrWhite);
		GrRectFill(&g_sContext, &myRectangleScreen);
		GrContextForegroundSet(&g_sContext, ClrBlack);
	}

	if (16-scrollOffset > 15 && 16-scrollOffset < 80) GrStringDraw(&g_sContext, "Profile Name:" , AUTO_STRING_LENGTH, 5, 16-scrollOffset, OPAQUE_TEXT);

	if (40-scrollOffset > 15 && 40-scrollOffset < 80) GrStringDraw(&g_sContext, "Rates:   |U/hr" , AUTO_STRING_LENGTH, 5, 40-scrollOffset, OPAQUE_TEXT);

	LoadRates(p_profile, scrollOffset);

	// Remove previously written letters and underline
	GrContextForegroundSet(&g_sContext, ClrWhite);
	if (26-scrollOffset > 15 && 26-scrollOffset < 80)GrStringDraw(&g_sContext, "xxxxxxxxxxx", AUTO_STRING_LENGTH, 5, 26-scrollOffset, OPAQUE_TEXT);
	if (30-scrollOffset > 15 && 30-scrollOffset < 80)GrStringDraw(&g_sContext, "xxxxxxxxxxx", AUTO_STRING_LENGTH, 5, 30-scrollOffset, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	if (cursorY > 13&& cursorY-scrollOffset < 81)GrLineDrawH(&g_sContext, cursorX, cursorX+cursorW, cursorY-scrollOffset);
	if (26-scrollOffset > 15 && 26-scrollOffset < 80)GrStringDraw(&g_sContext, p_profile->Name , AUTO_STRING_LENGTH, 5, 26-scrollOffset, OPAQUE_TEXT);

	LoadLeftButton("BACK");
	if (basCreateStatus_NameEntered == false) LoadRightButton("RATE");

	GrFlush(&g_sContext);
}


/**********************************************************************//**
 * @brief  UnsignedInt_To_ASCII
 *
 * @param  none
 *
 * @return i - number of digits that the Unsigned Int is
 *************************************************************************/
int UnsignedInt_To_ASCII(unsigned int hex, char *ASCII)
{
    int i, j;
    char flipped[5] = { 0, 0, 0, 0, 0 };

    // Convert from hex to ASCII
    for (i = 1; i < 6; i++) {
        flipped[i] = hex % 10 + 0x30;
        hex /= 10;
        if (hex == 0) {
            break;
        }
    }

    // Flip data values to correct position in array
    for (j = 0; j < 5; j++) {
        ASCII[j] = flipped[i - j];
    }

    return i;
}


void PrintMessage(char outString[32]){
	// Print basal status

		GrStringDrawCentered(&g_sContext, outString , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
	//	GrStringDrawCentered(&g_sContext, "Temp Basal: " , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
		//GrStringDrawCentered(&g_sContext, "No Basal" , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);



		//LoadBanner();
		// Load bottom buttons
		LoadLeftButton("BACK");
		//LoadMiddleButton("MENU");
		//LoadRightButton("");
		GrFlush(&g_sContext);

}

void PrintCreateBasProf(){
	// Print basal status

		GrStringDrawCentered(&g_sContext, "Create Basal " , AUTO_STRING_LENGTH, 48, 25, OPAQUE_TEXT);
	//	GrStringDrawCentered(&g_sContext, "Temp Basal: " , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
		//GrStringDrawCentered(&g_sContext, "No Basal" , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);



		//LoadBanner();
		// Load bottom buttons
		LoadLeftButton("BACK");
		//LoadMiddleButton("MENU");
		//LoadRightButton("");
		GrFlush(&g_sContext);

}



void PrintIdle(){
	// Print basal status
	if (TemporaryBasalIsActive()){
		GrStringDrawCentered(&g_sContext, "Basal: " , AUTO_STRING_LENGTH, 48, 25, OPAQUE_TEXT);
	} else if(BasalIsActive()){
		GrStringDrawCentered(&g_sContext, "Temp Basal: " , AUTO_STRING_LENGTH, 48, 25, OPAQUE_TEXT);
	} else {
		GrStringDrawCentered(&g_sContext, "No Basal" , AUTO_STRING_LENGTH, 48, 25, OPAQUE_TEXT);
	}

	// Print bolus status
	if(BolusInProgress())
		GrStringDrawCentered(&g_sContext, "Bolus: " , AUTO_STRING_LENGTH, 48, 40, OPAQUE_TEXT);
	else {
		GrStringDrawCentered(&g_sContext, "No Bolus" , AUTO_STRING_LENGTH, 48, 40, OPAQUE_TEXT);
	}
	//LoadBanner();
	// Load bottom buttons
	//LoadLeftButton("");
	LoadMiddleButton("MENU");
	//LoadRightButton("");
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
	GrStringDrawCentered(&g_sContext, text, AUTO_STRING_LENGTH, 82, 88, TRANSPARENT_TEXT);
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



void PrintMainMenu(){
    char outString[32];
    unsigned char text_start = 18;

    // Draw bottom buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Basal Menu", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Bolus Menu", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Schedule", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Settings", AUTO_STRING_LENGTH, 5, 57, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Shut Down", AUTO_STRING_LENGTH, 5, 70, OPAQUE_TEXT);


    // Highlight selected item
    switch (f_menuChoice) {
    case Basal:
        text_start = 18;
        strcpy(outString, "Basal Menu");
        break;
    case Bolus:
        text_start = 31;
        strcpy(outString, "Bolus Menu");
        break;
    case Schedule:
        text_start = 44;
        strcpy(outString, "Schedule");
        break;
    case Settings:
        text_start = 57;
        strcpy(outString, "Settings");
        break;
    case ShutDown:
        text_start = 70;
        strcpy(outString, "Shut Down");
        break;

    default: break;
    }

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack);    //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

    GrFlush(&g_sContext);
}


void PrintBasNoActive(){
    char outString[32];
    unsigned char text_start = 18;

    // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Start Profile", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Start Temporary", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);

    // Highlight selected item
    switch (f_menuChoice) {
    case Basal_StartProfile:
        text_start = 18;
        strcpy(outString, "Start Profile");
        break;
    case Basal_StartTmp:
        text_start = 31;
        strcpy(outString, "Start Temporary");
        break;
    case Basal_Manage:
        text_start = 44;
        strcpy(outString, "Manage Profiles");
        break;

    default: break;
    }

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack);    //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

    GrFlush(&g_sContext);
}

void PrintBasCreateNotAllowed(){
    // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	//LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDrawCentered(&g_sContext, "Basal Profile", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Creation", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "not Allowed", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

    GrFlush(&g_sContext);
}

void PrintNoBasProf(){
    // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	//LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDrawCentered(&g_sContext, "No Basal", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Profile", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Available", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

    GrFlush(&g_sContext);
}

void PrintBasProfActive(){
    char outString[32];
    unsigned char text_start = 18;

    // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Stop Profile", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Start Temporary", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);

    // Highlight selected item
    switch (f_menuChoice) {
    case Basal_StopProfile:
        text_start = 18;
        strcpy(outString, "Stop Profile");
        break;
    case Basal_StartTmp:
        text_start = 31;
        strcpy(outString, "Start Temporary");
        break;
    case Basal_Manage:
        text_start = 44;
        strcpy(outString, "Manage Profiles");
        break;

    default: break;
    }

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack);    //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

    GrFlush(&g_sContext);
}


void PrintBasBothActive(){
    char outString[32];
    unsigned char text_start = 18;

    // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Stop Profile", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Stop Temporary", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);

    // Highlight selected item
    switch (f_menuChoice) {
    case Basal_StopProfile:
        text_start = 18;
        strcpy(outString, "Stop Profile");
        break;
    case Basal_StopTmp:
        text_start = 31;
        strcpy(outString, "Stop Temporary");
        break;
    case Basal_Manage:
        text_start = 44;
        strcpy(outString, "Manage Profiles");
        break;

    default: break;
    }

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack);    //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

    GrFlush(&g_sContext);
}


void PrintBasTmpActive(){
    char outString[32];
    unsigned char text_start = 18;

    // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Start Profile", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Stop Temporary", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);

    // Highlight selected item
    switch (f_menuChoice) {
    case Basal_StartProfile:
        text_start = 18;
        strcpy(outString, "Start Profile");
        break;
    case Basal_StopTmp:
        text_start = 31;
        strcpy(outString, "Stop Temporary");
        break;
    case Basal_Manage:
        text_start = 44;
        strcpy(outString, "Manage Profiles");
        break;

    default: break;
    }

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack);    //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

    GrFlush(&g_sContext);
}


void PrintBasal_Manage(){
    char outString[32];
    unsigned char text_start = 18;


    // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Create Profile", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Remove Profile", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);


    // Highlight selected item
    switch (f_menuChoice) {
    case Basal_Manage_Create:
        text_start = 18;
        strcpy(outString, "Create Profile");
        break;
    case Basal_Manage_Remove:
        text_start = 31;
        strcpy(outString, "Remove Profile");
        break;

    default: break;
    }

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack);  //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

    GrFlush(&g_sContext);
}




/*
bool M_MenuReq(){
	if (c_operation == Idle){
		if (!(BIT3 & P1IN)) return true;
	}
	return false;
}

enum e_operations GetMainMenuChoice(){
	switch (mainMenuChoice){
	case Basal: return Basal;
	case Bolus: return MMBolus;
	case Settings: return MMSettings;
	case Schedule: return MMSchedule;
	case ShutDown: return MMShutDown;
	default: break;
	}
	return Error;
}

enum e_operations GetBasalActiveChoice(){
	switch (BasalActiveChoice){
	case Deactivate: return StopBasProf;
	case ManageProfilesActive: return BasalProfilesMenu;
	default: break;
	}
	return Error;
}

enum e_operations GetBasalInactiveChoice(){
	switch (BasalInactiveChoice){
	case Activate: return BasalActivateMenu;
	case ManageProfilesInactive: return BasalProfilesMenu;
	default: break;
	}
	return Error;
}


void DisplayBasalActive(){
    char outString[32];
    unsigned char text_start = 18;

    ClearBasalActive();

    // Draw top and bottom banner and buttons
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Deactivate", AUTO_STRING_LENGTH, 5, 18, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 31, TRANSPARENT_TEXT);


    // Highlight selected item
    switch (BasalActiveChoice) {
    case Deactivate:
        text_start = 18;
        strcpy(outString, "Deactivate");
        break;
    case ManageProfilesActive:
        text_start = 31;
        strcpy(outString, "Manage Profiles");
        break;

    default: break;
    }

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack);    //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

    GrFlush(&g_sContext);
}


void DisplayBasalInactive(){
    char outString[32];
    unsigned char text_start = 18;

    ClearBasalInactive();

    // Draw top and bottom banner and buttons
	LoadBanner();
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Activate", AUTO_STRING_LENGTH, 5, 18, TRANSPARENT_TEXT);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 31, TRANSPARENT_TEXT);


    // Highlight selected item
    switch (BasalInactiveChoice) {
    case Deactivate:
        text_start = 18;
        strcpy(outString, "Activate");
        break;
    case ManageProfilesInactive:
        text_start = 31;
        strcpy(outString, "Manage Profiles");
        break;

    default: break;
    }

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack);    //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

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

void ClearBasalActive(){
	GrStringDraw(&g_sContext, "Deactivate Basal", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Manage Profiles", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
}

void ClearBasalInactive(){
	GrStringDraw(&g_sContext, "Activate", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
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
	return i_leftSelBtn;
	//if (BIT4 & P1IN){
	//	return false;
	//} else {
	//	return true;
	//}
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
}*/
