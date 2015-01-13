#ifndef INSULINDELIVERYMECHANISM_H
#define INSULINDELIVERYMECHANISM_H



extern void InitInsulinDeliveryMechanism();
extern void DeliverPendingInsulin();
extern float GetInsulinOutputBuffer();


extern void EnableInsulinDeliveryMechanism();
extern void DisableInsulinDeliveryMechanism();

extern void ForceMotorForward();
extern void ForceMotorBackward();
extern void ForceMotorStop();
#endif
