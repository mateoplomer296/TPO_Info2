/*
 * DacConfig.cpp
 *
 *  Created on: 21 jun. 2026
 *      Author: joaqu
 */


#include "LPC845.h"
#include "DacConfig.h"

void DacConfig(void)
{
	SYSCON->SYSAHBCLKCTRL0 |= (1<<27);  	//Enable clock for DAC0
	SYSCON->PDRUNCFG 	   &= ~(1 << 13); 	//Power DAC0
	SYSCON->SYSAHBCLKCTRL0 |= (1<<7); 		//Enable clock for Switch Matrix
	SWM0->PINENABLE0 &= ~(1 << 26);   		//Habilitar DACOUT0 en P0_17
	SYSCON->SYSAHBCLKCTRL0 |= (1<<18);		//Enable IOCON
	IOCON->PIO[0] |= (1 << 16);				//DAC mode enable.

}

void DacWrite(uint16_t value)
{
        DAC0->CR = (value << 6); //Bits de 6 a 15 son para escribir
}
