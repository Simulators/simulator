
// Simple firmware for prototype 38kHz Sensors

// Use 8MHz internal clock

#define PIN_PWM 4     // IR LED - chip leg 3
#define PIN_DETECT 3  // IR Sensor - chip leg 2
#define PIN_STATUS 0  // Yellow LED - chip leg 5
#define PIN_OUTPUT 1  // Interface Output - chip leg 6


void setup()
{

  // Set up pins 
  pinMode(PIN_DETECT, INPUT_PULLUP);
  pinMode(PIN_STATUS, OUTPUT);
  pinMode(PIN_OUTPUT, OUTPUT);
  pinMode(PIN_PWM, OUTPUT);

  digitalWrite(PIN_STATUS, LOW);  // LED off
  digitalWrite(PIN_OUTPUT, HIGH); // Output off
  digitalWrite(PIN_PWM, LOW); // When not sending PWM, we want it low

  // Power-up signal on the LED
  digitalWrite(PIN_STATUS, HIGH);
  delay(250);
  digitalWrite(PIN_STATUS, LOW);
  delay(250);
  digitalWrite(PIN_STATUS, HIGH);
  delay(250);
  digitalWrite(PIN_STATUS, LOW);

  // Timer 1 Setup - 38kHz PWM, 25% Duty Cycle
  // Check against data sheet
  TCCR1 = _BV (CS10);           // no prescaler
  GTCCR = _BV (COM1B1) | _BV (PWM1B);  //  clear OC1B on compare
  OCR1B = 52;                   // duty cycle (25%)
  OCR1C = 210;                  // frequency 38kHz

}

void loop() {

  // Read the state of the IR sensor pin, track that state on the output pin,
  // and (inverted) on the LED.
  digitalWrite(PIN_OUTPUT, digitalRead(PIN_DETECT));
  // NB reading the *output* pin, set the LED to be the opposite.
  digitalWrite(PIN_STATUS, !digitalRead(PIN_OUTPUT));

}

