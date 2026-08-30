/*
 * Sineosc.cpp
 *
 *  Created on: 21 jun. 2026
 *      Author: joaqu
 */

#include "Sineosc.h"

uint16_t Sineosc::s_table[TABLE_SIZE];
bool     Sineosc::s_tableReady = false;

Sineosc::Sineosc(uint32_t freq_hz, uint16_t amplitude):Oscilador(freq_hz, amplitude)
{
	buildTable();
}

uint16_t  Sineosc::lookupShape(uint32_t phase, uint16_t amplitud)
{
    uint32_t indice = phase >> 24;		// 256 = 24, 512 = 23, 1024 = 22. Cambiar segun tablesize
    // Centrar en 0 (-512 a 511), escalar, recentrar en 512
       int32_t centered = (int32_t)s_table[indice] - 512;
       centered = (centered * (int32_t)amplitud) >> 9;
       return (uint16_t)(centered + 512);
}

void Sineosc::buildTable()
{

	if (s_tableReady) return;

	for (uint16_t i = 0; i < TABLE_SIZE; i++)
	{
		// Calculamos el ángulo en radianes para este índice
		// theta va a ir de 0 a 6.2831...
		float theta = (i * 6.283185307f) / (TABLE_SIZE);

		// El seno devuelve entre -1.0 y 1.0.
		// Lo multiplicamos por 511 para que vaya de -511 a 511.
		// Le sumamos el offset de 512 para que quede centrado entre 0 y 1023.
		float valor_flotante = 512.0f + (511.0f * sin(theta));

		// Lo guardamos en la tabla forzándolo a entero
		s_table[i] = (uint16_t)valor_flotante;

	};

	s_tableReady = true;

}

Sineosc::~Sineosc() {
	// TODO Auto-generated destructor stub
}

