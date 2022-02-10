/*
 * system.h
 *
 *  Created on: ٠٢‏/٠٩‏/٢٠٢١
 *      Author: MALEK MAHMOUD
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
#define WITH_ENGINE_TEMP_CONTROLLER 1

typedef unsigned char uint8;

typedef struct{
	char enginestate[5];
	char AC[5];
	uint8 vSpeed;
	unsigned short rTemp;
	char etempState[5];
	unsigned short etemp;

}vState;

void _initialState(vState *state);
void _startInterface (char*);
void _displayInitialstate (char*);
void _sensorSetMenu(char* userChoice2);
void _sensorReading(char* userChoice1,char* userChoice2,char* trafficLight,uint8* roomTemp,uint8* engineTemp,vState* state);
void _trafficLightSetting(char*,vState*);
void _roomTempSetting(uint8*,vState*);
void _engineTempSetting(uint8* temp,vState* state);
void _dataVehicleState(vState* displayState,uint8* roomTemp,uint8* engineTemp);
#endif /* SYSTEM_H_ */
