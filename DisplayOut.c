#include "DisplayOut.h"
#include <string.h>
#include "ActivateBolus.h"
#include "RTC.h"
#include "InsulinOutputCalculator.h"
#include "Reminder.h"

#include "ScreenPrintingFunctions/Basal/!PrintBasal_Master.h"
#include "ScreenPrintingFunctions/Basal/TemporaryBasal/!PrintTmpBas_Master.h"
#include "ScreenPrintingFunctions/Bolus/!PrintBolus_Master.h"
#include "ScreenPrintingFunctions/Reminder/!PrintReminder_Master.h"
#include "ScreenPrintingFunctions/Main/!Main_Master.h"
#include "ScreenPrintingFunctions/Settings/!PrintSettings_Master.h"


tContext g_sContext;
tRectangle myRectangleBotMid = { 33, 82, 63, 95};
tRectangle myRectangleBotRight = { 66, 82, 95, 95};
tRectangle myRectangleBotLeft = { 0, 82, 30, 95};
tRectangle myRectangleTopBan = { 0, 0, 95, 13};
tRectangle myRectangleScreen = { 0, 14, 95, 81};

tRectangle g_sRect;
uint8_t g_delayCounter = 0;

y_basal p_inputProfile;
unsigned char segments[ k_segDay ] = {k_segDay, 0};

y_basalRate rates[ k_segDay ];
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

unsigned char rateIndex = 0;
unsigned char segmentIndex = 0;
unsigned char nameIndex = 0;
bool updateScreen = false;
bool basCreateStatus_NameEntered = false;
bool tmpBasal_DurationEntered = false;
bool bolCreateStatus_NameEntered = false;
bool bolStartCalc_CarbsEntered = false;

void LoadBanner(void);
void LoadLeftButton(const char * text);
void LoadMiddleButton(const char * text);
void LoadRightButton(const char * text);
void ClearRightButton();


void ClearCreateBasProf_Idle(y_basal *p_profile);


void PrintError();


void ClearInputProfile();
void InputProfileToBasalProfile(y_basal *basProf);


void PrintRemoveBolusPreset_Idle();

void PrintCreateReminder_Idle();
void PrintCreateReminder_Confirm();
void PrintCreateReminder_Invalid();

void PrintRemoveReminder_Idle();
void PrintRemoveReminder_Confirm();

void UpdateScreen();

