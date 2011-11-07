#include "include.h"
#include "codeur.h"
#include "brochage.h"
#include "variablesGlobales.h"
//déclaration des variables globales internes au fichier

float nb_frontG; //compte le nombre de fronts de la voie 1 du codeur de gauche
float nb_frontD; //compte le nombre de fronts de la voie 1 du codeur de droite

long abs_nb_frontG; //pour le calcul de la distance moyenne parcourue
long abs_nb_frontD;

char sensG;      // pour la détermination du sens de rotation des codeurs DetG
char sensD;

float nb_front_precD;
float nb_front_precG;

float vitesseG;
float vitesseD;

float vitesse_precG;
float vitesse_precD;

float vitesseMoyenne;
float vitesseMoyPrec;

float acc_moyenne;
float acc_moyenne_prec;

//déclaration des fonctions privées
char determine_sens(char , char );
float determine_position(float );
float distance_Moy(long , long );
float determine_vitesse (float , float , float );
float determine_vmoyen(float , float );
float D_utilisation_moteur (float , float  );
float determine_acceleration(float , float , float , float , float );




// Fonction publiques
void interruptionCodeurG(void)
{
sensG=determine_sens(INTCON3bits.INT1F, CODEUR_B_GAUCHE);
if (sensG==1)			//selon le sens, on incrémente ou on décrémente
{++nb_frontG;}			//nb_front image de la distance parcourue

else if (sensG==0){--nb_frontD;}
++abs_nb_frontG;
INTCON3bits.INT1F=0;    //clear flag
}


void interruptionCodeurD(void)
{
sensD=determine_sens(INTCON3bits.INT2F, CODEUR_B_DROITE);
if (sensD==1)			//selon le sens, on incrémente ou on décrémente
{++nb_frontG;}			//nb_front image de la distance parcourue

else if (sensD==0){--nb_frontD;}
INTCON3bits.INT2F=0;    //clear flag
++abs_nb_frontD;
}

void initCodeurs(void)  //initialisation des codeurs
{
nb_frontG=0; //compte le nombre de fronts de la voie 1 du codeur de gauche
nb_frontD=0; //compte le nombre de fronts de la voie 1 du codeur de droite
abs_nb_frontG=0; //pour le calcul de la distance moyenne parcourue
abs_nb_frontD=0;
sensG=0;      // pour la détermination du sens de rotation des codeurs DetG
sensD=0;
nb_front_precD=0;
nb_front_precG=0;
vitesseG=0;
vitesseD=0;
vitesse_precG=0;
vitesse_precD=0;
vitesseMoyenne=0;
vitesseMoyPrec=0;
acc_moyenne=0;
acc_moyenne_prec=0;

}
struct Sroues lancerCalculsCodeur(float deltaT)
//struct Sroues, float deltaT,float ACCELERATION_COEF_FILTRE, float GRANDEUR_RAYON_ROUE,GRANDEUR_VITESSE_MAX, long nb_frontG, long nb_frontD)
{
        struct Sroues roues;

        //determiner les positions droites et gauches
        roues.positionGauche=determine_position(nb_frontG);
        roues.positionDroit=determine_position(nb_frontD);         //°  (entre -180 et +180)

        //déterminer la distance moyenne parcourue
        roues.distanceMoyenneParcourue=distance_Moy(abs_nb_frontG,abs_nb_frontD); //m

 		vitesse_precG=roues.vitesseGauche;
		vitesse_precD=roues.vitesseDroite;

		roues.vitesseGauche=determine_vitesse(nb_frontG,nb_front_precG,deltaT);  //°/s
        roues.vitesseDroite=determine_vitesse(nb_frontD,nb_front_precD,deltaT);

		nb_front_precG=nb_frontG;
		nb_front_precD=nb_frontD;

		vitesseG=roues.vitesseGauche;
		vitesseD=roues.vitesseDroite;

        //déterminer la vitesse moyenne
        vitesseMoyPrec=vitesseMoyenne;
		vitesseMoyenne=determine_vmoyen(vitesseG, vitesseD); //km/h
		roues.vitesseMoyenne=vitesseMoyenne;
        //déterminer le pourcentage d'utilisation moteur
        //entre 0 et 1, vaut 0,6 si en moyenne, les moteur tournent à 60% de leur vitesse maxi
        //roues.utilisationMoteur = D_utilisation_moteur(GRANDEUR_VITESSE_MAX, vitesseMoyenne);

        //déterminer l'accération moyenne
        
		acc_moyenne_prec=acc_moyenne;
		roues.accMoyenne=determine_acceleration(acc_moyenne_prec, vitesseMoyenne, vitesseMoyPrec, ACCELERATION_COEF_FILTRE, deltaT);
		acc_moyenne=roues.accMoyenne;

        return roues;
}

//Fonctions privées

//déterminer le sens
char determine_sens (char voie1, char voie2)
{
    char sens;

    if (voie1==1 && voie2==1) sens=1;
    else if (voie1==1 && voie2==0) sens=0;
    return sens;
}

//determine la position
float determine_position(float nb_front)
{

while (1000.<nb_front<-1000.)
    {
    float position;
    if (nb_front>1000.) nb_front=nb_front-1000.;
    else if (nb_front<-1000.) nb_front=nb_front+1000.;
    position=nb_front*0.36;	//nb_front*360/resolution (résolution=1000)
    return position; //position est ainsi entre +- 180°
    }
}

float distance_Moy(long frontsG, long frontsD)
{
float moyenne;
moyenne=frontsD+frontsG;

moyenne=moyenne*3.14;
moyenne=moyenne*GRANDEUR_RAYON_ROUE; //résolution de 1000 fronts/tour -> nbfronts*2Pi.R*10e-3/(2*1000), résultat en mm
moyenne=moyenne/1000000.; //en m
return moyenne;
}

float determine_vitesse (float nb_front, float nb_front_prec, float deltaT)
{
//en °/s, angle = DeltaNb_Front*360/1000 pour convertir les impulsions en °
// vitesse = (angle/deltaT) * 1000 car deltaT en ms
float vitesse;
vitesse=nb_front-nb_front_prec;
vitesse=vitesse*360.;
vitesse=vitesse/deltaT;
return vitesse;
}

float determine_vmoyen(float vgauche, float vdroite)
{
	float vmoy;
	vmoy=vgauche+vdroite;
	vmoy=vmoy/2.;
	vmoy=vmoy*GRANDEUR_RAYON_ROUE;
	vmoy=vmoy/3600.;	//conversion mm/s en km/h
	vmoy=vmoy/1000000.;
	return vmoy;
}

float D_utilisation_moteur(float vmax, float vmoyenne)
{
//entre 0 et 1, vaut 0,6 si en moyenne, les moteur tournent à 60% de leur vitesse maxi
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
    
	acceleration=(1-COEF_FILTRE)*acceleration_prec;
    
    deltaV=(vitessemoy-vitessemoy_prec);
    deltaV=deltaV/deltaT;
	
	acceleration=acceleration+COEF_FILTRE*deltaV;
	
	return acceleration;
}

