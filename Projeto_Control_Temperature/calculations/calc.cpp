/*
 * calc.cpp
 *
 *  Created on: 19 de set de 2019
 *      Author: samue
 */

#include "Arduino.h"

/*
 * This function change the set point value
 */
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

/*
 * This function change the gain value
 */
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

/*
 * This function calculates heat pwm
 */
float pwmHeat(float gain, float setpoint, float pv)
{
	float var;


	var = (setpoint - pv)*(gain*3);





	if(var > 65)
		var = 65;

	if(var <= 0)
		var =0;

	return var;
}
/*
 * This function calculates the percentage of pwm used by the heat
 */
int percHeat(float value)
{
	int var;
	var = map(value,0,65,0,100);

	return var;
}


/*
 * This function calculates fan pwm
 */
float pwmFan(float gain, float setpoint, float pv)
{
	float var;

	var = (-setpoint + pv)*(gain*2);





	if(var > 255)
		var = 255;
	if(var < 80)
		var = 80;

	return var;
}

/*
 * This function calculates the percentage of pwm used by the fan
 */
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
/*
 * This function does percentage conversion to pwm
 */
float percPwm(float value)
{
	float var;

	var = map(value, 0,100,0,255);

	return var;
}
