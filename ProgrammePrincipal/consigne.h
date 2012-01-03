/** \file 
Contient toutes les proc�dures s'occupant de calculer des couples.\n
Contient notamment la fonction d'asservissement PD de l'angle de tangage.
\author    Adrien Jaegy
 */
#ifndef CONSIGNE_H
#define CONSIGNE_H

struct Sconsigne
{
///couple total (somme)
	float coupleT; 
///couple roue gauche
	float coupleG; 
/// couple roue droite
	float coupleD; 
};

/*!
Calcule via un correcteur PD le couple necessaire pour r�tablir l'�quilibre de la M2.
\param[in] consigne   angle vis� (en degr�s). G�n�ralement 0, sauf quand la vitesse est trop grande.
\param[in] angle   angle de tangage mesur� en �
\param[in] vitesseAngle   vitesse angulaire de l'angle de tangage en �/s
\return le couple total n�cessaire pour garder l'�quilibre.
*/
float coupleTotal(float consigne, float angle, float vitesseAngle);

/*!
Partage le couple total eb couple de gauche et couple de droite selon l'orientation du guidon.
\param[in] couple    Le couple total � partager
\param[in] vitesseG    La vitesse de la roue gauche en �/s
\param[in] vitesseD    La vitesse de la roue droite en �/s
\param[in] guidon    La valeur de l'inclinaison du guidon, en tr sur soi meme par min (guidon positif = aller + vite � gauche donc tourner a droite)
\return une structure contenant les couples de chaque c�t� ainsi que le couple total.
*/
struct Sconsigne partagerCouple(float couple, float vitesseG, float vitesseD, float guidon); 

/*!
Calcule l'angle de tangage � viser. Cet angle vaut toujours 0 sauf si la vitesse de la M2 est trop grande et qu'il y a risque de chuite de couple. Dans ce cas, l'angle vis� devient n�gatif et la M2 acc�l�re pour d�s�quilibrer l'utilisateur vers l'arri�re et donc entrainer un freinage.
\param[in] utilisationMoteur    l'utilisation moteur contenue dans la structure roue (entre 0 et 1, vaut 0,6 si en moyenne, les moteur tournent � 60% de leur vitesse maxi)
\param[in] hysterisisAngleVise    angle vis� pr�c�demment (vaut ce que la fonction � retourn� la fois d'avant). Cette m�moire sert � pouvoir cr�er des hyst�risis.
\param[in] tangage    angle de tangage mesur� en �
\return l'angle � viser (angle utilis� par la fonction coupleTotal).
*/
float consigneAngle(float utilisationMoteur, float hysterisisAngleVise, float tangage);

#endif