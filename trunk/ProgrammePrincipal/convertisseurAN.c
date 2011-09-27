#include "include.h"
#include "convertisseurAN.h"


//short anAccX, anGyro, anAccZ, anGuidon, anBatterie;		// Variables pour les entrées analogiques

/*struct analogMesures{
	short anAccX;
	short anGyro;
	short anAccZ;
	short anGuidon;
	short anBatterie;
};*/

//struct analogMesures anMes;


//-------------------Lecture_AN--------------------------------------------------
struct analogMesures lectureAN(void)
{	struct analogMesures anMes;
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VREFPLUS);
		//Division par 64 de FOSC pour avoir un Tad de 2 us, justification à droite
		//Durée de conversion de 16 TAD, Sélection AN0 (arbitraire), Vref+ en fonction de RA3 (3.3V)
	SelChanConvADC(ADC_CH0);	//Broche n2	
 //Selection AN0 et conversion
	while(BusyADC());
	    anMes.anGyro=ReadADC();			// Lecture de la valeur convertie
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VREFPLUS | ADC_REF_VDD_VREFMINUS );
	SelChanConvADC(ADC_CH1);	//Broche n3
	while(BusyADC());
	    anMes.anAccX=ReadADC();
	SelChanConvADC(ADC_CH4);	//Broche n7
	while(BusyADC());
	    anMes.anAccZ=ReadADC();
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VDD);
	// Vref+ 5V
    SelChanConvADC(ADC_CH6);	//Broche n9
	while(BusyADC());
	    anMes.anBatterie=ReadADC();
	SelChanConvADC(ADC_CH5); //Broche n8
	while(BusyADC());
	    anMes.anGuidon=ReadADC(); 
return anMes;	
}


void initAN33(void)
{
OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VREFPLUS | ADC_REF_VDD_VREFMINUS );
}

short acquisitionX(void)
{
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VREFPLUS | ADC_REF_VDD_VREFMINUS );
	SelChanConvADC(ADC_CH1);
	while(BusyADC());
	return ReadADC();
}

short acquisitionG(void)
{
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VREFPLUS );
	SelChanConvADC(ADC_CH0);
	while(BusyADC());
	return ReadADC();
}

short acquisitionZ(void)
{
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VREFPLUS | ADC_REF_VDD_VREFMINUS );
	SelChanConvADC(ADC_CH4);
	while(BusyADC());
	return ReadADC();
}

short acquisitionVrefplus(void)
{
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VDD);
	SelChanConvADC(ADC_CH3);
	while(BusyADC());
	return ReadADC();
}

short acquisitionVrefminus(void)
{
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VDD);
	SelChanConvADC(ADC_CH2);
	while(BusyADC());
	return ReadADC();
}


short acquisitionGuidon(void)
{
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VDD);
	SelChanConvADC(ADC_CH5); //Broche n8
	while(BusyADC());
	return ReadADC();
}


short acquisitionBatterie(void)
{
	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VDD);
	// Vref+ 5V
    SelChanConvADC(ADC_CH6);	//Broche n9
	while(BusyADC());
	return ReadADC();
}


