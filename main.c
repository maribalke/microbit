#include "uart.h"

int main(){

	// Configure leds (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
	GPIO0->PIN_CNF[21] = 1; //Row 1
	GPIO0->PIN_CNF[22] = 1; //Row 2
	GPIO0->PIN_CNF[15] = 1; //Row 3
	GPIO0->PIN_CNF[24] = 1; //Row 4
	GPIO0->PIN_CNF[19] = 1; //Row 5

	GPIO0->PIN_CNF[28] = 1; //Col 1
	GPIO0->PIN_CNF[11] = 1; //Col 2
	GPIO0->PIN_CNF[31] = 1; //Col 3
	GPIO1->PIN_CNF[5] = 1;  //Col 4
	GPIO0->PIN_CNF[30] = 1; //Col 5 
	
	// Configure buttons (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
	GPIO0->PIN_CNF[14] = 0; // button A 
	GPIO0->PIN_CNF[23] = 0; // button B
	
	int sleep = 0;
	while(1){

		if(!(GPIO0->IN & (1 << 23))){ //skal skru på
			for(int i = 15; i <= 24; i++){
				GPIO0->OUTSET = (1 << i);
			}
		}
		

		if(!(GPIO0->IN & (1 << 14))){
			for(int i = 15; i <= 24; i++){
				GPIO0->OUTCLR = (1 << i);
			}
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}