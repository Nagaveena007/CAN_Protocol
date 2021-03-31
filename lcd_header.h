#include <lpc21xx.h>
/*MACROs DFN*/
#define RS  (1<<10)
#define RW  (1<<12)
#define EN  (1<<13)
#define DATA (0xFF<<15)

/*Function Declr*/
void lcd_config(void);
void lcd_cmd(unsigned char c);
void lcd_data(unsigned char d);
void delay(unsigned int count);
void lcd_str(unsigned char *ptr);
void lcd_num(unsigned int num);

/*CAN Functions decl*/
void can_config(void);
void can_tx( int ch);
 int can_rx(void);

/*ADC Configurations*/
unsigned int adc_data(void);
void adc_config(void);

void can_test(void);