/*
 * ADSR.cpp
 *
 *  Created on: 30 ago. 2026
 *      Author: joaqu
 */

#include <ADSR/ADSR.h>

ADSR::ADSR() {}

void ADSR::update() // llamado desde CallbackAudio a 22050Hz. contiene el switch con la maquina de estados
{
	switch(m_estado)
	{
	case SILENCIO:
		m_amplitudActual = 0;

		break;

	case ATTACK:
		if(m_amplitudActual + m_incAttack >= m_volumen)  // ← se pasaría?
			{
				m_amplitudActual = m_volumen;
				m_estado = DECAY;
			}
		else
			{
				m_amplitudActual += m_incAttack;
			}
		break;

	case DECAY:
		m_amplitudActual -= m_decDecay;
		if(m_amplitudActual <= m_nivSustain)  // ← llegó al nivel?
			{
				m_amplitudActual = m_nivSustain;  // ← clampear para no pasarse
				m_estado = SUSTAIN;              // ← transición
			}
		break;

	case SUSTAIN:
		if(m_amplitudActual <= m_nivSustain + m_decDecay)  // ← se pasaría?
		{
			m_amplitudActual = m_nivSustain;
			m_estado = SUSTAIN;
		}
		else
		{
			m_amplitudActual -= m_decDecay;
		}
		break;

	case RELEASE:

		if(m_amplitudActual <= m_decRelease)  // ← se pasaría de 0?
			{
				m_amplitudActual = 0;
				m_estado = SILENCIO;
			}
		else
			{
				m_amplitudActual -= m_decRelease;
			}
		break;
	}
}

void ADSR::noteOn() // llamado desde Keyboard al presionar tecla
{

}
                          // cambia estado a ATTACK

void ADSR::noteOff() // llamado desde Keyboard al soltar tecla
{

}                         // cambia estado a RELEASE

uint16_t ADSR::getAmplitud()
{
	return m_amplitudActual;
	// devuelve m_amplitudActual para pasarla al oscilador
}


// Setters llamados desde el while del main con los valores del ADCScanner
void ADSR::setAttack(uint16_t potval)
{
	uint16_t tiempoMs = 1 + (potval * 2000 / 4095); //de 1 a 2000ms
	m_incAttack = 512 / (tiempoMs * 22);  // 22 ≈ 22.050
	if(m_incAttack == 0) m_incAttack = 1; //si el tiempo es muy largo evito redondeo a 0
}
void ADSR::setDecay(uint16_t potval)
{
	uint16_t tiempoMs = 1 + (potval * 2000 / 4095); //de 1 a 2000ms
	m_decDecay = 512 / (tiempoMs * 22);  // 22 ≈ 22.050
	if(m_decDecay == 0) m_decDecay = 1; //si el tiempo es muy largo evito redondeo a 0
}
void ADSR::setSustain(uint16_t potval) // nivel 0-512
{
	m_nivSustain = (512 * potval) / 4095;
}
void ADSR::setRelease(uint16_t potval)
{
	uint16_t tiempoMs = 1 + (potval * 2000 / 4095); //de 1 a 2000ms
	m_decRelease = 512 / (tiempoMs * 22);  // 22 ≈ 22.050
	if(m_decRelease == 0) m_decRelease = 1; //si el tiempo es muy largo evito redondeo a 0
}
void ADSR::setVolumen(uint16_t potval)
{
	m_volumen = (512 * potval) / 4095;
}

ADSR::~ADSR() {}

