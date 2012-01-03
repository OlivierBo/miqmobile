/** \file 
Pour initialiser le pic.
\author    Adrien Jaegy
 */
#ifndef CONFIGE_H
#define CONFIGE_H

/*!
Initialise tous les ports (entr�e ou sortie, analogique ou num�rique), les timers, les uart etc...\n
A appeler en tout premier dans le main, et qu'une seule fois.\n
Cette proc�dure ne peut pas g�n�rer d'erreur.
*/
void initppal(void);


#endif

