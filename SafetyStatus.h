#ifndef SAFETYSTATUS_H
#define SAFETYSTATUS_H

#include<stdbool.h>

extern void UpdateSafetyStatus();

extern bool OcclusionDetected();
extern bool BubbleDetected();
extern void AcknowledgeOcclusion();
extern void AcknowledgeBubble();

#endif /* SAFETYSTATUS_H_ */
