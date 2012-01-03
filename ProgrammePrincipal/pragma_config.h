/** \file 
Contient toutes les pragma config nécessaires au fonctionnement du programme.
\author    Adrien Jaegy
 */
#ifndef CONFIG_H
#define CONFIG_H

//=============================================================================
//	Configuration des directives
//=============================================================================

/// oscillateur interne
#pragma config FOSC   = INTIO67		
///4 x PLL activée
#pragma config PLLCFG   = ON		
///Primary clock is always enabled  
#pragma config PRICLKEN = ON		
/// Fail safe Clock monitor désactivée
#pragma config FCMEN = OFF			
/// Pas de possibilité de passer en oscillateur interne ou externe
#pragma config IESO = OFF			
///Power up timer ENABLED
#pragma config PWRTEN = ON			
/// Brown-out Reset disabled in hardware and software
#pragma config BOREN = OFF		
/// Watchdog désactivé
#pragma config WDTEN = OFF			
/// EEPROM non protégée en écriture
#pragma config WRTD = OFF			
/// Debug ON
#pragma config DEBUG  = ON		
/// Enable MCLRE for reset function
#pragma config MCLRE  = EXTMCLR										
///Compteur 3 sur port RB5
#pragma config T3CMX = PORTB5
///Port C0 utilisé par le P2BMX (pour qu'il ne soit as sur la meme pin que le timer 3)
#pragma config P2BMX = PORTC0
///Low Voltage Programmation désactivé
#pragma config LVP=OFF
///Début du code
#pragma code

#endif