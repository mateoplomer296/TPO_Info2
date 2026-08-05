/*
 * Sawosc.h
 *
 *  Created on: 4 ago. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_OSCILADORES_SAWOSC_SAWOSC_H_
#define MODULOS_OSCILADORES_SAWOSC_SAWOSC_H_
#include "Oscilador.h"
class Sawosc :public Oscilador
{
public:
	Sawosc(uint32_t freq_hz = 440000, uint16_t amplitude = 512);


	virtual ~Sawosc();

protected:
	uint16_t lookupShape(uint32_t phase)override;
};

#endif /* MODULOS_OSCILADORES_SAWOSC_SAWOSC_H_ */
