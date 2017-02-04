/*******************************************************************************
* File Name: Vminus.c  
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
#include "Vminus.h"

static Vminus_BACKUP_STRUCT  Vminus_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Vminus_Sleep
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
*  \snippet Vminus_SUT.c usage_Vminus_Sleep_Wakeup
*******************************************************************************/
void Vminus_Sleep(void)
{
    #if defined(Vminus__PC)
        Vminus_backup.pcState = Vminus_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Vminus_backup.usbState = Vminus_CR1_REG;
            Vminus_USB_POWER_REG |= Vminus_USBIO_ENTER_SLEEP;
            Vminus_CR1_REG &= Vminus_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Vminus__SIO)
        Vminus_backup.sioState = Vminus_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Vminus_SIO_REG &= (uint32)(~Vminus_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Vminus_Wakeup
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
*  Refer to Vminus_Sleep() for an example usage.
*******************************************************************************/
void Vminus_Wakeup(void)
{
    #if defined(Vminus__PC)
        Vminus_PC = Vminus_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Vminus_USB_POWER_REG &= Vminus_USBIO_EXIT_SLEEP_PH1;
            Vminus_CR1_REG = Vminus_backup.usbState;
            Vminus_USB_POWER_REG &= Vminus_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Vminus__SIO)
        Vminus_SIO_REG = Vminus_backup.sioState;
    #endif
}


/* [] END OF FILE */
