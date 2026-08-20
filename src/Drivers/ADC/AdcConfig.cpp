/*
 * AdcConfig.cpp
 *
 *  Created on: 20 ago. 2026
 *      Author: joaqu
 */

#include "AdcConfig.h"
#include "LPC845.h"


void AdcConfig(void)
{
	SYSCON->SYSAHBCLKCTRL0 |= (1<<24);  	//Enable clock for ADC
	SYSCON->PDRUNCFG 	   &= ~(1 << 4); 	//Power DAC0
	SYSCON->SYSAHBCLKCTRL0 |= (1<<7); 		//Enable clock for Switch Matrix
	SWM0->PINENABLE0 &= ~( (1<<15)|(1<<16)|(1<<17)|				//Habilitar ADC en PIO0_6, PIO0_14, PIO0_23
	                      (1<<18)|(1<<19)|(1<<20)|(1<<21) );   	// PIO0_22, PIO0_21, PIO0_20, PIO0_19

	ADC0->CTRL |= (1 << 30)   // CALMODE: iniciar calibracion
             | (59 << 0);   // CLKDIV = 29 → 30MHz/60 = 500kHz para calibracion

	while(ADC0->CTRL & (1 << 30)); //espera a que se termine de calibrar

	ADC0->CTRL = (29 << 0); // Operación normal a 1MHz — más que suficiente para pots

	ADC0->SEQ_CTRL[0] |= (1 << 31); //Enable Seq A

}
