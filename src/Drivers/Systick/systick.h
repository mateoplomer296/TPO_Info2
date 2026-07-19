/*
 * systick.h
 *
 *  Created on: 13 may. 2026
 *      Author: danie
 */

#ifndef SRC_DRIVERS_SYSTICK_H_
#define SRC_DRIVERS_SYSTICK_H_
#include "LPC845.h"


#if defined (__cplusplus)
	extern "C"
	{

		void SysTick_Handler(void);
	}
#endif

extern uint32_t tiempo;
/*!< System Control Space Base Address */
#define 	SCS_BASE     (0xE000E000UL)
/*!< SysTick Base Address */
#define 	SysTick_BASE (SCS_BASE +  0x0010UL)

	typedef struct
	{
	  __IO uint32_t CTRL;	//CSR	/*!< SysTick Control and Status Register */
	  __IO uint32_t RELOAD;   //RVR	/*!< SysTick Reload Value Register */
	  __IO uint32_t CURR;    //CURR	/*!< SysTick Current Value Register */
	  __O  uint32_t CALIB;  	/*!< SysTick Calibration Register */
	} SysTick_Type;

//#define	 SysTick 		( (SysTick_Type* ) SysTick_BASE )

/*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Pos     	16U
/*!< COUNTFLAG Mask */
#define SysTick_CTRL_COUNTFLAG_Msk     	(1UL << SysTick_CTRL_COUNTFLAG_Pos)

/*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Pos      	2U
/*!< CLKSOURCE Mask */
#define SysTick_CTRL_CLKSOURCE_Msk     	(1UL << SysTick_CTRL_CLKSOURCE_Pos)

/*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Pos        	1U
/*!< TICKINT Mask */
#define SysTick_CTRL_TICKINT_Msk       	(1UL << SysTick_CTRL_TICKINT_Pos)

/*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Pos         	0U
/*!< ENABLE Mask */
#define SysTick_CTRL_ENABLE_Msk		(1UL << SysTick_CTRL_ENABLE_Pos)

/*!< RELOAD Mask */
#define SysTick_LOAD_RELOAD_Msk   (0x00FFFFFFUL)
	uint32_t SysTick_Config(uint32_t ticks);
#endif /* SRC_DRIVERS_SYSTICK_H_ */
