/*
 * Pulsador.cpp
 *
 *  Created on: 29 abr. 2026
 *      Author: danie
 */

#include "Pulsador.h"

Pulsador::Pulsador (uint8_t port , uint8_t pin):Gpio(port,pin,ENTRADA,BAJO) {
	estado_anterior = SUELTO;
};
bool Pulsador::operator== (estado estado_a_comparar) const {

	        bool estado_fisico_actual = this->GetPin();

	        return (estado_fisico_actual == estado_a_comparar);
	    };

Pulsador::operator bool() const{
	bool estado_fisico = this->GetPin();
	return (estado_fisico ==1);
};

bool Pulsador::Flanco(){
		bool estado_actual = this->GetPin();
		bool flanco_detectado = false;
		if (estado_anterior == SUELTO && estado_actual == PRESIONADO){
			flanco_detectado = true;
		}
		estado_anterior = estado_actual;
		return(flanco_detectado);
	};

Pulsador::~Pulsador() {
	// TODO Auto-generated destructor stub
}

