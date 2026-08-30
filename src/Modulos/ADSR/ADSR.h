/*
 * ADSR.h
 *
 *  Created on: 30 ago. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_ADSR_ADSR_H_
#define MODULOS_ADSR_ADSR_H_
#include "tipos.h"
class ADSR {
private:
	uint16_t m_amplitudActual;
	uint16_t m_incAttack;
	uint16_t m_decDecay;
	uint16_t m_decRelease;
	uint16_t m_nivSustain;
	uint16_t m_volumen;

	enum Estados {SILENCIO, ATTACK, DECAY, SUSTAIN, RELEASE};
	Estados m_estado;


public:


    void update();          // llamado desde CallbackAudio a 22050Hz
                            // contiene el switch con la maquina de estados

    void noteOn();          // llamado desde Keyboard al presionar tecla
                            // cambia estado a ATTACK

    void noteOff();         // llamado desde Keyboard al soltar tecla
                            // cambia estado a RELEASE

    uint16_t getAmplitud(); // devuelve m_amplitudActual para pasarla al oscilador

    // Setters llamados desde el while con los valores del ADCScanner
    void setAttack(uint16_t potval);
    void setDecay(uint16_t potval);
    void setSustain(uint16_t potval);    // nivel 0-512
    void setRelease(uint16_t potval);
    void setVolumen(uint16_t potval);
	ADSR();
	virtual ~ADSR();
};

#endif /* MODULOS_ADSR_ADSR_H_ */
