/*******************************************************************************
* File Name: Vplus.h  
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

#if !defined(CY_PINS_Vplus_H) /* Pins Vplus_H */
#define CY_PINS_Vplus_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Vplus_aliases.h"


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
} Vplus_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Vplus_Read(void);
void    Vplus_Write(uint8 value);
uint8   Vplus_ReadDataReg(void);
#if defined(Vplus__PC) || (CY_PSOC4_4200L) 
    void    Vplus_SetDriveMode(uint8 mode);
#endif
void    Vplus_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vplus_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Vplus_Sleep(void); 
void Vplus_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Vplus__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Vplus_DRIVE_MODE_BITS        (3)
    #define Vplus_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Vplus_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Vplus_SetDriveMode() function.
         *  @{
         */
        #define Vplus_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Vplus_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Vplus_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Vplus_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Vplus_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Vplus_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Vplus_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Vplus_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Vplus_MASK               Vplus__MASK
#define Vplus_SHIFT              Vplus__SHIFT
#define Vplus_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vplus_SetInterruptMode() function.
     *  @{
     */
        #define Vplus_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Vplus_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Vplus_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Vplus_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Vplus__SIO)
    #define Vplus_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Vplus__PC) && (CY_PSOC4_4200L)
    #define Vplus_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Vplus_USBIO_DISABLE              ((uint32)(~Vplus_USBIO_ENABLE))
    #define Vplus_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Vplus_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Vplus_USBIO_ENTER_SLEEP          ((uint32)((1u << Vplus_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Vplus_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vplus_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Vplus_USBIO_SUSPEND_SHIFT)))
    #define Vplus_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Vplus_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vplus_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Vplus__PC)
    /* Port Configuration */
    #define Vplus_PC                 (* (reg32 *) Vplus__PC)
#endif
/* Pin State */
#define Vplus_PS                     (* (reg32 *) Vplus__PS)
/* Data Register */
#define Vplus_DR                     (* (reg32 *) Vplus__DR)
/* Input Buffer Disable Override */
#define Vplus_INP_DIS                (* (reg32 *) Vplus__PC2)

/* Interrupt configuration Registers */
#define Vplus_INTCFG                 (* (reg32 *) Vplus__INTCFG)
#define Vplus_INTSTAT                (* (reg32 *) Vplus__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Vplus_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Vplus__SIO)
    #define Vplus_SIO_REG            (* (reg32 *) Vplus__SIO)
#endif /* (Vplus__SIO_CFG) */

/* USBIO registers */
#if !defined(Vplus__PC) && (CY_PSOC4_4200L)
    #define Vplus_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Vplus_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Vplus_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Vplus_DRIVE_MODE_SHIFT       (0x00u)
#define Vplus_DRIVE_MODE_MASK        (0x07u << Vplus_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Vplus_H */


/* [] END OF FILE */
