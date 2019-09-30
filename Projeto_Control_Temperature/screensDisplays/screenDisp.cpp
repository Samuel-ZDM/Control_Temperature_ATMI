/*
 * screenDisp.cpp
 *
 *  Created on: 18 de set de 2019
 *      Author: samuel
 */

#include "screenDisp.h"
#include <math.h>


#include "Arduino.h"
#include <LiquidCrystal.h>


int state_screen = SCREEN_FIRST;
bool mod = false;

unsigned long ultimotempo = 0;
unsigned long tempoatual = 0;
long tempoacionado = 50;
bool ch =0;



LiquidCrystal lcd(PIN_DIS_RS, PIN_DIS_E, PIN_DISP4, PIN_DISP5, PIN_DISP6, PIN_DISP7);

void initLCD()
{
	lcd.begin(16, 2);
	lcd.display();
	//delay(100);
	lcd.clear();
}

void selectSreen()
{
	lcd.clear();
	delay(200);

    state_screen = 1;

	//lcd.clear();
//	if(state_screen > 6)
//		state_screen = 0;




}

void screenPrintVar(uint8_t row, uint8_t col, float var, const char *unit)
{
	lcd.setCursor(col,row);
	lcd.print(var);
	lcd.print(unit);
}

void firstScreen (float var, float analog)
{
	//lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("SP: ");
	lcd.setCursor(4,0);
	lcd.print(var);
	if(var/100.0 >= 1.0)
		lcd.setCursor(10,0);
	else
		lcd.setCursor(8,0);

	lcd.print("C");

	lcd.setCursor(0,2);
	lcd.print("PV: ");
	lcd.setCursor(4,2);
	lcd.print(analog);
	lcd.setCursor(8,2);

	if(analog/100.0 >= 1.0)
		lcd.setCursor(10,2);
	else
		lcd.setCursor(8,2);

	lcd.print("C");


}
void secondScreen (float var)
{
	//lcd.clear();
	lcd.setCursor(1,0);
	lcd.print("New Set Point ");
	lcd.setCursor(1,2);
	lcd.print("SP: ");
	lcd.setCursor(4,2);
	lcd.print(var);


}

void thirdScreen (float var)
{
	//lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("New Prop. Gain ");
	lcd.setCursor(0,2);
	lcd.print("Kp: ");
	lcd.setCursor(4,2);
	lcd.print(var);


}
void fourthScreen(bool var,int pwm)
{
	lcd.setCursor(1,0);
	lcd.print("Manual Mode ST ");
	lcd.setCursor(0,2);
	lcd.print("Heat: ");
	if(var)
	{
		lcd.setCursor(6,2);
		lcd.print("ON");
		lcd.setCursor(9,2);
		lcd.print(pwm);
		lcd.setCursor(11,2);
		lcd.print("%");

	}else{
		lcd.setCursor(6,2);
		lcd.print("OFF");
	}

	//lcd.setCursor(8,1);
	//lcd.print(var);
}


void fifthScreen(int pwm)
{

	lcd.setCursor(1,0);
	lcd.print("Manual Mode OUT ");
	lcd.setCursor(0,2);
	lcd.print("Heat: ");

	lcd.setCursor(6,2);
	lcd.print("ON");
	lcd.setCursor(9,2);
	lcd.print(pwm);
	lcd.setCursor(11,2);
	lcd.print("%");


	//lcd.setCursor(8,1);
	//lcd.print(var);

}
void sixthScreen(bool var, int pwm)
{
	lcd.setCursor(1,0);
	lcd.print("Manual Mode ST");
	lcd.setCursor(0,2);
	lcd.print("FAN: ");
	if(var)
	{
		lcd.setCursor(4,2);
		lcd.print("ON");
		lcd.setCursor(7,2);
		lcd.print(pwm);

		if(pwm/100>=1)
		{
			lcd.setCursor(10,2);
			if(ch==1)
			{
				ch =0;
				clearLCD();
			}


		}else{
			lcd.setCursor(9,2);
			if(ch==0)
			{
				ch =1;
				clearLCD();
			}
		}



		lcd.print("%");

	}else{
		lcd.setCursor(8,2);
		lcd.print("OFF");
	}
}

void seventhScreen(int pwm)
{
	lcd.setCursor(1,0);
	lcd.print("Manual Mode OUT ");
	lcd.setCursor(0,2);
	lcd.print("FAN: ");

	lcd.setCursor(6,2);
	lcd.print("ON");
	lcd.setCursor(9,2);
	lcd.print(pwm);
	lcd.setCursor(11,2);
	lcd.print("%");


}
void eighthScreen(bool var)
{
	lcd.setCursor(1,0);
	lcd.print("Driver Status ");

	if(var)
	{
		lcd.setCursor(2,2);
		lcd.print("Enable");

	}else{
		lcd.setCursor(2,2);
		lcd.print("Disable");
	}
}

void manualHeat(bool man)
{
	lcd.setCursor(1,0);
	lcd.print("HEAT Manual");
	lcd.setCursor(0,2);
	if(man)
	{
		lcd.print("Manual    ON ");
	}else{
		lcd.print("Manual    OFF ");
	}

}

void manualFan(bool man)
{
	lcd.setCursor(1,0);
	lcd.print("FAN Manual");
	lcd.setCursor(0,2);
	if(man)
	{
		lcd.print("Manual    ON ");
	}else{
		lcd.print("Manual    OFF ");
	}
}

int getScreen()
{
	return state_screen;
}

void pushScreen(int var)
{
	//lcd.clear();
	state_screen = var;
}

bool getMod()
{
	return mod;
}

void pushMod(bool var)
{
	lcd.clear();
	mod = var;
}

void clearLCD()
{
	delay(100);
	lcd.clear();
}
