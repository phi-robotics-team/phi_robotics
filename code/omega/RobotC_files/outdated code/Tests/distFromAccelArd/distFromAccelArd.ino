#include <ADXL345.h>
#include <Wire.h>

ADXL345 accel;
int x = 0, y = 0, z = 0;
float gravityBias = 0;
float botAccel = 0, prevAccel = 0;
int deltaT = 0;
float velocity = 0, prevVelocity = 0, dist = 0, distDesired = 0;

int clockPin = 3, sigAPin = 4, sigBPin = 5;
bool checkAck = false;
bool halfReported = false;

int deltaTimer = 0;

void setup() {
  reset();
  Serial.begin(9600);
  accel.powerOn();
  for (int i = 0; i < 20; i++)
  {
    gravityBias += updateAccel(true);
    delay(5);
  }
  gravityBias /= 20;
}

float test = 0;
void loop() {
  updateAccel();
  Serial.println(botAccel);
  delay(500);
  if (digitalRead(clockPin) == HIGH && digitalRead(sigAPin) == LOW)
  {
    pinMode(sigBPin, OUTPUT);
    digitalWrite(sigBPin, LOW);
    
    int base = 0;
    int dir = 0;
    int dec = 0;
    for (int i = 0; i < 8; i++)
    {
      while (digitalRead(clockPin) == LOW);
      
      pinMode(clockPin, OUTPUT);
      pinMode(sigAPin, INPUT);
      pinMode(sigBPin, INPUT);
      digitalWrite(clockPin, LOW);
      
      if (i < 4)
      {
        base = (base << 1) | pinLow(sigAPin);
        base = (base << 1) | pinLow(sigBPin);
      }
      else if (i > 3 && i < 7)
      {
        dec = (dec << 1) | pinLow(sigAPin);
        dec = (dec << 1) | pinLow(sigBPin);
      }
      else
      {
        dec = (dec << 1) | pinLow(sigAPin);
        if (pinLow(sigBPin))
          dir = -1;
        else
          dir = 1;
      }
      
      pinMode(clockPin, INPUT);
      delay(1);
    }
    
    distDesired = dir * (base + (dec / 100));
    
    pinMode(clockPin, INPUT);
    pinMode(sigAPin, INPUT);
    pinMode(sigBPin, INPUT);
  }
  
  while (dist < distDesired)
  {
    updateAccel();
    
    deltaT = (deltaTimer - micros()) * 0.000001;
    deltaTimer = micros();
    
    if (abs(botAccel < 0.01))
      botAccel = 0;
    
    velocity += deltaT/2 * (prevAccel + botAccel);
    dist += deltaT/2 * (prevVelocity + velocity);
    
    prevAccel = botAccel;
    prevVelocity = velocity;
    
    if (dist >= distDesired / 2 && !halfReported)
    {
      pinMode(sigAPin, OUTPUT);
      digitalWrite(sigAPin, LOW);
      checkAck = true;
      halfReported = true;
    }
      
    if (checkAck)
    {
      if (digitalRead(sigBPin) == LOW)
      {
        pinMode(sigAPin, INPUT);
        checkAck = false;
      }
    }
    
    delay(5);
  }
  
  pinMode(clockPin, OUTPUT);
  pinMode(sigAPin, OUTPUT);
  digitalWrite(clockPin, LOW);
  digitalWrite(sigAPin, LOW);
  
  while (digitalRead(sigBPin) == HIGH);
  
  reset();
}

void reset()
{
  dist = 0;
  distDesired = 0;
  checkAck = false;
  halfReported = false;
  
  pinMode(clockPin, INPUT);
  pinMode(sigAPin, INPUT);
  pinMode(sigBPin, INPUT);
}

int pinLow(int pin)
{
  if (digitalRead(pin) == LOW)
    return 1;
  else
    return 0;
}

float updateAccel(bool start)
{
  float _x = 0, _y = 0, _z = 0;
  x = 0;
  y = 0;
  z = 0;
  accel.readAccel(&x, &y, &z);
  _x = (float)x * (4.0/1024.0) * 386.09;
  _y = (float)y * (4.0/1024.0) * 386.09;
  _z = (float)z * (4.0/1024.0) * 386.09;
  
  float vector = sqrt((_x * _x) + (_y * _y) + (_z * _z));
  return vector;
}

void updateAccel()
{
  float _x = 0, _y = 0, _z = 0;
  x = 0;
  y = 0;
  z = 0;
  accel.readAccel(&x, &y, &z);
  _x = (float)x * (4.0/1024.0) * 386.09;
  _y = (float)y * (4.0/1024.0) * 386.09;
  _z = (float)z * (4.0/1024.0) * 386.09;
  
  float vector = sqrt((_x * _x) + (_y * _y) + (_z * _z));
  botAccel = sqrt((vector * vector) - (gravityBias * gravityBias)) * sign(_x);
}

int sign(int n)
{
  if (n < 0)
    return -1;
  return 1;
}
