/*
 * AdcScanner.cpp
 *
 *  Created on: 20 ago. 2026
 *      Author: joaqu
 */

#include <AdcScanner/AdcScanner.h>

ADCScanner::ADCScanner()
{
	InstalarPerifericoTemporizado(this);
	m_primerTick = true;
	m_canalActual = 1;
}

void ADCScanner::HandlerDelPeriferico()
{
	if(!m_primerTick) //ignoro el primer tick
	{
		for(uint8_t i = 1; i <= 7; i++)
		{
			m_params[i-1] = getParam(i); //cargo todos los parametros en el vector
		}
	}

	m_primerTick = false;
	ADC0->SEQ_CTRL[0] |= (1 << 26);
}
uint16_t ADCScanner::getParam(uint8_t index)
{

	uint16_t result = ((ADC0->DAT[index]) >> 4 ) & 0x0FFF;

	return result;
}

