/*
 * Sintetizador.h
 *
 *  Created on: 27 oct. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_SINTETIZADOR_SINTETIZADOR_H_
#define MODULOS_SINTETIZADOR_SINTETIZADOR_H_
#include "LPC845.h"
#include "teclado.h"
#include "Oscilador.h"
#include "Sineosc.h"
#include "Squareosc.h"
#include "Triosc.h"
#include "Sawosc.h"
#include "ADSR.h"
#include "AdcScanner.h"

class Sintetizador {
public:
enum Estado{STANDALONE, REMOTE};
Sintetizador(Teclado& teclado, ADCScanner& scanner);
void ejecutar();                    // se llama en el while del main
void cambiarEstado(Estado nuevo);
uint16_t generarSample();
void remoteTecla(uint8_t id, uint16_t valor);
void remotePote(uint8_t id, uint16_t valor);
virtual ~Sintetizador();


private:
	Estado m_estado;
	Teclado&    m_teclado;
	ADCScanner& m_scanner;

	Sineosc   m_sine;
	Squareosc m_square;
	Sawosc    m_saw;
	Triosc    m_tri;
	Sineosc   m_modOsc;           // el modulador sigue siendo senoidal

	Oscilador* m_ondas[4];        // las 4 ondas, para recorrerlas
	Oscilador* m_osc;             // la activa
	uint8_t    m_onda;

	ADSR m_car;
	ADSR m_mod;
	uint8_t m_adsr; 	//para alternar config de pots car y mod

	uint32_t m_frecBase;
	uint32_t m_phaseIncBase;
	uint32_t m_ratio;
	int32_t  m_fmIndice;

	uint8_t m_modo; 	// para alternar standalone y remoto

	const uint32_t NOTAS[32] =
		{
		    // Octava 3
		    130813,  // [0]  Do 3
		    138591,  // [1]  Do# 3
		    146832,  // [2]  Re 3
		    155563,  // [3]  Re# 3
		    164814,  // [4]  Mi 3
		    174614,  // [5]  Fa 3
		    184997,  // [6]  Fa# 3
		    195998,  // [7]  Sol 3
		    207652,  // [8]  Sol# 3
		    220000,  // [9]  La 3
		    233082,  // [10] La# 3
		    246942,  // [11] Si 3

		    // Octava 4
		    261626,  // [12] Do 4 (Central)
		    277183,  // [13] Do# 4
		    293665,  // [14] Re 4
		    311127,  // [15] Re# 4
		    329628,  // [16] Mi 4
		    349228,  // [17] Fa 4
		    369994,  // [18] Fa# 4
		    391995,  // [19] Sol 4
		    415305,  // [20] Sol# 4
		    440000,  // [21] La 4
		    466164,  // [22] La# 4
		    493883,  // [23] Si 4

			//  Octava 5
			523251,  // [24] Do 5
			554365,  // [25] Do# 5
			587330,  // [26] Re 5
			622254,  // [27] Re# 5
			659255,  // [28] Mi 5
			698456,  // [29] Fa 5
			739989,  // [30] Fa# 5
			783991   // [31] Sol 5
		};
	uint16_t m_paramRemoto[8] = {0};


private:


	void atenderTeclado();     // notas, siempre activo
	void atenderBotones(uint8_t boton);     // eventos de función, siempre activo
	void estadoStandalone();   // los parámetros vienen de los pots
	void estadoRemote();       // los parámetros vienen de la UART
	void aplicarFrecuencia();
	void siguienteOnda();
	void iniciarRemoteUart();

	void actualizarLCD();




};

#endif /* MODULOS_SINTETIZADOR_SINTETIZADOR_H_ */
