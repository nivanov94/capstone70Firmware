/*******************************************************************************
* File Name: Vplus.h  
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

#if !defined(CY_PINS_Vplus_ALIASES_H) /* Pins Vplus_ALIASES_H */
#define CY_PINS_Vplus_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Vplus_0			(Vplus__0__PC)
#define Vplus_0_PS		(Vplus__0__PS)
#define Vplus_0_PC		(Vplus__0__PC)
#define Vplus_0_DR		(Vplus__0__DR)
#define Vplus_0_SHIFT	(Vplus__0__SHIFT)
#define Vplus_0_INTR	((uint16)((uint16)0x0003u << (Vplus__0__SHIFT*2u)))

#define Vplus_INTR_ALL	 ((uint16)(Vplus_0_INTR))


#endif /* End Pins Vplus_ALIASES_H */


/* [] END OF FILE */
