#ifndef CONFIG_H
#define CONFIG_H

//=============================================================================
//	Configuration des directives
//=============================================================================


#pragma config FOSC   = INTIO67		// oscillateur interne
#pragma config PLLCFG   = ON		//4 x PLL activ�e
#pragma config PRICLKEN = ON		//Primary clock is always enabled  
#pragma config FCMEN = OFF			// Fail safe Clock monitor d�sactiv�e
#pragma config IESO = OFF			// Pas de possibilit� de passer en oscillateur interne ou externe
#pragma config PWRTEN = OFF			//Power up timer disabled 
#pragma config BOREN = OFF			// Brown-out Reset disabled in hardware and software
#pragma config WDTEN = OFF			// Watchdog d�sactiv�
#pragma config WRTD = OFF			// EEPROM non prot�g�e en �criture
#pragma config DEBUG  = ON			// Debug ON
#pragma config MCLRE  = EXTMCLR		// Enable MCLRE for reset function								

#pragma config LVP=OFF

#endif