void InitDisplayContext(){
    GrContextInit(&g_sContext, &g_sharp96x96LCD);
  	GrContextForegroundSet(&g_sContext, ClrBlack);
  	GrContextBackgroundSet(&g_sContext, ClrWhite);
  	GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
  	GrClearDisplay(&g_sContext);
  	GrFlush(&g_sContext);

}

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
	switch( c_menuScreen ){
	case None: PrintIdle( &g_sContext ); break;
	case Main: PrintMainMenu( &g_sContext, f_menuChoice ); break;

	case BasalBothActive: PrintBasBothActive(&g_sContext, f_menuChoice); break;
	case BasalProfActive: PrintBasProfActive(&g_sContext, f_menuChoice); break;
	case BasalTmpActive: PrintBasTmpActive(&g_sContext, f_menuChoice); break;
	case BasalNoActive: PrintBasNoActive(&g_sContext, f_menuChoice); break;

	case Bolus: PrintBolus( &g_sContext, f_menuChoice ); break;
	case Reminder: PrintReminder( &g_sContext, f_menuChoice ); break;
	case Settings: PrintSettings( &g_sContext, f_menuChoice ); break;

	case BolusAlreadyActive: PrintBolusAlreadyActive( &g_sContext ); break;
	case Bolus_Manage: PrintBolus_Manage( &g_sContext, f_menuChoice ); break;
	case RemindCreateNotAllowed: PrintRemindCreateNotAllowed( &g_sContext ); break;
	case NoRemind: PrintNoRemind( &g_sContext ); break;

	case NoBasProf: PrintNoBasProf( &g_sContext ); break;
	case Basal_Manage: PrintBasal_Manage( &g_sContext, f_menuChoice ); break;
	case BasCreateNotAllowed: PrintBasCreateNotAllowed( &g_sContext ); break;
	case BolusCreateNotAllowed: PrintBolusCreateNotAllowed( &g_sContext ); break;
	case NoBolusPreset: PrintNoBolusPreset( &g_sContext ); break;

	case CreateBasProf_Idle: PrintCreateBasProf_Idle( &g_sContext, p_inputProfile, basCreateStatus_NameEntered, segmentIndex, rateIndex, segments ); break;
	case CreateBasProf_Confirm: PrintCreateBasProf_Confirm(&g_sContext); break;
	case CreateBasProf_Invalid: PrintCreateBasProf_Invalid(&g_sContext); break;

	case RemoveBasProf_Idle:PrintRemoveBasProf_Idle( &g_sContext, m_basRemSelected ); break;
	case RemoveBasProf_Confirm:PrintRemoveBasProf_Confirm( &g_sContext ); break;
	case RemoveBasProf_Invalid:PrintRemoveBasProf_Invalid( &g_sContext ); break;

	case StartBasProf_Idle:PrintStartBasProf_Idle( &g_sContext, m_basActSelected); break;
	case StartBasProf_Confirm:PrintStartBasProf_Confirm( &g_sContext ); break;
	case StartBasProf_Invalid:PrintStartBasProf_Invalid( &g_sContext ); break;

	case StopBasProf_All:PrintStopBas_All( &g_sContext ); break;

	case StartTmpBas_Idle:PrintStartTmpBas_Idle(&g_sContext, tmpBasal_DurationEntered, m_tmpBas); break;
	case StartTmpBas_Confirm:PrintStartTmpBas_Confirm(&g_sContext, m_tmpBas); break;
	case StartTmpBas_Invalid:PrintStartTmpBas_Invalid(&g_sContext); break;

	case StopTmpBas_All:PrintStopTmpBas_All(&g_sContext); break;

	case CreateBolusPreset_Idle:PrintCreateBolusPreset_Idle( &g_sContext, m_bolus, bolCreateStatus_NameEntered ); break;
	case CreateBolusPreset_Confirm:PrintCreateBolusPreset_Confirm( &g_sContext ); break;
	case CreateBolusPreset_Invalid:PrintCreateBolusPreset_Invalid( &g_sContext ); break;

	case RemoveBolusPreset_Idle:PrintRemoveBolusPreset_Idle(); break;
	case RemoveBolusPreset_Confirm:PrintRemoveBolusPreset_Confirm( &g_sContext ); break;
	case RemoveBolusPreset_Invalid:PrintRemoveBolusPreset_Invalid( &g_sContext ); break;

	case StartBolus_Idle:PrintStartBolus_Idle( &g_sContext, p_selectedMethod ); break;
	case StartBolus_Calculator:PrintStartBolus_Calculator( &g_sContext, bolStartCalc_CarbsEntered, m_carbs, m_bloodGlucose ); break;
	case StartBolus_Preset: PrintStartBolus_Preset( &g_sContext, m_bolSelected ); break;
	case StartBolus_Manual: PrintStartBolus_Manual( &g_sContext, m_bolus ); break;
	case StartBolus_Confirm: PrintStartBolus_Confirm( &g_sContext ); break;
	case StartBolus_Invalid: PrintStartBolus_Invalid( &g_sContext ); break;

	case CreateReminder_Idle: PrintCreateReminder_Idle(); break;
	case CreateReminder_Confirm:PrintCreateReminder_Confirm();break;
	case CreateReminder_Invalid:PrintCreateReminder_Invalid();break;

	case RemoveReminder_Idle:PrintRemoveReminder_Idle(); break;
	case RemoveReminder_Confirm: PrintRemoveReminder_Confirm();break;

	case Settings_DateTime: PrintSettings_DateTime(&g_sContext, p_calendar, p_calendarIndex); break;
	case Settings_DateTime_NotAllowed: PrintSettings_DateTime_NotAllowed(&g_sContext); break;


	default: PrintError(); break;
	}
	GrFlush(&g_sContext);
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
				case Reminder: f_menuChoice = Bolus;break;
				case Settings: f_menuChoice = Reminder;break;
				case ShutDown: f_menuChoice = Settings;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Basal: f_menuChoice = Bolus;break;
				case Bolus: f_menuChoice = Reminder;break;
				case Reminder: f_menuChoice = Settings;break;
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

				case Reminder:
					c_menuScreen = Reminder;
					f_menuChoice = Reminder_Create;
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

		case Reminder:
			if (M_backReq){
				c_menuScreen = Main;
				f_menuChoice = Reminder;
			} else if (M_upReq){
				switch (f_menuChoice){
				case Reminder_Create: f_menuChoice = Reminder_Remove;break;
				case Reminder_Remove: f_menuChoice = Reminder_Create;break;
				default:  break;
				}
			} else if (M_downReq){
				switch (f_menuChoice){
				case Reminder_Create: f_menuChoice = Reminder_Remove;break;
				case Reminder_Remove: f_menuChoice = Reminder_Create;break;
				default:  break;
				}
			} else if (M_selReq){
				switch (f_menuChoice){
				case Reminder_Create:
					if( ReminderCreationAllowed() ){
						p_reminder = k_emptyReminder;
						p_reminder.Time = GetCurrentCalendar();
						remindEntryIndex = 0;

					} else{
						c_menuScreen = RemindCreateNotAllowed;
					}
					break;
				case Reminder_Remove:
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
				c_menuScreen = Reminder;
			}
			break;

		case NoRemind:
			if (M_backReq){
				c_menuScreen = Reminder;
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



void PrintError(){
	;
}



void ClearCreateBasProf_Idle(y_basal *p_profile){
	GrStringDraw(&g_sContext, p_profile->Name, AUTO_STRING_LENGTH, 5, 44, TRANSPARENT_TEXT);

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
