/*
 * AdcScanner.h
 *
 *  Created on: 20 ago. 2026
 *      Author: joaqu
 */

#ifndef MODULOS_ADCSCANNER_ADCSCANNER_H_
#define MODULOS_ADCSCANNER_ADCSCANNER_H_
#include "PerifericoTemporizado.h"
class ADCScanner:public PerifericoTemporizado {

	 	uint8_t  m_canalActual;   // que canal toca ahora
	    bool     m_primerTick;    // ignorar primer resultado
	    uint16_t m_params[7];     // resultados
public:
	ADCScanner();


	 void HandlerDelPeriferico();  // se engancha al SysTick automático
	 uint16_t getParam(uint8_t index);  // única forma de leer params


	virtual ~ADCScanner(){};
};

#endif /* MODULOS_ADCSCANNER_ADCSCANNER_H_ */
