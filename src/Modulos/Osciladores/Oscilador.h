/*
 * Oscilador.h
 *
 *  Created on: 20 jun. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_OSCILADORES_OSCILADOR_H_
#define MODULOS_OSCILADORES_OSCILADOR_H_

#include "tipos.h"
static const uint32_t SAMPLE_RATE = 22050;

class Oscilador{
	protected:
	uint32_t m_phaseAcc;     // acumulador de fase (0 a 0xFFFFFFFF)
	volatile uint32_t m_phaseInc;     // incremento por sample (depende de freq)
	volatile uint16_t m_amplitude;    // 0 a 512 (512 = amplitud maxima)
	virtual  uint16_t lookupShape(uint32_t phase, uint16_t amplitud) = 0;



	// Convierte frecuencia a phaseIncrement.
	// Formula: phaseInc = (freq * 2^32) / sampleRate
	// Se usa solo en setFreq(), no en la ISR.


   public:

	Oscilador(uint32_t freq_hz = 440000, uint16_t amplitude = 512);
	uint32_t getPhaseInc() const { return m_phaseInc; }
	static uint32_t freqToPhaseInc(uint32_t freq_mHz);

	// Genera el siguiente sample de audio.
	// Retorna valor entre 0 y 1023 (centrado en 512 = silencio).
	// Llamado desde ISR — debe ser rapido.
	// virtual uint16_t nextSample() = 0;
	inline uint16_t nextSample(uint16_t amplitud)
	{
		m_phaseAcc += m_phaseInc;       // Todas las ondas hacen esto
		return lookupShape(m_phaseAcc, amplitud);
	}
    void setFreq(uint32_t freq_mHz);

    inline void setPhaseInc(uint32_t phaseInc)
	{ // solo para no llamar a setFreq que consume muchos ciclos
	   m_phaseInc = phaseInc;
	}

    // amplitude: 0 (silencio) a 512 (maximo)
    void setAmplitude(uint16_t amplitude);
    void reset();
    virtual ~Oscilador(){};
};

#endif /* MODULOS_OSCILADORES_OSCILADOR_H_ */
