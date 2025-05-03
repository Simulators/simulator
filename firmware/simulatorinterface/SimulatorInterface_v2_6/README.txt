
*********************************************************************************************
*                 HOW TO USE OPTION X - TURNING OFF DELAYS IN THE INTERFACE                 *
*********************************************************************************************

Type 1 Simulator Interface firmware v2.6 implements a feature to turn off the application of
strike delays in the Simulator Interface, i.e. to use the Type 2 behaviour where delays are
managed within the Simulator Software itself (e.g. Abel).

This feasture has been developed for one particular use case. For most Type 1 users, firmware
v2.5 is still the latest recommended version.

           *** THIS FEATURE DOES NOT APPEAR IN THE TYPE 1 SIMULATOR DOCUMENTATION ***

By default, a Type 1 interface stores and applies the strike delay (from BDC to strike point)
in the interface, receiving the delays from Abel at startup and saving them to EEPROM. CLI
option X turns this off, so that signals are sent to the PC at BDC, not at the strike point,
which is the Type 2 behaviour. To support this, the WAIT_TO_SEND state does double duty
as the post-signal guard timer. 

When application of delays in the interface is turned off, the option to set default timers
(Option Z in Debug Mode) is changed to set to 100ms, the default Type 2 Guard Timer, instead
of 500ms, and saving to EEPROM (Option S) is changed to save the delay timers to EEPROM along
with the other settings. The serial receiver code is also changed to not overwrite the timers
when application of delays is turned off.

To disable application of delay timers in the interface, do the following:
 * Select CLI Option X to toggle the applyDelayTimers flag to FALSE.
 * Select CLI Option D to enable debugging.
 * Select CLI Option Z to set 100ms (10cs) timers.
 * Select CLI Option S to save all this to EEPROM.
 * Reboot the interface with the reset button.
 * Change the Abel configuration to check the box "Abel applies delays (No MBI)".
 
Strike delays will now be applied by Abel, and any delay values sent to the interface will be ignored.

To re-enable application of delay timers in the interface, do the following:
 * Select CLI Option X to toggle the applyDelayTimers flag to TRUE.
 * Select CLI Option S to save this change to EEPROM.
 * Reboot the interface with the reset button.
 * Change the Abel configuration to uncheck the "Abel applies delays (No MBI)" box, and restart Abel.

Abel will now send delay values to the interface, which will store and apply them.
