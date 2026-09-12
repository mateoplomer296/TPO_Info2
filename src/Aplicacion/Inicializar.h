/*
 * Inicializar.h
 *
 *  Created on: 22 abr. 2026
 *      Author: Marcelo Trujillo
 */

#ifndef APLICACION_INICIALIZAR_H_
#define APLICACION_INICIALIZAR_H_

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
#include "intext.h"
#include "LPC845.h"
#include "Ctimer.h"
#include "DacConfig.h"
#include "AdcConfig.h"
#include "AdcScanner.h"
#include "ADSR.h"
#include "Teclado.h"



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

extern Teclado teclado;

//extern Gpio col0;
//extern Gpio fil0;
const uint32_t NOTAS[12] = {
    261626,  // Do
    277183,  // Do#
    293665,  // Re
    311127,  // Re#
    329628,  // Mi
    349228,  // Fa
    369994,  // Fa#
    391995,  // Sol
    415305,  // Sol#
    440000,  // La
    466164,  // La#
    493883,  // Si
};


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
