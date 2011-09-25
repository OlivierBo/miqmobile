#include "include.h"
#include "time.h"



void pause_ms(unsigned short ms)
{

unsigned short i,ms100;
unsigned short ms10,ms1;
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