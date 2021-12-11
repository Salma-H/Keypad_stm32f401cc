/*
 * Author : Abdullah Drwesh
 * Date   : 7/12/2021
 * Version: 1.0.0
 */
#include "GPIO.h"
#include "Keypad.h"

unsigned char sevenSegHex[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                                 0x6D, 0x7D, 0x07, 0x7F, 0x6F};



int main(void) {

  GPIO_EnableClock('A');

  for (unsigned char i = 0; i < 7; i++) {
    GPIO_Init('A', i, OUTPUT, PUSH_PULL);
  } 

  Keypad_init('B');

  while (1) {
  
	  Keypad_manage();

	  // delay
	  for (unsigned int i = 0; i < 50000; i++) {
	  }
  }
  return 0;
}


void KeypadCallouts_KeyPressNotificaton()
{
	char key = Keypad_GetKey();
	if(key == -1)
	{
		return;
	}

	// display key on 7 segment
    for (unsigned char i = 0; i < 7; i++)
    	GPIO_WritePin('A', i, (sevenSegHex[key] & (1 << i)) >> i);

}
