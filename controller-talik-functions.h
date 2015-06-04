#include <arduino.h>

int lastState[20];
unsigned long lastTouch[20];
int isAnalog(int pin);
int readPressState(int pin);
void initiateAll()
{
  int i;
  lastState[A0] = readPressState(A0);
  lastState[A1] = readPressState(A1);
  lastState[A2] = readPressState(A2);
  lastState[A3] = readPressState(A3);
  lastState[A4] = readPressState(A4);
  lastState[A5] = readPressState(A5);
}
int readPress(int analogSensorPIN)
{
  if((millis()-lastTouch[analogSensorPIN])<250 && lastTouch[analogSensorPIN]<millis())
    return 0;
  int state, touch;
  state = readPressState(analogSensorPIN);
  if(lastState[analogSensorPIN]==0 && state==1)
    touch = 1;
  else
    touch = 0;
  lastState[analogSensorPIN] = state;
  if(touch)
    lastTouch[analogSensorPIN] = millis();
  return touch;
}
int isAnalog(int pin)
{
  if(pin==A0 || pin==A1 || pin==A2 || pin==A3 || pin==A4 || pin==A5)
    return 1;
  return 0;
}
int readPressState(int analogSensorPIN)
{
   int state, sensorValue;
  if(isAnalog(analogSensorPIN))
  {
  sensorValue = analogRead(analogSensorPIN);
  if(sensorValue>800)
    state=1;
  else
    state=0;
  }else{
    state = digitalRead(analogSensorPIN);
  }
  return state;
}
boolean flip(int input)
{
  if(input)
    return false;
  return true;
}
int readFlip(int analogSensorPIN)
{
  int state, touch;
  state = readPressState(analogSensorPIN);
  if(state != lastState[analogSensorPIN])
    touch = 1;
  else
    touch = 0;
  lastState[analogSensorPIN] = state;
  return touch;
}
