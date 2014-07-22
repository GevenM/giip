#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "BasalProfiles.h"
#include "Shared.h"
#include "msp430.h"

#include "RTC.h"

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
int AddProfileToSet(y_basal *profile){
	LoadProfilesFromFlash();

	// Check if max number of profiles has been stored
	if (BasalCreationAllowed()){

		// create an index variable for where to store the next profile and increment number of profiles.
		char profileIndex = basalSetLocal.numberOfBasalProfiles;
		basalSetLocal.numberOfBasalProfiles++;

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

	return -1;
}



void SaveProfilesToFlash(void)
{
  flashEraseSegment((unsigned long)&basalSet);

  UnlockFlash();
  basalSet = basalSetLocal;
  LockFlash();
}


void LoadProfilesFromFlash(void)
{
  basalSetLocal = basalSet;
}

bool BasalCreationAllowed(){
	LoadProfilesFromFlash();
	if (basalSetLocal.numberOfBasalProfiles < k_maxNumberOfBasalProfiles){
		return true;
	}
	return false;
}

bool BasalProfileExists(){
	LoadProfilesFromFlash();
	if (basalSetLocal.numberOfBasalProfiles > 0){
		return true;
	}
	return false;
}

void GetProfileName(y_basalName *Name, int index){
	LoadProfilesFromFlash();
	strncpy( *Name, basalSetLocal.Profile[index].Name, k_basalNameLength-1 );
}

int GetNumberBasalProfiles(){
	LoadProfilesFromFlash();
	return basalSetLocal.numberOfBasalProfiles;
}

bool BasalProfileIsValid(y_basal *profile){
	LoadProfilesFromFlash();

	if ( !strcmp(profile->Name, "")) //check name is not empty string
		return false;

	int i;
	for ( i = 0 ; i < basalSetLocal.numberOfBasalProfiles ; i++ ){ //cycle through the profiles currently in memory
		if ( ProfileCompare(profile, &basalSetLocal.Profile[i]) ) //check name of new profile doesn't match names of other profiles
			return false;
	}

	y_insulinValue basalRateSum = 0;
	for ( i = 0 ; i < k_segDay ; i++ ){ //cycle through all segments or rates
		if ( profile->Rate[i] < k_minBasalBound || profile->Rate[i] > k_maxBasalBound) //each single rate is within allowable bounds
			return false;

		basalRateSum += profile->Rate[i]; //sum all rates to compare to daily max
	}


	if (basalRateSum > k_maxDailyInsulin) //compare sum of rates to daily max
		return false;
	else
		return true;
}


// implements Table 15
bool ActivateBasalProfileIsValid(y_basal *profile){
	int i;
	y_insulinValue basalRateSum = 0;

	for ( i = 0 ; i < k_segDay ; i++ ){ //cycle through all segments or rates
		if ( profile->Rate[i] < k_minBasalBound || profile->Rate[i] > k_maxBasalBound) //each single rate is within allowable bounds
			return false;

		basalRateSum += profile->Rate[i]; //sum all rates to compare to daily max
	}


	if (basalRateSum > k_maxDailyInsulin) //compare sum of rates to daily max
		return false;
	else
		return true;
}

int RemoveProfileFromSet(y_basal *profile){
	LoadProfilesFromFlash();

	// Create index to hold the location of profile to remove
	int profileIndex = GetProfileIndex(profile);
	if (profileIndex == -1) return -1; //not in set

	// If the profile to remove is the last one, simply decrement the number of profiles
	if(profileIndex == basalSetLocal.numberOfBasalProfiles - 1){
		basalSetLocal.numberOfBasalProfiles--;
		SaveProfilesToFlash();
		return 1;
	}

	// If it's a profile that is not the last, move all the profiles after the one to remove up one place.
	if (profileIndex < basalSetLocal.numberOfBasalProfiles - 1 ){
		int i;
		for (i = profileIndex; i < basalSetLocal.numberOfBasalProfiles - 1 ; i++){
			CopyProfile(&basalSetLocal.Profile[i + 1], &basalSetLocal.Profile[i]);
		}
		basalSetLocal.numberOfBasalProfiles--;
		SaveProfilesToFlash();
		return 1;
	}

	return -1;
}


void CopyProfile(y_basal *fromProfile, y_basal *toProfile){
	int i;

	strncpy( toProfile->Name, fromProfile->Name, k_basalNameLength-1 );

	for (i=0 ; i < k_segDay ; i++){
		toProfile->Rate[i] = fromProfile->Rate[i];
	}
}



bool BasalProfileIsActive(y_basal *profile){
	// check if the passed profile is the active profile
	return !strcmp(profile->Name, f_activeBasal.Name);
}

bool BasalIsActive(){
	return !( ProfileCompare( &f_activeBasal, &k_emptyBas ));
}


int GetProfileIndex( y_basal * profile){
	LoadProfilesFromFlash();

	int i = 0;
	while (strcmp(profile->Name, basalSetLocal.Profile[i].Name) && i < k_maxNumberOfBasalProfiles){
		i++;
	}

	if (i == k_maxNumberOfBasalProfiles) return -1;

	return i;
}

void LoadProfile( y_basal *profile, int index){
	LoadProfilesFromFlash();
	CopyProfile(&basalSetLocal.Profile[index], profile);
}

bool ProfileCompare(y_basal *profile1, y_basal *profile2){
	// if the names match, the profiles are the same.
	if ( !strcmp( profile1->Name, profile2->Name)){
		return true;
	}
	return false;
}


int GetCurrentTimeSegment (){
	int currentHour = GetCurrentHour();
	currentHour = BCDtoInt( currentHour );

	int currentMin = GetCurrentMin();
	currentMin = BCDtoInt( currentMin );

	int currentSegment = ( k_segDay / 24 ) * currentHour;
	currentSegment = currentSegment + ( currentMin / (60/(k_segDay/24)));

	return currentSegment;
}
