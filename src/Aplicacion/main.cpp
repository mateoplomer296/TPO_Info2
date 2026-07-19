#include "Inicializar.h"

Timer timerled(Timer::SEG,Callback1);
volatile uint32_t i = 440000;

void Callback1(void)
{
	i = i + 30000;
	ledV.CambiarEstado();
	sine.setFreq(i);
	timerled.TimerStart(1);
}
void CallbackAudio(){
	uint16_t muestra = sine.nextSample();

	DacWrite(muestra);
}
int main(void) {
CTimer_SetHandler( CallbackAudio );
Inicializar();
InicializarTimerAudio();
timerled.TimerStart(1);

    while(1)
    {
    	timerled.TmrEvent();
    }
    return 0 ;
}
