#include "include.h"
#include "codeur.h"


//déclaration des variables globales internes au fichier
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
	//init codeur est aussi appelé lorsque le programme principal fait un reset
	//penser à mettre toutes les variables à 0...

}


struct Sroues lancerCalculsCodeur(float deltaT)
{
	struct Sroues roues;


	//tout le code
	roues.vitesseDroite=12; // par exemple


	return roues;
}