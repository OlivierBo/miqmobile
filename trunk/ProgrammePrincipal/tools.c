#include "include.h"
#include "tools.h"
#include "brochage.h"


short acquisition(char channel)
{
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VDD);
	SelChanConvADC(channel); 
	while(BusyADC());
	return ReadADC();
}




void pause_ms(unsigned short ms)
{

unsigned short i,ms100;
unsigned char ms10,ms1;
ms100=ms/100;
ms10=(ms%100)/10;
ms1=ms%10;

for(i=0;i<ms100;i++)
Delay10KTCYx (80); //100ms

if(ms10)
Delay10KTCYx (8*ms10); // delay de 1000 x 8 x 4/32000000 = 10 ms

//max 32 ms - max utilisé : 1ms
if(ms1)
Delay1KTCYx (8*ms1); // delay de 1000 x 8 x 4/32000000 = 1 ms

}