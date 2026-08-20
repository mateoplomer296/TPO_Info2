/*
 * Triosc.cpp
 *
 *  Created on: 4 ago. 2026
 *      Author: joaqu
 */

#include <TriOsc/Triosc.h>

Triosc::Triosc(uint32_t freq_hz, uint16_t amplitude):Oscilador(freq_hz, amplitude) {
	// TODO Auto-generated constructor stub

}
uint16_t Triosc::lookupShape(uint32_t phase)
{
	uint32_t triangle_phase = (phase & 0x80000000) ? ~phase : phase;

	   // Escalamiento: triangle_phase ahora es un triángulo que va de 0 a 0x7FFFFFFF (31 bits).
	   // Usamos el cast a 64 bits y desplazamos 31 lugares para normalizarlo a m_amplitude.
	return (uint16_t)(((uint64_t)triangle_phase * m_amplitude) >> 31);
}
Triosc::~Triosc() {
	// TODO Auto-generated destructor stub
}

