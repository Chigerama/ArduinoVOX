# ArduinoVOX Created 19/12/2022 by Chigerama.

## Second Alpha.

Zero warranty provided.

Credit to [Wowki](https://wokwi.com) for use of their Arduino simulator, while waiting for the real hardware to get shipped to me.
Also thanks go to [Core Electronics](https://core-electronics.com.au) for supply of the actual hardware, and quick shipping right before Christmas!

A simulation of this project is [available here](https://wokwi.com/projects/351784284891120213) - it uses the "HIGH = Active" version of the sketch.

## The full parts list is as below (Part numbers from Core Electronics):
* CE05261 (x4) - General Purpose Diode 1N4007 --- In case i decide to use the diodes to drop the voltage input going into the DC barrel connector of the Arduino.
* PRT-14492 (x1) - Resistor 1K Ohm 1/4 Watt PTH - 20 pack (Thick Leads) --- LED Current limiting resistors
* COM-11840 (x1) - LED Holder - 5mm --- To mount the 5mm RGB LED into a case.
* COM-11705 (x1) - Barrel Jack Power Switch - M-F (3") --- To easily power on/off the Arduino. Plugs into the Arduino DC Barrel connector.
* CE05629 (x1) - Uno R3 --- The arduino itself - this could likely be any UNO type off-brand unit.
* CE05184 (x1) - Sound detection Sensor Module --- Used as the Vox trigger
* CE05137 (x1) - 5V Single Channel Relay Module 10A --- This is what is used as a dry-contact to short the PTT connection on the back of the radio.
* ADA1953 (x1) - Premium Female/Male Extension Jumper Wires - 20 x 3 --- Temporary cabling for circuits
* COM-10821 (x1) - LED - RGB Diffused Common Anode --- The indicator LED. Common Anode. Any type would work.
* CE05634 (x1) - Slim Case for Arduino Uno --- Just to protect against short circuits.
* CE08794 (x1) - Male DC Barrel Jack Adapter (2.1mm) --- To feed the 13.8v from the radio power supply into the DC Barrel jack power switch above.
* Also required: Two momentary button switches, enclosure.

## To Do list:
- [ ] Need to debounce Mode button, PTT Test Button. Shouldn't need to worry about AudioSense input.
- [x] Test alpha version on real hardware - PTT and Vox on standby, PTT and Vox on Active mode.
* Good!
- [x] Test PTT functionality with FT-847
* Good!
- [x] Test VOX functionality with FT-847
* Good!
- [x] Check with RF transmission - any need to consider opto-isolated inputs?
* Initial testing seems okay. Boxed in plastic enclosure, sitting on top of FT-847. 
- [x] Check delays/actual functionality is fit for purpose. Need any tweaks?
* So far so good. Final tests to be conducted in the coming days. (Xmas 2022)
- [x] Set final Vox Sensitivty once in enclosure.
* Seems okay so far, may need tweaks in the coming days.


## License:
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
