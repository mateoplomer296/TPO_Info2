/*
 * Sineosc.h
 *
 *  Created on: 21 jun. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_OSCILADORES_SINEOSC_H_
#define MODULOS_OSCILADORES_SINEOSC_H_
#include "Oscilador.h"
#include <math.h>



class Sineosc : public Oscilador
{
private:
	static constexpr uint16_t TABLE_SIZE = 512;
	static uint16_t s_table[TABLE_SIZE];
	static bool     s_tableReady;




public:


	Sineosc(uint32_t freq_hz = 440000, uint16_t amplitude = 512);
	virtual ~Sineosc();

	//FUNCIONES
private:

	static void buildTable();



protected:

	uint16_t lookupShape(uint32_t phase)override;
};

#endif /* MODULOS_OSCILADORES_SINEOSC_H_ */
