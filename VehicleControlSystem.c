/*
 * VehicleControlSystem.c
 *
 *  Created on: ٠٢‏/٠٩‏/٢٠٢١
 *      Author: MALEK MAHMOUD
 */
#include "system.h"
vState state;

int main()
{
	char user,user2,trafficsensor;
	unsigned char roomsensor=10,enginesensor=100;
	_initialState(&state);
	/*start options*/
	_startInterface (&user);
	while(user != 'c' )
	{
		_sensorSetMenu(&user2);
		_sensorReading(&user,&user2,&trafficsensor,&roomsensor,&enginesensor,&state);
	}
	return 0;
}
