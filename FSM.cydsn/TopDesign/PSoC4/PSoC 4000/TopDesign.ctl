-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-040 kit.
-- =============================================================================

-- === UART ===
attribute port_location of \UART:tx(0)\ : label is "PORT(0,5)";

-- === I2C ===
attribute port_location of \I2C:scl(0)\ : label is "PORT(1,2)";
attribute port_location of \I2C:sda(0)\ : label is "PORT(1,3)";

-- === RGB LED ===
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(3,2)"; -- RED LED
attribute port_location of LED_GREEN(0) : label is "PORT(1,1)"; -- GREEN LED
attribute port_location of LED_BLUE(0) : label is "PORT(0,2)"; -- BLUE LED

attribute port_location of CaptureInput(0) : label is "PORT(0,1)";
attribute port_location of CaptureSource(0) : label is "PORT(2,0)";
