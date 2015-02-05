#ifndef INSULINRESERVOIR_H
#define INSULINRESERVOIR_H



extern void InitInsulinReservoirSensorADC();
extern void UpdateInsulinReservoirSensor();

extern unsigned long GetInsulinReservoirLevelInIU();
extern int GetInsulinReservoirLevelInPercent();


#endif
