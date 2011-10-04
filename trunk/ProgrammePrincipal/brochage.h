#ifndef BROCHAGE_H
#define BROCHAGE_H

#define GYRO PORTAbits.RA0
#define ACC_X PORTAbits.RA1
#define VREF_MOINS PORTAbits.RA2
#define VREF_PLUS PORTAbits.RA3
#define LED_HAUT LATAbits.LATA4
#define ACC_Z PORTAbits.RA5
#define LED_CENTRE_VERTE LATAbits.LATA6
#define LED_CENTRE_ORANGE LATAbits.LATA7
#define ULTRASON_INT PORTBbits.RB0
#define CODEUR_A_GAUCHE PORTBbits.RB1
#define CODEUR_A_DROITE PORTBbits.RB2
#define CODEUR_B_DROITE PORTBbits.RB3
#define CODEUR_B_GAUCHE PORTBbits.RB4
#define LED_GAUCHE LATBbits.LATB5
#define PATTE_PGC PORTBbits.RB6
#define PATTE_PGD PORTBbits.RB7
#define LED_DROITE LATCbits.LATC0
#define LED_TEMOIN LATCbits.LATC1
#define BOUTON_VERT PORTCbits.RC2
#define BOUTON_ROUGE PORTCbits.RC3
#define LED_ERREUR LATCbits.LATC4
#define LED_BAS LATCbits.LATC5
#define USART_TX1 LATCbits.LATC6
#define USART_RX1 PORTCbits.RC7
#define SCL2_RES PORTDbits.RD0
#define SDA2_RES PORTDbits.RD1
#define LED_USART2 LATDbits.LATD2
#define LED_USART1 LATDbits.LATD3
#define ULTRASON_TRIG LATDbits.LATD4
#define BOUTON_LIMITATION PORTDbits.RD5
#define USART_TX2 LATDbits.LATD6
#define USART_RX2 PORTDbits.RD7
#define POTENTIOMETRE_GUIDON PORTEbits.RE0
#define BATTERIE PORTEbits.RE1
#define ACC_CENTRIFUGE PORTEbits.RE2
#define MCLR_VPP PORTEbits.RE3



#define CH_GYRO ADC_CH0
#define CH_ACC_X ADC_CH1
#define CH_ACC_Z ADC_CH4
#define CH_PRESENCE_UTILISATEUR ADC_CH13
#define CH_POTENTIOMETRE_GUIDON ADC_CH5
#define CH_BATTERIE ADC_CH6
#define CH_ACC_CENTRIFUGE ADC_CH7


//paramètres de l'eeprom
#define EEPROM_START	0
#define EEPROM_END		1023

#define EEPROM_CALIBRATION	100


#endif


