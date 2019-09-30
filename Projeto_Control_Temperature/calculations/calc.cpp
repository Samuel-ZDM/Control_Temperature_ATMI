/*
 * calc.cpp
 *
 *  Created on: 19 de set de 2019
 *      Author: samue
 */

#include "Arduino.h"

float changeSetpoint(float var, float par, int op)
{
	if(op)
	{
		var = var - par;
	}else{
		var = var + par;
	}

	return var;

}

float changeGain(float var, float par, int op)
{
	if(op)
	{
		var = var - par;
	}else{
		var = var + par;
	}

	return var;

}

float pwmHeat(float gain, float setpoint, float pv)
{
	float var;


	var = (setpoint - pv)*gain;





	if(var > 65)
		var = 65;

	if(var <= 0)
		var =0;

	return var;
}

int percHeat(float value)
{
	int var;
	var = map(value,0,65,0,100);

	return var;
}



float pwmFan(float gain, float setpoint, float pv)
{
	float var;

	var = (-setpoint + pv)*10;





	if(var > 255)
		var = 255;
	if(var < 70)
		var =70;

	return var;
}
int percFan(float value)
{
	int var;
	var = map(value,0,255,0,100);

	return var;
}


void desenaFunc(int pin,bool state)
{
	digitalWrite(pin,state);
}

float percPwm(float value)
{
	float var;

	var = map(value, 0,100,0,255);

	return var;
}
