#ifndef TANGAGE_H
#define TANGAGE_H

struct Stangage
{
	float teta;
	float vitesse;
	char defautBorne;
};


struct Stangage angleTangage(short tAccX, short tAccZ, short tGyro, float xpp, float tetaPrec, float te);
short calibrageTangage(void);



#endif


