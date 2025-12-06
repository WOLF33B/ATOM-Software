/*
  ATOM - Arduino Nano Complete Example
  Firmware Version: 1.0.0P (Public Example)
  This sketch is a simplified example for the ATOM API.
  It is intended to demonstrate the basic pairing (handshake)
  protocol and how to send analog slider data.
  this example are based from RMA300

  --- WHAT THIS EXAMPLE DOES ---
  1. Listens connect to Atom software
  2. Continuously reads 5 analog inputs (A0-A4) and stream to the computer

  --- WHAT THIS EXAMPLE *DOES NOT* DO ---
  - NO Noise Reduction (NR)
  - NO Advanced Filters
  - NO Health Check functions
  - NO Optimized and Save functions
  - NO Multi-profile support
  - NO Slider Invert or Disable features
*/



// Define the firmware version to be reported
const byte FW_VER_MAJOR = 1;
const byte FW_VER_MINOR = 0;
const byte FW_VER_PATCH = 0;
const byte FW_VER_SUFFIX = 'P'; // 'P' for Public/Example

// Define the hardware configuration to be reported
const byte SLIDER_COUNT = 5;  // This example uses five sliders on A0-A4
const byte PROFILE_COUNT = 1; // Report 1 profile, 
const byte ACTIVE_PROFILE = 0;  // Report profile 1 (index 0) is active

// Define the feature flags (all disabled)
const byte FEATURE_FLAGS = 0b00000000; // All features disabled

// Define supported options
// 'OFF' must be report. to increase compatiblity each software version
const byte NR_LEVELS_MASK = 0b00000001;    
const byte FILTER_TYPES_MASK = 0b00000001;  

// Define packet headers for handshake
const byte PACKET_START = 0xA5; //start byte
const byte PACKET_END = 0x5A;   //end byte
const byte SLIDER_UPDATE_HEADER = 0xB1; // Header for sending a slider value

// Define the analog pins for our sliders
const int SLIDER_PINS[SLIDER_COUNT] = {A0, A1, A2, A3, A4};

// Define the LED pin(optional)
const byte LED_PIN = LED_BUILTIN;

// Buffer for reading serial commands(optional)
char serialBuffer[32];
byte bufferIndex = 0;

// Store the last sent slider values to avoid flooding the serial port
int lastSliderValues[SLIDER_COUNT];
// A small deadzone to account for analog jitter
const int SLIDER_THRESHOLD = 2;

// Rate limiting for handshake(optional)
unsigned long lastHandshakeTime = 0;
const unsigned long HANDSHAKE_COOLDOWN = 1000; // 1 second

// State management(optional)
bool isPaired = false; // Tracks handhskae status

//LED blink timer(optional)
unsigned long lastLedToggleTime = 0;
bool ledState = false;
const int LED_BLINK_INTERVAL = 250; // Blink interval in ms

// --- Arduino Setup ---

