/*
 * calc.h
 *
 *  Created on: 19 de set de 2019
 *      Author: samue
 */

#ifndef CALCULATIONS_CALC_H_
#define CALCULATIONS_CALC_H_

/*
 * Function to change the Set Point Value
 */
float changeSetpoint(float var, float par, int op);

/*
 * Function to change the Gain Value
 */
float changeGain(float var, float par, int op);

/*
 * Function to Heat PWM calculation
 */
float pwmHeat(float gain, float setpoint, float pv);

/*
 * Function to Heat Percent calculation
 */
int percHeat(float value);

/*
 * Function to Fan PWM calculation
 */
float pwmFan(float gain, float setpoint, float pv);

/*
 * Function to Fan Percent calculation
 */
int percFan(float value);

/*
 * Function to change value Percent to PWM
 */
float percPwm(float value);

void desenaFunc(int pin,bool state);


#endif /* CALCULATIONS_CALC_H_ */
