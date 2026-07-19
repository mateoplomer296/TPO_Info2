/*
 * Pulsador.h
 *
 *  Created on: 29 abr. 2026
 *      Author: danie
 */

#ifndef MODULOS_GUIA_EJERCICIOS_PULSADOR_H_
#define MODULOS_GUIA_EJERCICIOS_PULSADOR_H_
#include <2-GPIO/Gpio.h>

class Pulsador: public Gpio {
private:
	bool estado_anterior;
public:
	enum estado{
			PRESIONADO, SUELTO //presionado devuelve 0 y suelto 1
		};
	Pulsador(uint8_t port , uint8_t pin);

	bool operator==(estado estado_a_comparar) const;
	operator bool() const;

	bool Flanco();

	virtual ~Pulsador();
};

#endif /* MODULOS_GUIA_EJERCICIOS_PULSADOR_H_ */
