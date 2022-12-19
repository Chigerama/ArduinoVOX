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
int ModeSwitchState = 1;

  // Set RGB_LED Controls
void RGB_LED(int red, int green, int blue) {
  digitalWrite(RedLED,red);
  digitalWrite(GreenLED,green);
  digitalWrite(BlueLED,blue);
}

void setup() {
  // Setting pin modes
  pinMode(AudioSense, INPUT);
  pinMode(PTTRelay, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(ModeSwitch, INPUT_PULLUP);
  pinMode(TestPTT, INPUT_PULLUP);
}



void loop() {
  // Modes:
  // 0) Startup. Initital boot, rainbow LED cycle before activation of Normal mode. Stand-by mode is selected only after first boot. No other actions are possible/enabled.
  // 1) Stand-by. Blue LED shown. Ignores inputs from Audio Sense Pin, PTT Relay is not activated except when the "Test PTT" button is pressed.
  // 2) Normal. Green LED shown. Activates the PTT Relay when vox is activated. Test PTT button is also active. 
  // 3) Activated. Red LED shown. PTT is active - either through vox activation or via Test PTT Button. 
  // Unsure if #3 is required, or if it can just be a momentary state, rather than an operating state.

// Check ModeSwitch Status - add debounce

// Check PTT Status - debounce? Important? Probably not critical, but perhaps improves user experience.

// Set ModeSwitch State

// Set RGB LED State
  if (FirstBoot == 1) {
  }


if (digitalRead(ModeSwitch) == HIGH) {
  
}

// Set TestPTT State


switch (ModeSwitchState) {
  case 0: // Default startup state, rainbow led cycle, then move to state 1
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
    ModeSwitchState = 1;
    break;
  case 1:
    RGB_LED(0,0,1); //Set LED Blue
    if (digitalRead(TestPTT) == HIGH) { // Normal Operation in this mode - standby.
      break;
    }
    else if (digitalRead(TestPTT == LOW)) { // PTT Test Button Pressed, closes relay to enable PTT while momementary button is pressed.
      digitalWrite(PTTRelay, HIGH);
      RGB_LED(1,0,0);
      delay(100);
      break;
    }
  case 2:
  RGB_LED(0,1,0);
  if (digitalRead(TestPTT) == HIGH) { // Normal Operation in this mode - standby.
      break;
    }
    else if (digitalRead(TestPTT) == LOW) { // PTT Test Button Pressed, closes relay to enable PTT while momementary button is pressed.
      digitalWrite(PTTRelay, HIGH);
      RGB_LED(1,0,0);
      delay(100);
      break;
    }
    else if (digitalRead(AudioSense) == HIGH) {
      digitalWrite(PTTRelay, HIGH);
      RGB_LED(1,0,0);
      delay(500);
      break;
    }
    else {      
      break;
    }
  } 
  delay(100);
}
