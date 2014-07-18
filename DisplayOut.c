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
unsigned char segments[k_segDay] = {k_segDay, 0};
y_basalRate rates[k_segDay];
y_tmpBasal p_inputTmpBasal;

unsigned char rateIndex = 0;
unsigned char segmentIndex = 0;
unsigned char nameIndex = 0;
bool updateScreen = false;
bool basCreateStatus_NameEntered = false;
bool tmpBasal_DurationEntered = false;


void PrintBasal_Manage();
void LoadBanner(void);
void LoadLeftButton(const char * text);
void LoadMiddleButton(const char * text);
void LoadRightButton(const char * text);
void ClearRightButton();
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
void PrintCreateBasProf_Confirm();
void ClearInputProfile();
void InputProfileToBasalProfile(y_basal *basProf);

void PrintRemoveBasProf_Idle();
void PrintRemoveBasProf_Confirm();
void PrintRemoveBasProf_Invalid();

void PrintStartBasProf_Idle();
void PrintStartBasProf_Confirm();
void PrintStartBasProf_Invalid();

void PrintStartTmpBas_Idle();
void PrintStartTmpBas_Confirm();
void PrintStartTmpBas_Invalid();

void PrintStopBas_All();

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

	case CreateBasProf_Idle: PrintCreateBasProf_Idle(&p_inputProfile); break;
	case CreateBasProf_Confirm:PrintCreateBasProf_Confirm(); break;
	case CreateBasProf_Invalid:PrintMessage("Invalid Create"); break;

	case RemoveBasProf_Idle:PrintRemoveBasProf_Idle(); break;
	case RemoveBasProf_Confirm:PrintRemoveBasProf_Confirm(); break;
	case RemoveBasProf_Invalid:PrintMessage("Invalid Rem"); break;

	case StartBasProf_Idle:PrintStartBasProf_Idle(); break;
	case StartBasProf_Confirm:PrintStartBasProf_Confirm(); break;
	case StartBasProf_Invalid:PrintStartBasProf_Invalid(); break;

	case StopBasProf_All:PrintStopBas_All(); break;

	case StartTmpBas_Idle:PrintStartTmpBas_Idle(); break;
	case StartTmpBas_Confirm:PrintStartTmpBas_Confirm(); break;
	case StartTmpBas_Invalid:PrintStartTmpBas_Idle(); break;

	case StopTmpBas_All:PrintMessage("Stop Tmp"); break;

	case CreateBolusPreset_Idle:PrintMessage("Create Bol"); break;
	case CreateBolusPreset_Confirm:break;
	case CreateBolusPreset_Invalid:break;
	case RemoveBolusPreset_Idle:PrintMessage("Remove Bol"); break;
	case RemoveBolusPreset_Confirm:break;
	case RemoveBolusPreset_Invalid:break;
	case StartBolus_Idle:PrintMessage("Start Bol"); break;
	case StartBolus_Calculator:break;
	case StartBolus_Preset:break;
	case StartBolus_Manual:break;
	case StartBolus_Confirm:break;
	case StartBolus_Invalid:break;
	case CreateReminder_Idle:PrintMessage("Create Remind"); break;
	case CreateReminder_Confirm:break;
	case CreateReminder_Invalid:break;
	case RemoveReminder_Idle:PrintMessage("Remove Remind"); break;
	case RemoveReminder_Confirm:break;



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

		case Settings:
			if (M_backReq){
				c_menuScreen = Main;
				f_menuChoice = Settings;
			} else if (M_selReq){
				InitBasalSet();
			}
			break;

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
						LoadProfile( &m_basActSelected, 0 ); // Selects the first available profile.
					} else {
						c_menuScreen=NoBasProf;
					}
					break;
				case Basal_StartTmp:
					CopyTmpBasal(&k_emptyTmp, &m_tmpBas);
					break;
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
						LoadProfile( &m_basActSelected, 0 ); // Selects the first available profile.
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
				case Basal_StartTmp:
					CopyTmpBasal(&k_emptyTmp, &m_tmpBas);
					break;
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
						LoadProfile( &m_basRemSelected, 0 ); // Selects the first available profile.
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

		default: c_menuScreen = None;
			break;
		}
		break;

	case CreateBasProf:
		switch (c_basCreateStatus){
		case e_opStatus_idle:
			c_menuScreen = CreateBasProf_Idle;

			if(basCreateStatus_NameEntered == false){ // Editing the profile name.

				/** Allow user to enter a profile name, temporarily stores it in p_inputProfile.**/
				// Initialize the First letter of Profile Name to 'A'
				if(nameIndex == 0 && p_inputProfile.Name[0] == 0) {
					p_inputProfile.Name[0] = 65;
					updateScreen = true;
				}

				if (M_upReq){ // Increment current character by one and wrap around the alphabet if needed.
					if (nameIndex==0 && p_inputProfile.Name[0] == 90) p_inputProfile.Name[0] = 65; //ASCII 90 = Z, 65 = A
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

			} else { // Editing the rates and time periods

				// Format of the profile here is different than when stored in the set of profiles. The segments array holds the number of segments that are part of
				// a time period. Each of the time periods has a corresponding rate, which is stored in the p_inputProfile.Rate array.
				// example: segments array holds {20, 15, 10, 3, 0, ...} each segment unit corresponds to 30min, so the time periods are
				// {00:00-10:00, 10:00-17:30, 17:30-22:30, 22:30-24:00, ...}
				if (M_upReq){
					if (rateIndex == 0){ // One of the time periods is highlighted. Increment the selected time period if possible.
						if (segments[segmentIndex+1] > 1){
							segments[segmentIndex]++;
							segments[segmentIndex+1]--;
						}
					} else { // One of the rates is highlighted. Increment the rate.
						p_inputProfile.Rate[segmentIndex]++;
					}
					updateScreen = true;

				} else if(M_downReq){
					if (rateIndex == 0){ // Decrement the selected time period if possible.
						if (segments[segmentIndex]>1){
							segments[segmentIndex]--;
							segments[segmentIndex+1]++;
						}
					} else { // Decrement the selected rate down to a lowest of 0.
						if (p_inputProfile.Rate[segmentIndex] > 0){
							p_inputProfile.Rate[segmentIndex]--;
						}
					}
					updateScreen = true;

				} else if(M_rightReq){
					if (rateIndex == 1){ // if rate is selected, go to the next time period if one exists.
						if (segments[segmentIndex+1]>0){
							segmentIndex++;
							rateIndex = 0;
						}
					} else{ // if a time period is selected, select the rate that correponds to that time period.
						rateIndex = 1;
					}
					updateScreen = true;

				} else if (M_leftReq){
					if (rateIndex == 1){ // if a rate is selected, go to the corresponding time period
						rateIndex = 0;
					} else { // if the time period is selected, go back to the previous rate if there is one, otherwise go back to editing the name.
						if (segmentIndex > 0){
							segmentIndex--;
							rateIndex = 1;
						} else {
							basCreateStatus_NameEntered = false;
						}
					}
					updateScreen = true;

				} else if (M_selReq){
					InputProfileToBasalProfile(&m_basProf);
					M_basProf = true;
					updateScreen = true;

					// Reset variables used by this function
					basCreateStatus_NameEntered = false;
					segmentIndex = 0;
					rateIndex = 0;
					nameIndex = 0;

					int i = 1;
					segments[ 0 ] = k_segDay;
					while (i < k_segDay && segments[ i ] != 0 ){
						segments[ i ] = 0;
						i++;
					}
					ClearInputProfile();
				}
			}

			break;

		case e_opStatus_confirm:
			c_menuScreen = CreateBasProf_Confirm;

		break;
		case e_opStatus_invalid: c_menuScreen = CreateBasProf_Invalid; break;
		}
		break;

	case RemoveBasProf:
		switch (c_basRemStatus){
		case e_opStatus_idle:
			c_menuScreen = RemoveBasProf_Idle;
			int profileIndex;
			if (M_downReq){
				profileIndex = GetProfileIndex( &m_basRemSelected );
				if(profileIndex == GetNumberBasalProfiles() - 1 ){
					LoadProfile( &m_basRemSelected, 0 );
					updateScreen = true;
				} else {
					profileIndex++;
					LoadProfile( &m_basRemSelected, profileIndex );
					updateScreen = true;
				}


			} else if(M_upReq){
				profileIndex = GetProfileIndex( &m_basRemSelected );
				if(profileIndex == 0 ){
					LoadProfile( &m_basRemSelected, GetNumberBasalProfiles() - 1 );
					updateScreen = true;
				} else {
					profileIndex--;
					LoadProfile( &m_basRemSelected, profileIndex );
					updateScreen = true;
				}


			} else if (M_selReq){
				M_basRemSelected = true;
				updateScreen = true;
			}


			break;


		case e_opStatus_confirm: c_menuScreen = RemoveBasProf_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = RemoveBasProf_Invalid; break;
		}
		break;

	case StartBasProf:
		switch (c_basStartStatus){
		case e_opStatus_idle:
			c_menuScreen = StartBasProf_Idle;
			int profileIndex;
			if (M_downReq){
				profileIndex = GetProfileIndex( &m_basActSelected );
				if(profileIndex == GetNumberBasalProfiles() - 1 ){
					LoadProfile( &m_basActSelected, 0 );
					updateScreen = true;
				} else {
					profileIndex++;
					LoadProfile( &m_basActSelected, profileIndex );
					updateScreen = true;
				}


			} else if(M_upReq){
				profileIndex = GetProfileIndex( &m_basActSelected );
				if(profileIndex == 0 ){
					LoadProfile( &m_basActSelected, GetNumberBasalProfiles() - 1 );
					updateScreen = true;
				} else {
					profileIndex--;
					LoadProfile( &m_basActSelected, profileIndex );
					updateScreen = true;
				}


			} else if (M_selReq){
				M_basActSelected = true;
				updateScreen = true;
			}


			break;

		case e_opStatus_confirm: c_menuScreen = StartBasProf_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = StartBasProf_Invalid; break;
		}
		break;

	case StopBasProf:
		c_menuScreen = StopBasProf_All;
		break;

	case StartTmpBas:


		switch (c_tmpStartStatus){
		case e_opStatus_idle:
			c_menuScreen = StartTmpBas_Idle;

			if(tmpBasal_DurationEntered == false){ //Editing tmp basal duration

				if(M_upReq){ // increment numbers, roll over from 9->0
					if(m_tmpBas.Duration == k_maxTmpDuration) m_tmpBas.Duration == 0;
					else m_tmpBas.Duration++;
					updateScreen = true;
				}
				else if(M_downReq) { // decrement numbers, roll over from 0->9
					if(m_tmpBas.Duration == 0) m_tmpBas.Duration == k_maxTmpDuration;
					else m_tmpBas.Duration--;
					updateScreen = true;
				}
				else if (M_nextReq){ // hit next, duration is entered
					tmpBasal_DurationEntered = true;
					updateScreen = true;
				}

			}
			else {
					if(M_upReq){ // increment numbers, roll over from 9->0
						if(m_tmpBas.Rate == k_maxTmpRate) m_tmpBas.Rate == 0;
						else m_tmpBas.Rate++;
						updateScreen = true;
					}
					else if(M_downReq) { // decrement numbers, roll over from 0->9
						if(m_tmpBas.Rate == 0) m_tmpBas.Rate == k_maxTmpRate;
						else m_tmpBas.Rate--;
						updateScreen = true;
					}
					else if(M_nextReq){
						tmpBasal_DurationEntered = false;
						updateScreen = true;
					}
					else if (M_selReq){ // hit next, duration is entered
						M_tmpBas = true;
					}
			}
		break;

		case e_opStatus_confirm: c_menuScreen = StartTmpBas_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = StartTmpBas_Invalid; break;
		}
		break;

	case StopTmpBas:
		c_menuScreen = StopTmpBas_All;
		break;

	case CreateBolPre:
		switch (c_bolCreateStatus){
		case e_opStatus_idle: c_menuScreen = CreateBolusPreset_Idle; break;
		case e_opStatus_confirm: c_menuScreen = CreateBolusPreset_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = CreateBolusPreset_Invalid; break;
		}
		break;

	case RemoveBolPre:
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
	LoadLeftButton("BACK");
	GrStringDraw(&g_sContext, "Settings" , AUTO_STRING_LENGTH, 5, 16, OPAQUE_TEXT);
	GrFlush(&g_sContext);
}

