/*
 * Gpio.cpp
 *
 *  Created on: 15 abr. 2026
 *      Author: Marcelo Trujillo
 */

#include "Gpio.h"


Gpio::Gpio( uint8_t port , uint8_t pin ,uint8_t direccion ,uint8_t actividad ):
m_port(port), m_pin(pin),m_direccion(direccion),m_actividad(actividad)
{


	SYSCON->SYSAHBCLKCTRL0 |=  ( 1 << 20 ) | ( 1 << 6 );

	if ( direccion )
		GPIO->DIR[ m_port ] |=  1 << pin ;
	else
		GPIO->DIR[ m_port ] &=  ~(1 << pin ) ;
}

void Gpio::SetPin( void )const
{
	GPIO->B[m_port][m_pin] = ( m_actividad == ALTO ) ? ON : OFF ;
}

void Gpio::ClrPin( void )const
{
	GPIO->B[m_port][m_pin] = ( m_actividad == ALTO ) ? OFF : ON ;
}

bool Gpio::GetPin( void )const
{
	return ( m_actividad == ALTO ) ? GPIO->B[m_port][m_pin] : !GPIO->B[m_port][m_pin] ;
}

void Gpio::SetDir ( uint8_t direccion )
{
	if ( direccion )
		GPIO->DIR[ m_port ] |=  1 << m_pin ;
	else
		GPIO->DIR[ m_port ] &=  ~(1 << m_pin ) ;

	m_direccion = direccion ;
}

Gpio::operator bool(){
	return this->GetPin();
}

bool Gpio::operator ==(Gpio &o){
	if(o.GetPin()== this->GetPin()){
		return true;
	}
	return false;
}

bool Gpio::operator !=(Gpio &o){
	if(o.GetPin()!= this->GetPin()){
		return true;
	}
	return false;
}
Gpio::~Gpio() {
	// TODO Auto-generated destructor stub
}

