#include "DisplayOut.h"
#include <string.h>
#include "ActivateBolus.h"
#include "RTC.h"
#include "InsulinOutputCalculator.h"
#include "Reminder.h"

#include "TestSettings.h"

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
y_bolMethod p_selectedMethod = e_bolMethod_noValue;
static y_reminder p_reminder = {"", "", {0}, e_remindFreq_oneTime };

static char remindEntryIndex;
#define NAME 0
#define DATETIME 1
#define FREQ 2
#define MSG 3

unsigned char p_remindSubIndex;


Calendar p_calendar;
unsigned char p_calendarIndex;
#define SEC		2
#define MIN		1
#define HR		0
#define MON		4
#define DOM		3
#define YEAR_1	5
#define YEAR_2	6


unsigned char rateIndex = 0;
unsigned char segmentIndex = 0;
unsigned char nameIndex = 0;
bool updateScreen = false;
bool basCreateStatus_NameEntered = false;
bool tmpBasal_DurationEntered = false;
bool bolCreateStatus_NameEntered = false;
bool bolStartCalc_CarbsEntered = false;

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
void PrintCreateBasProf_Invalid();

void ClearInputProfile();
void InputProfileToBasalProfile(y_basal *basProf);

void PrintRemoveBasProf_Idle();
void PrintRemoveBasProf_Confirm();
void PrintRemoveBasProf_Invalid();

void PrintStartBasProf_Idle();
void PrintStartBasProf_Confirm();
void PrintStartBasProf_Invalid();

void PrintStopBas_All();

void PrintStartTmpBas_Idle();
void PrintStartTmpBas_Confirm();
void PrintStartTmpBas_Invalid();

void PrintStopTmpBas_All();

void PrintCreateBolusPreset_Idle();
void PrintCreateBolusPreset_Confirm();
void PrintCreateBolusPreset_Invalid();

void PrintRemoveBolusPreset_Idle();
void PrintRemoveBolusPreset_Confirm();
void PrintRemoveBolusPreset_Invalid();

void PrintStartBolus_Idle();
void PrintStartBolus_Calculator();
void PrintStartBolus_Preset();
void PrintStartBolus_Manual();
void PrintStartBolus_Confirm();
void PrintStartBolus_Invalid();

void PrintSettings_DateTime();
void PrintSettings_DateTime_NotAllowed();

void PrintCreateReminder_Idle();
void PrintCreateReminder_Confirm();
void PrintCreateReminder_Invalid();

void PrintRemoveReminder_Idle();
void PrintRemoveReminder_Confirm();

void UpdateScreen();

void DisplayOut(void){
	switch(c_pwrStatus){
	case e_pwrStatus_standby:

		break;

	case e_pwrStatus_post:

		break;

	case e_pwrStatus_ready:
		UpdateScreen();
		//PrintScreen();
		break;

	case e_pwrStatus_offReq:

		break;

	//case e_pwrStatus_error:

		//break;

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
	case CreateBasProf_Invalid:PrintCreateBasProf_Invalid(); break;

	case RemoveBasProf_Idle:PrintRemoveBasProf_Idle(); break;
	case RemoveBasProf_Confirm:PrintRemoveBasProf_Confirm(); break;
	case RemoveBasProf_Invalid:PrintRemoveBasProf_Invalid(); break;

	case StartBasProf_Idle:PrintStartBasProf_Idle(); break;
	case StartBasProf_Confirm:PrintStartBasProf_Confirm(); break;
	case StartBasProf_Invalid:PrintStartBasProf_Invalid(); break;

	case StopBasProf_All:PrintStopBas_All(); break;

	case StartTmpBas_Idle:PrintStartTmpBas_Idle(); break;
	case StartTmpBas_Confirm:PrintStartTmpBas_Confirm(); break;
	case StartTmpBas_Invalid:PrintStartTmpBas_Invalid(); break;

	case StopTmpBas_All:PrintStopTmpBas_All(); break;

	case CreateBolusPreset_Idle:PrintCreateBolusPreset_Idle(); break;
	case CreateBolusPreset_Confirm:PrintCreateBolusPreset_Confirm(); break;
	case CreateBolusPreset_Invalid:PrintCreateBolusPreset_Invalid(); break;

	case RemoveBolusPreset_Idle:PrintRemoveBolusPreset_Idle(); break;
	case RemoveBolusPreset_Confirm:PrintRemoveBolusPreset_Confirm(); break;
	case RemoveBolusPreset_Invalid:PrintRemoveBolusPreset_Invalid(); break;

	case StartBolus_Idle:PrintStartBolus_Idle(); break;
	case StartBolus_Calculator:PrintStartBolus_Calculator(); break;
	case StartBolus_Preset: PrintStartBolus_Preset(); break;
	case StartBolus_Manual: PrintStartBolus_Manual(); break;
	case StartBolus_Confirm: PrintStartBolus_Confirm(); break;
	case StartBolus_Invalid: PrintStartBolus_Invalid(); break;

	case CreateReminder_Idle: PrintCreateReminder_Idle(); break;
	case CreateReminder_Confirm:PrintCreateReminder_Confirm();break;
	case CreateReminder_Invalid:PrintCreateReminder_Invalid();break;

	case RemoveReminder_Idle:PrintRemoveReminder_Idle(); break;
	case RemoveReminder_Confirm: PrintRemoveReminder_Confirm();break;

	case Settings_DateTime: PrintSettings_DateTime(); break;
	case Settings_DateTime_NotAllowed: PrintSettings_DateTime_NotAllowed(); break;


	default: PrintError(); break;
	}
}

