/*******************************************************************************************************************************//**
 *
 * @file		DigitalOutputs.cpp
 * @brief		Descripcion del modulo
 * @date		12 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "digital_outputs.h"


DigitalOutputs::DigitalOutputs( uint8_t puerto , uint8_t bit  , uint8_t actividad , uint8_t estado ):
					Gpio( puerto , bit , Gpio::SALIDA , actividad )
{
	m_bufferOutputs = estado;
	InstalarPerifericoTemporizado(this);
}

int8_t DigitalOutputs::set ( void )
{
	m_bufferOutputs = ON ;
	return 1;

}

int8_t DigitalOutputs::clr ( void )
{
	m_bufferOutputs =  OFF ;
	return 1;

}


DigitalOutputs& DigitalOutputs::operator= ( uint8_t estado )
{
	m_bufferOutputs =  estado ;
	return *this;
}

void DigitalOutputs::HandlerDelPeriferico ( void )
{
	if ( m_bufferOutputs )
		SetPin( );
	else
		ClrPin( );
}
