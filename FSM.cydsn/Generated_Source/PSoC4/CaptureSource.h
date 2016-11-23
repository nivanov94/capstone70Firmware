/*******************************************************************************
* File Name: CaptureSource.h  
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

#if !defined(CY_PINS_CaptureSource_H) /* Pins CaptureSource_H */
#define CY_PINS_CaptureSource_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CaptureSource_aliases.h"


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
} CaptureSource_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CaptureSource_Read(void);
void    CaptureSource_Write(uint8 value);
uint8   CaptureSource_ReadDataReg(void);
#if defined(CaptureSource__PC) || (CY_PSOC4_4200L) 
    void    CaptureSource_SetDriveMode(uint8 mode);
#endif
void    CaptureSource_SetInterruptMode(uint16 position, uint16 mode);
uint8   CaptureSource_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CaptureSource_Sleep(void); 
void CaptureSource_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CaptureSource__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CaptureSource_DRIVE_MODE_BITS        (3)
    #define CaptureSource_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CaptureSource_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CaptureSource_SetDriveMode() function.
         *  @{
         */
        #define CaptureSource_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CaptureSource_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CaptureSource_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CaptureSource_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CaptureSource_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CaptureSource_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CaptureSource_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CaptureSource_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CaptureSource_MASK               CaptureSource__MASK
#define CaptureSource_SHIFT              CaptureSource__SHIFT
#define CaptureSource_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CaptureSource_SetInterruptMode() function.
     *  @{
     */
        #define CaptureSource_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CaptureSource_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CaptureSource_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CaptureSource_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CaptureSource__SIO)
    #define CaptureSource_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CaptureSource__PC) && (CY_PSOC4_4200L)
    #define CaptureSource_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CaptureSource_USBIO_DISABLE              ((uint32)(~CaptureSource_USBIO_ENABLE))
    #define CaptureSource_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CaptureSource_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CaptureSource_USBIO_ENTER_SLEEP          ((uint32)((1u << CaptureSource_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CaptureSource_USBIO_SUSPEND_DEL_SHIFT)))
    #define CaptureSource_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CaptureSource_USBIO_SUSPEND_SHIFT)))
    #define CaptureSource_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CaptureSource_USBIO_SUSPEND_DEL_SHIFT)))
    #define CaptureSource_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CaptureSource__PC)
    /* Port Configuration */
    #define CaptureSource_PC                 (* (reg32 *) CaptureSource__PC)
#endif
/* Pin State */
#define CaptureSource_PS                     (* (reg32 *) CaptureSource__PS)
/* Data Register */
#define CaptureSource_DR                     (* (reg32 *) CaptureSource__DR)
/* Input Buffer Disable Override */
#define CaptureSource_INP_DIS                (* (reg32 *) CaptureSource__PC2)

/* Interrupt configuration Registers */
#define CaptureSource_INTCFG                 (* (reg32 *) CaptureSource__INTCFG)
#define CaptureSource_INTSTAT                (* (reg32 *) CaptureSource__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CaptureSource_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CaptureSource__SIO)
    #define CaptureSource_SIO_REG            (* (reg32 *) CaptureSource__SIO)
#endif /* (CaptureSource__SIO_CFG) */

/* USBIO registers */
#if !defined(CaptureSource__PC) && (CY_PSOC4_4200L)
    #define CaptureSource_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CaptureSource_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CaptureSource_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CaptureSource_DRIVE_MODE_SHIFT       (0x00u)
#define CaptureSource_DRIVE_MODE_MASK        (0x07u << CaptureSource_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CaptureSource_H */


/* [] END OF FILE */