void setup() {
  //Serial must communicated at 250000 baud
  Serial.begin(250000);
  
  // Set up the LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Clear junk in the buffer at start(optional)
  while (Serial.available() > 0) {
    Serial.read();
  }

  //setup slider pin
  for (int i = 0; i < SLIDER_COUNT; i++) {
    pinMode(SLIDER_PINS[i], INPUT);
    lastSliderValues[i] = -1; // Initialize last values
  }
}
void loop() {
  // Update the pairing status LED
  updatePairingLED();
  // Check for incoming commands
  checkSerialCommands();
  // Read sliders and send updates
  readAndSendAllSliders();
}
void updatePairingLED() {
  if (isPaired) {
    // Pairing is complete, set LED to ON
    digitalWrite(LED_PIN, HIGH);
  } else {
    //blink the LED
    unsigned long currentTime = millis();
    if (currentTime - lastLedToggleTime > LED_BLINK_INTERVAL) {
      lastLedToggleTime = currentTime;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  }
}

/**
   @brief Checks for incoming serial data.
   Reads bytes until a newline '\n' is found, then processes the command.
*/
void checkSerialCommands() {
  while (Serial.available() > 0) {
    char incomingByte = Serial.read();

    if (incomingByte == '\n') {
      serialBuffer[bufferIndex] = '\0'; // Null-terminate the string

      // Process the command
      if (strcmp(serialBuffer, "PAIR_REQ") == 0) {
        unsigned long currentTime = millis();
        // Only allow handshake if we aren't already paired OR
        // if it's been a while (in case of re-pair request)
        if (!isPaired || (currentTime - lastHandshakeTime > HANDSHAKE_COOLDOWN)) {
          lastHandshakeTime = currentTime;
          sendHandshake();
        }
      }
      // Other commands like "GET_SETTINGS" could be handled here
      // but are ignored in this simple example.
      // Reset the buffer
      bufferIndex = 0;

    } else if (bufferIndex < (sizeof(serialBuffer) - 1)) {
      // Add byte to the buffer
      serialBuffer[bufferIndex] = incomingByte;
      bufferIndex++;
    }
  }
}

/**
   @brief Sends the 14-byte handshake packet to the computer.
   This packet tells the ATOM software what features this device has.
*/
void sendHandshake() {
  byte packet[14];

  // [0] Start Byte
  packet[0] = PACKET_START;

  // [1] This byte is skipped in checksum calculation.
  packet[1] = 0x00;

  // [2-5] Firmware Version
  packet[2] = FW_VER_MAJOR;
  packet[3] = FW_VER_MINOR;
  packet[4] = FW_VER_PATCH;
  packet[5] = FW_VER_SUFFIX;

  // [6-8] Device Configuration
  packet[6] = SLIDER_COUNT;
  packet[7] = PROFILE_COUNT;
  packet[8] = ACTIVE_PROFILE;

  // [9-11] Feature Support (All minimal)
  packet[9] = FEATURE_FLAGS;
  packet[10] = NR_LEVELS_MASK;
  packet[11] = FILTER_TYPES_MASK;

  // [12] Checksum
  // The checksum is an XOR of bytes 2 through 11.
  byte checksum = 0;
  for (int i = 2; i <= 11; i++) {
    checksum ^= packet[i];
  }
  packet[12] = checksum;

  // [13] End Byte
  packet[13] = PACKET_END;

  // Send the full 14-byte packet all at once.
  Serial.write(packet, 14);

  // Wait for the transmission to complete before continuing.
  Serial.flush();
  
  // changed the state to True. for swithc from pairing to streaming
  isPaired = true;
}

//Reads all analog sliders and sends an update if any have changed.
void readAndSendAllSliders() {
  if (!isPaired) {
    return;
  }
  
  for (int i = 0; i < SLIDER_COUNT; i++) {
    // Read the 10-bit analog value (0-1023)
    int currentSliderValue = analogRead(SLIDER_PINS[i]);

    // Check if the value has changed by more than our threshold
    if (abs(currentSliderValue - lastSliderValues[i]) > SLIDER_THRESHOLD) {
      // Value has changed, send an update
      sendSliderUpdate(i, currentSliderValue); // Send on index i

      // Store the new value
      lastSliderValues[i] = currentSliderValue;
    }
  }
}

/**
   @brief Sends a slider value update packet (0xB1).
   Format: [Header] [Index] [Value High Byte] [Value Low Byte]
   @param index The slider index (0 for this example).
   @param value The 10-bit value (0-1023) to send.
*/
void sendSliderUpdate(byte index, unsigned int value) {
  // [0] Header
  Serial.write(SLIDER_UPDATE_HEADER);

  // [1] Slider Index
  Serial.write(index);

  // [2] Value High Byte (Big-Endian)
  Serial.write((value >> 8) & 0xFF);

  // [3] Value Low Byte (Big-Endian)
  Serial.write(value & 0xFF);
}

