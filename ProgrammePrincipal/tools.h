/** \file 
Fonctio
\author    Adrien Jaegy
 */
#ifndef TOOLS_H
#define TOOLS_H


/*!
Calcule le temps écoulé en ms entre la date actuelle et la date donnée en paramètre.
\param[in] time    Date (en ms) de référence
\return le temps écoulé en ms depuis la date de référence
*/
unsigned short tempsEcouleDepuisMs(unsigned short time);

/*!
Renvoie 1 le le temps écoulé depuis la date de réfénrence donnée en paramètre est supérieur à la durée spécifiée.
\param[in] time    Date (en ms) de référence
\param[in] duree   Durée en ms
\return 1 si la durée est dépassée, 0 sinon
*/
char siDelaiEcouleMs(unsigned short time, unsigned short duree);

/*!
Fait une pause de durée ms (en utilisant le global time)
\param[in] duree   Durée de la pause en ms
*/
void pauseMs(unsigned short duree);

/*!
Donne les µS de la date actuelle (qui elle, est en ms). Cette date ne peut excéder 1ms. 
\return une durée en µS
*/
unsigned short globalTimeUs(void);

/*!
Fait une pause de durée µs
\param[in] duree   Durée de la pause en µs
*/
void pauseUs(unsigned short duree);

/*!
Fait une pause de durée ms, à partir des fonctions de pause système
\param[in] duree   Durée de la pause en ms
*/
void pauseTcyMs(unsigned short ms);

/*!
Donne la date actuelle en µS. C'est en fait une fonction qui mixe le globalTime en ms et le global time µs.
\return une date en µS
*/
unsigned long globalTimeMsUs(void);

/*!
Calcule le temps écoulé en µs entre la date actuelle et la date donnée en paramètre.
\param[in] time    Date (en µs) de référence
\return le temps écoulé en µs depuis la date de référence
*/
unsigned long tempsEcouleDepuisMsUs(unsigned long time);

/*!
Variable se mettant à jour toute seule par les timers et valant la date actuelle en ms.
*/
extern volatile unsigned short globalTime; //en lecture seule!

/*!
Lancer une acquisition analogique.
\param[in] channel    Channel du pin à lire (se reporter aux defines concernant les channels)
\return la valeur de l'acquisition (entre 0 et 1023).
*/
short acquisition(char channel);

/*!
Ecrire dans l'eeprom.
\param[in] data    Le pointeur sur la donnée à écrire
\param[in] adress    L'adresse dans l'eeprom dans laquelle écrire (se reporter aux defines concernant l'eeprom)
\param[in] longueur    la longueur (en octets) de la donnée à écrire
\return OK
*/
char writeEeprom(void* data, unsigned short adress,  unsigned char longueur);

/*!
Ecrire dans l'eeprom.
\param[out] data    Le pointeur qui pointera sur la donnée lue
\param[in] adress    L'adresse dans l'eeprom dans laquelle lire (se reporter aux defines concernant l'eeprom)
\param[in] longueur    la longueur (en octets) de la donnée à lire
\return OK
*/
char readEeprom(void* data, unsigned short adress,  unsigned char longueur);

#endif