#include "Inicializar.h"

Timer timerled(Timer::SEG,Callback1);
volatile uint32_t i = 200000;

void Callback1(void)
{
	i = i + 30000;
	ledV.CambiarEstado();
	sine.setFreq(i);
	timerled.TimerStart(1);
}
void CallbackAudio(){
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
    	//timerled.TmrEvent();
    	 uint16_t potVal = scanner.getParam(7);

    	 uint32_t freq   = 220000 + (potVal * (550000 / 4095));
    	 sine.setFreq(freq);

    }
    return 0 ;
}
