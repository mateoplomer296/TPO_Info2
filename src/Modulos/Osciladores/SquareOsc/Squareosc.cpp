/*
 * Squareosc.cpp
 *
 *  Created on: 3 ago. 2026
 *      Author: joaqu
 */

#include "Squareosc.h"

Squareosc::Squareosc(uint32_t freq_hz, uint16_t amplitude):Oscilador(freq_hz, amplitude)
{

}

uint16_t Squareosc::lookupShape(uint32_t phase, uint16_t amplitud)
{
	return (phase >> 31) * amplitud;
}

Squareosc::~Squareosc() {}

