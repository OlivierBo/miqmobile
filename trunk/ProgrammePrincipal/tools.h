#ifndef TOOLS_H
#define TOOLS_H

unsigned short tempsEcouleDepuisMs(unsigned short time);
char siDelaiEcouleMs(unsigned short time, unsigned short duree);
void pauseMs(unsigned short duree);
unsigned short globalTimeUs(void);
void pauseUs(unsigned short duree);
void pauseTcyMs(unsigned short ms);
unsigned long globalTimeMsUs(void);
unsigned long tempsEcouleDepuisMsUs(unsigned long time);
extern volatile unsigned short globalTime; //en lecture seule!

short acquisition(char channel);

char writeEeprom(void* data, unsigned short adress,  unsigned char longueur);
char readEeprom(void* data, unsigned short adress,  unsigned char longueur);

#endif