/*******************************************************************************
* File Name: motor.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_motor_ALIASES_H) /* Pins motor_ALIASES_H */
#define CY_PINS_motor_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define motor_0			(motor__0__PC)
#define motor_0_PS		(motor__0__PS)
#define motor_0_PC		(motor__0__PC)
#define motor_0_DR		(motor__0__DR)
#define motor_0_SHIFT	(motor__0__SHIFT)
#define motor_0_INTR	((uint16)((uint16)0x0003u << (motor__0__SHIFT*2u)))

#define motor_INTR_ALL	 ((uint16)(motor_0_INTR))


#endif /* End Pins motor_ALIASES_H */


/* [] END OF FILE */
