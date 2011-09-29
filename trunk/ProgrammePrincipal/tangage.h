#ifndef TANGAGE_H
#define TANGAGE_H

extern short tAccX, tAccZ, tGyro, xpp, tetaPrec, te;

short angleTangage(short tAccX, short tAccZ, short tGyro, short xpp, short tetaPrec, short te);
short calibrageTangage(void);


#endif


