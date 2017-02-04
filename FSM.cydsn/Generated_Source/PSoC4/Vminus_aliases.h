/*******************************************************************************
* File Name: Vminus.h  
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

#if !defined(CY_PINS_Vminus_ALIASES_H) /* Pins Vminus_ALIASES_H */
#define CY_PINS_Vminus_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Vminus_0			(Vminus__0__PC)
#define Vminus_0_PS		(Vminus__0__PS)
#define Vminus_0_PC		(Vminus__0__PC)
#define Vminus_0_DR		(Vminus__0__DR)
#define Vminus_0_SHIFT	(Vminus__0__SHIFT)
#define Vminus_0_INTR	((uint16)((uint16)0x0003u << (Vminus__0__SHIFT*2u)))

#define Vminus_INTR_ALL	 ((uint16)(Vminus_0_INTR))


#endif /* End Pins Vminus_ALIASES_H */


/* [] END OF FILE */
