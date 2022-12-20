// #include <DebounceInput.h> // No point reinventing the wheel. Source: https://github.com/PaulMurrayCbr/DebounceInput
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

// Setting pin numbers
const int AudioSense = 2;   // Audio Sensor on pin 2
const int PTTRelay = 4;     // PTT Relay Output on pin 4
const int RedLED = 8;       // Red pin on RGB LED
const int GreenLED = 9;     // Green pin on RGB LED
const int BlueLED = 10;     // Blue pin on RGB LED
const int ModeSwitch = 11;  // Mode control switch
const int TestPTT = 12;     // PTT Test button

// Setting initial variables
int FirstBoot = 1;                 // Just to add some flavour to first boot. Absolutely not needed. Set to 0 to bypass.
int ModeSwitchState = 0;           // Stores the current state of the mode switch - used for switching modes.
int CurrentMode = 0;               // Used to store current operating mode - Standby/Active.
unsigned long AudioSenseTime = 0;  // This value is used to store the time at which the vox was last triggered.

// RGB_LED Control function, uses digital pin outputs rather than PWM (But would be easy to convert if someone wanted to use PWM instead for better colour control. Not really important.).
// RGB LED to be connected with serial resistor on each cathode.
void RGB_LED(int red, int green, int blue) {
  digitalWrite(RedLED, red);
  digitalWrite(GreenLED, green);
  digitalWrite(BlueLED, blue);
}

void setup() {
  // Setting pin modes
  pinMode(AudioSense, INPUT_PULLUP);
  pinMode(PTTRelay, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(ModeSwitch, INPUT_PULLUP);
  pinMode(TestPTT, INPUT_PULLUP);
  digitalWrite(PTTRelay, LOW);  // Set initial PTTRelay state.
  RGB_LED(1, 1, 1);             // Set initial LED state.
  delay(2000);
}

void loop() {
  // Modes:
  // 0) Startup. Initital boot, rainbow LED cycle before activation of Normal mode. Stand-by mode is selected only after first boot. No other actions are possible/enabled.
  // 1) Stand-by. Blue LED shown. Ignores inputs from Audio Sense Pin, PTT Relay is not activated except when the "Test PTT" button is pressed.
  // 2) Normal. Green LED shown. Activates the PTT Relay when vox is activated. Test PTT button is also active.
  // 3) Activated. Red LED shown. PTT is active - either through vox activation or via Test PTT Button.
  // Unsure if #3 is required, or if it can just be a momentary state, rather than an operating state.

  int TestPTTState = HIGH;  // Set TestPTT State if button is pressed.
  int ModeSwitchState = HIGH;
  int AudioSenseState = HIGH;

  // Read Switch States -- uncomment the lines below to create a loop for testing buttons.
  // modetest:
  TestPTTState = digitalRead(TestPTT);
  ModeSwitchState = digitalRead(ModeSwitch);
  AudioSenseState = digitalRead(AudioSense);
  // if (TestPTTState == LOW) { RGB_LED(1,0,0);}
  // if (ModeSwitchState == LOW) { RGB_LED(0,1,0);}
  // if (AudioSenseState == LOW) { RGB_LED(0,0,1);}
  // goto modetest;

  if (FirstBoot == 1) {  // Default startup state, rainbow led cycle, then move to state 1
    RGB_LED(0, 0, 0);  // Red
    delay(125);
    RGB_LED(1, 0, 1);  // Pink
    delay(125);
    RGB_LED(1, 1, 0);  // Yellow
    delay(125);
    RGB_LED(0, 1, 0);  // Green
    delay(125);
    RGB_LED(0, 1, 1);  // Teal
    delay(125);
    RGB_LED(0, 0, 1);  // Blue
    delay(125);
    RGB_LED(1, 1, 1);  // White
    delay(125);
    RGB_LED(0, 0, 0);  // Off
    delay(500);
    FirstBoot = 0;
    CurrentMode = 1;
  }
  //else if (FirstBoot == 0) { // Used when "FirstBoot" is set to 0 to bypass startup rainbow.
  //    CurrentMode = 1;
  //    RGB_LED(0,0,0);
  //    return;
  //}
  else if (CurrentMode == 1) {  // Standby mode - only TestPTT activates output
    if (ModeSwitchState == LOW) {
      CurrentMode = 2;
      RGB_LED(0, 0, 0);
      delay(250);
      return;
    } else if (TestPTTState == LOW) {  // PTT Test Button Pressed, closes relay to enable PTT while momementary button is pressed.
      RGB_LED(1, 0, 0);
      digitalWrite(PTTRelay, HIGH);
      delay(250);
      return;
    } else if (AudioSenseState == LOW) {  // This is used to test audio vox levels while in standby mode.
      RGB_LED(1, 0, 1);
      AudioSenseTime = (millis() + 500);
      return;
    } else if (AudioSenseState == HIGH) {
      if (AudioSenseTime < millis()) {
        digitalWrite(PTTRelay, LOW);
        RGB_LED(0, 0, 1);
        return;
      } else {
        return;
      }
    } else if (TestPTTState == HIGH) {  // Normal Operation in this mode - standby.
      if (AudioSenseTime < millis()) {
        digitalWrite(PTTRelay, LOW);
        RGB_LED(0, 0, 1);  // Set LED Blue
        return;
      }
    } else {
      return;
    }
  } else if (CurrentMode == 2) {
    if (ModeSwitchState == LOW) {
      CurrentMode = 1;
      RGB_LED(0, 0, 0);
      delay(250);
      return;
    } else if (TestPTTState == LOW) {  // PTT Test Button Pressed, closes relay to enable PTT while momementary button is pressed.
      RGB_LED(1, 0, 0);
      digitalWrite(PTTRelay, HIGH);
      delay(250);
      return;
    } else if (AudioSenseState == LOW) {  // This is used to test audio vox levels while in standby mode.
      RGB_LED(1, 0, 0);
      digitalWrite(PTTRelay, HIGH);
      AudioSenseTime = (millis() + 2000);
      return;
    } else if (AudioSenseState == HIGH) {
      if (AudioSenseTime < millis()) {
        digitalWrite(PTTRelay, LOW);
        RGB_LED(0, 1, 0);
        return;
      } else {
        return;
      }
    } else if (TestPTTState == HIGH) {  // Normal Operation in this mode - standby.
      if (AudioSenseTime < millis()) {
        digitalWrite(PTTRelay, LOW);
        RGB_LED(0, 1, 0);  // Set LED Blue
        return;
      }
    } else {
      return;
    }
  }
}