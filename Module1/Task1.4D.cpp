// C++ code
//
const int motionPin = 2;
const int buttonPin = 3;
const int echoPin = 4;
const int trigPin = 5;
const int tiltPin = 6;
const int orangePin = 10;
const int yellowPin = 11;
const int greenPin = 12;
const int redPin = 13;

int cm = 0;
int senseAudio = 0;

void setup()
{
  pinMode(motionPin, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(tiltPin, INPUT);
  pinMode(orangePin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  PCICR |= B00000100; // Activate interrupts for PD port
  PCMSK2 |= B01000000; // Activate interrupts on pin D6;
  
  attachInterrupt(digitalPinToInterrupt(motionPin), interruptMotion, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), interruptAudio, CHANGE);
  
  startTimer();
  
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
  Serial.print("Tilt sensor: ");
  Serial.println(digitalRead(tiltPin));
  Serial.print("Yellow LED: " );
  Serial.println(digitalRead(yellowPin));
  Serial.print("Orange LED: " );
  Serial.println(digitalRead(orangePin));
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

ISR(PCINT2_vect)
{
  digitalWrite(yellowPin, digitalRead(tiltPin));
}

ISR(TIMER1_COMPA_vect)
{
  digitalWrite(orangePin, digitalRead(orangePin) ^ 1);
}

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

void startTimer(){
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  TCCR1B |= ( 1 << WGM12); //CTC Mode
  
  TCCR1B |= (1 << CS12); // 1024 prescaler
  TCCR1B |= (1 << CS10);
  OCR1A = 31250; // 2 seconds
  
  TIMSK1 = (1 << OCIE1A); // enable timer interrupt
  
  interrupts();
}

