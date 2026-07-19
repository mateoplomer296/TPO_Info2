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

    // Genera el siguiente sample de audio.
    // Retorna valor entre 0 y 1023 (centrado en 512 = silencio).
    // Llamado desde ISR — debe ser rapido.
   // virtual uint16_t nextSample() = 0;
    uint16_t Oscilador::nextSample(){
        	m_phaseAcc += m_phaseInc;       // Todas las ondas hacen esto
    		return lookupShape(m_phaseAcc);
        };

    void Oscilador::setFreq(uint32_t freq_mHz) {
        m_phaseInc = freqToPhaseInc(freq_mHz);
    }

    // amplitude: 0 (silencio) a 512 (maximo)
    void Oscilador::setAmplitude(uint16_t amplitude) {
        m_amplitude = (amplitude > 512) ? 512 : amplitude;
    }

    void Oscilador::reset() {
        m_phaseAcc = 0;
    }

