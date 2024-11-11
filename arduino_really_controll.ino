#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX, TX for HC-05

const int relayPins[] = {2, 3, 4, 5}; // Relay control pins
const int switchPins[] = {6, 7, 8, 9}; // Switch input pins

void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
  
  // Initialize relay pins as OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Ensure relays are OFF initially
    pinMode(switchPins[i], INPUT_PULLUP); // Use internal pull-up resistors
  }
}

void loop() {
  // Check for Bluetooth commands
  if (BTSerial.available()) {
    char command = BTSerial.read();
    handleCommand(command);
  }
  
  // Check the state of switches
  for (int i = 0; i < 4; i++) {
    if (digitalRead(switchPins[i]) == LOW) { // Button pressed
      toggleRelay(i);
      delay(200); // Debounce delay
    }
  }
}

void handleCommand(char command) {
  switch (command) {
    case '1':
      toggleRelay(0);
      break;
    case '2':
      toggleRelay(1);
      break;
    case '3':
      toggleRelay(2);
      break;
    case '4':
      toggleRelay(3);
      break;
    default:
      break;
  }
}

void toggleRelay(int index) {
  int state = digitalRead(relayPins[index]);
  digitalWrite(relayPins[index], !state); // Toggle relay state
}
