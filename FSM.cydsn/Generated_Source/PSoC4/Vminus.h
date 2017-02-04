/*******************************************************************************
* File Name: Vminus.h  
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

#if !defined(CY_PINS_Vminus_H) /* Pins Vminus_H */
#define CY_PINS_Vminus_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Vminus_aliases.h"


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
} Vminus_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Vminus_Read(void);
void    Vminus_Write(uint8 value);
uint8   Vminus_ReadDataReg(void);
#if defined(Vminus__PC) || (CY_PSOC4_4200L) 
    void    Vminus_SetDriveMode(uint8 mode);
#endif
void    Vminus_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vminus_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Vminus_Sleep(void); 
void Vminus_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Vminus__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Vminus_DRIVE_MODE_BITS        (3)
    #define Vminus_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Vminus_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Vminus_SetDriveMode() function.
         *  @{
         */
        #define Vminus_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Vminus_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Vminus_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Vminus_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Vminus_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Vminus_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Vminus_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Vminus_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Vminus_MASK               Vminus__MASK
#define Vminus_SHIFT              Vminus__SHIFT
#define Vminus_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vminus_SetInterruptMode() function.
     *  @{
     */
        #define Vminus_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Vminus_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Vminus_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Vminus_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Vminus__SIO)
    #define Vminus_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Vminus__PC) && (CY_PSOC4_4200L)
    #define Vminus_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Vminus_USBIO_DISABLE              ((uint32)(~Vminus_USBIO_ENABLE))
    #define Vminus_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Vminus_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Vminus_USBIO_ENTER_SLEEP          ((uint32)((1u << Vminus_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Vminus_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vminus_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Vminus_USBIO_SUSPEND_SHIFT)))
    #define Vminus_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Vminus_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vminus_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Vminus__PC)
    /* Port Configuration */
    #define Vminus_PC                 (* (reg32 *) Vminus__PC)
#endif
/* Pin State */
#define Vminus_PS                     (* (reg32 *) Vminus__PS)
/* Data Register */
#define Vminus_DR                     (* (reg32 *) Vminus__DR)
/* Input Buffer Disable Override */
#define Vminus_INP_DIS                (* (reg32 *) Vminus__PC2)

/* Interrupt configuration Registers */
#define Vminus_INTCFG                 (* (reg32 *) Vminus__INTCFG)
#define Vminus_INTSTAT                (* (reg32 *) Vminus__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Vminus_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Vminus__SIO)
    #define Vminus_SIO_REG            (* (reg32 *) Vminus__SIO)
#endif /* (Vminus__SIO_CFG) */

/* USBIO registers */
#if !defined(Vminus__PC) && (CY_PSOC4_4200L)
    #define Vminus_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Vminus_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Vminus_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Vminus_DRIVE_MODE_SHIFT       (0x00u)
#define Vminus_DRIVE_MODE_MASK        (0x07u << Vminus_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Vminus_H */


/* [] END OF FILE */
