-- ======================================================================
-- FSM.ctl generated from FSM
-- 11/22/2016 at 17:55
-- This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
-- ======================================================================

-- TopDesign
-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-042-BLE kit.
-- =============================================================================

-- === UART ===
attribute port_location of \UART:rx(0)\ : label is "PORT(1,4)";
attribute port_location of \UART:tx(0)\ : label is "PORT(1,5)";

-- === I2C ===
attribute port_location of \I2C:scl(0)\ : label is "PORT(3,5)";
attribute port_location of \I2C:sda(0)\ : label is "PORT(3,4)";

-- === RGB LED ===
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(2,6)"; -- RED LED
attribute port_location of LED_GREEN(0) : label is "PORT(3,6)"; -- GREEN LED
attribute port_location of LED_BLUE(0) : label is "PORT(3,7)"; -- BLUE LED

-- === USER SWITCH ===
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(2,7)";

attribute port_location of CaptureInput(0) : label is "PORT(0,1)";
attribute port_location of CaptureSource(0) : label is "PORT(2,0)";

-- PSoC Clock Editor
-- Directives Editor
-- Analog Device Editor
