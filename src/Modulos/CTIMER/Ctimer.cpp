/*
 * Ctimer.cpp
 *
 *  Created on: 21 jun. 2026
 *      Author: joaqu
 */

#include "Ctimer.h"

void InicializarTimerAudio(){
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 25);
	CTIMER->TCR |= 0x2; 					//Counter reset Enabled
	CTIMER->MR0 |= 1359;					//Ticks = (30.000.000 / 22.050)  - 1
	CTIMER->MCR |= (1 << 0) | (1 << 1);		//Genera interrupcion y resetea timer

	NVIC->ISER[0]  |=  (1 << 23);				//Enable CTIMER Interrupt
	NVIC->IP[5] &= ~(3 << 30);				//Maxima prioridad a las interrupciones del CTIMER
	CTIMER->TCR = 0x01;					//Arranca el contador
}

static void (*funcionCallback)(void) = nullptr; // Puntero a función global y privado

// Función pública para que el main le pase el trabajo
void CTimer_SetHandler( void (*funcionExterna)(void) ) {
    funcionCallback = funcionExterna;
}


extern "C" void CTIMER0_IRQHandler(void) {
    CTIMER->IR = (1 << 0); // Limpiar bandera

    if (funcionCallback != nullptr) {
        funcionCallback();
    }
}
