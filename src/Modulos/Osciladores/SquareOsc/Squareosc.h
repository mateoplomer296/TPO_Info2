/*
 * Squareosc.h
 *
 *  Created on: 3 ago. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_OSCILADORES_SQUAREOSC_SQUAREOSC_H_
#define MODULOS_OSCILADORES_SQUAREOSC_SQUAREOSC_H_
#include "Oscilador.h"
class Squareosc : public Oscilador
{
public:
	Squareosc(uint32_t freq_hz = 440000, uint16_t amplitude = 512);
	virtual ~Squareosc();

private:
protected:

	uint16_t lookupShape(uint32_t phase)override;
};

#endif /* MODULOS_OSCILADORES_SQUAREOSC_SQUAREOSC_H_ */
