/*
 * Inicializar.h
 *
 *  Created on: 22 abr. 2026
 *      Author: Marcelo Trujillo
 */

#ifndef APLICACION_INICIALIZAR_H_
#define APLICACION_INICIALIZAR_H_

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
#include "Aplicacion.h"
#include "Sintetizador.h"
#include <ModoRemoto/MaquinaEstadosUart.h>

extern Gpio pin_debug;

extern Led ledV;
extern Led ledR;
extern Led ledA;

extern DigitalInputs teclaOn;
extern DigitalInputs teclaOff;

extern Sineosc sine;
extern Sineosc mod;
extern Squareosc squa;
extern Sawosc saw;

extern ADCScanner scanner;
extern ADSR adsr_car;
extern ADSR adsr_mod;

extern Uart uart0;

extern Teclado teclado;


extern Sintetizador Synth;
//extern Gpio col0;
//extern Gpio fil0;



void Scheduler (void);
void Callback1(void);
void Callback2(void);
void Callback3(void);
void Callback4(void);
void Callback5(void);
void Callback6(void);
void CallbackE(void);

void Inicializar ( void );

#endif /* APLICACION_INICIALIZAR_H_ */
