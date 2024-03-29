#include "Arduino.h"
#include "screensDisplays/screenDisp.h"
#include "calculations/calc.h"
#include "control/control.h"

extern "C"{

#include "defines/defines.h"

int cont = SCREEN_FIRST;

}

float sensorRead = 0;
float set_point = VALUE_SETPOINT;
int valueHeat = 0;
int valueFan = 0;
int man = 0;
int manFan =0;
float gain = VALUE_GAIN;
int screen = SCREEN_FIRST;
bool driveDisable =0;

unsigned long ultimo_tempo = 0;
unsigned long  ult_timeLed = 0;
unsigned long ult_tempo = 0;
unsigned long tempo_atual = 0;
long tempo_acionado = 10;

void setup()
{
	 //Serial.begin(9600);
	 Serial.end();
	 pinMode(PIN_BUT_P, INPUT);
	 pinMode(PIN_BUT_M, INPUT);
	 pinMode(PIN_BUT_L, INPUT);
	 pinMode(PIN_BUT_S, INPUT);

	 pinMode(PIN_HEAT,OUTPUT);
	 pinMode(PIN_FAN,OUTPUT);
	 pinMode(PIN_ENB1,OUTPUT);
	 pinMode(PIN_ENB2,OUTPUT);

	// pinMode(PIN_LED, OUTPUT);
	 pinMode(A1,OUTPUT);


	 digitalWrite(PIN_ENB1,1);
	 digitalWrite(PIN_ENB2,1);
	 sensorRead = (analogRead(PIN_LM) * 5.0/1023)/0.01;
	 valueHeat = percHeat( pwmHeat(gain,set_point,sensorRead));
	 valueFan = percFan( pwmFan(gain,set_point,sensorRead));

	initLCD();
	attachInterrupt(digitalPinToInterrupt(PIN_BUT_P), selectSreen, RISING); //Interrup��o no bot�o select


}

