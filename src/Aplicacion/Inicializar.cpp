/*
 * Inicializar.cpp
 *
 *  Created on: 22 abr. 2026
 *      Author: Marcelo Trujillo
 */

#include "Inicializar.h"


// Salidas Digitales



//Gpio g_O1( Gpio::PORT1 , 1 , Gpio::SALIDA , Gpio::ALTO );
//Gpio g_O2( Gpio::PORT1 , 2 , Gpio::SALIDA , Gpio::ALTO );
//Gpio g_O3( Gpio::PORT0 , 30 , Gpio::SALIDA , Gpio::ALTO );
Led ledV(1,0); // VERDE
Led ledA(1,1); // AZUL
Led ledR(1,2); // ROJO

// Entradas Digitales
//Gpio g_I0( Gpio::PORT0 , 4 , Gpio::ENTRADA , Gpio::BAJO );
//Gpio g_I1( Gpio::PORT0 , 7 , Gpio::ENTRADA , Gpio::BAJO );
DigitalInputs teclaOn(0,4,Gpio::BAJO);
DigitalInputs teclaOff(0,12,Gpio::BAJO);
//Intext Emergencia(0,0,12,CallbackE);

//Gpio buzzer(0,29,Gpio::SALIDA,Gpio::ALTO);
Sineosc sine(440000,512);
Squareosc squa(440000,128);
Sawosc saw (440000,512);



Sineosc  mod(880000, 512);  // ratio 2x por defecto

ADCScanner scanner;

ADSR adsr_car;
ADSR adsr_mod;

Gpio col0(Gpio::PORT0,  11, Gpio::PUSHPULL, Gpio::SALIDA, Gpio::ALTO);   // scn — columnas
Gpio col1(Gpio::PORT0,  10, Gpio::PUSHPULL, Gpio::SALIDA, Gpio::ALTO);
Gpio col2(Gpio::PORT0,  9, Gpio::PUSHPULL, Gpio::SALIDA, Gpio::ALTO);
Gpio col3(Gpio::PORT0,  8, Gpio::PUSHPULL, Gpio::SALIDA, Gpio::ALTO);

Gpio fil0(Gpio::PORT0,  26, Gpio::PULLUP, Gpio::ENTRADA, Gpio::BAJO);  // ret — filas
Gpio fil1(Gpio::PORT0,  27, Gpio::PULLUP, Gpio::ENTRADA, Gpio::BAJO);
Gpio fil2(Gpio::PORT0,  28, Gpio::PULLUP, Gpio::ENTRADA, Gpio::BAJO);
Gpio fil3(Gpio::PORT0,  29, Gpio::PULLUP, Gpio::ENTRADA, Gpio::BAJO);
// Arrays terminados en nullptr — así la clase sabe cuántos hay
Gpio* scans[]   = { &col0, &col1, &col2, &col3, nullptr };
Gpio* returns[] = { &fil0, &fil1, &fil2, &fil3, nullptr };

// Crear el teclado
Teclado teclado(returns, scans);


//
//Gpio g_pulsador0 ( Gpio::PORT0 , 11 , Gpio::PULLUP , Gpio::ENTRADA , Gpio::ALTO );
//Gpio g_pulsador1 ( Gpio::PORT0 , 27 , Gpio::PULLUP , Gpio::ENTRADA , Gpio::ALTO );
//Gpio g_pulsador2 ( Gpio::PORT0 , 31 , Gpio::PULLUP , Gpio::ENTRADA , Gpio::ALTO );
//Gpio g_pulsador3 ( Gpio::PORT0 ,  4 , Gpio::PULLUP , Gpio::ENTRADA , Gpio::BAJO );
//Gpio g_pulsador4 ( Gpio::PORT0 , 29 , Gpio::PULLUP , Gpio::ENTRADA , Gpio::ALTO );
//
//Gpio *g_pulsadores[] = {&g_pulsador0 , &g_pulsador1, &g_pulsador2, &g_pulsador3 , &g_pulsador4 , nullptr};
//
//
//Teclado teclado(g_pulsadores);

void Scheduler (void){
	uint8_t i;
	for(i=0; i<PerifericoTemporizado::m_countPerifericosTemporizados; i++)
	{
		g_perifericosTemporizados[i]->HandlerDelPeriferico();
	}
}

void SysTick_Handler(void){
			Scheduler();
}
void Inicializar ( void )
{
	//clock del sistema a 30Mhz
	LPC_ROM_API->froApiBase->set_fro_frequency(30000);
	SYSCON->FROOSCCTRL |= (1 << 17);
	SYSCON->FRODIRECTCLKUEN &= ~1;
	SYSCON->FRODIRECTCLKUEN |= 1;


	ledV.Apagar();
	ledA.Apagar();
	ledR.Apagar();

	SysTick_Config(30000);
	DacConfig();
	AdcConfig();


}
