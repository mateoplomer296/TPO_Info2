#include "Inicializar.h"

Timer timerled(Timer::SEG,Callback1);
volatile uint32_t i = 200000;

void Callback1(void)
{
	i = i + 30000;
	ledV.CambiarEstado();
	saw.setFreq(i);
	timerled.TimerStart(1);
}
void CallbackAudio(){
	uint16_t muestra = saw.nextSample();

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
