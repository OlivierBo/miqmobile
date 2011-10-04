#ifndef TANGAGE_H
#define TANGAGE_H

//uniquement pour le debag, normalement ne sert qu'en interne
extern short tAccX, tAccZ, tGyro, xpp, tetaPrec, te;


void angleTangage(short tAccX, short tAccZ, short tGyro, short xpp, short tetaPrec, short te);
short calibrageTangage(void);

void enregistrerValeurDeCalibration();
void recupererValeurDeCalibration();


short valeurTetaAngle(void);
short valeurtetaVitesse(void);
char presenceDefautBorne(void);

#endif


