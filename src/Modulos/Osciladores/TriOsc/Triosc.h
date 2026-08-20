/*
 * Triosc.h
 *
 *  Created on: 4 ago. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_OSCILADORES_TRIOSC_TRIOSC_H_
#define MODULOS_OSCILADORES_TRIOSC_TRIOSC_H_
#include "Oscilador.h"
class Triosc :public Oscilador
{
public:
	Triosc(uint32_t freq_hz, uint16_t amplitude);
	virtual ~Triosc();

protected:

	uint16_t lookupShape(uint32_t phase)override;
};

#endif /* MODULOS_OSCILADORES_TRIOSC_TRIOSC_H_ */
