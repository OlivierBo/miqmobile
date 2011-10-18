#include "include.h"
#include "tools.h"
#include "brochage.h"


volatile unsigned short globalTime=0;


unsigned short tempsEcouleDepuisMs(unsigned short time)
{
	return globalTime-time;
}

char siDelaiEcouleMs(unsigned short time, unsigned short duree)
{
	return globalTime-time>duree;
}

void pauseMs(unsigned short duree)
{
	unsigned short debut = globalTime;
	while(globalTime-debut<duree);
}

unsigned short globalTimeUs(void)
{
	//peut aller jusqu'à un maximum de 1ms
	return (ReadTimer3()-63535)/2 ;
}

void pauseUs(unsigned short duree)
{
	//utile pour générer des triggers
	unsigned short debut = globalTimeUs();
	while(globalTimeUs()-debut<duree);
}

unsigned long globalTimeMsUs(void)
{
	unsigned long tus = (unsigned long)globalTimeUs +  globalTime*1000;
	return tus;
}

unsigned long tempsEcouleDepuisMsUs(unsigned long time)
{
	return globalTimeMsUs()-time;
}


void pauseTcyMs(unsigned short ms)
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
	
	//max 32 ms - max utilisÃ© : 1ms
	if(ms1)
	Delay1KTCYx (8*ms1); // delay de 1000 x 8 x 4/32000000 = 1 ms

}





//aton assez attendu?
//attendre

short acquisition(char channel)
{
	pauseUs(50);
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VDD);
	SelChanConvADC(channel); 
	while(BusyADC());
	return ReadADC();
}




char writeEeprom(void* data, unsigned short adress,  unsigned char longueur)
{
	unsigned short i;
	unsigned char buffer;
	
	if(adress+i>EEPROM_END) return ERREUR;

	for(i=0;i<longueur;i++)
	{
		memcpy(&buffer, (void*)data + i, 1);
		Busy_eep ();
		Write_b_eep (adress+i, buffer); 
	}

	return OK;
}


char readEeprom(void* data, unsigned short adress,  unsigned char longueur)
{
	unsigned short i;
	unsigned char buffer;
	
	if(adress+i>EEPROM_END) return ERREUR;

	for(i=0;i<longueur;i++)
	{
		buffer = Read_b_eep (adress+i); 
		memcpy((void*)(data)+i, (void*)(&buffer), 1);
	}

	return OK;
}
