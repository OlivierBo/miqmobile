/** \file 
Contient toutes les proc�dures utilisant l'ultrason : capture et traitement.
\author    Adrien Jaegy
 */
#ifndef ULTRA_H
#define ULTRA_H

/*!
Une fois une acquisition r�alis�e (enregistr�e sous forme de variable locale au fichier ultrason), cette fonction permet de lire la distance.\n
Si vous n'avez pas lanc� de nouvelle acquisition mais que vous appelez cette fonction une deuxi�e fois, elle renvoie la distance en m�moire, c'est � dire la meme que la premire fois.

\return la distance en mm.
*/
short distanceUS(void);

/*!
Cette fonction doit �tre appell�e par l'interruption de la pin connect�e � l'utrason.\n
Elle enregistre la date de fin de reception du module ultrason. La distance est maintenant calculable par la fonction distanceUs()
*/
void receptionUS(void);

/*!
D�marrer une acquisitio ultrason. Cette fonction configure l'interruption, envoie un trigger et enregistre la date actuelle.\n
A la r�ception de la r�ponse du module ultrason, c'est la fonction receptionUS qui termine le traitement.
\return ERREUR si l'acquisition pr�c�dente ne s'est pas encore termin�e (en dur�e), OK sinon
*/
unsigned char lancerUS(void);

#endif

