/*
 * Led.h
 *
 *  Created on: 29 abr. 2026
 *      Author: danie
 */

#ifndef MODULOS_GUIA_EJERCICIOS_LED_H_
#define MODULOS_GUIA_EJERCICIOS_LED_H_
#include <2-GPIO/Gpio.h>

class Led: public Gpio {

public:

	Led( uint8_t port , uint8_t pin);

	void Encender(void);
	void Apagar(void);
	void CambiarEstado(void);

};

#endif /* MODULOS_GUIA_EJERCICIOS_LED_H_ */
