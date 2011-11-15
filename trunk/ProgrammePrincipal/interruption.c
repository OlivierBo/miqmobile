#include "interruption.h"
#include "include.h"
#include "asserv.h"
#include "tools.h"
#include "codeur.h"
#include "communication.h"
#include "brochage.h"


//=============================================================================
//Réglages interruptions
//=============================================================================
#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh (void)
{
  _asm
    goto InterruptHandlerHigh //jump to interrupt routine
  _endasm
}



#pragma code
#pragma interrupt InterruptHandlerHigh

void InterruptHandlerHigh()
{
	if(PIR2bits.TMR3IF) //timer 3 = globalTime
	{
		WriteTimer3(63535); 
		globalTime++;
		PIR2bits.TMR3IF=0;
	}

	if(	INTCONbits.INT0IF) //INT0 = ultrason
	{
		
		INTCONbits.INT0IF=0;
	}
}




#pragma code InterruptVectorlow = 0x18
void InterruptVectorlow (void)
{
  _asm
    goto InterruptHandlerlow //jump to interrupt routine
  _endasm
}



#pragma code
#pragma interrupt InterruptHandlerlow

void InterruptHandlerlow()
{
	char caractere;

	if(INTCON3bits.INT1IF) //codeur GAUCHE
	{
		interruptionCodeurG(INTER_1);
		INTCON3bits.INT1IF=0;
	}

	if(INTCON3bits.INT2IF) //codeur DROITE
	{
		interruptionCodeurD(INTER_2);
		INTCON3bits.INT2IF=0;
	}
	
	if(PIR1bits.RC1IF) //usart1
	{
		caractere = RCREG1;
		interruptionRx1(caractere);
		LED_USART1=!LED_USART1;
		PIR1bits.RC1IF;
	}

	if(PIR3bits.RC2IF) //usart2
	{
		caractere = RCREG2;
		//interruptionRx2(caractere);
		LED_USART2=!LED_USART2;
		PIR3bits.RC2IF;
	}


	if(INTCONbits.TMR0IF) //timer0 : clignotement de led
	{
		LED_TEMOIN =! LED_TEMOIN;
		INTCONbits.TMR0IF=0;
	}

}
