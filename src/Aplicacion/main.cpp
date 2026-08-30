#include "Inicializar.h"

Timer timerled(Timer::SEG,Callback1);
volatile uint32_t i = 200000;

bool estadoAnteriorOn  = false;
bool estadoAnteriorOff = false;



void Callback1(void)
{
	i = i + 30000;
	ledV.CambiarEstado();
	sine.setFreq(i);
	timerled.TimerStart(1);
}
void CallbackAudio(){
	adsr.update();
	uint16_t muestra = sine.nextSample(adsr.getAmplitud());
	DacWrite(muestra);
}
int main(void) {
CTimer_SetHandler( CallbackAudio );
Inicializar();
InicializarTimerAudio();
//timerled.TimerStart(1);


    while(1)
    {
    	bool estadoActualOn  = teclaOn.get();
		bool estadoActualOff = teclaOff.get();
    	//timerled.TmrEvent();
    	 uint16_t potVal = scanner.getParam(7);

    	 uint32_t freq   = 220000 + (potVal * (550000 / 4095));
    	 sine.setFreq(freq);

    	 // Flanco ascendente teclaOn: antes era 0, ahora es 1
    	     if(estadoActualOn && !estadoAnteriorOn)
    	         adsr.noteOn();

    	     // Flanco ascendente teclaOff: antes era 0, ahora es 1
    	     if(estadoActualOff && !estadoAnteriorOff)
    	         adsr.noteOff();

    	     estadoAnteriorOn  = estadoActualOn;
    	     estadoAnteriorOff = estadoActualOff;
    	     	 	 adsr.setAttack(2000);    // 2 segundos de attack
    	       	     adsr.setDecay(1000);     // 1 segundo de decay
    	       	     adsr.setSustain(2000);   // sustain a mitad
    	      	     adsr.setRelease(2000);   // 2 segundos de release
    	       	     adsr.setVolumen(4000);

    }
    return 0 ;
}
