#include "Inicializar.h"

//Timer timerled(Timer::SEG,Callback1);

uint32_t fmIndice = 100000000;
uint32_t  sine_phaseIncBase = 1;
void Callback1(void)
{

}
//void CallbackAudio(){
//	adsr_car.update();
//	uint16_t muestra = sine.nextSample(adsr_car.getAmplitud());
//	DacWrite(muestra);
//}

void CallbackAudio(){
	pin_debug.SetPin();

	adsr_car.update();
	adsr_mod.update();

	volatile int32_t mod_sample = (int32_t)mod.nextSample(adsr_mod.getAmplitud()) - 512;
	volatile int32_t desviacion = (int32_t)((int64_t)mod_sample * (int32_t)fmIndice >> 9);

	uint32_t nuevoPhaseInc = (sine_phaseIncBase + desviacion);  // desviacion puede ser negativo, la suma en unsigned "wrappea" correctamente
	sine.setPhaseInc(nuevoPhaseInc);

	uint16_t muestra = sine.nextSample(adsr_car.getAmplitud());
	DacWrite(muestra);
	pin_debug.ClrPin();
}


int main(void) {
CTimer_SetHandler( CallbackAudio );
Inicializar();
InicializarTimerAudio();
//timerled.TimerStart(1);


    while(1)
    {


    	uint8_t tecla       = teclado.GetKey();
    	uint8_t teclaSuelta = teclado.GetKeyReleased();

    	 uint32_t ratio = 1 + ((scanner.getParam(7) * 7) / 4095);

    	if(tecla != NO_KEY && tecla < 12)
    	{


    	    sine.setFreq(NOTAS[tecla]);
    	    sine_phaseIncBase = sine.getPhaseInc();
    	    mod.setFreq(NOTAS[tecla] * ratio);


    	    adsr_car.noteOn();
    	    adsr_mod.noteOn();

    	}

    	if(teclaSuelta != NO_KEY)
		{
			adsr_car.noteOff();
			adsr_mod.noteOff();
		}





				 adsr_car.setAttack(100);    // 0.5 segundos de attack
				 adsr_car.setDecay(1000);     // 1 segundo de decay
				 adsr_car.setSustain(1000);   // sustain a mitad
				 adsr_car.setRelease(1000);   // 2 segundos de release
				 adsr_car.setVolumen(1000);

				 adsr_mod.setAttack(200);
				 adsr_mod.setDecay(300);
				 adsr_mod.setSustain(000);
				 adsr_mod.setRelease(2000);
				 adsr_mod.setVolumen(scanner.getParam(5));

    }
    return 0 ;
}
