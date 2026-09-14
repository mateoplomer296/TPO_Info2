/*
 * Sawosc.cpp
 *
 *  Created on: 4 ago. 2026
 *      Author: joaqu
 */

#include <SawOsc/Sawosc.h>

Sawosc::Sawosc(uint32_t freq_mHz, uint16_t amplitude):Oscilador(freq_mHz, amplitude)
{

}

uint16_t Sawosc::lookupShape(uint32_t phase, uint16_t amplitud)
{
	return (uint16_t)(((uint64_t)phase * amplitud) >> 32);
}

Sawosc::~Sawosc() {}

