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
//float value = 0;
int screen = SCREEN_FIRST;
//valor = &float();
bool fourthBool = 0;

unsigned long ultimo_tempo = 0;
unsigned long tempo_atual = 0;
long tempo_acionado = 100;

void setup()
{
	 //Serial.begin(9600);

	 pinMode(PIN_BUT_P, INPUT_PULLUP);
	 pinMode(PIN_BUT_M, INPUT_PULLUP);
	 pinMode(PIN_BUT_L, INPUT_PULLUP);
	 pinMode(PIN_BUT_S, INPUT_PULLUP);

	 pinMode(PIN_HEAT,OUTPUT);
	 pinMode(PIN_FAN,OUTPUT);
	 pinMode(PIN_ENB,OUTPUT);
	 //pinMode(A1,OUTPUT);

	initLCD();
	attachInterrupt(digitalPinToInterrupt(PIN_BUT_P), selectSreen, RISING); //Interrupção no botão select
}

// The loop function is called in an endless loop
void loop()
{

	digitalWrite(PIN_ENB,1);
	for (int i = 0; i < 50; i++)
	{
		sensorRead += (analogRead(PIN_LM) * 5.0/1023)/0.01;

	}

	sensorRead = sensorRead /50;


//	if(set_point >= sensorRead )
//	{
//
//		for(int i = 0; i<10;i++){
//			analogWrite(PIN_HEAT, pwmHeat(gain,set_point,sensorRead));
//			delay(100);
//		}
//
//		digitalWrite(A1,1);
//		//
//	}

	//analogWrite(A1,0);

	 //controlHeat(PIN_HEAT,gain,set_point,sensorRead,pwmHeat);
	//controlFan(PIN_FAN,gain,set_point,sensorRead,pwmFan);


	switch(screen)
	{
		case SCREEN_FIRST:
		{
			tempo_atual = millis();
			if ( tempo_atual-ultimo_tempo  >= 200)
			{
				firstScreen(set_point,sensorRead);
				ultimo_tempo = millis();
			}





			 if(getScreen())
			 {

				 secondScreen(set_point);
				 pushScreen(0);
				 screen= SCREEN_SECOND;

			 }

		break;
		}


		case SCREEN_SECOND:
		{
			tempo_atual = millis();
			if ( tempo_atual - ultimo_tempo >= 100)
			{
			secondScreen(set_point);
			ultimo_tempo = millis();
			}


			if(digitalRead(PIN_BUT_M))
			{
				tempo_atual = millis();
				while (digitalRead(PIN_BUT_M) == HIGH);
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
					while (digitalRead(PIN_BUT_L) == HIGH);
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
				//Serial.println("Vai para o proximo");
				screen = SCREEN_THIRD;
				pushScreen (0);
				//thirdScreen(gain);
			}


			break;
		}

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

		case MANUAL_HEAT:
		{
			tempo_atual = millis();
			if ( tempo_atual - ultimo_tempo >= 100)
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
				tempo_atual = millis();
				while(digitalRead(PIN_BUT_S));
				if ( ultimo_tempo- tempo_atual >= 50)
				{
					digitalWrite(PIN_BUT_S,0);
					clearLCD();
					if(man)
					{
						screen = SCREEN_FOURTH;
					}else{
						screen = SCREEN_FIRST;
					}
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

		case SCREEN_FOURTH:
		{
			//analogWrite(PIN_HEAT, pwmHeat(gain,set_point,sensorRead));

			if(!fourthBool)
			{


				//digitalWrite(PIN_HEAT,1);
				valueHeat = percHeat( pwmHeat(gain,set_point,sensorRead));
			}


			tempo_atual = millis();
			if ( tempo_atual -ultimo_tempo  >= 200)
			{
				fourthScreen((bool)digitalRead(PIN_HEAT),valueHeat);
				ultimo_tempo = millis();
			}




			if(digitalRead(PIN_BUT_M))
			{
//				tempo_atual = millis();
//				while (digitalRead(PIN_BUT_M) == HIGH);
//					ultimo_tempo = millis();
				fourthBool = 1;
//					if ( ultimo_tempo - tempo_atual >= 2000)
//					{
				clearLCD();


				digitalWrite(PIN_HEAT,1);
				//fourthScreen((bool)digitalRead(PIN_HEAT),valueHeat);

					//}
			}

			if(digitalRead(PIN_BUT_L))
			{

				fourthBool = 1;
				clearLCD();
				digitalWrite(PIN_BUT_M,0);
				digitalWrite(PIN_HEAT,0);
				fourthScreen((bool)digitalRead(PIN_HEAT),valueHeat);

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
					if(digitalRead(PIN_HEAT))
						screen = SCREEN_FIFTH;
					else
						screen = SCREEN_SIXTH;

					//fourthBool = 0;
					clearLCD();

					pushScreen (0);
				}

				break;
		}


		case SCREEN_FIFTH:
		{

			tempo_atual = millis();
			if ( tempo_atual -ultimo_tempo  >= 200)
			{
				fifthScreen(valueHeat);
				ultimo_tempo = millis();
			}
			//analogWrite(PIN_HEAT, pwmHeat(gain,set_point,sensorRead));

			if(digitalRead(PIN_BUT_M))
			{
				fourthBool = 1;
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
					fourthBool = 1;
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
					fourthBool = 0;
					clearLCD();
					screen = SCREEN_FIRST;
					pushScreen (0);
				}



					if(getScreen())
					{

						screen = SCREEN_SIXTH;


						fourthBool = 0;
						clearLCD();

						pushScreen (0);
					}




			break;

		}

		case MANUAL_FAN:
		{

			manualFan(manFan);
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
			{	clearLCD();
				if(manualFan)
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

		case SCREEN_SIXTH:
		{


			if(!fourthBool)
			{


				tempo_atual = millis();
				if ( tempo_atual - ultimo_tempo>= 200)
				{
					//digitalWrite(PIN_FAN,1);
					analogWrite(PIN_FAN, pwmFan(gain,set_point,sensorRead));
					valueFan = percFan( pwmFan(gain,set_point,sensorRead));
					sixthScreen((bool)digitalRead(PIN_FAN),valueFan);
					ultimo_tempo = millis();
				}

			}


			if(digitalRead(PIN_BUT_M))
			{
//				tempo_atual = millis();
//				while (digitalRead(PIN_BUT_M) == HIGH);
//					ultimo_tempo = millis();
				fourthBool = 1;
//					if ( ultimo_tempo - tempo_atual >= 2000)
//					{
				clearLCD();


				digitalWrite(PIN_FAN,1);
				sixthScreen((bool)digitalRead(PIN_FAN),valueFan);

					//}
			}

			if(digitalRead(PIN_BUT_L))
			{
				fourthBool = 1;
				clearLCD();

				digitalWrite(PIN_FAN,0);
				sixthScreen((bool)digitalRead(PIN_FAN),valueFan);


//

				}





			if(digitalRead(PIN_BUT_S))
			{
				fourthBool = 0;
				clearLCD();
				screen = SCREEN_FIRST;
				pushScreen (0);
			}



				if(getScreen())
				{
					if(digitalRead(PIN_FAN))
						screen = SCREEN_SEVENTH;
					else
						screen = SCREEN_EIGHTH;

					fourthBool = 0;
					clearLCD();

					pushScreen (0);
				}

				break;



		}

		case SCREEN_SEVENTH:
		{


			tempo_atual = millis();
			if ( tempo_atual -ultimo_tempo  >= 100)
			{
				seventhScreen(valueFan);
				ultimo_tempo = millis();
			}
			//analogWrite(PIN_HEAT, pwmHeat(gain,set_point,sensorRead));

			if(digitalRead(PIN_BUT_M))
			{
				fourthBool = 1;
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
					fourthBool = 1;
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
					fourthBool = 0;
					clearLCD();
					screen = SCREEN_FIRST;
					pushScreen (0);
				}



					if(getScreen())
					{

						screen = SCREEN_EIGHTH;


						fourthBool = 0;
						clearLCD();

						pushScreen (0);
					}

			break;
		}

		case SCREEN_EIGHTH:
		{


			tempo_atual = millis();
			if ( tempo_atual -ultimo_tempo  >= 200)
			{
				eighthScreen(digitalRead(PIN_ENB));
				ultimo_tempo = millis();
			}
			//analogWrite(PIN_HEAT, pwmHeat(gain,set_point,sensorRead));

			if(digitalRead(PIN_BUT_M))
				digitalWrite(PIN_ENB,1);

			if(digitalRead(PIN_BUT_L))
				digitalWrite(PIN_ENB,0);


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


//
//			if(digitalRead(PIN_BUT_L))
//			{
//				tempo_atual = millis();
//				while (digitalRead(PIN_BUT_L) == HIGH);
//					ultimo_tempo = millis();
//					if ( ultimo_tempo - tempo_atual >= 1000)
//					{
//						clearLCD();
//						while(!digitalRead(PIN_BUT_S))
//						{
//
//							if(digitalRead(PIN_BUT_M))
//							{
//								fourthBool = 1;
//								tempo_atual = millis();
//								while (digitalRead(PIN_BUT_M) == HIGH);
//									ultimo_tempo = millis();
//
//									if ( ultimo_tempo - tempo_atual >= tempo_acionado)
//									{
//										valueFan = valueFan + 1;
//
//										fifthScreen((bool)digitalRead(PIN_FAN),valueFan);
//									}
//
//								}
//								if(digitalRead(PIN_BUT_L))
//								{
//									fourthBool = 1;
//									tempo_atual = millis();
//									while (digitalRead(PIN_BUT_L) == HIGH);
//										ultimo_tempo = millis();
//
//										if ( ultimo_tempo - tempo_atual >= tempo_acionado)
//										{
//											valueFan = valueFan - 1;
//											fifthScreen((bool)digitalRead(PIN_FAN),valueFan);
//										}
//
//								}
//						}
//				}
//
//			}
//
//
//
//			if(digitalRead(PIN_BUT_S))
//			{
//				fourthBool = 0;
//				clearLCD();
//				screen = SCREEN_FIRST;
//				pushScreen (screen);
//			}
//
//
//
//				if(digitalRead(PIN_BUT_P))
//				{
//					//Serial.println("Vai para o proximo");
//					fourthBool = 0;
//
//					clearLCD();
//					screen = SCREEN_SIXTH;
//				}


