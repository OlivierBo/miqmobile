#ifndef BROCHAGE_H
#define BROCHAGE_H

#define ledGyroHaut PORTAbits.RA4
#define ledGyroBas PORTDbits.RD0
#define ledAttente PORTAbits.RA7
#define ledOK PORTAbits.RA6
#define ledGuidonDroit PORTCbits.RC0
#define ledGuidonGauche PORTDbits.RD1

#define minGyro 100
#define maxGyro 500
#define minGuidon 100
#define maxGuidon 500
#define nombreDeMesuresOk 10




void initppal(void);
void testInit(void);




#endif


