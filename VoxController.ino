// #include <DebounceInput.h> // No point reinventing the wheel. Source: https://github.com/PaulMurrayCbr/DebounceInput
// First Beta.
//
// Relay Logic = Relay active = HIGH
// LED logic = common anode, active = LOW.
//
// Zero warranty provided. The software below is free and unencumbered software released into the public domain.
// Unlicense: https://unlicense.org/
//
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
int ModeSwitchState = HIGH;           // Stores the current state of the mode switch - used for switching modes.
int CurrentMode = 0;               // Used to store current operating mode - Standby/Active.
unsigned long AudioSenseTime = 0;  // This value is used to store the time at which the vox was last triggered.
int TestPTTState = HIGH;  // Set TestPTT State if button is pressed.
// int ModeSwitchState = HIGH;
int AudioSenseState = LOW;


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
  digitalWrite(PTTRelay, HIGH);  // Set initial PTTRelay state.
  RGB_LED(1, 1, 1);             // Set initial LED state.
  delay(1000);
}

void loop() {
  // Modes:
  // 0) Startup. Initital boot, rainbow LED cycle before activation of Normal mode. Stand-by mode is selected only after first boot. No other actions are possible/enabled.
  // 1) Stand-by. Blue LED shown. Ignores inputs from Audio Sense Pin, PTT Relay is not activated except when the "Test PTT" button is pressed.
  // 2) Normal. Green LED shown. Activates the PTT Relay when vox is activated. Test PTT button is also active.
  // 3) Activated. Red LED shown. PTT is active - either through vox activation or via Test PTT Button.
  // Unsure if #3 is required, or if it can just be a momentary state, rather than an operating state.

  // Read Switch States -- uncomment the lines below to create a loop for testing buttons.
  // modetest:
  TestPTTState = digitalRead(TestPTT);
  ModeSwitchState = digitalRead(ModeSwitch);
  AudioSenseState = digitalRead(AudioSense);
  // if (TestPTTState == LOW) { RGB_LED(1,0,0);}
  // if (ModeSwitchState == LOW) { RGB_LED(0,1,0);}
  // if (AudioSenseState == LOW) { RGB_LED(0,0,1);}
  // goto modetest;
  delay(2);  // This seems to be critical to allowing the relay to de-latch... Any lower and it won't work. Higher and usability suffers.

  if (FirstBoot == 1) {  // Default startup state, rainbow led cycle, then move to state 1
    RGB_LED(0, 1, 1);  // Red
    delay(250);
    RGB_LED(0, 1, 0);  // Pink
    delay(250);
    RGB_LED(0, 0, 1);  // Yellow
    delay(250);
    RGB_LED(1, 0, 1);  // Green
    delay(250);
    RGB_LED(1, 0, 0);  // Teal
    delay(250);
    RGB_LED(1, 1, 0);  // Blue
    delay(250);
    RGB_LED(0, 0, 0);  // White
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
      RGB_LED(1, 1, 0);
      delay(250);
      return;
    } else if (TestPTTState == LOW) {  // PTT Test Button Pressed, closes relay to enable PTT while momementary button is pressed.
      RGB_LED(0, 1, 1);
      digitalWrite(PTTRelay, LOW);
      delay(250);
      return;
    } else if (AudioSenseState == LOW) {  // This is used to test audio vox levels while in standby mode. Turns LED purple.
      RGB_LED(0, 1, 0);
      AudioSenseTime = (millis() + 500);
      return;
    } else if (AudioSenseState == HIGH) { // Turns off relay after 2 seconds of non-activity
      if (AudioSenseTime < millis()) {
        digitalWrite(PTTRelay, HIGH);
        RGB_LED(1, 1, 0);
        return;
      } else {
        return;
      }
    } else if (TestPTTState == HIGH) {  // Normal Operation in this mode - standby.
      if (AudioSenseTime < millis()) {
        digitalWrite(PTTRelay, HIGH);
        RGB_LED(1, 1, 0);  // Set LED Blue
        return;
      }
    } else {
      return;
    }
  } else if (CurrentMode == 2) {  // Active mode - TestPTT and VOX activates output
    if (ModeSwitchState == LOW) {
      CurrentMode = 1;
      RGB_LED(1, 0, 1);
      delay(250);
      return;
    } else if (TestPTTState == LOW) {  // PTT Test Button Pressed, closes relay to enable PTT/testing while momementary button is pressed.
      RGB_LED(0, 1, 1);
      digitalWrite(PTTRelay, LOW);
      delay(250);
      return;
    } else if (AudioSenseState == LOW) {  // This activates the PTT trigger in 'normal' mode...
      RGB_LED(0, 1, 1);
      digitalWrite(PTTRelay, LOW);
      AudioSenseTime = (millis() + 2000);
      return;
    } else if (AudioSenseState == HIGH) { // Turns off relay after 2 seconds of non-activity.
      if (AudioSenseTime < millis()) {
        digitalWrite(PTTRelay, HIGH);
        RGB_LED(1, 0, 1);
        return;
      } else {
        return;
      }
    } else if (TestPTTState == HIGH) {  // Normal Operation in this mode - standby.
      if (AudioSenseTime < millis()) {
        digitalWrite(PTTRelay, HIGH);
        RGB_LED(1, 0, 1);  // Set LED GREEN - Normal "active" mode. 
        return;
      }
    } else {
      return;
    }
  }
}
