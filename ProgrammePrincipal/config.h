/** \file 
Pour initialiser le pic.
\author    Adrien Jaegy
 */
#ifndef CONFIGE_H
#define CONFIGE_H

/*!
Initialise tous les ports (entrée ou sortie, analogique ou numérique), les timers, les uart etc...\n
A appeler en tout premier dans le main, et qu'une seule fois.\n
Cette procédure ne peut pas générer d'erreur.
*/
void initppal(void);


#endif

