// C++ code
//
int sensorState = 0;
int ledState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // read the state of the sensor/digital input
  sensorState = digitalRead(2);
  ledState = digitalRead(13);
  // check if sensor pin is HIGH. if it is, set the
  // LED on.
  if (sensorState == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.print(sensorState);
  Serial.println(ledState);
  delay(10); // Delay a little bit to improve simulation performance
}