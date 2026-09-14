/*
 * ADSR.cpp
 *
 *  Created on: 30 ago. 2026
 *      Author: joaqu
 */

#include <ADSR/ADSR.h>
#include "Oscilador.h"
ADSR::ADSR() :
m_amplitudActual(0),
m_incAttack(1),
m_decDecay(1),
m_decRelease(1),
m_nivSustain(256000),
m_volumen(512000),
m_estado(SILENCIO)
{}

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

		if(m_amplitudActual <= (m_nivSustain + m_decDecay))  // ← llegó al nivel?
			{
				m_amplitudActual = m_nivSustain;  // ← clampear para no pasarse
				m_estado = SUSTAIN;              // ← transición
			}
		else
			{
				m_amplitudActual -= m_decDecay;
			}
		break;

	case SUSTAIN:
	    m_amplitudActual = m_nivSustain;
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
	m_estado = ATTACK;
}
                          // cambia estado a ATTACK

void ADSR::noteOff() // llamado desde Keyboard al soltar tecla
{
	m_estado = RELEASE;
}                         // cambia estado a RELEASE

uint16_t ADSR::getAmplitud()
{
	uint32_t amp = (m_amplitudActual / 1000);
	return (uint16_t)(amp > 512 ? 512 : amp);  // clampear a 512 máximo
	// devuelve m_amplitudActual para pasarla al oscilador
}




// Setters llamados desde el while del main con los valores del ADCScanner
void ADSR::setAttack(uint16_t potval) {
    // potval 0-4095 → tiempo 10ms a 5000ms
    uint32_t tiempoMs = 10 + ((uint32_t)potval * 4990 / 4095);


    //m_incAttack = 512000 / (tiempoMs * 22);

    m_incAttack = 512000 / (tiempoMs * (SAMPLE_RATE / 1000));
    if(m_incAttack == 0) m_incAttack = 1;  //si el tiempo es muy largo evito redondeo a 0
}

void ADSR::setDecay(uint16_t potval) {
    // potval 0-4095 → tiempo 10ms a 5000ms
    uint32_t tiempoMs = 10 + ((uint32_t)potval * 4990 / 4095);

    //m_decDecay = 512000 / (tiempoMs * 22);

    m_decDecay = 512000 / (tiempoMs * (SAMPLE_RATE / 1000));
    if(m_decDecay == 0) m_decDecay = 1;		//si el tiempo es muy largo evito redondeo a 0
}

void ADSR::setSustain(uint16_t potval) {
    // potval 0-4095 → nivel 0 a 512000
    m_nivSustain = ((uint32_t)potval * 512000) / 4095;
}

void ADSR::setRelease(uint16_t potval) {
    // potval 0-4095 → tiempo 10ms a 5000ms


    uint32_t tiempoMs = 10 + ((uint32_t)potval * 4990 / 4095);

    //m_decRelease = 512000 / (tiempoMs * 22);

    m_decRelease = 512000 / (tiempoMs * (SAMPLE_RATE / 1000));
    if(m_decRelease == 0) m_decRelease = 1;		//si el tiempo es muy largo evito redondeo a 0
}

void ADSR::setVolumen(uint16_t potval) {
    // potval 0-4095 → volumen 0 a 512000
    m_volumen = ((uint32_t)potval * 512000) / 4095;
}

ADSR::~ADSR() {}

