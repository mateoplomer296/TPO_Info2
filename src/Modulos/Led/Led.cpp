

#include "Led.h"

Led::Led(uint8_t port , uint8_t pin):Gpio(port,pin,SALIDA,BAJO) {

}
void Led::Encender(void){
	SetPin();
};
void Led::Apagar(void){
	ClrPin();
};

void Led::CambiarEstado(){
	if(GetPin()){
		ClrPin();
	}else
		SetPin();
};


