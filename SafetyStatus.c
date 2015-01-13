#include "SafetyStatus.h"
#include "MonitoredVariables.h"
#include "Shared.h"

bool p_bubbleInLine = false;
bool p_occlusionInLine = false;

void UpdateSafetyStatus(){
	if( M_bubbleInLine ){
		// if bubble is detected, deal with it by telling user to fix it and acknowledge.
		p_bubbleInLine = true;
	}
	if ( M_occlusionInLine ){
		// if occlusion is detected, deal with it by telling user to fix it and acknowledge.
		p_occlusionInLine = true;
	}


	if ( p_bubbleInLine ){
		c_safetyStatus = e_notSafe;
	} else if ( p_occlusionInLine ){
		c_safetyStatus = e_notSafe;
	} else {
		c_safetyStatus = e_safe;
	}

}


bool OcclusionDetected(){
	return p_occlusionInLine;
}

bool BubbleDetected(){
	return p_bubbleInLine;
}


void AcknowledgeOcclusion(){
	p_occlusionInLine = false;
}

void AcknowledgeBubble(){
	p_bubbleInLine = false;
}

