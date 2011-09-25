#ifndef PARAMETRAGE_H
#define PARAMETRAGE_H



#define LedHaut PORTAbits.RA4
#define LedBas PORTDbits.RD0
#define LedGauche PORTDbits.RD1
#define LedDroite PORTCbits.RC0
#define LedMilieu PORTAbits.RA7

#define OK 1
#define ERREUR 0
#define ON 1
#define OFF 0

#define MEMOIRE_CAPTEUR 0x00


short calibrageTangage(void);


#endif


