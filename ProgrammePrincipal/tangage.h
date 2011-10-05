#ifndef TANGAGE_H
#define TANGAGE_H



void angleTangage(short tAccX, short tAccZ, short tGyro, short xpp, short tetaPrec, short te);
short calibrageTangage(void);

short valeurTetaAngle(void);
short valeurtetaVitesse(void);
char presenceDefautBorne(void);

#endif


