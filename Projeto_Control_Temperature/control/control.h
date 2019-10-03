/*
 * control.h
 *
 *  Created on: 28 de set de 2019
 *      Author: samue
 */

#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

typedef float (*Op)(float,float,float);

typedef float (*Op2) (float);

typedef int (*Op3) (float);

/*
 * Control the Heat value
 */
void controlHeat (int pin,int pinEnable, float gain, float setpoint, float sensor, int *value,  bool man);

/*
 * Control the Fan value
 */
void controlFan (int pin,int pinEnable, float gain, float setpoint,  float sensor, int *value, bool man);

/*
 * Reads LM35 sensor
 */
void readSensor(int pin, float *p);


/*
 * Control LED time
 */
void ledControl(float freq, int pin, bool stateD,unsigned long *ultimo,unsigned long *primeiro);



void FirstScreenControl(int pinEnb1, int pinEnb2, int pinButM, int pintButL, int *screen, unsigned long *ultimo,unsigned long *primeiro);

//void delayScreen(unsigned long atual, unsigned long ultimo, )


#endif /* CONTROL_CONTROL_H_ */
