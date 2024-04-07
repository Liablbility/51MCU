#include <REGX52.H>
#include "Delay.h"
#include "DigitalTube.h"
void main(){
	while(1){
		Display(1,1);
		P2_0 = 1;
		
		Delayxms(200);
		
		Display(2,2);
		P2_0 = 0;
		
		Delayxms(200);
		
		Display(3,3);
		P2_0 = 1;
		
		Delayxms(200);
		
		Display(4,4);
		P2_0 = 0;
		
		Delayxms(200);
	}
}