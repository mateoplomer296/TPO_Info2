/*
 * Gpio.h
 *
 *  Created on: 15 abr. 2026
 *      Author: Marcelo Trujillo
 */

#ifndef MODULOS_2_GPIO_GPIO_H_
#define MODULOS_2_GPIO_GPIO_H_

#include "LPC845.h"
#include "In.h"
#include "Out.h"

class Gpio : public In , Out
{
	protected:
		const uint8_t m_port;
		const uint8_t m_pin;
		const uint8_t m_modo;
		uint8_t m_direccion;
		const uint8_t m_actividad;

	public:
		enum ACTIVIDAD {BAJO,ALTO};
		enum ESTADO {OFF,ON};
		enum DIRECCION {ENTRADA,SALIDA};
		enum PUERTOS { PORT0,PORT1};
		enum MODE_OUTPUT {PUSHPULL, OPENCOLECTOR};
		enum MODE_INTPUT {INACTIVE, PULLDOWN, PULLUP, REPEATER};

		Gpio();
		Gpio( uint8_t port , uint8_t pin ,uint8_t mode, uint8_t direccion ,uint8_t actividad = ALTO);
		bool GetPin( void ) const ;
		void SetPin( void ) const;
		void ClrPin( void ) const;
		void SetDir ( uint8_t direccion );
		uint8_t IndiceIOCON(void);
		void SetPinModeIn(void);
		void SetPinModeOut(void);
		explicit operator bool();
		bool operator ==(Gpio &o);
		bool operator !=(Gpio &o);

		virtual ~Gpio(){};
};


#endif /* MODULOS_2_GPIO_GPIO_H_ */
