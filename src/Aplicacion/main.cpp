#include "Inicializar.h"

//Timer timerled(Timer::SEG,Callback1);

uint32_t fmIndice = 100000000;
uint32_t  sine_phaseIncBase = 1;
void Callback1(void)
{

}


void CallbackAudio(){

//	adsr_car.update();
//	adsr_mod.update();
//
//	volatile int32_t mod_sample = (int32_t)mod.nextSample(adsr_mod.getAmplitud()) - 512;
//	volatile int32_t desviacion = (int32_t)((int64_t)mod_sample * (int32_t)fmIndice >> 9);
//
//	uint32_t nuevoPhaseInc = (sine_phaseIncBase + desviacion);  // desviacion puede ser negativo, la suma en unsigned "wrappea" correctamente
//	sine.setPhaseInc(nuevoPhaseInc);
//
//	uint16_t muestra = sine.nextSample(adsr_car.getAmplitud());
//	DacWrite(muestra);
	DacWrite(Synth.generarSample());
}


int main(void) {
CTimer_SetHandler( CallbackAudio );
Inicializar();
InicializarTimerAudio();


    while(1)
    {


//    	uint8_t tecla       = teclado.GetKey();
//    	uint8_t teclaSuelta = teclado.GetKeyReleased();

    	// uint32_t ratio = 1 + ((scanner.getParam(7) * 7) / 4095);


    	 Synth.ejecutar();




    }
    return 0 ;
}
