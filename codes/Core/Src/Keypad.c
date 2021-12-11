/*
 * Author : Abdullah Drwesh
 * Date   : 8/12/2021
 * Version: 1.0.0
 */
#include "GPIO.h"
#include "Keypad.h"


static unsigned char key_map[4][3] = {{1, 2, 3},
							   	   	  {4, 5, 6},
									  {7, 8, 9},
									  {0, 0, 0}};

static unsigned char buttonPressed = 0;
static char key;

void delay30ms() {
  for (unsigned int i = 0; i < 30000; i++) {
  }
}

void Keypad_init()
{
	GPIO_EnableClock('B');

	// takes first 3 pins as output (upper in keypad)
	for(char i = 0; i < 3; i++)
	{
		GPIO_Init('B', i, OUTPUT, PUSH_PULL);
		GPIO_WritePin('B', i, 1);
	}
	// takes next 4 pins as input (side in keypad)
	for(char i = 3; i < 7; i++)
		GPIO_Init('B', i, INPUT, PULL_UP);
}


void Keypad_manage()
{
	// there is no press yet
	if(!buttonPressed)
	{
		unsigned char row, col;
		for(col = 0; col < 3; col++)
		{
			// activate column
			GPIO_WritePin('B', col, 0);
			for(row = 3; row < 7; row++)
			{
				if(!GPIO_ReadPin('B', row))        //
				{									  //
					delay30ms();                      //  --> Read Pin
					if(!GPIO_ReadPin('B', row))    //
					{
						buttonPressed = 1;
						// store i and j
						key = key_map[row - 3][col];
						// use the pressed key by the user
						KeypadCallouts_KeyPressNotificaton();
					}
				}

			}
			// deactivate column
			GPIO_WritePin('B', col, 1);

		}
	}
}


char Keypad_GetKey()
{
	if(buttonPressed)
	{
		//release
		buttonPressed = 0;
		return key;
	}
	else
		return -1;
}
