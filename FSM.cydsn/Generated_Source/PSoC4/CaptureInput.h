/*******************************************************************************
* File Name: CaptureInput.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CaptureInput_H) /* Pins CaptureInput_H */
#define CY_PINS_CaptureInput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CaptureInput_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} CaptureInput_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CaptureInput_Read(void);
void    CaptureInput_Write(uint8 value);
uint8   CaptureInput_ReadDataReg(void);
#if defined(CaptureInput__PC) || (CY_PSOC4_4200L) 
    void    CaptureInput_SetDriveMode(uint8 mode);
#endif
void    CaptureInput_SetInterruptMode(uint16 position, uint16 mode);
uint8   CaptureInput_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CaptureInput_Sleep(void); 
void CaptureInput_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CaptureInput__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CaptureInput_DRIVE_MODE_BITS        (3)
    #define CaptureInput_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CaptureInput_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CaptureInput_SetDriveMode() function.
         *  @{
         */
        #define CaptureInput_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CaptureInput_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CaptureInput_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CaptureInput_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CaptureInput_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CaptureInput_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CaptureInput_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CaptureInput_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CaptureInput_MASK               CaptureInput__MASK
#define CaptureInput_SHIFT              CaptureInput__SHIFT
#define CaptureInput_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CaptureInput_SetInterruptMode() function.
     *  @{
     */
        #define CaptureInput_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CaptureInput_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CaptureInput_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CaptureInput_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CaptureInput__SIO)
    #define CaptureInput_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CaptureInput__PC) && (CY_PSOC4_4200L)
    #define CaptureInput_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CaptureInput_USBIO_DISABLE              ((uint32)(~CaptureInput_USBIO_ENABLE))
    #define CaptureInput_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CaptureInput_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CaptureInput_USBIO_ENTER_SLEEP          ((uint32)((1u << CaptureInput_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CaptureInput_USBIO_SUSPEND_DEL_SHIFT)))
    #define CaptureInput_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CaptureInput_USBIO_SUSPEND_SHIFT)))
    #define CaptureInput_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CaptureInput_USBIO_SUSPEND_DEL_SHIFT)))
    #define CaptureInput_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CaptureInput__PC)
    /* Port Configuration */
    #define CaptureInput_PC                 (* (reg32 *) CaptureInput__PC)
#endif
/* Pin State */
#define CaptureInput_PS                     (* (reg32 *) CaptureInput__PS)
/* Data Register */
#define CaptureInput_DR                     (* (reg32 *) CaptureInput__DR)
/* Input Buffer Disable Override */
#define CaptureInput_INP_DIS                (* (reg32 *) CaptureInput__PC2)

/* Interrupt configuration Registers */
#define CaptureInput_INTCFG                 (* (reg32 *) CaptureInput__INTCFG)
#define CaptureInput_INTSTAT                (* (reg32 *) CaptureInput__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CaptureInput_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CaptureInput__SIO)
    #define CaptureInput_SIO_REG            (* (reg32 *) CaptureInput__SIO)
#endif /* (CaptureInput__SIO_CFG) */

/* USBIO registers */
#if !defined(CaptureInput__PC) && (CY_PSOC4_4200L)
    #define CaptureInput_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CaptureInput_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CaptureInput_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CaptureInput_DRIVE_MODE_SHIFT       (0x00u)
#define CaptureInput_DRIVE_MODE_MASK        (0x07u << CaptureInput_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CaptureInput_H */


/* [] END OF FILE */
