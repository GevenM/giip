#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "BasalProfiles.h"
#include "Shared.h"
#include "msp430.h"

#include "RTC.h"

// Allocates space on flash for the given variable
#pragma DATA_SECTION(p_basalSet, ".mydata1");
#pragma DATA_ALIGN(p_basalSet, 512);


void LoadProfilesFromFlash(void);
void SaveProfilesToFlash(void);


// Private variables that store the basal profiles
y_basalSet p_basalSet;
y_basalSet p_basalSetLocal;


void InitBasalSet(){
	p_basalSetLocal.numberOfBasalProfiles = 0;
	SaveProfilesToFlash();
}

bool ProfileHasName( y_basal *profile ){
	if ( strcmp(profile->Name, "") == 0 ){
		return false;
	}
	return true;
}

bool ProfileSegmentOutOfBound ( y_basal *profile ){
	// some segment is out of bound.
	int i;

	for ( i = 0 ; i < k_segDay ; i++ ){ //cycle through all segments or rates
		if ( profile->Rate[i] < k_minBasalBound || profile->Rate[i] > k_maxBasalBound) //each single rate is within allowable bounds
			return true;
	}

	return false;
}

bool ProfileSumOutOfBound ( y_basal *profile ){
	// some segment is out of bound.
	int i;
	y_insulinValue basalRateSum = 0;

	for ( i = 0 ; i < k_segDay ; i++ ){ //cycle through all segments or rates
		basalRateSum += profile->Rate[i]; //sum all rates to compare to daily max
	}

	// the total insulin to be delivered is out of bound.
	if (basalRateSum > k_maxDailyInsulin) //compare sum of rates to daily max
		return true;

	return false;
}


// Add a basal profile to a set of basal profiles.
int AddProfileToSet(y_basal *profile){
	LoadProfilesFromFlash();

	// Check if max number of profiles has been stored
	if (BasalCreationAllowed()){

		// create an index variable for where to store the next profile and increment number of profiles.
		char profileIndex = p_basalSetLocal.numberOfBasalProfiles;
		p_basalSetLocal.numberOfBasalProfiles++;

		// Copy the name into the set
		strncpy( p_basalSetLocal.Profile[profileIndex].Name, profile->Name, k_basalNameLength-1);

		// Copy the rates into the set
		int i;
		for (i = 0; i < k_segDay ; i++){
			p_basalSetLocal.Profile[profileIndex].Rate[i] = profile->Rate[i];
		}

		SaveProfilesToFlash();
		return 1;
	}

	return -1;
}



void SaveProfilesToFlash(void)
{
  flashEraseSegment((unsigned long)&p_basalSet);

  UnlockFlash();
  p_basalSet = p_basalSetLocal;
  LockFlash();
}


void LoadProfilesFromFlash(void)
{
  p_basalSetLocal = p_basalSet;
}

bool BasalCreationAllowed(){
	LoadProfilesFromFlash();
	if (p_basalSetLocal.numberOfBasalProfiles < k_maxNumberOfBasalProfiles){
		return true;
	}
	return false;
}

bool BasalProfileExists(){
	LoadProfilesFromFlash();
	if (p_basalSetLocal.numberOfBasalProfiles > 0){
		return true;
	}
	return false;
}

void GetProfileName(y_basalName *Name, int index){
	LoadProfilesFromFlash();
	strncpy( *Name, p_basalSetLocal.Profile[index].Name, k_basalNameLength-1 );
}

int GetNumberBasalProfiles(){
	LoadProfilesFromFlash();
	return p_basalSetLocal.numberOfBasalProfiles;
}


bool ProfileInSet ( y_basal *profile ){
	LoadProfilesFromFlash();

	int i;
	for ( i = 0 ; i < p_basalSetLocal.numberOfBasalProfiles ; i++ ){ //cycle through the profiles currently in memory
		if ( ProfileCompare(profile, &p_basalSetLocal.Profile[i]) ) //check name of new profile doesn't match names of other profiles
			return true;
	}
	return false;
}



int RemoveProfileFromSet(y_basal *profile){
	LoadProfilesFromFlash();

	// Create index to hold the location of profile to remove
	int profileIndex = GetProfileIndex(profile);
	if (profileIndex == -1) return -1; //not in set

	// If the profile to remove is the last one, simply decrement the number of profiles
	if(profileIndex == p_basalSetLocal.numberOfBasalProfiles - 1){
		p_basalSetLocal.numberOfBasalProfiles--;
		SaveProfilesToFlash();
		return 1;
	}

	// If it's a profile that is not the last, move all the profiles after the one to remove up one place.
	if (profileIndex < p_basalSetLocal.numberOfBasalProfiles - 1 ){
		int i;
		for (i = profileIndex; i < p_basalSetLocal.numberOfBasalProfiles - 1 ; i++){
			CopyProfile(&p_basalSetLocal.Profile[i + 1], &p_basalSetLocal.Profile[i]);
		}
		p_basalSetLocal.numberOfBasalProfiles--;
		SaveProfilesToFlash();
		return 1;
	}

	return -1;
}


void CopyProfile(y_basal *fromProfile, y_basal *toProfile){
	*toProfile = *fromProfile;
//	int i;
//
//	strncpy( toProfile->Name, fromProfile->Name, k_basalNameLength-1 );

//	for (i=0 ; i < k_segDay ; i++){
//		toProfile->Rate[i] = fromProfile->Rate[i];
//	}
}





bool BasalIsActive(){
	return !( ProfileCompare( &f_activeBasal, &k_emptyBas ));
}


int GetProfileIndex( y_basal * profile){
	LoadProfilesFromFlash();

	int i = 0;
	while (strcmp(profile->Name, p_basalSetLocal.Profile[i].Name) && i < k_maxNumberOfBasalProfiles){
		i++;
	}

	if (i == k_maxNumberOfBasalProfiles) return -1;

	return i;
}

void LoadProfile( y_basal *profile, int index){
	LoadProfilesFromFlash();
	CopyProfile(&p_basalSetLocal.Profile[index], profile);
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

// returns whether the profile passed to it is the active profile.
bool IsActiveProfile( y_basal *profile ){
	if ( strcmp(profile->Name, f_activeBasal.Name) == 0 ){ // if profile name matches the active basal name return true
		return true;
	}
	return false;
}
