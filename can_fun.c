	#include "lcd_header.h"
	int k=1;

	char MSG[10];
	void can_config(void)
	{
	VPBDIV=2;  		 // Pclk=30Mhz
	/* P0.23, P0.24,P0.25, P10*/
	/*TD2,RD2,RD1*/
	PINSEL1=(1<<14)|(1<<16)|(1<<18);
	 
	C2MOD=(1<<0);   // Disable the CAN2
	C2BTR=(1<<18)|(1<<19)|(1<<20)|(29<<0); // TSEG1=1100, TSEG2=001, BRP=29
	C2MOD=0;   //Enable CAN2

	C1MOD=(1<<0);   // Disable the CAN2
	C1BTR=(1<<18)|(1<<19)|(1<<20)|(29<<0); // TSEG1=1100, TSEG2=001, BRP=29
	C1MOD=0;   //Enable CAN2
	}

	void can_tx(int a)
	{
	 while(!(C2GSR&(1<<2)));  //Check Tx buffer Empty or not
	 C2TID1=0x44;       		// Load Msg Id ti TID Reg
	 C2TFI1=(1<<18);   		// 19 18 17 16--> DLC=0100, RTR=0,IDE=0
	 C2TDA1=a;   			 // Load the data to DATA A Reg
	 C2CMR=(1<<0)|(1<<5);    // queueing and Select Tx buffer 1
	 while(!(C2GSR&(1<<3))); // Check for successful Tx
	}

  int can_rx(void)
	{
	  while(C1GSR&(1<<0)); // Check Rx buffer Empty or not
	  MSG[0]=C1RID;		 //  Load the Rx id to variable
	  MSG[1]=C1RDA;    // Load the Rx data to variable
	  C1CMR=(1<<2);    // Release the Rx Buffer

	 if(k==1)
	 { 
	  lcd_str("ID:");
	  lcd_num(MSG[0]);

	  lcd_cmd(0xc0);
	  lcd_str("MSG:");
	  k++;
	  }
	  
	  lcd_data(MSG[1]);

	  return MSG[1];    // return msg to main pgm
	}

   /*ADC Config*/
	void adc_config(void)
	{

 	PINSEL1|=(1<<24);   // Configure P0.28 as a Temp sensor using PINSEL1 Register
 	PINSEL1&=~(1<<25);	  // 24=1,25=0
 
 	PINSEL1|=(1<<22);   // Configure P0.27 as a Pot using PINSEL1 Register
 	PINSEL1&=~(1<<23);	  // 22=1,23=0
	 /*Configure ADC with ch1(temp Sensor), ClkDiv=4, Burst mode, PDN mode*/
 	ADCR=(1<<1)|(4<<8)|(1<<16)|(1<<21);
  	}

	int adc_read(void)
	{
	int val;
		while(!(ADDR&(1<<31)));
		{
		val=(ADDR&(0X3FF<<6));     //Extract 10 Bit Digital Data to val
		val=val>>6;          // Get val as LSB
		val=val/3.3;
		return val;	
		}
	}
