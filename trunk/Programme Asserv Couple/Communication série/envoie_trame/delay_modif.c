
//réalisation d'une tempode 10ms avec le registre OPTION 

void delay_10ms (char n){
	char i;
	//OPTION = 7; //à commenter
	do{
		i=TMR0 + 39;
		while(i!=TMR0);
		}	
	while(--n>0);

}