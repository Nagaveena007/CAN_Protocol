	#include "lcd_header.h"
	
	/*Only Fun Defn*/
	void lcd_config(void)
	{
	IODIR0|=RS|RW|EN|DATA;   // Configure all LCD pins as ouput ports
	lcd_cmd(0x38);	      //2 line disp, 8 bit
	lcd_cmd(0x0E);		 //	Cursor on and Disp on
	lcd_cmd(0x01);		 // clear the LCD
	lcd_cmd(0x80);		 // Start from 1st row 1st col
   	}

	void lcd_cmd(unsigned char c)    // Function to Send a Command
	{
	 IOCLR0=DATA;   //Clear The data Lines
	 IOSET0=c<<15;	// Load the command from Pin P0.15 to P0.22
	 IOCLR0=RS;     // Clear RS.. RS=0 for cmd
	 IOCLR0=RW;       //WR=0 for write operation
	 IOSET0=EN;        //Set en bit
	 delay(10);
	 IOCLR0=EN;		  // Clr en bit
	 }

	 void lcd_data(unsigned char d)    // Function to Send a data
	{
	 IOCLR0=DATA;   //Clear The data Lines
	 IOSET0=d<<15;	// Load the command from Pin P0.15 to P0.22
	 IOSET0=RS;     // Set RS.. RS=1 for data
	 IOCLR0=RW;       //WR=0 for write operation
	 IOSET0=EN;        //Set en bit
	 delay(10);
	 IOCLR0=EN;		  // Clr en bit
	 }

	 void delay(unsigned int count)
	{
	int i,j;
	for(i=0;i<=count;i++)
	for(j=0;j<=6000;j++);
	}

	void lcd_str(unsigned char *ptr)
	{
	int i=1;
	   while(*ptr !='\0')
	   {
	   lcd_data(*ptr);
	   	if(i==16)
		{
		lcd_cmd(0xC0);
		}
	   ptr++;
	   i++;
	   }
	}

	void lcd_num(unsigned int num)		 // Function disp numbers
	{
		if(num)
		{
		lcd_num(num/10);	   // Recursive function     num/10 and Create a STACK
		lcd_data(num%10+0x30);	   //Reminder+0x30----> to Disp on LCD
		}
	}

	