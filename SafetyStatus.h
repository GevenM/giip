#ifndef SAFETYSTATUS_H
#define SAFETYSTATUS_H

#include<stdbool.h>
#include"TypesAndConstants.h"

extern void UpdateSafetyStatus();

extern y_safetyStatus GetSafetyStatus();


extern bool OcclusionDetected();
extern bool BubbleDetected();
extern void AcknowledgeOcclusion();
extern void AcknowledgeBubble();


#endif /* SAFETYSTATUS_H_ */
