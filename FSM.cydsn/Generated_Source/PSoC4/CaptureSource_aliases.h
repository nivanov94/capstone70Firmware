/*******************************************************************************
* File Name: CaptureSource.h  
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

#if !defined(CY_PINS_CaptureSource_ALIASES_H) /* Pins CaptureSource_ALIASES_H */
#define CY_PINS_CaptureSource_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CaptureSource_0			(CaptureSource__0__PC)
#define CaptureSource_0_PS		(CaptureSource__0__PS)
#define CaptureSource_0_PC		(CaptureSource__0__PC)
#define CaptureSource_0_DR		(CaptureSource__0__DR)
#define CaptureSource_0_SHIFT	(CaptureSource__0__SHIFT)
#define CaptureSource_0_INTR	((uint16)((uint16)0x0003u << (CaptureSource__0__SHIFT*2u)))

#define CaptureSource_INTR_ALL	 ((uint16)(CaptureSource_0_INTR))


#endif /* End Pins CaptureSource_ALIASES_H */


/* [] END OF FILE */
