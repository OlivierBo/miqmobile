//**********************************************************************
//        			   												   *
//       					Sérial communication      	               *  
//                                                                     *
//**********************************************************************
//                                                                     *
//    Date:     20/09/2011                                             *
//    Auteur:   Gauthier Yoann                         				   *
//                                                                     *
//**********************************************************************
#include <pic.h>
#include <ctype.h>
#include <htc.h> //indispensable pour High Tech
#include <math.h>
#ifndef _XTAL_FREQ
 #define _XTAL_FREQ 4000000
#endif


//*******************************Définitions*************************
#define TYPE_TRAME_CON_DEPART 153 //Ö
#define TYPE_TRAME_CON_STOP 180
#define TYPE_TRAME_CON_COUPLEG 138
#define TYPE_TRAME_CON_COUPLED 139 //ï
#define TYPE_TRAME_INF_COUPLEG 10
#define TYPE_TRAME_INF_COUPLED 11
#define TYPE_TRAME_INF_ERREUR_CARTE_COURANT 12
#define TYPE_TRAME_INF_PRET 25
#define TYPE_TRAME_CON_TEST_COM 155


#define LG_TRAME_CON_TEST_COM 1
#define LG_TRAME_CON_COUPLEG 1
#define LG_TRAME_CON_COUPLED 1
#define LG_TRAME_INF_COUPLEG 1
#define LG_TRAME_INF_COUPLED 1
#define LG_TRAME_INF_ERREUR_CARTE_COURANT 1




#define _taille_buffer 50

//*******************************Déclaration des variables globales*************************
char buffer[50];
char top_buffer = 0; //indice du dernier octet de la pile + 1





//********************Interruption**************************************


 void interrupt reception(void)		//Interruption

	{	if(RCIF){
			if (top_buffer < _taille_buffer -1)
				{buffer[top_buffer]=RCREG;	// on remplit le buffer (pile)
				RCREG=0;
				top_buffer++;
					}			
			else {top_buffer = 1;
					}//dépassement de capacité de la pile => on supprime la pile
			}
								
	}


void decalage_buffer(char ind){//ind : indice du premier octet utile
	char i;
	for(i=0;i<(top_buffer - ind);i++){
		buffer[i]=buffer[i+ind];
	}
	top_buffer -= ind;
}

void send_usart(char octet){
	TXREG=octet;
	while(!TXIF);
	TXIF=0;
}


char longueur_trame(char titre){
char curTrameLength;
	switch (titre){
		case TYPE_TRAME_CON_COUPLEG: curTrameLength= LG_TRAME_CON_COUPLEG + 3; break;
		case TYPE_TRAME_CON_COUPLED: curTrameLength= LG_TRAME_CON_COUPLED + 3 ; break;
		case TYPE_TRAME_INF_COUPLEG: curTrameLength= LG_TRAME_INF_COUPLEG + 3 ; break;
		case TYPE_TRAME_INF_COUPLED: curTrameLength= LG_TRAME_INF_COUPLED + 3 ; break;
		case TYPE_TRAME_INF_ERREUR_CARTE_COURANT: curTrameLength= LG_TRAME_INF_ERREUR_CARTE_COURANT + 3 ; break;

		
		default : curTrameLength = 4;break;
	}
return curTrameLength;
}

//********************Programme principal******************************

void main(void){

char i;
char j;
char check_sum=0;
char consigne_couple;
char indice;
char frame_length;
char data_nb;
char data_type;

//*******************************Initialisation des registres**********************
//on envoie par RC6 et on recoie par RC7
TXSTA=0b00000110;//assynchrone/8 bits/usart disable(activer avec TXEN)/high speed/TSR empty
RCSTA=0b10001110;//port disable(activer avec SPEN)/8 bits/assychrone/no continous receive/enable addresse detect/Faming error bit/over run error bit
SPBRG=20;//57,6 K BAUDS bauds

INTCON=0;
PIE1=0;
TXEN=1;//on active la transmission
SPEN=1;//on active les ports
CREN=1;//on active la reception continue
GIE=1;//global interrupt enable
PEIE=1;//Enables peripheral interrupts 
RCIE=1;//Active interuption en reception

TRISA=0b00000000;
TRISB=0b00000000;
TRISD=0b00000000;
PORTA=0;
PORTB=0;
PORTD=0;


//Voire si on met une tempo pour laisser le tps au pic principal de s'initialiser

//Envoie d'une trame qui indique que notre pic est prêt
send_usart(TYPE_TRAME_CON_DEPART);
send_usart(TYPE_TRAME_INF_PRET);
send_usart(TYPE_TRAME_INF_PRET+TYPE_TRAME_CON_DEPART);



while (1){

//*******************************Découpage données en trames*************************


RB0=!RB0;



indice=0;//indique le début de la trame

while(indice+4 < top_buffer){//on a au minimum 4 octet dans une trame

	
	while((buffer[indice])!=TYPE_TRAME_CON_DEPART && indice < top_buffer){//on cherche l'octet de start
	indice++;
	}//end while
    

if(indice+1 < top_buffer){//on veut pouvoir lire le data type
	
		data_type = buffer[indice+1];
				
		switch(data_type){

			case TYPE_TRAME_CON_COUPLED: 
			frame_length = longueur_trame(data_type);
			check_sum=0;

			if(indice + frame_length -1 < top_buffer){//on veut pouvoir lire toute la trame
				for(i=indice+1;i<indice + frame_length -1;i++){
				check_sum+=buffer[i];
				}//end for

				if(buffer[indice + frame_length - 1 ] == check_sum){
					consigne_couple = buffer[indice+2];
					PORTD = consigne_couple;
					indice = indice+frame_length;
				}//end if
				else{indice = indice+frame_length;}
			}//end if
			break;

			case TYPE_TRAME_CON_COUPLEG: 
			frame_length = longueur_trame(data_type);
			check_sum=0;

			if(indice + frame_length -1 < top_buffer){//on veut pouvoir lire toute la trame
				for(i=indice+1;i<indice + frame_length -1;i++){
				check_sum+=buffer[i];
				}//end for

				if(buffer[indice + frame_length - 1 ] == check_sum){
					consigne_couple = buffer[indice+2];
					PORTD = consigne_couple;
					indice = indice+frame_length;
				}//end if
				else{indice = indice+frame_length;}
			}//end if
			break;
			
			default:indice = indice+4;break;//trame sautée		
		}




}//end if

}//end while


//on efface tout avant le end de la dernière trame
decalage_buffer(indice);



}//end while



}//end prog


