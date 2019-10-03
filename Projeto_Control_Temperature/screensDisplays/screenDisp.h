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
#define PIN_BUT_M	A2
#define PIN_BUT_L	A3
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
 *  First screen on display, show the inital settings
 */
void firstScreen (float var, float analog, bool enb1, bool enb2);

/*
 *  Second screen on display, show the set point configuration screen
 */
void secondScreen (float var);

/*
 *  Third screen on display, show the gain configuration screen
 */
void thirdScreen (float var);

/*
 *  Forth screen on display,show the heat state configuration screen
 */
void fourthScreen(bool var, int pwm);

/*
 * Fifth screen on display, show the set heat configuration screen
 */

void fifthScreen(int pwm);

/*
 * Sixth screen on display,show the fan state configuration screen
 */
void sixthScreen(bool var,int pwm);

/*
 * Seven screen on display, show the set fan configuration screen
 */
void seventhScreen(int pwm);

/*
 * Eighth screen on display, show the drive state screen
 */
void eighthScreen(bool var, bool var2);

/*
 * Manual Heat screen on display
 */
void manualHeat(bool man);

/*
 * Manual Fan screen on display
 */
void manualFan(bool man);
/*
 * Push what display screen is
 */
void pushScreen(int var);

/*
 * Get what display screen is
 */
int getScreen();

/*
 * Clear lcd
 */
void clearLCD();

//bool getMod();
//void pushMod(bool var);

//float getValue(float var);


#endif /* SCREENSDISPLAYS_SCREENDISP_H_ */
