/*******************************************************************************************************************************//**
 *
 * @file		swhandler.h
 * @brief		Clase virtual pura. Esta clase debe ser heredada por las clases que se tienen que enganchar del Systick Timer
 * @date		4 may. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/
#ifndef CALLBACK_H_
#define CALLBACK_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "LPC845.h"

using namespace std;


class PerifericoTemporizado
{
	private:
		void (*m_callbackDelperiferico) (void);

	public:
		static uint8_t m_countPerifericosTemporizados;

		PerifericoTemporizado(  );

		void InstalarPerifericoTemporizado (PerifericoTemporizado *);

		virtual void HandlerDelPeriferico ( void ) = 0 ;

		virtual ~PerifericoTemporizado( );
};
extern PerifericoTemporizado *g_perifericosTemporizados[ ];

#endif /* CALLBACK_H_ */
