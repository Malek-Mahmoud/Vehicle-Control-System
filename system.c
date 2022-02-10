/*
 * system.c
 *
 *  Created on: ٠٢‏/٠٩‏/٢٠٢١
 *      Author: MALEK MAHMOUD
 */


#include<stdio.h>
#include<string.h>
#include"system.h"

void _initialState(vState *state)
{
	strcpy(state->enginestate,"OFF");
	strcpy(state->AC,"OFF");
#if (WITH_ENGINE_TEMP_CONTROLLER)
	strcpy(state->etempState,"OFF");
	state->etemp = 90;
#endif
	state->rTemp=30;
	state->vSpeed = 0;
}
void _displayInitialstate (char*userChoice1)
{
	switch(*userChoice1){
	case'a':
		printf("Turn on the vehicle engine\n\n");
		break;
	case'b':
		printf("Turn off the vehicle engine\n\n");
		break;
	case'c':
		printf("Quit the system\n\n");
		break;
	}
}
void _dataVehicleState(vState* displayState,uint8* roomTemp,uint8* engineTemp)
{
	printf("\nEngine state: %s\n",displayState->enginestate);
	printf("Vehicle speed: %d\n",displayState->vSpeed);
	if(displayState->vSpeed == 30)
	{
		if(strcmp(displayState->AC,"ON"))
		{
			strcpy(displayState->AC,"ON");
		}
		printf("AC: %s\n",displayState->AC);
		printf("Room Temperature: %d\n",(int)((*roomTemp) * (2.25)));
#if (WITH_ENGINE_TEMP_CONTROLLER)
		if(strcmp(displayState->etempState,"ON"))
		{
			strcpy(displayState->etempState,"ON");
		}
		printf("Engine Temperature Controller State: %s\n",displayState->etempState);
		printf("Room Temperature: %d\n",(int)((*engineTemp) * (2.25)));
#endif
	}
	else
	{
		printf("AC: %s\n",displayState->AC);
		printf("Room Temperature: %d\n",displayState->rTemp);
#if (WITH_ENGINE_TEMP_CONTROLLER)
		printf("Engine Temperature Controller State: %s\n",displayState->etempState);
		printf("Engine Temperature: %d\n",displayState->etemp);
#endif

	}
	printf("\n");
	fflush(0);
}
void _startInterface (char* userChoice1)
{
	do
	{
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n");
		fflush(0);
		scanf(" %c",userChoice1);
		_displayInitialstate(userChoice1);
	}while(*userChoice1 == 'b');
}
void _sensorSetMenu(char* userChoice2)
{
	printf("a. Turn off the vehicle engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
#if (WITH_ENGINE_TEMP_CONTROLLER)
	printf("d. Set the engine temperature\n");
#endif
	fflush(0);
	scanf(" %c",userChoice2);
	while(!(*userChoice2>='a' && *userChoice2<='d'));
}

void _trafficLightSetting(char* trafficLight,vState* state)
{
	switch(* trafficLight)
	{
	case 'G':
		state->vSpeed = 100;
		break;
	case 'O':
		state->vSpeed = 30;
		break;
	case 'R':
		state->vSpeed = 0;
		break;
	}
}
void _roomTempSetting(uint8* temp,vState* state)
{
	if(*temp < 10 || *temp > 30)
	{
		strcpy(state->AC,"ON");
		state->rTemp = 20;
	}
	else
	{
		strcpy(state->AC,"OFF");
	}
}
void _engineTempSetting(uint8* temp,vState* state)
{
	if(*temp < 100 || *temp > 150)
	{
		strcpy(state->etempState,"ON");
		state->etemp = 125;
	}
	else
	{
		strcpy(state->etempState,"OFF");
	}
}
void _sensorReading(char* userChoice1,char* userChoice2,char* trafficLight,uint8* roomTemp,uint8* engineTemp,vState* state)
{
	strcpy(state->enginestate,"ON");
	switch(*userChoice2)
	{
	case 'a':
		_startInterface(userChoice1);
		if(*userChoice1 != 'c')
		{
			_sensorSetMenu(userChoice2);
		}
		break;
	case 'b':
		printf("is the traffic light is G , O or R :");
		fflush(0);
		scanf(" %c",trafficLight);
		_trafficLightSetting(trafficLight,state);
		_dataVehicleState(state,roomTemp,engineTemp);
		break;
	case 'c':
		printf("enter the room temperature:");
		fflush(0);
		scanf("  %hhd",roomTemp);
		_roomTempSetting(roomTemp,state);
		_dataVehicleState(state,roomTemp,engineTemp);
		break;
#if (WITH_ENGINE_TEMP_CONTROLLER)
	case 'd':
		printf("enter the engine temperature:");
		fflush(0);
		scanf("  %hhd",engineTemp);
		_engineTempSetting(engineTemp,state);
		_dataVehicleState(state,roomTemp,engineTemp);
		break;
#endif
	}
}

