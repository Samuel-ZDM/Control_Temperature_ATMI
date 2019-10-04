/*
 * control.cpp
 *
 *  Created on: 28 de set de 2019
 *      Author: samue
 */

#include "Arduino.h"

#include "control.h"
#include "../calculations/calc.h"
#include "../screensDisplays/screenDisp.h"

void controlHeat (int pin,int pinEnable, float gain, float setpoint, float sensor, int *value,  bool man)
{
	if(setpoint > sensor)
	{
		if(man)
		{

			analogWrite(pin,percPwm(*value));

		}else{

			digitalWrite(pinEnable, 1);
			*value = percHeat( pwmHeat(gain,setpoint,sensor));
			analogWrite(pin, pwmHeat(gain,setpoint,sensor));
		}

	}else{
		if(!man)
			digitalWrite(pinEnable, 0);
		else

			analogWrite(pin,percPwm(*value));

	}

}


void controlFan (int pin, int pinEnable, float gain, float setpoint, float sensor, int *value, bool manFan)
{
	if(setpoint < sensor )
	{

		if(manFan)
		{

			analogWrite(pin,percPwm(*value));
		}else{
			digitalWrite(pinEnable, 1);
			*value = percFan( pwmFan(gain,setpoint,sensor));
			analogWrite(pin, pwmFan(gain,setpoint,sensor));

		}



	}else{
		if(!manFan)
			digitalWrite(pinEnable, 0);
		else

			analogWrite(pin,percPwm(*value));
	}

}

void readSensor(int pin, float *p)
{
	for (int i = 0; i < 50; i++)
	{
		*p += (analogRead(pin) * 5.0/1023)/0.01;
		delay(1);
	}

	*p = *p /50;
}

void ledControl(float freq, int pin, bool stateD,unsigned long *ultimo,unsigned long *primeiro)
{
	*primeiro = millis();
	if ( *primeiro-*ultimo  >= freq*1000)
		{

			digitalWrite(pin, 1);
			*ultimo = millis();
			clearLCD();
		}
		*primeiro = millis();
		if ( *primeiro-*ultimo   >= 200)
		{
			if(!stateD)
				digitalWrite(pin, 0);

		}
}

