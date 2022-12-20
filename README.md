# ArduinoVOX Created 19/12/2022 by Chigerama.

// Second Alpha.
//
// Zero warranty provided. The software below is free and unencumbered software released into the public domain.
// Unlicense: https://unlicense.org/
//
// Credit to https://wokwi.com for use of their Arduino simulator, while waiting for the real hardware to get shipped to me.
// Also thanks go to https://core-electronics.com.au for supply of the actual hardware, and quick shipping right before Christmas!
//
// A full description of the build shall be available online here: http://mywebsite.here.maybe?

// The full parts list is as below (Part numbers from Core Electronics):
// •	CE05261 (x4) - General Purpose Diode 1N4007 --- In case i decide to use the diodes to drop the voltage input going into the DC barrel connector of the Arduino.
// •	PRT-14492 (x1) - Resistor 1K Ohm 1/4 Watt PTH - 20 pack (Thick Leads) --- LED Current limiting resistors
// •	COM-11840 (x1) - LED Holder - 5mm --- To mount the 5mm RGB LED into a case.
// •	COM-11705 (x1) - Barrel Jack Power Switch - M-F (3") --- To easily power on/off the Arduino. Plugs into the Arduino DC Barrel connector.
// •	CE05629 (x1) - Uno R3 --- The arduino itself - this could likely be any UNO type off-brand unit.
// •	CE05184 (x1) - Sound detection Sensor Module --- Used as the Vox trigger
// •	CE05137 (x1) - 5V Single Channel Relay Module 10A --- This is what is used as a dry-contact to short the PTT connection on the back of the radio.
// •	ADA1953 (x1) - Premium Female/Male Extension Jumper Wires - 20 x 3 --- Temporary cabling for circuits
// •	COM-10821 (x1) - LED - RGB Diffused Common Anode --- The indicator LED. Common Anode. Any type would work.
// •	CE05634 (x1) - Slim Case for Arduino Uno --- Just to protect against short circuits.
// •	CE08794 (x1) - Male DC Barrel Jack Adapter (2.1mm) --- To feed the 13.8v from the radio power supply into the DC Barrel jack power switch above.

//
// To Do list:
//  Need to debounce Mode button, PTT Test Button. Shouldn't need to worry about AudioSense input.
//  Test alpha version on real hardware - PTT and Vox on standby, PTT and Vox on Active mode.
//  Test PTT functionality with FT-847
//  Test VOX functionality with FT-847
//  Check with RF transmission - any need to consider opto-isolated inputs?
//  Check delays/actual functionality is fit for purpose. Need any tweaks?






This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>