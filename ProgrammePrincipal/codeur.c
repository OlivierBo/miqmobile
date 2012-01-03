#include "include.h"
#include "codeur.h"
#include "brochage.h"
#include "variablesGlobales.h"

//d�claration des variables globales internes au fichier

float nb_frontG; //compte le nombre de fronts de la voie 1 du codeur de gauche
float nb_frontD; //compte le nombre de fronts de la voie 1 du codeur de droite

//long abs_nb_frontG; //pour le calcul de la distance moyenne parcourue
//long abs_nb_frontD;

//char sensG;      // pour la d�termination du sens de rotation des codeurs DetG
//char sensD;

float vitesseG;
float vitesseD;

//float vitesseMoyenne;
float vitesseMoyPrec;

float acc_moyenne;
float acc_moyenne_prec;

float deltafrontD;
float deltafrontG;

float deltaV;

volatile struct Sroues roues;

//d�claration des fonctions priv�es
char determine_sens(char , char );
float determine_position(float );
float distance_Moy(long , long );
float determine_vitesse (float , float);// , float );
float determine_vmoyen(float , float );
float D_utilisation_moteur (float , float  );
float determine_acceleration(float , float , float , float , float );
float determine_nb_front(float , float , char );

// Fonction publiques

void interruptionCodeurG(char signe)
{
deltafrontG=LireCodeurGauche();
nb_frontG=determine_nb_front(nb_frontG, deltafrontG, roues.signeGauche);//mise a jour du nb de front
//roues.vitesseGauche=0.;		//raz des vitesses				//la vitesse repasse par 0 car chgt de sens, donc init
EcrireCodeurGauche(0);										//raz timer
//sensG=signe;
roues.signeGauche=signe;
}

void interruptionCodeurD(char signe)
{
deltafrontG=LireCodeurDroite();
nb_frontD=determine_nb_front(nb_frontD, deltafrontD, roues.signeDroite);
//roues.vitesseDroite=0.;		//raz des vitesses
EcrireCodeurDroite(0);		//raz timer
//sensD=signe;
roues.signeDroite=signe;
}


void initCodeurs(void)  //initialisation des codeurs
{
nb_frontG=0.; //compte le nombre de fronts de la voie 1 du codeur de gauche
nb_frontD=0.; //compte le nombre de fronts de la voie 1 du codeur de droite
//abs_nb_frontG=0.; //pour le calcul de la distance moyenne parcourue
//abs_nb_frontD=0.;
vitesseG=0.;
vitesseD=0.;
//vitesseMoyenne=0.;
vitesseMoyPrec=0.;
acc_moyenne=0.;
acc_moyenne_prec=0.;
//sensG=1;
//sensD=1;
deltafrontD=0.;
deltafrontG=0.;
//initialisation de la structure roues
roues.positionGauche=0.;
roues.positionDroite=0.;
roues.distanceMoyenneParcourue=0.;
roues.vitesseGauche=0.;
roues.vitesseDroite=0.;
roues.vitesseMoyenne=0.;
roues.utilisationMoteur=0.;
roues.accMoyenne=0.;
roues.signeGauche=1;
roues.signeDroite=1;
}
struct Sroues lancerCalculsCodeur(float deltaT)
//struct Sroues, float deltaT,float ACCELERATION_COEF_FILTRE, float GRANDEUR_RAYON_ROUE,GRANDEUR_VITESSE_MAX, long nb_frontG, long nb_frontD)
{

        deltafrontG=LireCodeurGauche();
		deltafrontD=LireCodeurDroite();
		
		EcrireCodeurGauche(0);
		EcrireCodeurDroite(0);
		
		//peut �tre supprim� si l'on consid�re que le segway ne fait qu'avancer
		//�conomie de deux calculs!
		//abs_nb_frontG=abs_nb_frontG+deltafrontG;
		//abs_nb_frontD=abs_nb_frontD+deltafrontD;
		//

		nb_frontG=determine_nb_front(nb_frontG, deltafrontG, roues.signeGauche);
		nb_frontD=determine_nb_front(nb_frontD, deltafrontD, roues.signeDroite);

        //determiner les positions droites et gauches
        roues.positionGauche=determine_position(nb_frontG);
        roues.positionDroite=determine_position(nb_frontD);         //�  (entre -180 et +180)

        //d�terminer la distance moyenne parcourue
        roues.distanceMoyenneParcourue=distance_Moy(nb_frontG,nb_frontD);//(abs_nb_frontG,abs_nb_frontD); //m
		// on prend direct le nb_front car a priori, on passe plus de temps a avancer qu'� reculer!

 		//vitesse_precG=roues.vitesseGauche;
		//vitesse_precD=roues.vitesseDroite;
		
		//Calcul des vitesses 
		if (roues.signeGauche==0)roues.vitesseGauche=-determine_vitesse(deltafrontG,deltaT);//, vitesse_precG);  //�/s
		else if (roues.signeGauche==1)roues.vitesseGauche=determine_vitesse(deltafrontG,deltaT);
        if (roues.signeDroite==0)roues.vitesseDroite=-determine_vitesse(deltafrontD,deltaT);//, vitesse_precD);
		else if (roues.signeDroite==1)roues.vitesseDroite=determine_vitesse(deltafrontD,deltaT);
		

		//vitesseG=roues.vitesseGauche;
		//vitesseD=roues.vitesseDroite;

        //d�terminer la vitesse moyenne
        vitesseMoyPrec=roues.vitesseMoyenne;
		roues.vitesseMoyenne=determine_vmoyen(roues.vitesseGauche, roues.vitesseDroite); //km/h
		//vitesseMoyenne=roues.vitesseMoyenne;
        //d�terminer le pourcentage d'utilisation moteur
        //entre 0 et 1, vaut 0,6 si en moyenne, les moteur tournent � 60% de leur vitesse maxi
        roues.utilisationMoteur = D_utilisation_moteur(GRANDEUR_VITESSE_MAX, roues.vitesseMoyenne);

        //d�terminer l'acc�ration moyenne
        
		acc_moyenne_prec=roues.accMoyenne;
		roues.accMoyenne==(1.-ACCELERATION_COEF_FILTRE)*acc_moyenne_prec;
    	deltaV=(roues.vitesseMoyenne-vitesseMoyPrec);
		deltaV=deltaV*0.28; //conversion des km/h en m/s (deltaV*1000/3600)
    	deltaV=deltaV/(deltaT*0.001); //car deltaT en ms
		roues.accMoyenne=roues.accMoyenne;//+COEF_FILTRE*deltaV;
	
	//	roues.accMoyenne=determine_acceleration(acc_moyenne_prec, roues.vitesseMoyenne, vitesseMoyPrec, ACCELERATION_COEF_FILTRE, deltaT);
//		roues.accMoyenne=0.124;
		//acc_moyenne=roues.accMoyenne;

        return roues;
}

