/** \file 
Fonctio
\author    Adrien Jaegy
 */
#ifndef TOOLS_H
#define TOOLS_H


/*!
Calcule le temps �coul� en ms entre la date actuelle et la date donn�e en param�tre.
\param[in] time    Date (en ms) de r�f�rence
\return le temps �coul� en ms depuis la date de r�f�rence
*/
unsigned short tempsEcouleDepuisMs(unsigned short time);

/*!
Renvoie 1 le le temps �coul� depuis la date de r�f�nrence donn�e en param�tre est sup�rieur � la dur�e sp�cifi�e.
\param[in] time    Date (en ms) de r�f�rence
\param[in] duree   Dur�e en ms
\return 1 si la dur�e est d�pass�e, 0 sinon
*/
char siDelaiEcouleMs(unsigned short time, unsigned short duree);

/*!
Fait une pause de dur�e ms (en utilisant le global time)
\param[in] duree   Dur�e de la pause en ms
*/
void pauseMs(unsigned short duree);

/*!
Donne les �S de la date actuelle (qui elle, est en ms). Cette date ne peut exc�der 1ms. 
\return une dur�e en �S
*/
unsigned short globalTimeUs(void);

/*!
Fait une pause de dur�e �s
\param[in] duree   Dur�e de la pause en �s
*/
void pauseUs(unsigned short duree);

/*!
Fait une pause de dur�e ms, � partir des fonctions de pause syst�me
\param[in] duree   Dur�e de la pause en ms
*/
void pauseTcyMs(unsigned short ms);

/*!
Donne la date actuelle en �S. C'est en fait une fonction qui mixe le globalTime en ms et le global time �s.
\return une date en �S
*/
unsigned long globalTimeMsUs(void);

/*!
Calcule le temps �coul� en �s entre la date actuelle et la date donn�e en param�tre.
\param[in] time    Date (en �s) de r�f�rence
\return le temps �coul� en �s depuis la date de r�f�rence
*/
unsigned long tempsEcouleDepuisMsUs(unsigned long time);

/*!
Variable se mettant � jour toute seule par les timers et valant la date actuelle en ms.
*/
extern volatile unsigned short globalTime; //en lecture seule!

/*!
Lancer une acquisition analogique.
\param[in] channel    Channel du pin � lire (se reporter aux defines concernant les channels)
\return la valeur de l'acquisition (entre 0 et 1023).
*/
short acquisition(char channel);

/*!
Ecrire dans l'eeprom.
\param[in] data    Le pointeur sur la donn�e � �crire
\param[in] adress    L'adresse dans l'eeprom dans laquelle �crire (se reporter aux defines concernant l'eeprom)
\param[in] longueur    la longueur (en octets) de la donn�e � �crire
\return OK
*/
char writeEeprom(void* data, unsigned short adress,  unsigned char longueur);

/*!
Ecrire dans l'eeprom.
\param[out] data    Le pointeur qui pointera sur la donn�e lue
\param[in] adress    L'adresse dans l'eeprom dans laquelle lire (se reporter aux defines concernant l'eeprom)
\param[in] longueur    la longueur (en octets) de la donn�e � lire
\return OK
*/
char readEeprom(void* data, unsigned short adress,  unsigned char longueur);

#endif