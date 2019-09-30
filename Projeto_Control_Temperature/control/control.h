/*
 * control.h
 *
 *  Created on: 28 de set de 2019
 *      Author: samue
 */

#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

typedef float (*Op)(float,float,float);

void controlHeat (int pin,float gain, float set, float sensor, Op op);

void controlFan (int pin,float gain, float set, int value, bool man, float sensor, Op op);




#endif /* CONTROL_CONTROL_H_ */
