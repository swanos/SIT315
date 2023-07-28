// C++ code
//
const int motionPin = 2;
const int buttonPin = 3;
const int echoPin = 4;
const int trigPin = 5;
const int greenPin = 12;
const int redPin = 13;

int cm = 0;
int senseAudio = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(motionPin, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motionPin), interruptMotion, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), interruptAudio, CHANGE);
  Serial.begin(9600);
}

void loop()
{
  if (senseAudio) 
  {
    cm = 0.01723 * readUltrasonicDistance(trigPin, echoPin);
    if (cm < 150)
    {
      digitalWrite(greenPin, HIGH);
    } else {
      digitalWrite(greenPin, LOW);
    }
  }
  // Print to serial monitor
  Serial.print("Motion sensor: ");
  Serial.println(digitalRead(motionPin));
  Serial.print("Red LED: ");
  Serial.println(digitalRead(redPin));
  Serial.println(cm);
  Serial.print("Sound sensor: ");
  Serial.println(digitalRead(buttonPin));
  Serial.print("Green LED: ");
  Serial.println(digitalRead(greenPin));
  Serial.println();
  delay(500); // Delay a little bit to improve simulation performance
}

void interruptMotion()
{
  digitalWrite(redPin, digitalRead(motionPin));
}

void interruptAudio()
{
  senseAudio = digitalRead(buttonPin);
}