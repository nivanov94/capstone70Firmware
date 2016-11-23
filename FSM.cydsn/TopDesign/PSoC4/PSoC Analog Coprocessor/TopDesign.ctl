-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-048 kit.
-- =============================================================================

-- === RGB LED ===
attribute port_location of LED_GREEN(0) : label is "PORT(2,6)"; -- GREEN LED
attribute port_location of LED_BLUE(0) : label is "PORT(1,6)"; -- BLUE LED

attribute port_location of CaptureInput(0) : label is "PORT(4,0)";
attribute port_location of CaptureSource(0) : label is "PORT(2,0)";