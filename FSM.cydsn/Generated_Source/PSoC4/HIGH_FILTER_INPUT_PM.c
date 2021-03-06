/*******************************************************************************
* File Name: HIGH_FILTER_INPUT.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "HIGH_FILTER_INPUT.h"

static HIGH_FILTER_INPUT_BACKUP_STRUCT  HIGH_FILTER_INPUT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: HIGH_FILTER_INPUT_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet HIGH_FILTER_INPUT_SUT.c usage_HIGH_FILTER_INPUT_Sleep_Wakeup
*******************************************************************************/
void HIGH_FILTER_INPUT_Sleep(void)
{
    #if defined(HIGH_FILTER_INPUT__PC)
        HIGH_FILTER_INPUT_backup.pcState = HIGH_FILTER_INPUT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            HIGH_FILTER_INPUT_backup.usbState = HIGH_FILTER_INPUT_CR1_REG;
            HIGH_FILTER_INPUT_USB_POWER_REG |= HIGH_FILTER_INPUT_USBIO_ENTER_SLEEP;
            HIGH_FILTER_INPUT_CR1_REG &= HIGH_FILTER_INPUT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HIGH_FILTER_INPUT__SIO)
        HIGH_FILTER_INPUT_backup.sioState = HIGH_FILTER_INPUT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        HIGH_FILTER_INPUT_SIO_REG &= (uint32)(~HIGH_FILTER_INPUT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: HIGH_FILTER_INPUT_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to HIGH_FILTER_INPUT_Sleep() for an example usage.
*******************************************************************************/
void HIGH_FILTER_INPUT_Wakeup(void)
{
    #if defined(HIGH_FILTER_INPUT__PC)
        HIGH_FILTER_INPUT_PC = HIGH_FILTER_INPUT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            HIGH_FILTER_INPUT_USB_POWER_REG &= HIGH_FILTER_INPUT_USBIO_EXIT_SLEEP_PH1;
            HIGH_FILTER_INPUT_CR1_REG = HIGH_FILTER_INPUT_backup.usbState;
            HIGH_FILTER_INPUT_USB_POWER_REG &= HIGH_FILTER_INPUT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HIGH_FILTER_INPUT__SIO)
        HIGH_FILTER_INPUT_SIO_REG = HIGH_FILTER_INPUT_backup.sioState;
    #endif
}


/* [] END OF FILE */
