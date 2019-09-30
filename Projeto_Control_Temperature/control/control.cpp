/*
 * control.cpp
 *
 *  Created on: 28 de set de 2019
 *      Author: samue
 */

#include "Arduino.h"

#include "control.h"
#include "../calculations/calc.h"

void controlHeat (int pin,float gain, float set, int value, bool man, float sensor, Op op)
{
	if(man)
	{
		analogWrite(pin,percPwm(value));
	}else{
		analogWrite(pin, op(gain,set,sensor));
	}
	while(set >= sensor){


	}
	if(set <= sensor)
		digitalWrite(pin,0);
	else
		digitalWrite(pin,1);




}


void controlFan (int pin,float gain, float set, float sensor, Op op)
{
	while(set <= sensor)
		analogWrite(pin, op(gain,set,sensor));

	if(set >= sensor)
		digitalWrite(pin,0);
	else
		digitalWrite(pin,1);
}
