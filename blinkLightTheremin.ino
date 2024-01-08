/*
  Blinking Theremin 2.0

  inspiration from light theremin in the Arduino library
  
  By L.V. Olavi Rantala  
  aka ozf1r
  Late@Linuxrauta.fi

  Read analog input to blink a led randomly
  blink faster as finger is closer to the LDR
  connected to analog input SEED
  constants MIN and MAX determine the duration of each blink

  code should be pretty clear

  I connected a simple LDR voltage divider to the analog input

  happy hacking!
  
*/

const int LED = 4;      // The LED pin
const int SEED = A0;    // analog read pin for random seed

const int MIN = 50;     // absolute minimum LED on/off  
const int MAX = 1000;    // absolute maximum LED on/off

int l = 1023;           // sensor low value from calibration
int h = 0;              // sensor high value from calibration
int p;                  // calibrated value for delay

int r;                  // random value in milliseconds
int s;                  // sensor value

// the setup function runs once when you press reset or power the board
// yes I did use Blink as a base for this, hence the silly comments
void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED, OUTPUT);
  // to make this truly random, connect analog pin zero to something random
  // like a voltage divider made with an LDR
  // but please do not use this for cryptography!
  randomSeed(analogRead(SEED));

  // turn the led on for five seconds for calibration
  digitalWrite(LED, HIGH);

  // calibrate for the first five seconds after program runs
  while (millis() < 5000) {
    // record the maximum sensor value
    s = analogRead(SEED);
    if (s > h) {
      h = s;
    }
    // record the minimum sensor value
    if (s < l) {
      l = s;
    }
  }
  // turn the LED off, signaling the end of the calibration period
  digitalWrite(LED, LOW);
}

// the loop function runs over and over again forever
void loop() {
  //read the input
  s = analogRead(SEED);

  // map the sensor value to range
  int p = map(s, l, h, MIN, MAX);

  r = random(MIN,p);       // get a random value r
  digitalWrite(LED, HIGH);   // turn the LED on
  delay(r);                  // wait for r milliseconds
  r = random(MIN,p);       // get a random value r
  digitalWrite(LED, LOW);    // turn the LED off
  delay(r);                  // wait for r milliseconds
  
}
