/*
 * Oscilador.cpp
 *
 *  Created on: 20 jun. 2026
 *      Author: joaqu
 */

#include <Osciladores/Oscilador.h>



    Oscilador::Oscilador(uint32_t freq_mHz, uint16_t amplitude)
        : m_phaseAcc(0), m_amplitude(amplitude)
    {
        m_phaseInc = freqToPhaseInc(freq_mHz);
    }



    void Oscilador::setFreq(uint32_t freq_mHz)
    {
        m_phaseInc = freqToPhaseInc(freq_mHz);
    }



    uint32_t Oscilador::freqToPhaseInc(uint32_t freq_mHz) //milihertz
	{
	   // Evitamos overflow de 32 bits operando en 64 bits.
	   // El compilador del LPC845 soporta uint64_t.
		return (uint32_t)((((uint64_t)freq_mHz) << 32) / (SAMPLE_RATE * 1000));
	}

    // amplitude: 0 (silencio) a 512 (maximo)
    void Oscilador::setAmplitude(uint16_t amplitude)
    {
        m_amplitude = (amplitude > 512) ? 512 : amplitude;
    }

    void Oscilador::reset()
    {
        m_phaseAcc = 0;
    }

