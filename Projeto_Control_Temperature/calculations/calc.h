/*
 * calc.h
 *
 *  Created on: 19 de set de 2019
 *      Author: samue
 */

#ifndef CALCULATIONS_CALC_H_
#define CALCULATIONS_CALC_H_

float changeSetpoint(float var, float par, int op);
float changeGain(float var, float par, int op);

float pwmHeat(float gain, float setpoint, float pv);
int percHeat(float value);

float pwmFan(float gain, float setpoint, float pv);
int percFan(float value);

float percPwm(float value);

void desenaFunc(int pin,bool state);


#endif /* CALCULATIONS_CALC_H_ */
