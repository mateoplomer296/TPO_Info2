#include "systick.h"/*

 * systick.cpp
 *
 *  Created on: 13 may. 2026
 *      Author: danie
 */

uint32_t tiempo;
uint32_t SysTick_Config(uint32_t ticks)
{
	if((ticks-1)> SysTick_LOAD_RELOAD_Msk)
	{
		return 1;
	};
	SCB->SHPR3 &= ~(3 << 30); //limpio
	SCB->SHPR3 |= (3 << 30); //seteo prioridad mas baja al systick (va de 0 a 3)
	SysTick->RELOAD = ticks-1;
	SysTick->CURR = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk
			| SysTick_CTRL_TICKINT_Msk
			| SysTick_CTRL_ENABLE_Msk;




	return 0;


}


/*void SysTick_Handler(void){
			if(tiempo)
				tiempo--;
		};
*/