void UpdateScreen(){
	switch (c_operation){
	case e_operation_idle:
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
					f_menuChoice = Settings_ClearFlash;
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
					if(BolusIsActive()){
						c_menuScreen = BolusAlreadyActive;
					} else{
						p_selectedMethod = e_bolMethod_calculator;
						m_bloodGlucose = 0;
						m_carbs = 0;
						CopyBolusPreset( &k_emptyBol, &m_bolSelected );
						CopyBolusPreset( &k_emptyBol, &m_bolus );
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

		case Bolus_Manage:
			if (M_backReq){
				c_menuScreen = Bolus;
				f_menuChoice = Bolus_Manage;

			} else if (M_upReq){
				switch (f_menuChoice){
				case Bolus_Manage_Create: f_menuChoice = Bolus_Manage_Remove;break;
				case Bolus_Manage_Remove: f_menuChoice = Bolus_Manage_Create;break;
				default:  break;
				}

			} else if (M_downReq){
				switch (f_menuChoice){
				case Bolus_Manage_Create: f_menuChoice = Bolus_Manage_Remove;break;
				case Bolus_Manage_Remove: f_menuChoice = Bolus_Manage_Create;break;
				default:  break;
				}

			} else if (M_selReq){
				switch (f_menuChoice){
				case Bolus_Manage_Create:
					if(BolusPresetCreationAllowed()){
						CopyBolusPreset( &k_emptyBol, &m_bolus );
					} else{
						c_menuScreen = BolusCreateNotAllowed;
					}
					break;
				case Bolus_Manage_Remove:
					if(BolusPresetExists()){
						LoadPreset( &m_bolSelected, 0 ); // Selects the first available preset.
					} else{
						c_menuScreen = NoBolusPreset;
					}
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
					if( ReminderCreationAllowed() ){
						p_reminder = k_emptyReminder;
						p_reminder.Time = GetCurrentCalendar();
						remindEntryIndex = 0;

					} else{
						c_menuScreen = RemindCreateNotAllowed;
					}
					break;
				case Schedule_Remove:
					if( ReminderRemovalAllowed() ){
						m_reminder = GetReminderFromIndex( 0 );

					} else{
						c_menuScreen = NoRemind;
					}
					break;
				default: break;
				}
			}
			break;

		case Settings:
			if( M_downReq ){
				switch( f_menuChoice ){
				case Settings_ClearFlash: f_menuChoice = Settings_DateTime; break;
				case Settings_DateTime: f_menuChoice = Settings_ClearFlash; break;
				}
			} else if ( M_upReq ){
				switch( f_menuChoice ){
					case Settings_ClearFlash: f_menuChoice = Settings_DateTime; break;
					case Settings_DateTime: f_menuChoice = Settings_ClearFlash; break;
				}
			} else if (M_backReq){
				c_menuScreen = Main;
				f_menuChoice = Settings;

			} else if (M_selReq){
				switch( f_menuChoice ){
				case Settings_ClearFlash:
					InitBasalSet();
					InitBolusSet();
					InitReminderSet();
					break;

				case Settings_DateTime:
					if (BasalIsActive() || BolusIsActive() || TemporaryBasalIsActive())
						c_menuScreen = Settings_DateTime_NotAllowed;
					else {
						p_calendar = GetCurrentCalendar();
						p_calendarIndex = 0;
						c_menuScreen = f_menuChoice;
					}
					break;
				}

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
						basCreateStatus_NameEntered = false;
					} else {
						c_menuScreen=NoBasProf;
					}
					break;
				case Basal_StartTmp:
					CopyTmpBasal(&k_emptyTmp, &m_tmpBas);
					tmpBasal_DurationEntered = false;
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
						basCreateStatus_NameEntered = false;
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
					tmpBasal_DurationEntered = false;
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

		case Settings_DateTime:
			if ( M_upReq ){
				switch ( p_calendarIndex ){
				int value;
				case SEC:
					value = BCDtoInt( p_calendar.Seconds );
					value = (value + 1 ) % 60;
					p_calendar.Seconds = IntToBCD( value );
					break;
				case MIN:
					value = BCDtoInt( p_calendar.Minutes );
					value = (value + 1 ) % 60;
					p_calendar.Minutes = IntToBCD( value );
					break;
				case HR:
					value = BCDtoInt( p_calendar.Hours );
					value = (value + 1 ) % 24;
					p_calendar.Hours = IntToBCD( value );
					break;
				case MON:
					value = BCDtoInt( p_calendar.Month );
					value = value % 12 + 1;
					p_calendar.Month = IntToBCD( value );
					break;
				case DOM:
					value = BCDtoInt( p_calendar.DayOfMonth );
					if (value < 31 ) value++;
					else value = 1;
					p_calendar.DayOfMonth = IntToBCD( value );
					break;
				case YEAR_1:
					value = BCDtoInt( p_calendar.Year >> 8 );
					value = (value + 1 ) % 100;
					p_calendar.Year = (p_calendar.Year & 0x00FF) | (IntToBCD( value ) << 8);
					break;
				case YEAR_2:
					value = BCDtoInt( p_calendar.Year & 0x00FF );
					value = (value + 1 ) % 100;
					p_calendar.Year = ( p_calendar.Year & 0xFF00) | IntToBCD( value );
					break;
				}
				updateScreen = true;

			} else if ( M_downReq ){
				switch ( p_calendarIndex ){
				int value;
				case SEC:
					value = BCDtoInt( p_calendar.Seconds );
					value = (value + 59 ) % 60;
					p_calendar.Seconds = IntToBCD( value );
					break;
				case MIN:
					value = BCDtoInt( p_calendar.Minutes );
					value = (value + 59 ) % 60;
					p_calendar.Minutes = IntToBCD( value );
					break;
				case HR:
					value = BCDtoInt( p_calendar.Hours );
					value = (value + 23 ) % 24;
					p_calendar.Hours = IntToBCD( value );
					break;
				case MON:
					value = BCDtoInt( p_calendar.Month );
					value--;
					if ( value == 0 ) value = 12;
					p_calendar.Month = IntToBCD( value );
					break;
				case DOM:
					value = BCDtoInt( p_calendar.DayOfMonth );
					if (value > 1 ) value--;
					else value = 31;
					p_calendar.DayOfMonth = IntToBCD( value );
					break;
				case YEAR_1:
					value = BCDtoInt( p_calendar.Year >> 8 );
					value = (value + 99 ) % 100;
					p_calendar.Year = (p_calendar.Year & 0x00FF) | (IntToBCD( value ) << 8);
					break;
				case YEAR_2:
					value = BCDtoInt( p_calendar.Year & 0x00FF );
					value = (value + 99 ) % 100;
					p_calendar.Year = ( p_calendar.Year & 0xFF00) | IntToBCD( value );
					break;
				}
				updateScreen = true;

			} else if ( M_rightReq ) {
				p_calendarIndex = (p_calendarIndex + 1) % (YEAR_2 + 1);
				updateScreen = true;

			} else if ( M_leftReq ) {
				if (p_calendarIndex == 0 ) p_calendarIndex = YEAR_2;
				else p_calendarIndex--;
				updateScreen = true;

			} else if ( M_backReq ) {
				c_menuScreen = Settings;
				f_menuChoice = Settings_DateTime;

			} else if ( M_selReq ) {
				if ( CalendarIsValid( p_calendar )){
					SetCalendar( p_calendar );
					updateScreen = true;
				}
			}
			break;
		case Settings_DateTime_NotAllowed:
			if ( M_selReq ){
				c_menuScreen = Settings;
			}
			break;

		default: c_menuScreen = None;
			break;
		}
		break;

	case e_operation_createBasProf:
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
						p_inputProfile.Rate[segmentIndex] += 3600;
					}
					updateScreen = true;

				} else if(M_downReq){
					if (rateIndex == 0){ // Decrement the selected time period if possible.
						if (segments[segmentIndex]>1){
							segments[segmentIndex]--;
							segments[segmentIndex+1]++;
						}
					} else { // Decrement the selected rate down to a lowest of 0.
						if (p_inputProfile.Rate[segmentIndex] >= 3600){
							p_inputProfile.Rate[segmentIndex] -= 3600;
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
						}
						updateScreen = true;
					}

				} else if (M_nextReq){
					basCreateStatus_NameEntered = false;
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

	case e_operation_removeBasProf:
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

	case e_operation_startBasProf:
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

	case e_operation_stopBasProf:
		c_menuScreen = StopBasProf_All;
		break;

	case e_operation_startTmpBas:
		switch (c_tmpStartStatus){
		case e_opStatus_idle:
			c_menuScreen = StartTmpBas_Idle;

			if(tmpBasal_DurationEntered == false){ //Editing tmp basal duration

				if(M_upReq){
					if(m_tmpBas.Duration >= k_maxTmpDuration ) m_tmpBas.Duration = k_minTmpDuration;
					else m_tmpBas.Duration = m_tmpBas.Duration + 60;
					updateScreen = true;
				}
				else if(M_downReq) { // decrement numbers
					if(m_tmpBas.Duration <= k_minTmpDuration) m_tmpBas.Duration = k_maxTmpDuration;
					else m_tmpBas.Duration = m_tmpBas.Duration - 60;
					updateScreen = true;
				}
				else if (M_nextReq || M_rightReq){ // hit next, duration is entered
					tmpBasal_DurationEntered = true;
					updateScreen = true;
				}
				else if (M_selReq){ // hit next, duration is entered
					tmpBasal_DurationEntered = false;
					M_tmpBas = true;
				}

			}
			else {
				if(M_upReq){ // increment numbers
					if(m_tmpBas.Rate >= k_maxTmpRate) m_tmpBas.Rate = k_minTmpRate;
					else m_tmpBas.Rate += 3600;
					updateScreen = true;
				}
				else if(M_downReq) { // decrement numbers
					if(m_tmpBas.Rate <= k_minTmpRate) m_tmpBas.Rate = k_maxTmpRate;
					else m_tmpBas.Rate -= 3600;
					updateScreen = true;
				}
				else if(M_nextReq || M_leftReq){
					tmpBasal_DurationEntered = false;
					updateScreen = true;
				}
				else if (M_selReq){ // hit next, duration is entered
					tmpBasal_DurationEntered = false;
					M_tmpBas = true;
				}
			}
		break;

		case e_opStatus_confirm: c_menuScreen = StartTmpBas_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = StartTmpBas_Invalid; break;
		}
		break;

	case e_operation_stopTmpBas:
		c_menuScreen = StopTmpBas_All;
		break;

	case e_operation_createBolusPreset:
		switch (c_bolCreateStatus){
		case e_opStatus_idle:
			c_menuScreen = CreateBolusPreset_Idle;

			if(bolCreateStatus_NameEntered == false){ // Editing the profile name.
				/** Allow user to enter a preset name **/
				// Initialize the First letter of Profile Name to 'A'
				if( strlen(m_bolus.Name) == 0 ) {
					m_bolus.Name[ 0 ] = 65;
					updateScreen = true;
				}

				int index = strlen( m_bolus.Name ) - 1;
				if (M_upReq){ // Increment current character by one and wrap around the alphabet if needed.
					if (index == 0 && m_bolus.Name[0] == 90) m_bolus.Name[0] = 65; //ASCII 90 = Z, 65 = A
					else if (m_bolus.Name[ index ] == 122) m_bolus.Name[ index ] = 97; //ASCII 122 = z, 97 = a
					else m_bolus.Name[ index ]++;
					updateScreen = true;

				} else if( M_downReq ){ // Decrement current character by one and wrap around the alphabet if needed.
					if (index == 0 && m_bolus.Name[ index ] == 65 ) m_bolus.Name[ index ] = 90;
					else if (m_bolus.Name[ index ] == 97 ) m_bolus.Name[ index ] = 122;
					else m_bolus.Name[ index ]--;
					updateScreen = true;

				} else if( M_rightReq ){ // Go to next character and initialize it to 'a'
					if( index < 10){
						m_bolus.Name[ ++index ] = 97;
						updateScreen = true;
					}

				} else if ( M_leftReq ){ // Go to previous character (if possible) and remove last character.
					if( index > 0 ){
						m_bolus.Name[ index-- ] = 0;
						updateScreen = true;
					}

				} else if ( M_nextReq ){ // Switch to entering Amount
					bolCreateStatus_NameEntered = true;
					updateScreen = true;

				} else if ( M_selReq ){ // Submit Preset
					M_bolus = true;
					updateScreen = true;

					// Reset variables used by this function
					bolCreateStatus_NameEntered = false;
				}

			} else { // Editing Amount

				if ( M_upReq ){
					m_bolus.Amount += 3600;
					updateScreen = true;

				} else if( M_downReq ){
					if (m_bolus.Amount >= 3600){
						m_bolus.Amount -= 3600;
						updateScreen = true;
					}

				} else if ( M_nextReq ){
					bolCreateStatus_NameEntered = false;
					updateScreen = true;

				} else if (M_selReq){
					M_bolus = true;
					updateScreen = true;
					bolCreateStatus_NameEntered = false;
				}
			}
			break;

		case e_opStatus_confirm: c_menuScreen = CreateBolusPreset_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = CreateBolusPreset_Invalid; break;
		}
		break;

	case e_operation_removeBolusPreset:
		switch (c_bolRemStatus){
		case e_opStatus_idle:
			c_menuScreen = RemoveBolusPreset_Idle;
			int presetIndex;
			if (M_downReq){
				presetIndex = GetPresetIndex( &m_bolSelected );
				if(presetIndex == GetNumberOfBolusPresets() - 1 ){
					LoadPreset( &m_bolSelected, 0 );
					updateScreen = true;
				} else {
					presetIndex++;
					LoadPreset( &m_bolSelected, presetIndex );
					updateScreen = true;
				}


			} else if(M_upReq){
				presetIndex = GetPresetIndex( &m_bolSelected );
				if(presetIndex == 0 ){
					LoadPreset( &m_bolSelected, GetNumberOfBolusPresets() - 1 );
					updateScreen = true;
				} else {
					presetIndex--;
					LoadPreset( &m_bolSelected, presetIndex );
					updateScreen = true;
				}


			} else if (M_selReq){
				M_bolSelected = true;
				updateScreen = true;
			}
			break;

		case e_opStatus_confirm: c_menuScreen = RemoveBolusPreset_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = RemoveBolusPreset_Invalid; break;
		}
		break;

	case e_operation_startBolus:
		switch (c_bolStartStatus){
		case e_bolStatus_idle:
			c_menuScreen = StartBolus_Idle;

			if (M_upReq){
				switch( p_selectedMethod ){
				case e_bolMethod_calculator: p_selectedMethod = e_bolMethod_manual; break;
				case e_bolMethod_manual: p_selectedMethod = e_bolMethod_preset; break;
				case e_bolMethod_preset: p_selectedMethod = e_bolMethod_calculator; break;
				}
				updateScreen = true;

			} else if( M_downReq ){
				switch( p_selectedMethod){
				case e_bolMethod_calculator: p_selectedMethod = e_bolMethod_preset; break;
				case e_bolMethod_manual: p_selectedMethod = e_bolMethod_calculator; break;
				case e_bolMethod_preset: p_selectedMethod = e_bolMethod_manual; break;
				}
				updateScreen = true;

			} else if ( M_selReq ){
				M_selectedMethod = p_selectedMethod;
				if (p_selectedMethod == e_bolMethod_preset) LoadPreset( &m_bolSelected, 0 ); // selects first preset.
				else if (p_selectedMethod == e_bolMethod_manual ) {
					CopyBolusPreset( &k_emptyBol, &m_bolus );
					strncpy( m_bolus.Name, "*Manual", 7);
				} else {
					m_carbs = 0;
					m_bloodGlucose = 0;
				}
				updateScreen = true;
			}
			break;

		case e_bolStatus_confirm: c_menuScreen = StartBolus_Confirm; break;
		case e_bolStatus_invalid: c_menuScreen = StartBolus_Invalid; break;
		case e_bolStatus_preset:
			c_menuScreen = StartBolus_Preset;

			if( BolusPresetExists() ){
				int presetIndex;
				if (M_downReq){
					presetIndex = GetPresetIndex( &m_bolSelected );
					if(presetIndex == GetNumberOfBolusPresets() - 1 ){
						LoadPreset( &m_bolSelected, 0 );
						updateScreen = true;
					} else {
						presetIndex++;
						LoadPreset( &m_bolSelected, presetIndex );
						updateScreen = true;
					}


				} else if(M_upReq){
					presetIndex = GetPresetIndex( &m_bolSelected );
					if(presetIndex == 0 ){
						LoadPreset( &m_bolSelected, GetNumberOfBolusPresets() - 1 );
						updateScreen = true;
					} else {
						presetIndex--;
						LoadPreset( &m_bolSelected, presetIndex );
						updateScreen = true;
					}


				} else if (M_selReq){
					M_bolSelected = true;
					updateScreen = true;
				}
			}
			break;

		case e_bolStatus_calculator:
			c_menuScreen = StartBolus_Calculator;

			if(bolStartCalc_CarbsEntered == false){
				if(M_upReq){
					m_carbs++;
					updateScreen = true;
				}
				else if(M_downReq) {
					if( m_carbs > 0 ){
						m_carbs--;
						updateScreen = true;
					}
				}
				else if (M_rightReq){
					bolStartCalc_CarbsEntered = true;
					updateScreen = true;
				}
				else if (M_selReq){
					bolStartCalc_CarbsEntered = false;
					M_carbs = true;
					M_bloodGlucose = true;
				}
			}
			else {
				if(M_upReq){
					m_bloodGlucose++;
					updateScreen = true;
				}
				else if(M_downReq) {
					if( m_bloodGlucose > 0 ){
						m_bloodGlucose--;
						updateScreen = true;
					}
				}
				else if (M_leftReq){
					bolStartCalc_CarbsEntered = false;
					updateScreen = true;
				}
				else if (M_selReq){
					bolStartCalc_CarbsEntered = false;
					M_carbs = true;
					M_bloodGlucose = true;
				}
			}
			break;

		case e_bolStatus_manual:
			c_menuScreen = StartBolus_Manual;

			if( M_upReq ){
				m_bolus.Amount += 3600;
				updateScreen = true;

			} else if( M_downReq ) {
				if( m_bolus.Amount >= 3600 ){
					m_bolus.Amount -= 3600;
					updateScreen = true;
				}
			}
			else if ( M_selReq ){
				M_bolus = true;
			}

			break;

		default: break;

		}
		break;

	case e_operation_createReminder:
		switch (c_remindCreateStatus){
		case e_opStatus_idle:
			c_menuScreen = CreateReminder_Idle;

			if ( M_selReq ){ // Submit Preset
				M_reminder = true;
				CopyReminder( &p_reminder, &m_reminder );
				updateScreen = true;

				// Reset variables used by this function
				remindEntryIndex = 0;
				p_remindSubIndex = HR;
			}

			if ( remindEntryIndex == NAME ){
				/** Allow user to enter a reminder name **/
				// Initialize the First letter of Name to 'A'
				if( strlen( p_reminder.Name ) == 0 ) {
					p_reminder.Name[ 0 ] = 65;
					updateScreen = true;
				}

				int index = strlen( p_reminder.Name ) - 1;
				if ( M_upReq ){ // Increment current character by one and wrap around the alphabet if needed.
					if (index == 0 && p_reminder.Name[0] == 90) p_reminder.Name[0] = 65; //ASCII 90 = Z, 65 = A
					else if (p_reminder.Name[ index ] == 122) p_reminder.Name[ index ] = 97; //ASCII 122 = z, 97 = a
					else p_reminder.Name[ index ]++;
					updateScreen = true;

				} else if( M_downReq ){ // Decrement current character by one and wrap around the alphabet if needed.
					if (index == 0 && p_reminder.Name[ index ] == 65 ) p_reminder.Name[ index ] = 90;
					else if ( p_reminder.Name[ index ] == 97 ) p_reminder.Name[ index ] = 122;
					else p_reminder.Name[ index ]--;
					updateScreen = true;

				} else if( M_rightReq ){ // Go to next character and initialize it to 'a'
					if( index < k_remindNameLength - 1){
						p_reminder.Name[ ++index ] = 97;
						updateScreen = true;
					}

				} else if ( M_leftReq ){ // Go to previous character (if possible) and remove last character.
					if( index > 0 ){
						p_reminder.Name[ index-- ] = 0;
						updateScreen = true;
					}

				} else if ( M_nextReq ){ // Switch to entering Amount
					remindEntryIndex++;
					updateScreen = true;
				}
			} else if ( remindEntryIndex == DATETIME ){
				if ( M_upReq ){
					switch ( p_remindSubIndex ){
					int value;
					//case SEC:
					//	value = BCDtoInt( p_reminder.Time.Seconds );
					//	value = (value + 1 ) % 60;
					//	p_reminder.Time.Seconds = IntToBCD( value );
					//	break;
					case MIN:
						value = BCDtoInt( p_reminder.Time.Minutes );
						value = (value + 1 ) % 60;
						p_reminder.Time.Minutes = IntToBCD( value );
						break;
					case HR:
						value = BCDtoInt( p_reminder.Time.Hours );
						value = (value + 1 ) % 24;
						p_reminder.Time.Hours = IntToBCD( value );
						break;
					case MON:
						value = BCDtoInt( p_reminder.Time.Month );
						value = (value) % 12 + 1;
						p_reminder.Time.Month = IntToBCD( value );
						break;
					case DOM:
						value = BCDtoInt( p_reminder.Time.DayOfMonth );
						if (value < 31 ) value++;
						else value = 1;
						p_reminder.Time.DayOfMonth = IntToBCD( value );
						break;
					case YEAR_1:
						value = BCDtoInt(p_reminder.Time.Year >> 8 );
						value = (value + 1 ) % 100;
						p_reminder.Time.Year = (p_reminder.Time.Year & 0x00FF) | (IntToBCD( value ) << 8);
						break;
					case YEAR_2:
						value = BCDtoInt( p_reminder.Time.Year & 0x00FF );
						value = (value + 1 ) % 100;
						p_reminder.Time.Year = ( p_reminder.Time.Year & 0xFF00) | IntToBCD( value );
						break;
					}
					updateScreen = true;

				} else if ( M_downReq ){
					switch ( p_remindSubIndex ){
					int value;
					//case SEC:
					//	value = BCDtoInt( p_reminder.Time.Seconds );
					//	value = (value + 59 ) % 60;
					//	p_reminder.Time.Seconds = IntToBCD( value );
					//	break;
					case MIN:
						value = BCDtoInt( p_reminder.Time.Minutes );
						value = (value + 59 ) % 60;
						p_reminder.Time.Minutes = IntToBCD( value );
						break;
					case HR:
						value = BCDtoInt( p_reminder.Time.Hours );
						value = (value + 23 ) % 24;
						p_reminder.Time.Hours = IntToBCD( value );
						break;
					case MON:
						value = BCDtoInt( p_reminder.Time.Month );
						value--;
						if ( value == 0 ) value = 12;
						p_reminder.Time.Month = IntToBCD( value );
						break;
					case DOM:
						value = BCDtoInt( p_reminder.Time.DayOfMonth );
						if (value > 1 ) value--;
						else value = 31;
						p_reminder.Time.DayOfMonth = IntToBCD( value );
						break;
					case YEAR_1:
						value = BCDtoInt( p_reminder.Time.Year >> 8 );
						value = (value + 99 ) % 100;
						p_reminder.Time.Year = (p_reminder.Time.Year & 0x00FF) | (IntToBCD( value ) << 8);
						break;
					case YEAR_2:
						value = BCDtoInt( p_reminder.Time.Year & 0x00FF );
						value = (value + 99 ) % 100;
						p_reminder.Time.Year = ( p_reminder.Time.Year & 0xFF00) | IntToBCD( value );
						break;
					}
					updateScreen = true;

				} else if ( M_rightReq ) {
					if ( p_remindSubIndex == MIN ) p_remindSubIndex = DOM;
					else if ( p_remindSubIndex == YEAR_2 ){
						remindEntryIndex = FREQ;
					} else {
						p_remindSubIndex++;
					}
					updateScreen = true;

				} else if ( M_leftReq ) {
					if ( p_remindSubIndex == DOM ) p_remindSubIndex = MIN;
					else if (p_remindSubIndex == HR ) remindEntryIndex = NAME;
					else p_remindSubIndex--;
					updateScreen = true;

				}

			} else if ( remindEntryIndex == FREQ ){
				if ( M_downReq ){
					switch ( p_reminder.Frequency ){
					case e_remindFreq_oneTime: p_reminder.Frequency = e_remindFreq_daily; break;
					case e_remindFreq_daily: p_reminder.Frequency = e_remindFreq_weekly; break;
					case e_remindFreq_weekly: p_reminder.Frequency = e_remindFreq_weekdays; break;
					case e_remindFreq_weekdays: p_reminder.Frequency = e_remindFreq_weekends; break;
					case e_remindFreq_weekends: p_reminder.Frequency = e_remindFreq_oneTime; break;
					default: break;
					}
					updateScreen = true;
				} else if ( M_upReq ){
					switch ( p_reminder.Frequency ){
					case e_remindFreq_oneTime: p_reminder.Frequency = e_remindFreq_weekends; break;
					case e_remindFreq_daily: p_reminder.Frequency = e_remindFreq_oneTime; break;
					case e_remindFreq_weekly: p_reminder.Frequency = e_remindFreq_daily; break;
					case e_remindFreq_weekdays: p_reminder.Frequency = e_remindFreq_weekly; break;
					case e_remindFreq_weekends: p_reminder.Frequency = e_remindFreq_weekly; break;
					default: break;
					}
					updateScreen = true;
				} else if ( M_rightReq ) {
					remindEntryIndex = MSG;
					updateScreen = true;

				} else if ( M_leftReq ) {
					remindEntryIndex = DATETIME;
					updateScreen = true;

				}
			} else if ( remindEntryIndex == MSG ){
				/** Allow user to enter a reminder message **/
				// Initialize the First letter of Name to 'A'
				if( strlen( p_reminder.Message ) == 0 ) {
					p_reminder.Message[ 0 ] = 65;
					updateScreen = true;
				}

				int index = strlen( p_reminder.Message ) - 1;
				if ( M_upReq ){ // Increment current character by one and wrap around the alphabet if needed.
					if (index == 0 && p_reminder.Message[0] == 90) p_reminder.Message[0] = 65; //ASCII 90 = Z, 65 = A
					else if (p_reminder.Message[ index ] == 122) p_reminder.Message[ index ] = 32; //ASCII 122 = z, 97 = a, 32 = space
					else if (p_reminder.Message[index ] == 32 ) p_reminder.Message[ index ] = 97;
					else p_reminder.Message[ index ]++;
					updateScreen = true;

				} else if( M_downReq ){ // Decrement current character by one and wrap around the alphabet if needed.
					if (index == 0 && p_reminder.Message[ index ] == 65 ) p_reminder.Message[ index ] = 90;
					else if ( p_reminder.Message[ index ] == 97 ) p_reminder.Message[ index ] = 32;
					else if ( p_reminder.Message[index ] == 32 ) p_reminder.Message[ index ] = 122;
					else p_reminder.Message[ index ]--;
					updateScreen = true;

				} else if( M_rightReq ){ // Go to next character and initialize it to ' '
					if( index < k_remindMessageLength - 1){
						p_reminder.Message[ ++index ] = 32;
						updateScreen = true;
					}

				} else if ( M_leftReq ){ // Go to previous character (if possible) and remove last character.
					if( index > 0 ){
						p_reminder.Message[ index-- ] = 0;
						updateScreen = true;
					}

				} else if ( M_nextReq ){ // Switch to entering Amount
					remindEntryIndex = FREQ;
					updateScreen = true;

				}
			} else {
				remindEntryIndex = NAME;
			}

			break;
		case e_opStatus_confirm: c_menuScreen = CreateReminder_Confirm; break;
		case e_opStatus_invalid: c_menuScreen = CreateReminder_Invalid; break;
		}
		break;

	case e_operation_removeReminder:
		switch (c_remindRemStatus){
		case e_opStatus_idle:
			c_menuScreen = RemoveReminder_Idle;
			int reminderIndex;
			if ( M_downReq ){
				reminderIndex = GetReminderIndex( &m_reminder );
				if( reminderIndex == GetNumberOfReminders() - 1 ){
					m_reminder = GetReminderFromIndex ( 0 );
					updateScreen = true;
				} else {
					reminderIndex++;
					m_reminder = GetReminderFromIndex ( reminderIndex );
					updateScreen = true;
				}


			} else if(M_upReq){
				reminderIndex = GetReminderIndex( &m_reminder );
				if( reminderIndex == 0 ){
					m_reminder = GetReminderFromIndex ( GetNumberOfReminders() - 1 );
					updateScreen = true;
				} else {
					reminderIndex--;
					m_reminder = GetReminderFromIndex ( reminderIndex );
					updateScreen = true;
				}


			} else if ( M_selReq ){
				M_reminder = true;
				updateScreen = true;
			}
			break;

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
	char outString[32];
	unsigned char text_start = 18;

	// Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Create Preset", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Remove Preset", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);


	// Highlight selected item
	switch (f_menuChoice) {
	case Bolus_Manage_Create:
		text_start = 18;
		strcpy(outString, "Create Preset");
		break;
	case Bolus_Manage_Remove:
		text_start = 31;
		strcpy(outString, "Remove Preset");
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
void PrintBolus(){
	char outString[32];
	unsigned char text_start = 18;

	// Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Start Bolus", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Manage Presets", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);


	// Highlight selected item
	switch (f_menuChoice) {
	case Bolus_Start:
		text_start = 18;
		strcpy(outString, "Start Bolus");
		break;
	case Bolus_Manage:
		text_start = 31;
		strcpy(outString, "Manage Presets");
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
void PrintBolusAlreadyActive(){
	 // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");

	// Menu options
	GrStringDrawCentered(&g_sContext, "A bolus", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "is already ", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "in progress", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

	GrFlush(&g_sContext);
}
void PrintBolusCreateNotAllowed(){
	 // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");

	// Menu options
	GrStringDrawCentered(&g_sContext, "Bolus Preset", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Creation", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "not Allowed", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

	GrFlush(&g_sContext);
}
void PrintError(){
	;
}
void PrintNoBolusPreset(){
	 // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");

	// Menu options
	GrStringDrawCentered(&g_sContext, "No Bolus", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Presets", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Available", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

	GrFlush(&g_sContext);
}
void PrintNoRemind(){
	GrStringDrawCentered(&g_sContext, "No Reminder" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Exists" , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);
	//GrStringDrawCentered(&g_sContext, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("BACK");

	GrFlush(&g_sContext);
}

void PrintRemindCreateNotAllowed(){
	GrStringDrawCentered(&g_sContext, "Reminder" , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Creation" , AUTO_STRING_LENGTH, 46, 40, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Not Allowed" , AUTO_STRING_LENGTH, 46, 50, OPAQUE_TEXT);
	//GrStringDrawCentered(&g_sContext, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("BACK");

	GrFlush(&g_sContext);
}

void PrintSchedule(){
	char outString[32] = "";
	unsigned char text_start = 18;

	// Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Create Reminder", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Remove Reminder", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);


	// Highlight selected item
	switch (f_menuChoice) {
	case Schedule_Create:
		text_start = 18;
		strcpy(outString, "Create Reminder");
		break;
	case Schedule_Remove:
		text_start = 31;
		strcpy(outString, "Remove Reminder");
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

void PrintSettings(){
	char outString[32] = "";
	unsigned char text_start = 18;

	// Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");

	ShowDay();

	// Menu options
	GrStringDraw(&g_sContext, "Clear Flash", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Edit Calendar", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);


	// Highlight selected item
	switch (f_menuChoice) {
	case Settings_ClearFlash:
		text_start = 18;
		strcpy(outString, "Clear Flash");
		break;
	case Settings_DateTime:
		text_start = 31;
		strcpy(outString, "Edit Calendar");
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

		rateDigs = UnsignedInt_To_ASCII(p_profile->Rate[i] / 3600, rateBuffer);
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

	rateDigs = UnsignedInt_To_ASCII(p_profile->Rate[i] / 3600, rateBuffer);
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


void PrintCreateBasProf_Invalid(){

	GrStringDrawCentered(&g_sContext, "Invalid Profile" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	//GrStringDrawCentered(&g_sContext, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	//LoadMiddleButton("OK");
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
	if (basCreateStatus_NameEntered == false){
		LoadRightButton("RATE");
		LoadMiddleButton("DONE");
	}
	else {
		LoadRightButton("NAME");
		LoadMiddleButton("DONE");
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
	char buffer[10] = "";
	char outString[32] = "";
	int digits;

	// Print basal status
	if (TemporaryBasalIsActive()){
		UnsignedInt_To_ASCII(f_activeTmpBasal.Rate / 3600, outString);
		strncat(outString, " IU/hr", 6);

		GrStringDraw(&g_sContext, "Temporary Basal:" , AUTO_STRING_LENGTH, 5, 25, OPAQUE_TEXT);
		GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 15, 35, OPAQUE_TEXT);

		// Draw duration in hours and minutes
		// get hours
		memset(outString, 0, sizeof(outString));
		digits = UnsignedInt_To_ASCII(f_activeTmpBasal.Duration / 60, buffer);
		strncpy(outString, buffer, digits);
		strncat(outString, ":", 1);

		// get minutes
		digits = UnsignedInt_To_ASCII(f_activeTmpBasal.Duration % 60, buffer);
		if (digits == 1) strncat(outString, "0", 1);
		strncat(outString, buffer, digits);

		strncat(outString, " Remain", 7);

		GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 15, 45, OPAQUE_TEXT);


	} else if(BasalIsActive()){
		int currentHour = GetCurrentHour();
		currentHour = BCDtoInt( currentHour );

		int currentMin = GetCurrentMin();
		currentMin = BCDtoInt( currentMin );

		int currentSegment = ( k_segDay / 24 ) * currentHour;
		currentSegment = currentSegment + ( currentMin / (60/(k_segDay/24)));

		UnsignedInt_To_ASCII(f_activeBasal.Rate[ currentSegment ] / 3600, outString);
		strncat(outString, " IU/hr", 6);

		GrStringDraw(&g_sContext, "Basal:" , AUTO_STRING_LENGTH, 5, 25, OPAQUE_TEXT);
		GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 15, 35, OPAQUE_TEXT);

	} else {
		// Clear previous entries from screen
		GrContextForegroundSet(&g_sContext, ClrWhite);
		GrStringDraw(&g_sContext, "XXXXXXXXXXXXXXXX" , AUTO_STRING_LENGTH, 5, 25, OPAQUE_TEXT);
		GrStringDraw(&g_sContext, "XXXXXXXXXXXXXX" , AUTO_STRING_LENGTH, 15, 35, OPAQUE_TEXT);
		GrStringDraw(&g_sContext, "XXXXXXXXXXXXXX" , AUTO_STRING_LENGTH, 15, 45, OPAQUE_TEXT);
		GrContextForegroundSet(&g_sContext, ClrBlack);

		GrStringDraw(&g_sContext, "No Basal" , AUTO_STRING_LENGTH, 5, 25, OPAQUE_TEXT);
	}

	// Print bolus status
	if(BolusIsActive()){

		UnsignedInt_To_ASCII(f_activeBolus.Amount / 3600, outString);

		UnsignedInt_To_ASCII(( f_activeBolus.Amount % 3600 ) / 360, buffer);
		strncat(outString, ".", 1);
		strncat(outString, buffer, 1);
		strncat(outString, " IU Remain", 10);

		GrStringDraw(&g_sContext, "Bolus: " , AUTO_STRING_LENGTH, 5, 55, OPAQUE_TEXT);
		GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 15, 65, OPAQUE_TEXT);

	} else {
		// Clear previous entries from screen
		GrContextForegroundSet(&g_sContext, ClrWhite);
		GrStringDraw(&g_sContext, "XXXXXXXXXXXXXX" , AUTO_STRING_LENGTH, 15, 65, OPAQUE_TEXT);
		GrContextForegroundSet(&g_sContext, ClrBlack);


		GrStringDraw(&g_sContext, "No Bolus" , AUTO_STRING_LENGTH, 5, 55, OPAQUE_TEXT);
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

	int hour = GetCurrentHour();
	int min = GetCurrentMin();
	int sec = GetCurrentSec();

	int digits = 0;
	char buffer[10] = "";
    char outString[10] = "";

    // Get Hours
	digits = UnsignedInt_To_ASCII( hour >> 4, buffer ); // Read upper half of byte by bitshifting four places
	strncpy(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( hour & 0xF, buffer ); // Read lower half of byte by overwriting the upper half with 0s
	strncat(outString, buffer, digits);
	strncat(outString, ":", 1);

	// Get Minutes
	digits = UnsignedInt_To_ASCII( min >> 4, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( min & 0xF, buffer );
	strncat(outString, buffer, digits);
	//strncat(outString, ":", 1);

	// Get Seconds
	//digits = UnsignedInt_To_ASCII( sec >> 4, buffer );
	//strncat(outString, buffer, digits);
	//digits = UnsignedInt_To_ASCII( sec & 0xF, buffer );
	//strncat(outString, buffer, digits);


	// Draw top banner
	GrRectFill(&g_sContext, &myRectangleTopBan);
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDrawCentered(&g_sContext, outString, AUTO_STRING_LENGTH, 75 , 7, TRANSPARENT_TEXT);
	//GrStringDrawCentered(&g_sContext, "bat%", AUTO_STRING_LENGTH, 15, 7, TRANSPARENT_TEXT);
	//GrStringDrawCentered(&g_sContext, "res%", AUTO_STRING_LENGTH, 48, 7, TRANSPARENT_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);





	// Get basal and bolus rate
	strcpy(outString, "");
	digits = UnsignedInt_To_ASCII( f_basalOut, buffer );
	strncat(outString, buffer, digits);
	strncat(outString, "/", 1);
	digits = UnsignedInt_To_ASCII( f_bolusOut, buffer );
	strncat(outString, buffer, digits);
	//strncat(outString, ":", 1);

	// Draw top banner
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDrawCentered(&g_sContext, outString, AUTO_STRING_LENGTH, 20 , 7, TRANSPARENT_TEXT);
	//GrStringDrawCentered(&g_sContext, "bat%", AUTO_STRING_LENGTH, 15, 7, TRANSPARENT_TEXT);
	//GrStringDrawCentered(&g_sContext, "res%", AUTO_STRING_LENGTH, 48, 7, TRANSPARENT_TEXT);
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

void PrintStopTmpBas_All(){
	GrStringDrawCentered(&g_sContext, "Stop" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Temporary" , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Basal?" , AUTO_STRING_LENGTH, 46, 40, OPAQUE_TEXT);

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
			LoadRightButton("RATE");
			cursorY = 38;
			cursorX = 65;

			if (m_tmpBas.Duration / 60 <= 9)
				cursorW = 4;
			else if (m_tmpBas.Duration / 60 > 9)
				cursorW = 10;
		}
		else {
			LoadRightButton("DUR");
			cursorY = 48;
			cursorX = 65;
			if(m_tmpBas.Rate / 3600 <= 9)
				cursorW = 4;
			else if (m_tmpBas.Rate / 3600 > 9)
				cursorW = 10;
		}

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	GrStringDraw(&g_sContext, "Temporary Basal" , AUTO_STRING_LENGTH, 5, 20, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Duration / 60, buffer);
	strcpy(outString, "Duration: ");
	strncat(outString, buffer, digits);


	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 30, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Rate / 3600, buffer);
	strcpy(outString, "Rate:     ");
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 40, OPAQUE_TEXT);

	GrLineDrawH(&g_sContext, cursorX, cursorX+cursorW, cursorY);

	LoadLeftButton("CANC");
	LoadMiddleButton("DONE");

	GrFlush(&g_sContext);

}

void PrintStartTmpBas_Confirm(){
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	GrStringDrawCentered(&g_sContext, "Start Temporary", AUTO_STRING_LENGTH, 47, 19, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Basal?", AUTO_STRING_LENGTH, 47, 29, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Duration / 60, buffer);
	strcpy(outString, "Duration: ");
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 39, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Rate / 3600, buffer);
	strcpy(outString, "Rate: ");
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 49, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintStartTmpBas_Invalid(){

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	GrStringDrawCentered(&g_sContext, "Temporary", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Basal", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Invalid", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintCreateBolusPreset_Idle(){

	// Clear previous entries from screen
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	// Draw name header and user entered name
	GrStringDraw(&g_sContext, "Preset Name:" , AUTO_STRING_LENGTH, 5, 16, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, m_bolus.Name , AUTO_STRING_LENGTH, 5, 26, OPAQUE_TEXT);

	// Draw Amount header and user entered amount
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;
	digits = UnsignedInt_To_ASCII(m_bolus.Amount / 3600, buffer);
	strcpy(outString, "Amount: ");
	strncat(outString, buffer, digits);
	strncat(outString, " IU", 3);
	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, 43, OPAQUE_TEXT);

	// Draw Cursor
	int cursorY, cursorX, cursorW;
	if (bolCreateStatus_NameEntered == false){
		cursorY = 35; // y location
		cursorW = 4; // width
		cursorX = (6 * strlen(m_bolus.Name)) - 1; // x location is under last entered letter
	}
	else {
		cursorY = 51;
		cursorX = 53;
		cursorW = digits * 5;
	}
	GrLineDrawH(&g_sContext, cursorX, cursorX+cursorW, cursorY);

	// Draw Buttons
	LoadLeftButton("CANC");
	LoadMiddleButton("DONE");
	if (bolCreateStatus_NameEntered == false) LoadRightButton("AMNT");
	else LoadRightButton("NAME");

	// Flush to screen
	GrFlush(&g_sContext);
}

void PrintCreateBolusPreset_Confirm(){
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	GrStringDrawCentered(&g_sContext, "Save Bolus", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Preset?", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT);

	GrStringDraw(&g_sContext, "Name: " , AUTO_STRING_LENGTH, 5, 40, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, m_bolus.Name, AUTO_STRING_LENGTH, 15, 50, OPAQUE_TEXT);


	digits = UnsignedInt_To_ASCII(m_bolus.Amount / 3600, buffer);
	strcpy(outString, "Amount: ");
	strncat(outString, buffer, digits);
	strncat(outString, " IU", 3);
	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 65, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}
void PrintCreateBolusPreset_Invalid(){
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	GrStringDrawCentered(&g_sContext, "Bolus", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Preset", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Invalid", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintRemoveBolusPreset_Idle(){
	int numberOfPresets = GetNumberOfBolusPresets();

	// Get names of saved presets and draw them
	y_bolusName *Name;
	Name = (y_bolusName *) malloc( sizeof( y_bolusName ));

	int i;
	for ( i = 0; i < numberOfPresets; i++ ){
		GetPresetName( Name, i );
		GrStringDraw( &g_sContext, *Name, AUTO_STRING_LENGTH, 5, 16 + ( 10 * i ), OPAQUE_TEXT );
	}
	free(Name);

	// highlight the selected profile
	unsigned char text_start = 18;
	int index = GetPresetIndex( &m_bolSelected );
	text_start = 16 + 10 * index;

	GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
	GrContextBackgroundSet(&g_sContext, ClrBlack); //ClrWhite      this affects the text color in the highlight
	GrStringDraw(&g_sContext, m_bolSelected.Name, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

	LoadLeftButton( "CANC" );
	LoadMiddleButton( "SEL" );
	GrFlush(&g_sContext);
}

void PrintRemoveBolusPreset_Confirm(){
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	GrStringDrawCentered(&g_sContext, "Remove Bolus", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Preset?", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT);

	GrStringDraw(&g_sContext, "Name: " , AUTO_STRING_LENGTH, 5, 40, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, m_bolSelected.Name, AUTO_STRING_LENGTH, 15, 50, OPAQUE_TEXT);


	digits = UnsignedInt_To_ASCII(m_bolSelected.Amount, buffer);
	strcpy(outString, "Amount: ");
	strncat(outString, buffer, digits);
	strncat(outString, " IU", 3);
	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 65, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintRemoveBolusPreset_Invalid(){
	GrStringDrawCentered(&g_sContext, "Selected", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Preset", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "is Active", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintStartBolus_Idle(){
	char outString[32];
	unsigned char text_start = 18;


	// Draw top and bottom banner and buttons
	LoadLeftButton("CANC");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Calculator", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Preset", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Manual", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);

	// Highlight selected item
	switch ( p_selectedMethod ) {
	case e_bolMethod_calculator:
		text_start = 18;
		strcpy(outString, "Calculator");
		break;
	case e_bolMethod_preset:
		text_start = 31;
		strcpy(outString, "Preset");
		break;
	case e_bolMethod_manual:
		text_start = 44;
		strcpy(outString, "Manual");
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

void PrintStartBolus_Calculator(){
	// Clear previous entries from screen
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	// Print header
	GrStringDrawCentered(&g_sContext, "Use < > arrows", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "to select input", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT);

	// Draw carbs header and user entered carbs
	char buffer[10] = "";
	char outString[32] = "";
	int digitsCarb = 0;
	digitsCarb = UnsignedInt_To_ASCII(m_carbs, buffer);
	strcpy(outString, "Carb: ");
	strncat(outString, buffer, digitsCarb);
	strncat(outString, " g", 2);
	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, 45, OPAQUE_TEXT);


	// Draw glucose header and user entered glucose
	int digitsGluc = 0;
	digitsGluc = UnsignedInt_To_ASCII(m_bloodGlucose, buffer);
	strcpy(outString, "BG: ");
	strncat(outString, buffer, digitsGluc);
	strncat(outString, " mmol/L", 7);
	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, 58, OPAQUE_TEXT);

	// Draw Cursor
	int cursorY, cursorX, cursorW;
	if (bolStartCalc_CarbsEntered == false){
		cursorY = 53; // y location
		cursorW = digitsCarb * 5;; // width
		cursorX = 41; // x location is under last entered letter
	}
	else {
		cursorY = 66;
		cursorX = 29;
		cursorW = digitsGluc * 5;
	}
	GrLineDrawH(&g_sContext, cursorX, cursorX+cursorW, cursorY);

	// Draw Buttons
	LoadLeftButton("CANC");
	LoadMiddleButton("DONE");
	LoadRightButton("RETY");


	// Flush to screen
	GrFlush(&g_sContext);
}

void PrintStartBolus_Preset(){
	if( BolusPresetExists() ){
		int numberOfPresets = GetNumberOfBolusPresets();

		// Get names of saved presets and draw them
		y_bolusName *Name;
		Name = (y_bolusName *) malloc( sizeof( y_bolusName ));

		int i;
		for ( i = 0; i < numberOfPresets; i++ ){
			GetPresetName( Name, i );
			GrStringDraw( &g_sContext, *Name, AUTO_STRING_LENGTH, 5, 16 + ( 10 * i ), OPAQUE_TEXT );
		}
		free(Name);

		// highlight the selected profile
		unsigned char text_start = 18;
		int index = GetPresetIndex( &m_bolSelected );
		text_start = 16 + 10 * index;

		GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
		GrContextBackgroundSet(&g_sContext, ClrBlack); //ClrWhite      this affects the text color in the highlight
		GrStringDraw(&g_sContext, m_bolSelected.Name, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
		GrContextForegroundSet(&g_sContext, ClrBlack);
		GrContextBackgroundSet(&g_sContext, ClrWhite);

		LoadMiddleButton( "SEL" );

	} else {
		GrStringDrawCentered(&g_sContext, "No Presets", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT);
		GrStringDrawCentered(&g_sContext, "Available", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT);
	}

	LoadLeftButton( "CANC" );
	LoadRightButton( "RETY" );

	GrFlush(&g_sContext);
}

void PrintStartBolus_Manual(){
	// Clear previous entries from screen
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	// Draw Header
	GrStringDrawCentered(&g_sContext, "Enter Bolus", AUTO_STRING_LENGTH, 47, 21, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Amount", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);


	// Draw  header and user entered amount
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;
	digits = UnsignedInt_To_ASCII(m_bolus.Amount / 3600, buffer);

	strcpy(outString, "Amount: ");
	strncat(outString, buffer, digits);
	strncat(outString, " IU", 3);
	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, 45, OPAQUE_TEXT);


	// Draw Cursor
	int cursorY, cursorX, cursorW;
	cursorY = 53; // y location
	cursorW = digits * 5;; // width
	cursorX = 53; // x location is under last entered letter
	GrLineDrawH(&g_sContext, cursorX, cursorX+cursorW, cursorY);

	// Draw Buttons
	LoadLeftButton("CANC");
	LoadMiddleButton("DONE");
	LoadRightButton("RETY");


	// Flush to screen
	GrFlush(&g_sContext);
}

void PrintStartBolus_Confirm(){
	// Draw Header
	GrStringDrawCentered(&g_sContext, "Activate Bolus?", AUTO_STRING_LENGTH, 47, 21, OPAQUE_TEXT);

	// Get names of saved presets and draw them
	y_bolus *bolus;
	bolus = (y_bolus *) malloc( sizeof( y_bolus ));

	// Get the bolus to activate
	BolusToActivate( bolus );

	// Draw bolus name
	GrStringDraw(&g_sContext, "Name: " , AUTO_STRING_LENGTH, 5, 37, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, bolus->Name, AUTO_STRING_LENGTH, 15, 47, OPAQUE_TEXT);

	// Draw bolus amount
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;
	digits = UnsignedInt_To_ASCII(bolus->Amount / 3600, buffer);

	strcpy(outString, "Amount: ");
	strncat(outString, buffer, digits);
	strncat(outString, " IU", 3);
	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5, 60, OPAQUE_TEXT);

	free( bolus );

	// Draw Buttons
	LoadLeftButton("CANC");
	LoadMiddleButton("DONE");
	LoadRightButton("RETY");


	// Flush to screen
	GrFlush(&g_sContext);
}

void PrintStartBolus_Invalid(){
	GrStringDrawCentered(&g_sContext, "Provided", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Bolus is", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Invalid", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void  PrintSettings_DateTime(){
	// Clear previous entries from screen
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	int digits = 0, domDigits = 0;
	char buffer[10] = "";
	char outString[32] = "";

	/* DRAW TIME */
	strcpy( outString, "Time: " );

	// Get Hours
	digits = UnsignedInt_To_ASCII( p_calendar.Hours >> 4, buffer ); // Read upper half of byte by bitshifting four places
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_calendar.Hours & 0xF, buffer ); // Read lower half of byte by overwriting the upper half with 0s
	strncat(outString, buffer, digits);
	strncat(outString, ":", 1);

	// Get Minutes
	digits = UnsignedInt_To_ASCII( p_calendar.Minutes >> 4, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_calendar.Minutes & 0xF, buffer );
	strncat(outString, buffer, digits);
	strncat(outString, ":", 1);

	// Get Seconds
	digits = UnsignedInt_To_ASCII( p_calendar.Seconds >> 4, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_calendar.Seconds & 0xF, buffer );
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5 , 40, TRANSPARENT_TEXT);


	/* DRAW DATE */
	strcpy( outString, "Dt: " );

	// Get Day of month
	domDigits = UnsignedInt_To_ASCII( BCDtoInt( p_calendar.DayOfMonth ), buffer ); // Read upper half of byte by bitshifting four places
	strncat(outString, buffer, domDigits);

	// Get Month
	switch ( BCDtoInt( p_calendar.Month ) ){
	case 1: strncat(outString, " Jan ", 5); break;
	case 2: strncat(outString, " Feb ", 5); break;
	case 3: strncat(outString, " Mar ", 5); break;
	case 4: strncat(outString, " Apr ", 5); break;
	case 5: strncat(outString, " May ", 5); break;
	case 6: strncat(outString, " Jun ", 5); break;
	case 7: strncat(outString, " Jul ", 5); break;
	case 8: strncat(outString, " Aug ", 5); break;
	case 9: strncat(outString, " Sep ", 5); break;
	case 10: strncat(outString, " Oct ", 5); break;
	case 11:strncat(outString, " Nov ", 5); break;
	case 12:strncat(outString, " Dec ", 5); break;
	default: break;
	}

	// Get Year
	digits = UnsignedInt_To_ASCII( p_calendar.Year >> 12, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_calendar.Year >> 8 & 0xF, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_calendar.Year >> 4 & 0xF, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_calendar.Year & 0xF, buffer );
	strncat(outString, buffer, digits);



	/* Draw Cursor */
	int cursorY, cursorX, cursorW;
	switch ( p_calendarIndex ){
	case SEC: 		cursorX = 77; 					cursorY = 48; cursorW = 10;					break;
	case MIN: 		cursorX = 59;				 	cursorY = 48; cursorW = 10;					break;
	case HR: 		cursorX = 41; 					cursorY = 48; cursorW = 10;					break;
	case MON:		cursorX = 35 + (domDigits * 6); cursorY = 63; cursorW = 16;					break;
	case DOM:		cursorX = 29; 					cursorY = 63; cursorW = (domDigits * 5);	break;
	case YEAR_1:	cursorX = 59 + (domDigits * 6); cursorY = 63; cursorW = 10;					break;
	case YEAR_2:	cursorX = 71 + (domDigits * 6); cursorY = 63; cursorW = 10;					break;
	}

	GrLineDrawH(&g_sContext, cursorX, cursorX+cursorW, cursorY);


	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 5 , 55, TRANSPARENT_TEXT);

	GrStringDrawCentered(&g_sContext, "Edit Calendar", AUTO_STRING_LENGTH, 46 , 27, TRANSPARENT_TEXT);

	LoadLeftButton("BACK");
	LoadMiddleButton("SET");

	GrFlush(&g_sContext);
}

void PrintSettings_DateTime_NotAllowed(){
	GrStringDrawCentered(&g_sContext, "Cannot edit", AUTO_STRING_LENGTH, 47, 27, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "while insulin", AUTO_STRING_LENGTH, 47, 38, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "delivery is", AUTO_STRING_LENGTH, 47, 49, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "in progress", AUTO_STRING_LENGTH, 47, 60, OPAQUE_TEXT);

	LoadMiddleButton("OK");


	GrFlush(&g_sContext);

}

void PrintCreateReminder_Idle(){
	int digits = 0, domDigits = 0;
	char buffer[10] = "";
	char outString[32] = "";

	// Clear previous entries from screen
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	GrStringDraw(&g_sContext, "Name:" , AUTO_STRING_LENGTH, 3, 16, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, p_reminder.Name , AUTO_STRING_LENGTH, 33, 16, OPAQUE_TEXT);


	// Get Day of month
	domDigits = UnsignedInt_To_ASCII( BCDtoInt( p_reminder.Time.DayOfMonth ), buffer ); // Read upper half of byte by bitshifting four places
	strncpy(outString, buffer, domDigits);
	strncat( outString, "/", 1 );

	// Get Month
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Month >> 4, buffer );
	strncat( outString, buffer, digits );
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Month & 0xF, buffer );
	strncat( outString, buffer, digits );
	strncat( outString, "/", 1 );

	// Get Year
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Year >> 12, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Year >> 8 & 0xF, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Year >> 4 & 0xF, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Year & 0xF, buffer );
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, "Date:" , AUTO_STRING_LENGTH, 3, 36, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 33 , 36, TRANSPARENT_TEXT);


	// Get Hours
	strcpy(outString, "");
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Hours >> 4, buffer ); // Read upper half of byte by bitshifting four places
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Hours & 0xF, buffer ); // Read lower half of byte by overwriting the upper half with 0s
	strncat(outString, buffer, digits);
	strncat(outString, ":", 1);

	// Get Minutes
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Minutes >> 4, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( p_reminder.Time.Minutes & 0xF, buffer );
	strncat(outString, buffer, digits);
//	strncat(outString, ":", 1);

	// Get Seconds
//	digits = UnsignedInt_To_ASCII( p_reminder.Time.Seconds >> 4, buffer );
//	strncat(outString, buffer, digits);
//	digits = UnsignedInt_To_ASCII( p_reminder.Time.Seconds & 0xF, buffer );
//	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, "Time:" , AUTO_STRING_LENGTH, 3, 26, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 33 , 26, OPAQUE_TEXT);



	strcpy(outString, "");
	switch ( p_reminder.Frequency ){
	case e_remindFreq_oneTime: strcpy( outString, "One Time" ); break;
	case e_remindFreq_daily: strcpy( outString, "Daily" ); break;
	case e_remindFreq_weekly: strcpy( outString, "Weekly" ); break;
	case e_remindFreq_weekdays: strcpy( outString, "Weekdays" ); break;
	case e_remindFreq_weekends: strcpy( outString, "Weekends" ); break;
	default: break;
	}

	GrStringDraw(&g_sContext, "Freq:" , AUTO_STRING_LENGTH, 3, 46, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, outString, AUTO_STRING_LENGTH, 33 , 46, OPAQUE_TEXT);

	GrStringDraw(&g_sContext, "Msg:" , AUTO_STRING_LENGTH, 3, 56, OPAQUE_TEXT);

	// split message over as many lines as needed
	if ( strlen( p_reminder.Message ) < 10){
		GrStringDraw(&g_sContext, p_reminder.Message , AUTO_STRING_LENGTH, 30, 56, OPAQUE_TEXT);
	} else if ( strlen( p_reminder.Message ) < 25 ){
		strcpy( outString, "" );
		strncat( outString, p_reminder.Message, 10 );
		if ( p_reminder.Message[9] != 32 && p_reminder.Message[10] != 32 && strlen( p_reminder.Message ) > 10){
			strncat( outString, "-", 1 );
		}

		GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 30, 56, OPAQUE_TEXT);

		strcpy( outString, "" );
		strcat( outString, p_reminder.Message + 10 );
		GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 3, 66, OPAQUE_TEXT);

	}



	/* Draw Cursor */
	int cursorY, cursorX, cursorW;
	switch ( remindEntryIndex ){
	case NAME: 							cursorX = 27 + strlen( p_reminder.Name ) * 6;	cursorY = 24; 	cursorW = 4; 	break;
	case DATETIME:
		switch ( p_remindSubIndex ){
		//case SEC:						cursorX = 69;	cursorY = 34; 	cursorW = 10; 	break;
		case MIN:						cursorX = 51;	cursorY = 34; 	cursorW = 10; 	break;
		case HR:						cursorX = 33;	cursorY = 34; 	cursorW = 10; 	break;
		case DOM:						cursorX = 33;	cursorY = 44; 	cursorW = 10; 	break;
		case MON: 						cursorX = 51;	cursorY = 44; 	cursorW = 10; 	break;
		case YEAR_1:					cursorX = 69;	cursorY = 44; 	cursorW = 10; 	break;
		case YEAR_2:					cursorX = 80;	cursorY = 44; 	cursorW = 10; 	break;
		}
		break;
	case FREQ: 							cursorX = 33; 	cursorY = 54; 	cursorW = 50;	break;
	case MSG:
		if ( strlen( p_reminder.Message ) <= 10){
			cursorX = 24 + strlen( p_reminder.Message ) * 6; 	cursorY = 64; 	cursorW = 4;	break;
		} else if ( strlen( p_reminder.Message ) < 25 ){
			cursorX = (strlen( p_reminder.Message )-10) * 6 - 3; 	cursorY = 74; 	cursorW = 4;	break;
		}
	}
	GrLineDrawH(&g_sContext, cursorX, cursorX+cursorW, cursorY);

	LoadLeftButton("CANC");
	LoadMiddleButton("DONE");
	if( remindEntryIndex == NAME ) LoadRightButton("TIME");
	else if ( remindEntryIndex == MSG ) LoadRightButton("FREQ");
	else ClearRightButton();


	GrFlush(&g_sContext);
}

void PrintCreateReminder_Confirm(){
	GrStringDraw(&g_sContext, "Save Reminder?" , AUTO_STRING_LENGTH, 5, 16, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}

void PrintCreateReminder_Invalid(){

	GrStringDrawCentered(&g_sContext, "Invalid Reminder" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	//GrStringDrawCentered(&g_sContext, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	//LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}


void PrintRemoveReminder_Idle(){
	int numberOfReminders;
	numberOfReminders = GetNumberOfReminders();

	y_remindName *Name;
	Name = (y_remindName *) malloc( sizeof( y_remindName ));

	int i;
	for ( i = 0; i < numberOfReminders; i++ ){
		GetReminderName( Name, i );
		GrStringDraw( &g_sContext, *Name, AUTO_STRING_LENGTH, 5, 16 + ( 10 * i ), OPAQUE_TEXT );
	}
	free(Name);

	// highlight the selected profile
    unsigned char text_start = 18;
    int index = GetReminderIndex( &m_reminder );
	text_start = 16 + 10 * index;

    GrContextForegroundSet(&g_sContext, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(&g_sContext, ClrBlack); //ClrWhite      this affects the text color in the highlight
    GrStringDraw(&g_sContext, m_reminder.Name, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);

	LoadLeftButton( "CANC" );
	LoadMiddleButton( "SEL" );
	GrFlush(&g_sContext);
}


void PrintRemoveReminder_Confirm(){
	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	GrStringDrawCentered(&g_sContext, "Remove", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT);
	GrStringDrawCentered(&g_sContext, "Reminder?", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT);

	GrStringDraw(&g_sContext, "Name: " , AUTO_STRING_LENGTH, 5, 40, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, m_reminder.Name, AUTO_STRING_LENGTH, 15, 50, OPAQUE_TEXT);


	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

	GrFlush(&g_sContext);
}
