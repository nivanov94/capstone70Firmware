/*******************************************************************************
* File Name: FIRE_FILTER_INPUT.c  
* Version 2.20
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "FIRE_FILTER_INPUT.h"


#if defined(FIRE_FILTER_INPUT__PC)
    #define FIRE_FILTER_INPUT_SetP4PinDriveMode(shift, mode)  \
    do { \
        FIRE_FILTER_INPUT_PC =   (FIRE_FILTER_INPUT_PC & \
                                (uint32)(~(uint32)(FIRE_FILTER_INPUT_DRIVE_MODE_IND_MASK << \
                                (FIRE_FILTER_INPUT_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << \
                                (FIRE_FILTER_INPUT_DRIVE_MODE_BITS * (shift))); \
    } while (0)
#else
    #if (CY_PSOC4_4200L)
        #define FIRE_FILTER_INPUT_SetP4PinDriveMode(shift, mode)  \
        do { \
            FIRE_FILTER_INPUT_USBIO_CTRL_REG = (FIRE_FILTER_INPUT_USBIO_CTRL_REG & \
                                    (uint32)(~(uint32)(FIRE_FILTER_INPUT_DRIVE_MODE_IND_MASK << \
                                    (FIRE_FILTER_INPUT_DRIVE_MODE_BITS * (shift))))) | \
                                    (uint32)((uint32)(mode) << \
                                    (FIRE_FILTER_INPUT_DRIVE_MODE_BITS * (shift))); \
        } while (0)
    #endif
#endif
  

#if defined(FIRE_FILTER_INPUT__PC) || (CY_PSOC4_4200L) 
    /*******************************************************************************
    * Function Name: FIRE_FILTER_INPUT_SetDriveMode
    ****************************************************************************//**
    *
    * \brief Sets the drive mode for each of the Pins component's pins.
    * 
    * <b>Note</b> This affects all pins in the Pins component instance. Use the
    * Per-Pin APIs if you wish to control individual pin's drive modes.
    *
    * <b>Note</b> USBIOs have limited drive functionality. Refer to the Drive Mode
    * parameter for more information.
    *
    * \param mode
    *  Mode for the selected signals. Valid options are documented in 
    *  \ref driveMode.
    *
    * \return
    *  None
    *
    * \sideeffect
    *  If you use read-modify-write operations that are not atomic, the ISR can
    *  cause corruption of this function. An ISR that interrupts this function 
    *  and performs writes to the Pins component Drive Mode registers can cause 
    *  corrupted port data. To avoid this issue, you should either use the Per-Pin
    *  APIs (primary method) or disable interrupts around this function.
    *
    * \funcusage
    *  \snippet FIRE_FILTER_INPUT_SUT.c usage_FIRE_FILTER_INPUT_SetDriveMode
    *******************************************************************************/
    void FIRE_FILTER_INPUT_SetDriveMode(uint8 mode)
    {
		FIRE_FILTER_INPUT_SetP4PinDriveMode(FIRE_FILTER_INPUT__0__SHIFT, mode);
    }
#endif


