#include "include.h"
#include "codeur.h"


//d�claration des variables globales internes au fichier
//du genre le compteur de front
long nbFrontsGauche; //par exemple


void interruptionCodeurG(void)
{

}


void interruptionCodeurD(void)
{

}


void initCodeurs(float rayon)
{
	//init codeur est aussi appel� lorsque le programme principal fait un reset
	//penser � mettre toutes les variables � 0...

}


struct Sroues lancerCalculsCodeur(float deltaT)
{
	struct Sroues roues;


	//tout le code
	roues.vitesseDroite=12; // par exemple


	return roues;
}