#include "Inicializar.h"

//Timer timerled(Timer::SEG,Callback1);



void Callback1(void)
{

}
void CallbackAudio(){
	adsr_car.update();
	uint16_t muestra = sine.nextSample(adsr_car.getAmplitud());
	DacWrite(muestra);
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

    	// Primero el release, luego el press


    	if(tecla != NO_KEY && tecla < 12)
    	{


    	    sine.setFreq(NOTAS[tecla]);
    	    adsr_car.noteOn();

    	 //   adsr_mod.noteOn();
    	}

    	if(teclaSuelta != NO_KEY)
    	    	{
    	    	    adsr_car.noteOff();
    	    	   // adsr_mod.noteOff();
    	    	}





				 adsr_car.setAttack(500);    // 0.5 segundos de attack
				 adsr_car.setDecay(1000);     // 1 segundo de decay
				 adsr_car.setSustain(1000);   // sustain a mitad
				 adsr_car.setRelease(3500);   // 2 segundos de release
				 adsr_car.setVolumen(1000);

    }
    return 0 ;
}
