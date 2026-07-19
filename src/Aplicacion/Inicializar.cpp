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
DigitalInputs Start(0,4,Gpio::BAJO);
DigitalInputs Stop(0,12,Gpio::BAJO);
//Intext Emergencia(0,0,12,CallbackE);

//Gpio buzzer(0,29,Gpio::SALIDA,Gpio::ALTO);
Sineosc sine(440000,512);
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


}
