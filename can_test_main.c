#include "lcd_header.h"
#include "lcd_fun.c"
#include "can_fun.c"
#include "can_test.c"	// CAN TEST FUNCTIONS


	int main()
	{
	unsigned char a;
	unsigned int b;
	IODIR1|=(0XFF<<17);   //LEDS AD OP

	IODIR1&=~(1<<25);     // Switch P1.25 as Ignition Key
	IODIR0&=~((1<<4)|(1<<6)|(1<<3));    // P0.4 and P0.6 as input port
	IODIR0|=(1<<11);        // P0.11 Buzzer as a op

	lcd_config();          //LCD configuration
	can_config();		   // CAN configuration

	 	while(1)
		{
		can_test();
		}
	
	}
							  	