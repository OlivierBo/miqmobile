#ifndef CONVERSIONS_H
#define CONVERSIONS_H

//extern short anAccX, anGyro, anAccZ, anGuidon, anBatterie;		// Variables pour les entrées analogiques
struct analogMesures{
	short anAccX;
	short anGyro;
	short anAccZ;
	short anGuidon;
	short anBatterie;
};
//Lecture de toutes les valeurs
struct analogMesures lectureAN(void);


//Lecture de valeurs séparées
short acquisitionX(void);
short acquisitionG(void);
short acquisitionZ(void);
short acquisitionVrefplus(void);
short acquisitionVrefminus(void);
short acquisitionGuidon(void);
short acquisitionBatterie(void);

//initialisation des seuils de tension pour les mesures des accéléromètres
void initAN33(void);

#endif
