/** \file 
Contient toutes les procédures utilisant l'ultrason : capture et traitement.
\author    Adrien Jaegy
 */
#ifndef ULTRA_H
#define ULTRA_H

/*!
Une fois une acquisition réalisée (enregistrée sous forme de variable locale au fichier ultrason), cette fonction permet de lire la distance.\n
Si vous n'avez pas lancé de nouvelle acquisition mais que vous appelez cette fonction une deuxièe fois, elle renvoie la distance en mémoire, c'est à dire la meme que la premire fois.

\return la distance en mm.
*/
short distanceUS(void);

/*!
Cette fonction doit être appellée par l'interruption de la pin connectée à l'utrason.\n
Elle enregistre la date de fin de reception du module ultrason. La distance est maintenant calculable par la fonction distanceUs()
*/
void receptionUS(void);

/*!
Démarrer une acquisitio ultrason. Cette fonction configure l'interruption, envoie un trigger et enregistre la date actuelle.\n
A la réception de la réponse du module ultrason, c'est la fonction receptionUS qui termine le traitement.
\return ERREUR si l'acquisition précédente ne s'est pas encore terminée (en durée), OK sinon
*/
unsigned char lancerUS(void);

#endif

