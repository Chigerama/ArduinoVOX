// #include <DebounceInput.h> // No point reinventing the wheel. Source: https://github.com/PaulMurrayCbr/DebounceInput
// First Alpha? 
//
// To Do list:
//  Need to debounce Mode button, PTT Test Button. Shouldn't need to worry about AudioSense input.
//  May need a reset timer on the AudioSense, similar to debounce, but to delay the closure of the PTT without delaying sensing of audio input.
//  Test alpha version on real hardware - PTT and Vox on standby, PTT and Vox on Active mode.
//  Test PTT functionality with FT-847
//  Test VOX functionality with FT-847
//  Check with RF transmission - any need to consider opto-isolated inputs?
//  Check delays/actual functionality is fit for purpose. Need any tweaks?

// Setting pin numbers
const int AudioSense = 2; // Audio Sensor on pin 2
const int PTTRelay = 4; // PTT Relay Output on pin 4
const int RedLED = 8; // Red pin on RGB LED
const int GreenLED = 9; // Green pin on RGB LED
const int BlueLED = 10;// Blue pin on RGB LED
const int ModeSwitch = 11; // Mode control switch
const int TestPTT = 12; // PTT Test button

// Setting initial variables
int FirstBoot = 1;
int ModeSwitchState = 0;
int CurrentMode = 0;
unsigned long AudioSenseTime = 0;

// RGB_LED Control function, uses digital pin outputs rather than PWM (But would be easy to convert if someone wanted to use PWM instead for better colour control. Not really important.). 
// RGB LED to be connected with serial resistor on each cathode. 
void RGB_LED(int red, int green, int blue) {
  digitalWrite(RedLED,red);
  digitalWrite(GreenLED,green);
  digitalWrite(BlueLED,blue);
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
  digitalWrite(PTTRelay,LOW); // Set initial PTTRelay state.
  RGB_LED(1,1,1); // Set initial LED state.
  delay(2000);
}

void loop() {
  // Modes:
  // 0) Startup. Initital boot, rainbow LED cycle before activation of Normal mode. Stand-by mode is selected only after first boot. No other actions are possible/enabled.
  // 1) Stand-by. Blue LED shown. Ignores inputs from Audio Sense Pin, PTT Relay is not activated except when the "Test PTT" button is pressed.
  // 2) Normal. Green LED shown. Activates the PTT Relay when vox is activated. Test PTT button is also active. 
  // 3) Activated. Red LED shown. PTT is active - either through vox activation or via Test PTT Button. 
  // Unsure if #3 is required, or if it can just be a momentary state, rather than an operating state.

// Check ModeSwitch Status

// Check PTT Status


// Set RGB LED State -- Depricated. Any need for this if using void setup?
//  if (FirstBoot == 1) {
//    int FirstBoot = 0;
//  }

// Set ModeSwitchState if button is pressed.
// if (digitalRead(ModeSwitch) == HIGH) {
//   break;
// }

// Set TestPTT State if button is pressed.
int TestPTTState = HIGH;
int ModeSwitchState = HIGH;
int AudioSenseState = HIGH;

// Read Switch States
// modetest:
TestPTTState = digitalRead(TestPTT);
ModeSwitchState = digitalRead(ModeSwitch);
AudioSenseState = digitalRead(AudioSense);
// if (TestPTTState == LOW) { RGB_LED(1,0,0);}
// if (ModeSwitchState == LOW) { RGB_LED(0,1,0);}
// if (AudioSenseState == LOW) { RGB_LED(0,0,1);}
// goto modetest;

if (FirstBoot == 1) {  // Default startup state, rainbow led cycle, then move to state 1
    RGB_LED(0, 0, 0); // Red
    delay(125);
    RGB_LED(1, 0, 1); // Pink
    delay(125);
    RGB_LED(1, 1, 0); // Yellow
    delay(125);
    RGB_LED(0, 1, 0); // Green
    delay(125);
    RGB_LED(0, 1, 1); // Teal
    delay(125);
    RGB_LED(0, 0, 1); // Blue
    delay(125);
    RGB_LED(1, 1, 1); // White
    delay(125);
    RGB_LED(0,0,0); // Off
    delay(500);
    FirstBoot = 0;
    CurrentMode = 1;
}
else if (CurrentMode == 1) { // Standby mode - only TestPTT activates output
    if (ModeSwitchState == LOW) {
      CurrentMode = 2;
      RGB_LED(0,0,0);
      delay(250);
      return;
      }
    else if (TestPTTState == LOW) { // PTT Test Button Pressed, closes relay to enable PTT while momementary button is pressed.
      RGB_LED(1,0,0);
      digitalWrite(PTTRelay, HIGH);
      delay(250);
      return;
    }
    else if (AudioSenseState == LOW) { // This is used to test audio vox levels while in standby mode.
      RGB_LED(1,0,1);
      digitalWrite(PTTRelay, HIGH);
      AudioSenseTime = (millis()+2000);
      return;
    }
    else if (AudioSenseState == HIGH) {
      if (AudioSenseTime < millis()) {
        digitalWrite(PTTRelay, LOW);
        RGB_LED(0,0,1);
        return;
      }
      else {
        return;
      }
    }
    else if (TestPTTState == HIGH) { // Normal Operation in this mode - standby.
    if (AudioSenseTime < millis()) {
          digitalWrite(PTTRelay, LOW);
      RGB_LED(0,0,1); // Set LED Blue
      return;
      }
    }
    else {
      return;
    }
}
  else if (CurrentMode == 2) {
    if (ModeSwitchState == LOW) {
      CurrentMode = 1;
      RGB_LED(0,0,0);
      delay(250);
      return;
      }
    else if (AudioSenseState == LOW) {
      digitalWrite(PTTRelay, HIGH);
      RGB_LED(1,0,0);
      AudioSenseTime = millis();
      return;
    }
    else if (TestPTTState == LOW) { // PTT Test Button Pressed, closes relay to enable PTT while momementary button is pressed.
      digitalWrite(PTTRelay, HIGH);
      RGB_LED(1,0,0);
      delay(250);
      return;
    }
    else if (TestPTTState == HIGH) { // Normal Operation in this mode.
      digitalWrite(PTTRelay, LOW);
      RGB_LED(0,1,0); // Set LED Green
      return;
    }
    else if (AudioSenseState == HIGH) {
    if ((AudioSenseTime + 2000) < millis()) {
      digitalWrite(PTTRelay, LOW);
      return;
    }
    else {
      return;
    }
  }
 }
 }