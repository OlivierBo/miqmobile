/** \file 
Contient toutes les fonctions d'entrée/sortie autres que accéléromètre gyroscope, usart et codeur.
Soit donc le guidon et l'ultrason.
\author    Adrien Jaegy
*/

#ifndef AUTRESES_H
#define AUTRESES_H

/*!
Convertit la valeur du potentiomètre en une valeur de vitesse.
\param[in] tGuidon    Valeur brute du CAN du potentiomètre du guidon.
\return La valeur de vitesse en tour sur soi même par minute.
*/
float guidonTrMin(short tGuidon);


/*!
Interroge l'ultrason (qui doit avoir au préalable été activé par un trigger) pour vérifier si l'utilisateur est là.
\return OUI ou NON
*/
char presenceUtilisateur(void);


/*!
 Lance la procédure de calibration du guidon.\n
 IMH:\n
 Led du bas : mode calibration guidon.\n
 Led du haut : mesure du guidon à la verticale.\n
 Led verte : mesure en cours d'enregistrement : ne pas bouger.\n
 Led de droite : mesure du guidon à fond à droite.\n
 Les 4 leds rouges : voulez vous enregistrer la configuration?\n
 -bouton vert : oui\n
 -bouton rouge : non\n
 Led verte : enregistré!\n
 Led orange : annulé\n
 \return OK si la nouvelle configuration a été enregistrée ou ERREUR sinon.

*/
short calibrerGuidon(void);

#endif

