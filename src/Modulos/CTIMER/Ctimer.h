/*
 * Ctimer.h
 *
 *  Created on: 21 jun. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_CTIMER_CTIMER_H_
#define MODULOS_CTIMER_CTIMER_H_
#include "LPC845.h"

void InicializarTimerAudio();
void CTimer_SetHandler( void (*funcionExterna)(void) );



#endif /* MODULOS_CTIMER_CTIMER_H_ */
