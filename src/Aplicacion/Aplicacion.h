/*
 * Aplicacion.h
 *
 *  Created on: 27 oct. 2026
 *      Author: joaqu
 */

#ifndef APLICACION_APLICACION_H_
#define APLICACION_APLICACION_H_
#include <ADC/AdcConfig.h>
#include <DAC/DacConfig.h>
#include <Intext/intext.h>
#include "Sineosc.h"
#include "Squareosc.h"
#include "Sawosc.h"

#include "Gpio.h"
#include <Pulsador.h>
#include <Led.h>
#include <Queue.h>
#include "digital_inputs.h"
#include "digital_outputs.h"
#include "Timer.h"
#include "systick.h"
#include "LPC845.h"
#include "Ctimer.h"
#include "AdcScanner.h"
#include "ADSR.h"
#include "Teclado.h"
#include "Lcd.h"
#include "Uart.h"

void AtenderUart ( void );
void ProcesarTrama(uint8_t*trama, uint8_t tamanio);




#endif /* APLICACION_APLICACION_H_ */
