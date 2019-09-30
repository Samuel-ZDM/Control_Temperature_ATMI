/*
 * screenDisp.h
 *
 *  Created on: 18 de set de 2019
 *      Author: samuel
 */

#ifndef SCREENSDISPLAYS_SCREENDISP_H_
#define SCREENSDISPLAYS_SCREENDISP_H_

#include <stdint.h>

#define SCREEN_FIRST	0
#define SCREEN_SECOND   1
#define SCREEN_THIRD	2
#define SCREEN_FOURTH	3
#define SCREEN_FIFTH	4
#define SCREEN_SIXTH 	5
#define SCREEN_SEVENTH  6
#define SCREEN_EIGHTH	7
#define MANUAL_HEAT		8
#define MANUAL_FAN		9
/*
 * Display pins
 */

#define PIN_DISP4	4
#define PIN_DISP5	5
#define PIN_DISP6	6
#define PIN_DISP7	7
#define PIN_DIS_RS	12
#define PIN_DIS_E	11

/*
 * Buttons pins
 */
#define PIN_BUT_P	2
#define PIN_BUT_M	1
#define PIN_BUT_L	0
#define PIN_BUT_S	3


/*
 * Start display
 */
void initLCD();

/*
 * Interruption to chose the screen
 */
void selectSreen();

/*
 * Print message on specified address
 */
void screenPrintVar(uint8_t row, uint8_t col, float var, const char *unit);

/*
 *  First screen on display
 */
void firstScreen (float var, float analog);

/*
 *  Second screen on display
 */
void secondScreen (float var);

/*
 *  Third screen on display
 */
void thirdScreen (float var);

/*
 *  Forth screen on display
 */
void fourthScreen(bool var, int pwm);

/*
 * Fifth screen on display
 */

void fifthScreen(int pwm);

void sixthScreen(bool var,int pwm);

void seventhScreen(int pwm);

void eighthScreen(bool var);

void manualHeat(bool man);

void manualFan(bool man);
/*
 * Push what display screen is
 */
void pushScreen(int var);

/*
 * Get what display screen is
 */
int getScreen();


void clearLCD();

bool getMod();
void pushMod(bool var);

//float getValue(float var);


#endif /* SCREENSDISPLAYS_SCREENDISP_H_ */
