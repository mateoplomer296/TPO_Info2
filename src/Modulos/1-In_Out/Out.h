/*
 * Out.h
 *
 *  Created on: 22 abr. 2026
 *      Author: Marcelo Trujillo
 */

#ifndef MODULOS_1_IN_OUT_1A_OUT_OUT_H_
#define MODULOS_1_IN_OUT_1A_OUT_OUT_H_

class Out
{
	public:
		virtual void SetPin( void ) const = 0;
		virtual void ClrPin( void ) const = 0;
		virtual void SetDir ( uint8_t direccion )= 0;
};

#endif /* MODULOS_1_IN_OUT_1A_OUT_OUT_H_ */
