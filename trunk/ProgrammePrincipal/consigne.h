/** \file 
Contient toutes les procédures s'occupant de calculer des couples.\n
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
Calcule via un correcteur PD le couple necessaire pour rétablir l'équilibre de la M2.
\param[in] consigne   angle visé (en degrés). Généralement 0, sauf quand la vitesse est trop grande.
\param[in] angle   angle de tangage mesuré en °
\param[in] vitesseAngle   vitesse angulaire de l'angle de tangage en °/s
\return le couple total nécessaire pour garder l'équilibre.
*/
float coupleTotal(float consigne, float angle, float vitesseAngle);

/*!
Partage le couple total eb couple de gauche et couple de droite selon l'orientation du guidon.
\param[in] couple    Le couple total à partager
\param[in] vitesseG    La vitesse de la roue gauche en °/s
\param[in] vitesseD    La vitesse de la roue droite en °/s
\param[in] guidon    La valeur de l'inclinaison du guidon, en tr sur soi meme par min (guidon positif = aller + vite à gauche donc tourner a droite)
\return une structure contenant les couples de chaque côté ainsi que le couple total.
*/
struct Sconsigne partagerCouple(float couple, float vitesseG, float vitesseD, float guidon); 

/*!
Calcule l'angle de tangage à viser. Cet angle vaut toujours 0 sauf si la vitesse de la M2 est trop grande et qu'il y a risque de chuite de couple. Dans ce cas, l'angle visé devient négatif et la M2 accélère pour déséquilibrer l'utilisateur vers l'arrière et donc entrainer un freinage.
\param[in] utilisationMoteur    l'utilisation moteur contenue dans la structure roue (entre 0 et 1, vaut 0,6 si en moyenne, les moteur tournent à 60% de leur vitesse maxi)
\param[in] hysterisisAngleVise    angle visé précédemment (vaut ce que la fonction à retourné la fois d'avant). Cette mémoire sert à pouvoir créer des hystérisis.
\param[in] tangage    angle de tangage mesuré en °
\return l'angle à viser (angle utilisé par la fonction coupleTotal).
*/
float consigneAngle(float utilisationMoteur, float hysterisisAngleVise, float tangage);

#endif