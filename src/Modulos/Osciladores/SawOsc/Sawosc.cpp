/*
 * Sawosc.cpp
 *
 *  Created on: 4 ago. 2026
 *      Author: joaqu
 */

#include <SawOsc/Sawosc.h>

Sawosc::Sawosc(uint32_t freq_hz, uint16_t amplitude):Oscilador(freq_hz, amplitude)
{

}

uint16_t Sawosc::lookupShape(uint32_t phase)
{
	return (uint16_t)(((uint64_t)phase * m_amplitude) >> 32);
}

Sawosc::~Sawosc() {}

