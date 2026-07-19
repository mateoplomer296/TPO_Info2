/*
 * Oscilador.h
 *
 *  Created on: 20 jun. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_OSCILADORES_OSCILADOR_H_
#define MODULOS_OSCILADORES_OSCILADOR_H_

#include "tipos.h"


class Oscilador{
	protected:
	uint32_t m_phaseAcc;     // acumulador de fase (0 a 0xFFFFFFFF)
	volatile uint32_t m_phaseInc;     // incremento por sample (depende de freq)
	volatile uint16_t m_amplitude;    // 0 a 512 (512 = amplitud maxima)
	virtual  uint16_t lookupShape(uint32_t phase) = 0;
	static const uint32_t SAMPLE_RATE = 22050;


	// Convierte frecuencia a phaseIncrement.
   // Formula: phaseInc = (freq * 2^32) / sampleRate
   // Se usa solo en setFreq(), no en la ISR.
	uint32_t freqToPhaseInc(uint32_t freq_mHz) //milihertz
	{
       // Evitamos overflow de 32 bits operando en 64 bits.
       // El compilador del LPC845 soporta uint64_t.
		return (uint32_t)((((uint64_t)freq_mHz) << 32) / (SAMPLE_RATE * 1000));
	}

   public:

	Oscilador(uint32_t freq_hz = 440000, uint16_t amplitude = 512);
    uint16_t nextSample();
    void setFreq(uint32_t freq_mHz);

    // amplitude: 0 (silencio) a 512 (maximo)
    void setAmplitude(uint16_t amplitude);
    void reset();
    virtual ~Oscilador(){};
};

#endif /* MODULOS_OSCILADORES_OSCILADOR_H_ */
