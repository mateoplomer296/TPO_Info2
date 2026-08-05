/*
 * Gpio.cpp
 *
 *  Created on: 15 abr. 2026
 *      Author: Marcelo Trujillo
 */

#include "Gpio.h"


Gpio::Gpio( uint8_t port , uint8_t pin , uint8_t modo , uint8_t direccion ,uint8_t actividad ):
m_port(port), m_pin(pin),m_modo(modo), m_direccion(direccion),m_actividad(actividad)
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

uint8_t Gpio::IndiceIOCON( void )

{
	uint8_t Indice_PortPin ;
	Indice_PortPin = IOCON_INDEX_PIO0[m_pin];
	if ( m_port )
		Indice_PortPin = IOCON_INDEX_PIO1[m_pin];
	return Indice_PortPin;
}


void Gpio::SetPinModeIn ( void )

{
	uint8_t Indice_PortPin ;
	Indice_PortPin = IndiceIOCON();
	IOCON->PIO[ Indice_PortPin ] &= ~0x18;
	IOCON->PIO[ Indice_PortPin ] |= m_modo << 3;
	return ;
}



void Gpio::SetPinModeOut( void )

{
	uint8_t Indice_PortPin ;

	Indice_PortPin = IndiceIOCON();
	IOCON->PIO[ Indice_PortPin ] &= ~(1<<10);
	IOCON->PIO[ Indice_PortPin ] |= (m_modo << 10 );
	return;
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


