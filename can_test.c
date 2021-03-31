	/* CAN_TEST Function file*/

#include "lcd_header.h"

		/* Disply mesg*/
		void can_test(void)
		{
		  lcd_cmd(0x01);
		  lcd_str("CAN MODULE TEST");//welcome message
		  delay(3000);

if(IOPIN1&(1<<25))	       // If Switch  P1.25 (Ignition Key) is pressed enter into the test condistion
                           // Else turn off the engine
{
 lcd_cmd(0x01);
 lcd_str("Ignition Key Pass.... ");
 delay(3000);

		  	if(IOPIN0&(1<<4))			  // Monitor P0.4
		  {
		  			can_tx(0x1F);		  // Tx 0x1F if P0.4-> Vcc
		  				if(can_rx()==0x1F)
						{
						lcd_cmd(0x01);
						lcd_str("SEAT BELT IS ON....");
						delay(2000);
						}
						}

			else
			{
			    lcd_cmd(0x01);
				lcd_str("SEAT BELT IS OFF....");
					delay(2000);
			}

		
		if(IOPIN0&(1<<6))
		  {
		  			can_tx(0x2F);
		  				if(can_rx()==0x2F)
						{
						lcd_cmd(0x01);
						lcd_str("HAND BREAK IS RELEASED....");
						delay(2000);
						}
						}

			else
			{
			    lcd_cmd(0x01);
				lcd_str("HAND BREAK IS NOT RELEASED....");
					delay(2000);
			}

			while(IOPIN0&(1<<4)&&IOPIN0&(1<<6))
			{
  				if(IOPIN0&(1<<4)&&IOPIN0&(1<<6))
				{
				IOSET1=(0XFF<<17);
				delay(500);
				IOCLR1=(0XFF<<17);
				delay(500);
				lcd_cmd(0x01);
				lcd_str("ENGINE IS ON....");
				//delay(2000);
			 	}
				}
			 
			 	if(!(IOPIN0&(1<<4)&&IOPIN0&(1<<6)))	   // false condistion
			 	{
			 	IOCLR1=(0XFF<<17);
				lcd_cmd(0x01);
				lcd_str("ENGINE IS OFF...");
				delay(4000);
			 
			 	IOSET0=(1<<11);
			 	delay(200);
			 	IOCLR0=(1<<11);
			 	delay(200);
				//can_test();
			
			 	}
}

else	  // Not ignited  Key(P1.25)

lcd_cmd(0x01);
lcd_str("ENGINE IS OFF....");
delay(3000);
IOSET0=(1<<11);
delay(200);
IOCLR0=(1<<11);
delay(200);
can_test();

 }		    

		  