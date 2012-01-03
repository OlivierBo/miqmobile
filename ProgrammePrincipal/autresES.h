/** \file 
Contient toutes les fonctions d'entr�e/sortie autres que acc�l�rom�tre gyroscope, usart et codeur.
Soit donc le guidon et l'ultrason.
\author    Adrien Jaegy
*/

#ifndef AUTRESES_H
#define AUTRESES_H

/*!
Convertit la valeur du potentiom�tre en une valeur de vitesse.
\param[in] tGuidon    Valeur brute du CAN du potentiom�tre du guidon.
\return La valeur de vitesse en tour sur soi m�me par minute.
*/
float guidonTrMin(short tGuidon);


/*!
Interroge l'ultrason (qui doit avoir au pr�alable �t� activ� par un trigger) pour v�rifier si l'utilisateur est l�.
\return OUI ou NON
*/
char presenceUtilisateur(void);


/*!
 Lance la proc�dure de calibration du guidon.\n
 IMH:\n
 Led du bas : mode calibration guidon.\n
 Led du haut : mesure du guidon � la verticale.\n
 Led verte : mesure en cours d'enregistrement : ne pas bouger.\n
 Led de droite : mesure du guidon � fond � droite.\n
 Les 4 leds rouges : voulez vous enregistrer la configuration?\n
 -bouton vert : oui\n
 -bouton rouge : non\n
 Led verte : enregistr�!\n
 Led orange : annul�\n
 \return OK si la nouvelle configuration a �t� enregistr�e ou ERREUR sinon.

*/
short calibrerGuidon(void);

#endif