// The loop function is called in an endless loop
void loop()
{

	/*
	 * Settings:
	 *
	 *
	 * 			Is possible to configure the gain, increment and frequency in defines.h file.
	 * 			The buttons are:
	 * 						  P: The P button changes to the next screen
	 * 						  M: Up the values and On in the configurations
	 * 						  L: Down the value and OFF in the configurations
	 * 						  S: In the MANUAL_HEAT and MANUAL_FAN choose the state.
	 * 						  	 In the others screens, go back to the First screen.
	 *
	 */

	/*
	 * Read sensor LM35 and do calculations
	 */
	readSensor(PIN_LM,&sensorRead);

	/*
	 * Heart Beat, led blink (1/0.5) *1000
	 */

	ledControl(FREQ_LED,PIN_LED,driveDisable,&ult_timeLed,&tempo_atual);


	/*
	 * Calculation the job
	 */

	tempo_atual = millis();
	if ( tempo_atual-ult_tempo  >= 60)
	{
		if(!driveDisable)
		{


			controlHeat(PIN_HEAT, PIN_ENB1, gain, set_point, sensorRead, &valueHeat, man);

			controlFan(PIN_FAN,PIN_ENB2,gain,set_point, sensorRead, &valueFan, manFan);


			ult_tempo = millis();

		}
	}




	switch(screen)
	{

	/*
	 * case SCREEN_FIRST, show the first screen. Show the initial settings
	 */
		case SCREEN_FIRST:
		{
			tempo_atual = millis();
			if ( tempo_atual-ultimo_tempo  >= 60)
			{
				firstScreen(set_point,sensorRead,digitalRead(PIN_ENB1),digitalRead(PIN_ENB2));

			}


			 if(getScreen())
			 {
				 pushScreen (0);

				 digitalWrite(PIN_BUT_M,0);
				 digitalWrite(PIN_BUT_L,0);

				 screen= SCREEN_SECOND;

			 }

		break;
		}


		/*
		 * case SCREEN_SECOND:, show the second screen. Show the set point value.
		 * Is possible change the set point value.
		 */
		case SCREEN_SECOND:
		{
			tempo_atual = millis();
			if ( tempo_atual - ultimo_tempo >= 50)
			{
				secondScreen(set_point);

			}


			if(digitalRead(PIN_BUT_M))
			{

				tempo_atual = millis();
				while (digitalRead(PIN_BUT_M)==HIGH);
				ultimo_tempo = millis();

					if ( ultimo_tempo - tempo_atual >= tempo_acionado)
					{
						set_point = changeSetpoint(set_point,VALUE_INCR,OP_SUM);

						secondScreen(set_point);
					}

				}

				if(digitalRead(PIN_BUT_L))
				{

					tempo_atual = millis();
					while (digitalRead(PIN_BUT_L)==HIGH);
						ultimo_tempo = millis();

						if ( ultimo_tempo - tempo_atual >= tempo_acionado)
						{

							set_point = changeSetpoint(set_point,VALUE_INCR,OP_SUB);

							secondScreen(set_point);
						}
				}


			if(digitalRead(PIN_BUT_S))
			{

				clearLCD();
				screen = SCREEN_FIRST;
				pushScreen(0);

			}

			if(getScreen())
			{

				thirdScreen(gain);
				screen = SCREEN_THIRD;
				pushScreen (0);

			}


			break;
		}

		/*
		 * case SCREEN_THIRD:, show the third screen. Show the gain value.
		 * Is possible change the gain value.
		 */

		case SCREEN_THIRD:
		{
//
			tempo_atual = millis();
			if ( tempo_atual - ultimo_tempo >= 100)
			{
				thirdScreen(gain);
				ultimo_tempo = millis();

			}



			if(digitalRead(PIN_BUT_M))
			{
				tempo_atual = millis();
				while (digitalRead(PIN_BUT_M) == HIGH);
					ultimo_tempo = millis();

					if ( ultimo_tempo - tempo_atual >= tempo_acionado)
					{
						gain = changeGain(gain,VALUE_INCR,OP_SUM);

						thirdScreen(gain);
					}

				 }
				if(digitalRead(PIN_BUT_L))
				{
					tempo_atual = millis();
					while (digitalRead(PIN_BUT_L) == HIGH);
						ultimo_tempo = millis();

						if ( ultimo_tempo - tempo_atual >= tempo_acionado)
						{

							gain = changeGain(gain,VALUE_INCR,OP_SUB);

							thirdScreen(gain);;
						}
				}

				if(digitalRead(PIN_BUT_S))
				{	clearLCD();
					screen = SCREEN_FIRST;
					pushScreen(0);
				}

				if(getScreen())
				{

					clearLCD();
					screen = MANUAL_HEAT;
					pushScreen(0);
				}

		 break;
		}

		/*
		 * case MANUAL_HEAT:,  Show if the manual mode is ON.
		 * Is possible change the manual heat state.
		 * Button M: On Manual mode Heat
		 * Button L: OFF Manual mode Heat
		 * OBS: After choose the state, ON or OFF, click the button S
		 * If button P the next screen will be the MANUAL_FAN
		 *
		 */
		case MANUAL_HEAT:
		{
			tempo_atual = millis();
			if ( tempo_atual - ultimo_tempo >= 10)
			{
				manualHeat(man);
				ultimo_tempo = millis();
			}


			if(digitalRead(PIN_BUT_M))
			{	man = 1;
				clearLCD();

				manualHeat(man);

			}


			if(digitalRead(PIN_BUT_L))
			{
				man = 0;
				clearLCD();

				manualHeat(man);
			}

			if(digitalRead(PIN_BUT_S))
			{

					digitalWrite(PIN_BUT_S,0);
					clearLCD();
					if(man)
					{
						screen = SCREEN_FOURTH;
					}else{
						screen = SCREEN_FIRST;
					}


				pushScreen(0);
			}

			if(getScreen())
			{

				clearLCD();
				screen = MANUAL_FAN;
				pushScreen(0);
			}

			break;
		}
		/*
		 * case SCREEN_FOURTH:,  Show if the heat mode is ON or OFF.
		 * Is possible change the heat state.
		 * Button M: On heat
		 * Button L: OFF heat
		 */

		case SCREEN_FOURTH:
		{


			tempo_atual = millis();
			if ( tempo_atual -ultimo_tempo  >= 100)
			{
				fourthScreen((bool)digitalRead(PIN_ENB1),valueHeat);
				ultimo_tempo = millis();
			}




			if(digitalRead(PIN_BUT_M))
			{


				clearLCD();


				digitalWrite(PIN_ENB1,1);

			}

			if(digitalRead(PIN_BUT_L))
			{


				clearLCD();
				digitalWrite(PIN_BUT_M,0);
				digitalWrite(PIN_ENB1,0);
				fourthScreen((bool)digitalRead(PIN_ENB1),valueHeat);

			}




			if(digitalRead(PIN_BUT_S))
			{
				//fourthBool = 0;
				clearLCD();
				screen = SCREEN_FIRST;
				pushScreen (0);
			}



				if(getScreen())
				{
					if(digitalRead(PIN_ENB1))
						screen = SCREEN_FIFTH;
					else
						screen = SCREEN_SIXTH;


					clearLCD();

					pushScreen (0);
				}

				break;
		}

		/*
		 * case SCREEN_FOURTH: Show the heat PWM value.
		 * Is possible change the PWM heat state.
		 * Button M: Up the PWM value
		 * Button L: Down the PWM value
		 */
		case SCREEN_FIFTH:
		{

			tempo_atual = millis();
			if ( tempo_atual -ultimo_tempo  >= 100)
			{
				fifthScreen(valueHeat);
				ultimo_tempo = millis();
			}


			if(digitalRead(PIN_BUT_M))
			{

				tempo_atual = millis();
				while (digitalRead(PIN_BUT_M) == HIGH);
					ultimo_tempo = millis();

					if ( ultimo_tempo - tempo_atual >= tempo_acionado)
					{
						valueHeat = valueHeat + 1;

						fifthScreen(valueHeat);
					}

				}
				if(digitalRead(PIN_BUT_L))
				{

					tempo_atual = millis();
					while (digitalRead(PIN_BUT_L) == HIGH);
						ultimo_tempo = millis();

						if ( ultimo_tempo - tempo_atual >= tempo_acionado)
						{
							if(valueHeat == 0)
								valueHeat =0;
							else
								valueHeat = valueHeat - 1;

							fifthScreen(valueHeat);
						}

				}

				if(digitalRead(PIN_BUT_S))
				{

					clearLCD();
					screen = SCREEN_FIRST;
					pushScreen (0);
				}



					if(getScreen())
					{

						screen = MANUAL_FAN;



						clearLCD();

						pushScreen (0);
					}




			break;

		}

		/*
		 * case MANUAL_FAN:,  Show if the fan manual mode is ON.
		 * Is possible change the manual heat state.
		 * Button M: On Manual mode Fan
		 * Button L: OFF Manual mode Fan
		 * OBS: After choose the state, ON or OFF, click the button S
		 * If button P the next screen will be the eighth screen
		 *
		 */
		case MANUAL_FAN:
		{

			tempo_atual = millis();
			if ( tempo_atual -ultimo_tempo  >= 200)
			{
				manualFan(manFan);
				ultimo_tempo = millis();
			}

			if(digitalRead(PIN_BUT_M))
			{
				clearLCD();
				manFan = 1;
				manualFan(manFan);

			}


			if(digitalRead(PIN_BUT_L))
			{

				clearLCD();
				manFan = 0;
				manualFan(manFan);
			}

			if(digitalRead(PIN_BUT_S))
			{

					digitalWrite(PIN_BUT_S,0);

					if(manFan)
					{
						screen = SCREEN_SIXTH;
					}else{
						screen = SCREEN_FIRST;
					}


				pushScreen(0);

			}

			if(getScreen())
			{


					clearLCD();
					screen = SCREEN_EIGHTH;
					pushScreen(0);

			}



			break;
		}

		/*
		 * case SCREEN_SIXTH:,  Show if the fan mode is ON or OFF.
		 * Is possible change the heat state.
		 * Button M: On fan
		 * Button L: OFF fan
		 */
		case SCREEN_SIXTH:
		{


			tempo_atual = millis();
			if ( tempo_atual - ultimo_tempo>= 200)
			{

				sixthScreen((bool)digitalRead(PIN_ENB2),valueFan);
				ultimo_tempo = millis();
			}


			if(digitalRead(PIN_BUT_M))
			{


				clearLCD();


				digitalWrite(PIN_ENB2,1);
				sixthScreen((bool)digitalRead(PIN_ENB2),valueFan);


			}

			if(digitalRead(PIN_BUT_L))
			{

				clearLCD();

				digitalWrite(PIN_ENB2,0);
				sixthScreen((bool)digitalRead(PIN_ENB2),valueFan);

				}

			if(digitalRead(PIN_BUT_S))
			{

				digitalWrite(PIN_BUT_S,0);
				clearLCD();
				screen = SCREEN_FIRST;
				pushScreen (0);
			}



				if(getScreen())
				{
					if(digitalRead(PIN_ENB2))
						screen = SCREEN_SEVENTH;
					else
						screen = SCREEN_EIGHTH;


					clearLCD();

					pushScreen (0);
				}

				break;



		}

		/*
		 * case SCREEN_SEVENTH: Show the fan PWM value.
		 * Is possible change the PWM fan state.
		 * Button M: Up the PWM value
		 * Button L: Down the PWM value
		 */

		case SCREEN_SEVENTH:
		{


			tempo_atual = millis();
			if ( tempo_atual -ultimo_tempo  >= 100)
			{
				seventhScreen(valueFan);
				ultimo_tempo = millis();
			}


			if(digitalRead(PIN_BUT_M))
			{

				tempo_atual = millis();
				while (digitalRead(PIN_BUT_M) == HIGH);
					ultimo_tempo = millis();

					if ( ultimo_tempo - tempo_atual >= tempo_acionado)
					{
						valueFan = valueFan + 1;

						seventhScreen(valueFan);
					}

				}
				if(digitalRead(PIN_BUT_L))
				{

					tempo_atual = millis();
					while (digitalRead(PIN_BUT_L) == HIGH);
						ultimo_tempo = millis();

						if ( ultimo_tempo - tempo_atual >= tempo_acionado)
						{
							if(valueFan == 0)
								valueFan =0;
							else
								valueFan = valueFan - 1;

							seventhScreen(valueFan);
						}

				}

				if(digitalRead(PIN_BUT_S))
				{

					clearLCD();
					screen = SCREEN_FIRST;
					pushScreen (0);
				}



					if(getScreen())
					{

						screen = SCREEN_EIGHTH;



						clearLCD();

						pushScreen (0);
					}

			break;
		}

		/*
		 * case SCREEN_EIGHTH: Show the driver state.
		 * Is possible change drive state
		 * Button M: On driver
		 * Button L: OFF driver
		 */

		case SCREEN_EIGHTH:
		{


			tempo_atual = millis();
			if ( tempo_atual -ultimo_tempo  >= 200)
			{
				eighthScreen(digitalRead(PIN_ENB1),digitalRead(PIN_ENB2));
				ultimo_tempo = millis();
			}


			if(digitalRead(PIN_BUT_M))
			{
				driveDisable = 0;
				digitalWrite(PIN_ENB1,1);
				digitalWrite(PIN_ENB2,1);
			}


			if(digitalRead(PIN_BUT_L))
			{
				driveDisable = 1;
				digitalWrite(PIN_ENB1,0);
				digitalWrite(PIN_ENB2,0);
			}



				if(digitalRead(PIN_BUT_S))
				{
					clearLCD();
					screen = SCREEN_FIRST;
					pushScreen (0);
				}



				if(getScreen())
				{
					screen = SCREEN_FIRST;
					clearLCD();
					pushScreen (0);
				}

			break;
		}
	}




}

