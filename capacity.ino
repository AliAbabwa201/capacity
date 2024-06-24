// our pin that supports PWM
int inputPin = 10;

// our packet, where we will store our 16bits information about sensor.
uint_fast32_t packet = 0;

// our bit duration, for short = 80nS, long = 220nS and start bit = 1.02mS
unsigned long pulseDuration = 0;

void setup() {
  pinMode(inputPin, INPUT);
  Serial.begin(2000000);
}

void loop() {

  // pulseIn is a build-in function, that waits for HIGH signal. 
  // We have defined that our logic is PWM-HIGH, that's why we are using HIGH. 
  // 20.000 is a timeout of waiting for signal.
   packet = 0;
  pulseDuration = pulseIn(inputPin, LOW, 20000);

  // We detect the start packet pulse. In our case the start bit is 1.02mS,
  // so it is between these values:
  if (pulseDuration > 900 && pulseDuration < 1040) {
    // We have successfully detected start bit, now we need to read the body of the packet.
    //pulseDuration = pulseIn(inputPin, HIGH, 3000);
    // Only read 16 bits of data.
    for (int i = 31; i >= 0; i--) {
      // Read packet (only HIGH bits, zeros are ignored, because we already have it)
      pulseDuration = pulseIn(inputPin, HIGH, 3000);

      // we detect only LONG bits with 220nS duration (logical 1);
      if (pulseDuration > 180 && pulseDuration < 220) {
        bitSet(packet, i);
      }
    }
    // Print the packet;
    Serial.println(packet,BIN);
  }  
}
