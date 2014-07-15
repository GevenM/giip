#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "BasalProfiles.h"
#include "msp430.h"


#define FLASH_UNLOCK    FCTL3 = FWKEY; FCTL1 = FWKEY + WRT;
#define FLASH_LOCK      FCTL1 = FWKEY; FCTL3 = FWKEY +  LOCK;


// Allocates space on flash for the given variable
#pragma DATA_SECTION(basalSet, ".mydata1");
#pragma DATA_ALIGN(basalSet, 512);


void LoadProfilesFromFlash(void);
void SaveProfilesToFlash(void);


// Private variables that store the basal profiles
y_basalSet basalSet;
y_basalSet basalSetLocal;


void InitBasalSet(){
	basalSetLocal.numberOfBasalProfiles = 0;
	SaveProfilesToFlash();
}

// Takes a profile and updates the name and rates.
void CreateProfile(y_basal *me, char *Name, unsigned char Rate[]){
	//strncpy( me->Name, Name, K_NAME_LENGTH-1);

	//int i;
	//for (i = 0; i<K_RATES; i++){
	//	me->Rate[i] = Rate[i];
	//}
}

// Changes the name of the given profile with the provided name
void ChangeProfileName(y_basal *me, char * Name){
	//strncpy( me->Name, Name, K_NAME_LENGTH-1);
}

// Add a basal profile to a set of basal profiles. Takes a set and a profile as inputs. Allocates memory for profiles.
char AddProfileToSet(y_basal *profile){
	LoadProfilesFromFlash();

	// Check if max number of profiles has been stored
	if (basalSetLocal.numberOfBasalProfiles < k_maxNumberOfBasalProfiles){

		// increment number of profiles stored (and create variable to use as index)
		char profileIndex = ++basalSetLocal.numberOfBasalProfiles;

		// Copy the name into the set
		strncpy( basalSetLocal.Profile[profileIndex].Name, profile->Name, k_basalNameLength-1);

		// Copy the rates into the set
		int i;
		for (i = 0; i < k_segDay ; i++){
			basalSetLocal.Profile[profileIndex].Rate[i] = profile->Rate[i];
		}

		SaveProfilesToFlash();
		return 1;
	}

	return 0;
}


/**********************************************************************//**
 * @brief  Stores calibration and user-config data into flash segment
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void SaveProfilesToFlash(void)
{
  flashEraseSegment((unsigned long)&basalSet);
  FLASH_UNLOCK;
  basalSet = basalSetLocal;
  FLASH_LOCK;
}

/**********************************************************************//**
 * @brief  Loads calibration and user-config data from flash segment.
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void LoadProfilesFromFlash(void)
{
  basalSetLocal = basalSet;
}