//Fonctions priv�es

//calcule le nb de fronts
float determine_nb_front(float nb_front, float deltafront, char sens)
{
if (sens==1) nb_front=nb_front+deltafront;
else if (sens==0) nb_front=nb_front-deltafront;
return nb_front;
}

//determine la position
float determine_position(float nb_front)
{
float position;
position=nb_front*0.36;	//nb_front*360/resolution (r�solution=1000)

while (360.<position||position<-360.)
    {
    if (position>360.) position=position-360.;
    else if (position<-360.) position=position+360.;
	}
    if (position>180.) position=position-360.;
	else if (position<-180.) position=position+360.;

	return position; //position est ainsi entre +- 180�    
}

float distance_Moy(long frontsG, long frontsD)
{
float moyenne;
moyenne=frontsD+frontsG;

moyenne=moyenne*3.14;
moyenne=moyenne*GRANDEUR_RAYON_ROUE; //r�solution de 1000 fronts/tour -> nbfronts*2Pi.R*10e-3/(2*1000), r�sultat en mm
moyenne=moyenne/1000000.; //en m
return moyenne;
}

float determine_vitesse (float deltafront, float deltaT)//, float vitesseprec)
{
//en �/s, angle = DeltaNb_Front*360/1000 pour convertir les impulsions en �
// vitesse = (angle/deltaT) * 1000 car deltaT en ms
float vitesse;
vitesse=deltafront;
vitesse=vitesse*360.;
vitesse=vitesse/deltaT;
//vitesse=vitesseprec+vitesse;
return vitesse;
}

float determine_vmoyen(float vgauche, float vdroite)
{
	float vmoy;
	vmoy=vgauche+vdroite;
	vmoy=vmoy/2.;
	vmoy=vmoy*GRANDEUR_RAYON_ROUE;
	vmoy=vmoy*3600.;	//conversion mm/s en km/h
	vmoy=vmoy/1000000.;
	return vmoy;
}

float D_utilisation_moteur(float vmax, float vmoyenne)
{
//entre 0 et 1, vaut 0,6 si en moyenne, les moteur tournent � 60% de leur vitesse maxi
float umoteur;
vmoyenne=vmoyenne/GRANDEUR_RAYON_ROUE;		//vmoyenne*10^6/(2PI.R.60)
vmoyenne=vmoyenne*377.;						//conversion en tour par minute pour comparer
umoteur=vmoyenne/vmax;						//vitesse max en tour par minutes!!
return umoteur;
}

float determine_acceleration(float acceleration_prec, float vitessemoy, float vitessemoy_prec, float COEF_FILTRE, float deltaT)
{
    float acceleration;
    float deltaV;
    
	acceleration=(1.-COEF_FILTRE)*acceleration_prec;
    
    deltaV=(vitessemoy-vitessemoy_prec);
	deltaV=deltaV*0.28; //conversion des km/h en m/s (deltaV*1000/3600)
    deltaV=deltaV/(deltaT*0.001); //car deltaT en ms
	//deltaV=deltaV/(deltaT);
	acceleration=acceleration+COEF_FILTRE*deltaV;
	
	return acceleration;
}