/*******************************************************************************
* Function Name: FIRE_FILTER_INPUT_Write
****************************************************************************//**
*
* \brief Writes the value to the physical port (data output register), masking
*  and shifting the bits appropriately. 
*
* The data output register controls the signal applied to the physical pin in 
* conjunction with the drive mode parameter. This function avoids changing 
* other bits in the port by using the appropriate method (read-modify-write or
* bit banding).
*
* <b>Note</b> This function should not be used on a hardware digital output pin 
* as it is driven by the hardware signal attached to it.
*
* \param value
*  Value to write to the component instance.
*
* \return 
*  None 
*
* \sideeffect
*  If you use read-modify-write operations that are not atomic; the Interrupt 
*  Service Routines (ISR) can cause corruption of this function. An ISR that 
*  interrupts this function and performs writes to the Pins component data 
*  register can cause corrupted port data. To avoid this issue, you should 
*  either use the Per-Pin APIs (primary method) or disable interrupts around 
*  this function.
*
* \funcusage
*  \snippet FIRE_FILTER_INPUT_SUT.c usage_FIRE_FILTER_INPUT_Write
*******************************************************************************/
void FIRE_FILTER_INPUT_Write(uint8 value)
{
    uint8 drVal = (uint8)(FIRE_FILTER_INPUT_DR & (uint8)(~FIRE_FILTER_INPUT_MASK));
    drVal = (drVal | ((uint8)(value << FIRE_FILTER_INPUT_SHIFT) & FIRE_FILTER_INPUT_MASK));
    FIRE_FILTER_INPUT_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: FIRE_FILTER_INPUT_Read
****************************************************************************//**
*
* \brief Reads the associated physical port (pin status register) and masks 
*  the required bits according to the width and bit position of the component
*  instance. 
*
* The pin's status register returns the current logic level present on the 
* physical pin.
*
* \return 
*  The current value for the pins in the component as a right justified number.
*
* \funcusage
*  \snippet FIRE_FILTER_INPUT_SUT.c usage_FIRE_FILTER_INPUT_Read  
*******************************************************************************/
uint8 FIRE_FILTER_INPUT_Read(void)
{
    return (uint8)((FIRE_FILTER_INPUT_PS & FIRE_FILTER_INPUT_MASK) >> FIRE_FILTER_INPUT_SHIFT);
}


/*******************************************************************************
* Function Name: FIRE_FILTER_INPUT_ReadDataReg
****************************************************************************//**
*
* \brief Reads the associated physical port's data output register and masks 
*  the correct bits according to the width and bit position of the component 
*  instance. 
*
* The data output register controls the signal applied to the physical pin in 
* conjunction with the drive mode parameter. This is not the same as the 
* preferred FIRE_FILTER_INPUT_Read() API because the 
* FIRE_FILTER_INPUT_ReadDataReg() reads the data register instead of the status 
* register. For output pins this is a useful function to determine the value 
* just written to the pin.
*
* \return 
*  The current value of the data register masked and shifted into a right 
*  justified number for the component instance.
*
* \funcusage
*  \snippet FIRE_FILTER_INPUT_SUT.c usage_FIRE_FILTER_INPUT_ReadDataReg 
*******************************************************************************/
uint8 FIRE_FILTER_INPUT_ReadDataReg(void)
{
    return (uint8)((FIRE_FILTER_INPUT_DR & FIRE_FILTER_INPUT_MASK) >> FIRE_FILTER_INPUT_SHIFT);
}


/*******************************************************************************
* Function Name: FIRE_FILTER_INPUT_SetInterruptMode
****************************************************************************//**
*
* \brief Configures the interrupt mode for each of the Pins component's
*  pins. Alternatively you may set the interrupt mode for all the pins
*  specified in the Pins component.
*
*  <b>Note</b> The interrupt is port-wide and therefore any enabled pin
*  interrupt may trigger it.
*
* \param position
*  The pin position as listed in the Pins component. You may OR these to be 
*  able to configure the interrupt mode of multiple pins within a Pins 
*  component. Or you may use FIRE_FILTER_INPUT_INTR_ALL to configure the
*  interrupt mode of all the pins in the Pins component.       
*  - FIRE_FILTER_INPUT_0_INTR       (First pin in the list)
*  - FIRE_FILTER_INPUT_1_INTR       (Second pin in the list)
*  - ...
*  - FIRE_FILTER_INPUT_INTR_ALL     (All pins in Pins component)
*
* \param mode
*  Interrupt mode for the selected pins. Valid options are documented in
*  \ref intrMode.
*
* \return 
*  None
*  
* \sideeffect
*  It is recommended that the interrupt be disabled before calling this 
*  function to avoid unintended interrupt requests. Note that the interrupt
*  type is port wide, and therefore will trigger for any enabled pin on the 
*  port.
*
* \funcusage
*  \snippet FIRE_FILTER_INPUT_SUT.c usage_FIRE_FILTER_INPUT_SetInterruptMode
*******************************************************************************/
void FIRE_FILTER_INPUT_SetInterruptMode(uint16 position, uint16 mode)
{
    uint32 intrCfg;
    
    intrCfg =  FIRE_FILTER_INPUT_INTCFG & (uint32)(~(uint32)position);
    FIRE_FILTER_INPUT_INTCFG = intrCfg | ((uint32)position & (uint32)mode);
}


/*******************************************************************************
* Function Name: FIRE_FILTER_INPUT_ClearInterrupt
****************************************************************************//**
*
* \brief Clears any active interrupts attached with the component and returns 
*  the value of the interrupt status register allowing determination of which
*  pins generated an interrupt event.
*
* \return 
*  The right-shifted current value of the interrupt status register. Each pin 
*  has one bit set if it generated an interrupt event. For example, bit 0 is 
*  for pin 0 and bit 1 is for pin 1 of the Pins component.
*  
* \sideeffect
*  Clears all bits of the physical port's interrupt status register, not just
*  those associated with the Pins component.
*
* \funcusage
*  \snippet FIRE_FILTER_INPUT_SUT.c usage_FIRE_FILTER_INPUT_ClearInterrupt
*******************************************************************************/
uint8 FIRE_FILTER_INPUT_ClearInterrupt(void)
{
	uint8 maskedStatus = (uint8)(FIRE_FILTER_INPUT_INTSTAT & FIRE_FILTER_INPUT_MASK);
	FIRE_FILTER_INPUT_INTSTAT = maskedStatus;
    return maskedStatus >> FIRE_FILTER_INPUT_SHIFT;
}


/* [] END OF FILE */
