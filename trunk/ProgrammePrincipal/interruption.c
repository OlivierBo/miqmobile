#include "interruption.h"
#include "include.h"
#include "asserv.h"


//=============================================================================
//Réglages interruptions
//=============================================================================


#pragma interrupt InterruptHandlerHigh

void InterruptHandlerHigh(void)
{
 //Ecrire ici

	//compteur de temps
}

#pragma code interruption = 0x08
void fonction (void)
{
  _asm
    goto InterruptHandlerHigh //jump to interrupt routine
  _endasm
}
#pragma code


#pragma interrupt lowInterruption
void lowInterruption(void)
{
  //Ecrire ici

	//les rx
	//les mesure du gyro

}

#pragma code low_vector=0x18
void lowInterrupt (void)
{
  //Interruption de basse priorité
	_asm
    goto lowInterruption //jump to interrupt routine
  _endasm
}
#pragma code



void initInter(void)
{
// Fonction pour l'initialisation lors d'une interruption
}
