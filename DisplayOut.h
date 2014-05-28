#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include "driverlib.h"
#include "stdlib.h"

extern void Delay(void);
extern void DisplayOut(void);
extern void LoadBanner(void);
extern void LoadLeftButton(const char * text);
extern void LoadMiddleButton(const char * text);
extern void LoadRightButton(const char * text);
extern bool FirstButtonPressed();
extern bool SecondButtonPressed();
extern bool ThirdButtonPressed();
extern bool UpButtonPressed();
extern bool DownButtonPressed();
extern bool LeftButtonPressed();
extern bool RightButtonPressed();
extern void PrintMMBasal();
extern void PrintMMBolus();
extern void PrintIdle();
extern void PrintMMSchedule();
extern void PrintMMSettings();
extern void PrintMMShutDown();
extern void SetLED1();
extern void ResetLED1();
extern void ClearMM();
extern void ClearBasMenuActive();
extern void ClearBasMenuInactive();

extern void PrintBasMenuActiveA();
extern void PrintBasMenuActiveB();
extern void PrintBasMenuInactiveA();
extern void PrintBasMenuInactiveB();

extern const char * convertToChar(unsigned int x);

extern tContext g_sContext;
extern tRectangle myRectangleBotMid;
extern tRectangle myRectangleBotRight;
extern tRectangle myRectangleBotLeft;
extern tRectangle myRectangleTopBan;


enum e_operations{
  		Idle,
  		CreateBasProf,
  		RemoveBasProf,
  		StartBasProf,
  		StopBasProf,
  		StartTmpBas,
  		StopTmpBas,
  		CreateBolusPreset,
  		RemoveBolusPreset,
  		StartBolus,
  		CreateReminder,
  		RemoveReminder,
  		MainMenu,
  		none,
  		MMBasal,
  		MMBolus,
  		MMSchedule,
  		MMSettings,
  		MMShutDown,
  		BasMenu,
  		BasMenuActiveA,
  		BasMenuActiveB,
  		BasMenuInactiveA,
  		BasMenuInactiveB
  	};

extern enum e_operations c_operation;
extern enum e_operations nextOperation;

extern bool f_basalIsActive;
extern bool f_temporaryBasalIsActive;
extern bool f_bolusInProgress;
