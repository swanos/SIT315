// C++ code
//
int sensorState = 0;
int ledState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), interrupt, CHANGE);
  Serial.begin(9600);
}

void loop()
{
  Serial.print(sensorState);
  Serial.println(ledState);
  delay(500); // Delay a little bit to improve simulation performance
}

void interrupt()
{
  sensorState = !sensorState;
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}