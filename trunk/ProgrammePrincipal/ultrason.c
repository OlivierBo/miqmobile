#include "include.h"
#include "tools.h" 
#include "ultrason.h"
#include "brochage.h"

unsigned long debut;
unsigned long duree;


short distanceUS(void) //en mm
{
	//µs*10/58 = mm
	unsigned long dist = duree*10/58;
	return (short)dist;
}

void receptionUS(void)
{
	if(EDGE_INT0)
	{
		debut=globalTimeMsUs();
		EDGE_INT0=0;
	}
	else
	{
		duree=(unsigned long)(globalTimeMsUs()-debut);
		EDGE_INT0=1;
		if(duree>30000) duree=0;
	}
}

unsigned char lancerUS(void)
{
	unsigned long ii;
	if(globalTimeMsUs()-debut<55000) return ERREUR;
	EDGE_INT0=1;
	ULTRASON_TRIG=1;
	ii=globalTime;
	while(globalTimeMsUs()-ii<20);
	ULTRASON_TRIG=0;
}
