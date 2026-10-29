/*
 * Sintetizador.cpp
 *
 *  Created on: 27 oct. 2026
 *      Author: joaqu
 */

#include <Sintetizador/Sintetizador.h>

Sintetizador::Sintetizador(Teclado& t, ADCScanner& s) :
	m_estado(STANDALONE), m_teclado(t), m_scanner(s),
    m_sine(440000, 512), m_square(440000, 512),
    m_saw(440000, 512),  m_tri(440000, 512),
    m_modOsc(880000, 512),
    m_onda(0), m_adsr(0), m_frecBase(440000),
	m_phaseIncBase(0), m_ratio(2), m_fmIndice(0), m_modo(0)
{
	m_ondas[0] = &m_sine;
	m_ondas[1] = &m_square;
	m_ondas[2] = &m_saw;
	m_ondas[3] = &m_tri;
	m_osc = m_ondas[0];
}
void Sintetizador::ejecutar()
{
	atenderTeclado();    // en cualquier estado se puede tocar

	switch(m_estado)
	{
		case STANDALONE: estadoStandalone(); break;
		case REMOTE:     estadoRemote();     break;
	}

	actualizarLCD();
}
//void Sintetizador::cambiarEstado(Estado nuevo)
//{
//	if(nuevo == m_estado) return;
//
//	// Acciones de entrada
//	if(nuevo == REMOTE)
//		/* avisar a Qt, desenganchar los pots */;
//
//
//	if(nuevo == STANDALONE)
//		/* desenganchar los pots para que no salten */;
//
//
//	m_estado = nuevo;
//}
void Sintetizador::atenderTeclado()
{
	  uint8_t tecla  = m_teclado.GetKey();
	  uint8_t teclaSuelta = m_teclado.GetKeyReleased();

	if(tecla != NO_KEY && tecla < 32)
		{
		  m_frecBase = NOTAS[tecla];
		  aplicarFrecuencia();
		  m_car.noteOn();
		  m_mod.noteOn();
		}

	if(teclaSuelta != NO_KEY)
		{
			m_car.noteOff();
			m_mod.noteOff();
		}
	if(tecla != NO_KEY && tecla >= 32 && tecla < 40) //botones
		{
		 	 atenderBotones(tecla);
		}
}
void Sintetizador::atenderBotones(uint8_t boton)
{
	switch(boton)
	{
	case 32: // siguiente forma de onda
		siguienteOnda();
		break;
	case 33: //Editar ADSR carrier/modulador
		m_adsr = (m_adsr + 1) % 2;
		break;
	case 34: //Preset anterior

		break;
	case 35: //Preset siguiente

		break;
	case 36: //Guardar preset actual

		break;
	case 37: //Modo Standalone/Remoto
		m_modo = (m_modo + 1) % 2;
		if(m_modo == 0)
			m_estado = STANDALONE;
		else
		{
			m_estado = REMOTE;
			iniciarRemoteUart();
		}
		break;

	case 38:
		break;
	case 39:
		break;
	}
}
void Sintetizador::estadoStandalone()//ignorar uart, valores adsr por pots
{
	if(m_adsr == 0)
	{
		m_car.setAttack(m_scanner.getParam(1));
		m_car.setDecay(m_scanner.getParam(2));
		m_car.setSustain(m_scanner.getParam(3));
		m_car.setRelease(m_scanner.getParam(4));
		m_car.setVolumen(m_scanner.getParam(5));
	}
	else
	{
		m_mod.setAttack(m_scanner.getParam(1));
		m_mod.setDecay(m_scanner.getParam(2));
		m_mod.setSustain(m_scanner.getParam(3));
		m_mod.setRelease(m_scanner.getParam(4));
		m_mod.setVolumen(m_scanner.getParam(5));
	}

	m_fmIndice = 500000 + (((uint32_t)m_scanner.getParam(6) * 1000000) / 4095);
	m_ratio = 1 + ((m_scanner.getParam(7) * 7) / 4095); 	//ratio y fmindice se manejan siempre
}
void Sintetizador::estadoRemote()//ignorar pots fisicos, manejado por uart
{

}
void Sintetizador::aplicarFrecuencia()
{
	m_osc->setFreq(m_frecBase);
	m_phaseIncBase = Oscilador::freqToPhaseInc(m_frecBase);
	m_modOsc.setFreq(m_frecBase * m_ratio);
}
void Sintetizador::siguienteOnda()
{
	m_onda = (m_onda + 1) % 4;
	m_osc  = m_ondas[m_onda];
	aplicarFrecuencia();   // la onda nueva arranca con la frecuencia actual
							//cada oscilador tiene su propio m_phaseInc
}
uint16_t Sintetizador::generarSample()
{
	m_car.update();
	m_mod.update();

	int32_t mod_sample = (int32_t)m_modOsc.nextSample(m_mod.getAmplitud()) - 512;
	int32_t desviacion = ((int32_t)((int64_t)mod_sample * (int32_t)m_fmIndice) >> 9);

	m_osc->setPhaseInc((uint32_t)((int32_t)m_phaseIncBase + desviacion));
	return m_osc->nextSample(m_car.getAmplitud());
}
void Sintetizador::actualizarLCD()
{

}

void Sintetizador::iniciarRemoteUart()
{

}
Sintetizador::~Sintetizador() {
	// TODO Auto-generated destructor stub
}