void PrintCreateBasProf_Confirm(){
	GrStringDraw(&g_sContext, "Save Profile?" , AUTO_STRING_LENGTH, 5, 16, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, m_basProf.Name , AUTO_STRING_LENGTH, 5, 26, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
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

void PrintRemoveBasProf_Confirm(){

	GrStringDrawCentered(&g_sContext, "Remove Profile?" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, m_basRemSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintRemoveBasProf_Invalid(){

	GrStringDrawCentered(&g_sContext, "Profile Active" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Cannot Remove" , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);
	//GrStringDrawCentered(&g_sContext, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	//LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintStartBasProf_Confirm(){

	GrStringDrawCentered(&g_sContext, "Start Profile?" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintStartBasProf_Invalid(){

	GrStringDrawCentered(&g_sContext, "Profile Invalid" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	//GrStringDrawCentered(&g_sContext, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	//LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintStartBasProf_Idle(){
	int numberOfProfiles;
	numberOfProfiles = GetNumberBasalProfiles();

	y_basalName *Name;
	Name = (y_basalName *) malloc( sizeof( y_basalName ));

	int i;
	for ( i = 0; i < numberOfProfiles; i++ ){
		GetProfileName( Name, i );
		GrStringDraw( &g_sContext, *Name, AUTO_STRING_LENGTH, 5, 16 + ( 10 * i ), OPAQUE_TEXT );
	}
	free(Name);

	// highlight the selected profile
    unsigned char text_start = 18;
    int index = GetProfileIndex( &m_basActSelected );
	text_start = 16 + 10 * index;

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack); //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, m_basActSelected.Name, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

	LoadLeftButton( "CANC" );
	LoadMiddleButton( "SEL" );
	GrFlush(&g_sContext);
}

void PrintRemoveBasProf_Idle(){
	int numberOfProfiles;
	numberOfProfiles = GetNumberBasalProfiles();

	y_basalName *Name;
	Name = (y_basalName *) malloc( sizeof( y_basalName ));

	int i;
	for ( i = 0; i < numberOfProfiles; i++ ){
		GetProfileName( Name, i );
		GrStringDraw( &g_sContext, *Name, AUTO_STRING_LENGTH, 5, 16 + ( 10 * i ), OPAQUE_TEXT );
	}
	free(Name);

	// highlight the selected profile
    unsigned char text_start = 18;
    int index = GetProfileIndex( &m_basRemSelected );
	text_start = 16 + 10 * index;

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack); //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, m_basRemSelected.Name, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

	LoadLeftButton( "CANC" );
	LoadMiddleButton( "SEL" );
	GrFlush(&g_sContext);
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

	LoadLeftButton("CANC");
	if (basCreateStatus_NameEntered == false) LoadRightButton("RATE");
	else {
		ClearRightButton();
		LoadMiddleButton("OK");
	}

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
		GrStringDrawCentered(&g_sContext, "Temp Basal: " , AUTO_STRING_LENGTH, 48, 25, OPAQUE_TEXT);
	} else if(BasalIsActive()){
		GrStringDrawCentered(&g_sContext, "Basal: " , AUTO_STRING_LENGTH, 48, 25, OPAQUE_TEXT);
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

void ClearRightButton(){
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrRectFill(&g_sContext, &myRectangleBotRight);
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


void ClearInputProfile(){
	int i;
	for (i = 0; i < k_basalNameLength-1; i++){
		p_inputProfile.Name[i] = 0;
	}

	for(i = 0; i < k_segDay; i++){
		p_inputProfile.Rate[ i ] = 0;
	}
}

// Converts the inputed profile using ranges to the format used to store in flash.
// Format of the profile here is different than when stored in the set of profiles. The segments array holds the number of segments that are part of
// a time period. Each of the time periods has a corresponding rate, which is stored in the p_inputProfile.Rate array.
// example: segments array holds {20, 15, 10, 3, 0, ...} each segment unit corresponds to 30min, so the time periods are
// {00:00-10:00, 10:00-17:30, 17:30-22:30, 22:30-24:00, ...}
void InputProfileToBasalProfile( y_basal *basProf ){
	int segIndex = 0;
	int i = 0;
	int count = 0;

	while (segments[ segIndex ] > 0 && count < k_segDay){
		for(i = 0; i < segments[ segIndex ]; i++){
			basProf->Rate[ i + count ] = p_inputProfile.Rate[ segIndex ];
		}
		count += segments[ segIndex ];
		segIndex++;
	}

	strncpy( basProf->Name, p_inputProfile.Name, k_basalNameLength-1 );
}

void PrintStopBas_All(){
	GrStringDrawCentered(&g_sContext, "Stop Profile?" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, f_activeBasal.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");

	GrFlush(&g_sContext);
}

void PrintStartTmpBas_Idle(){
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;
	int cursorY, cursorX, cursorW;

	if (tmpBasal_DurationEntered == false){
			cursorY = 46;
			cursorX = 46;

			if (m_tmpBas.Duration <= 9)
				cursorW = 4;
			else if (m_tmpBas.Duration > 9)
				cursorW = 9;
		} else {
			cursorY = 60;
			cursorX = 46;
			if(m_tmpBas.Rate <= 9)
				cursorW = 4;
			else if (m_tmpBas.Rate > 9)
				cursorW = 9;
		}

	GrStringDraw(&g_sContext, "Temporary Basal" , AUTO_STRING_LENGTH, 5, 16, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Duration, buffer);
	strcpy(outString, "Duration: ");
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 26, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Rate, buffer);
	strcpy(outString, "Rate:     ");
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 36, OPAQUE_TEXT);

	GrLineDrawH(&g_sContext, cursorX, cursorX+cursorW, cursorY);


}

void PrintStartTmpBas_Confirm(){
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;

	GrStringDrawCentered(&g_sContext, "Start Temporary", AUTO_STRING_LENGTH, 47, 16, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Basal?", AUTO_STRING_LENGTH, 47, 26, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Duration, buffer);
	strcpy(outString, "Duration: ");
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 36, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Rate, buffer);
	strcpy(outString, "Rate: ");
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 46, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintStartTmpBas_Invalid(){
	PrintMessage("Invalid Temporary Basal");
}
