#include "include.h"
#include "tools.h" 
#include "ultrason.h"
#include "brochage.h"

unsigned long debut=0;
unsigned long duree=0;


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
		if(duree>30000) duree=30000;
	}
}

unsigned char lancerUS(void)
{
	static unsigned long ii=0;
	if(globalTimeMsUs()-ii<55000) return ERREUR;
	EDGE_INT0=1;
	ULTRASON_TRIG=1;
	ii=globalTimeMsUs();
	while(globalTimeMsUs()-ii<20);
	ULTRASON_TRIG=0;
}
