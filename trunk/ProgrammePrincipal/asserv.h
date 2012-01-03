/** \file 
Contient la procedure d'asservissement global de la M2. 
\author    Adrien Jaegy
 */

#ifndef ASSERV_H
#define ASSERV_H

/*!
Boucle d'asservissement globale du Segway. 
A chaque appel, elle s'occupe de lire les donnees capteurs, calculer les gains et envoyer les consignes aux moteurs.
\param[in] reinit    Le mettre a 1 pour effacer ses variables internes et le mettre a 0 en utilisation normale.
\return ERREUR si l'utilisateur n'est plus là.
*/
char boucleAsservissement(char reinit); //reinit a true pour effacer la "memoire"


/*!
Procédure qui teste la présence de l'utilisateur. La led de droite s'allume si le guidon est trop a droite, la led de gauche si il est de trop à gauche.
La led du haut s'allume si la M2 est trop inclinée vers l'avant et la led du bas si elle est trop inclinee vers l'arrière.
Si le guidon est bien centre et la M2 bien verticale, la led jaune s'allume, a condition qu'un utilisateur soit présent devant le capteur ultrason. Si aucun utilisateur n'est présent, les 4 leds rouges s'allument.
Si la led jaune est allumee pendant plus de DEMARRAGE_DELAI_EQUILIBRE, alors la led verte s'allume, ce qui signifie que la M2 est prete a demarrer.

\return OK si la led verte est allumee et que la M2 peut demarrer et ERREUR sinon.
*/
char testDemarrage(void);



#endif
