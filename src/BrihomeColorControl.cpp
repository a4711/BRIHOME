#include "BrihomeColorControl.h"

void BrihomeColorControl::setup_bulb()
{
    /*
    GPIO4, 
    GPIO5,
    GPIO12
    GPIO13
    GPIO14
    */

    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(COLD, OUTPUT);
    pinMode(WARM, OUTPUT);
}

void BrihomeColorControl::controlLeds (const char* message)
{
  Serial.print ("message: ");
  Serial.println (message);
  unsigned int values[] =
  { 0, 0, 0, 0, 0 };
  char buffer[5];
  size_t tmpIdx = 0;
  size_t valIdx = 0;
  for (; 0 != message; message++)
  {
    if (',' == *message || '\0' == *message)
    {
      buffer[tmpIdx] = 0;
      tmpIdx = 0;
      if (valIdx < (sizeof(values) / sizeof(values[0])))
      {
        values[valIdx++] = ::atoi (buffer);
      }
      else
      {
        break; // no more space in values array
      }
      if ('\0' == *message)
      {
        break;
      }
    }
    else if (tmpIdx < (sizeof(buffer) / sizeof(buffer[0])))
    {
      buffer[tmpIdx++] = *message;
    }
  }
  controlLeds (values, sizeof(values) / sizeof(values[0]));
}

void BrihomeColorControl::controlLeds (const unsigned int* values, size_t length)
{
  // (c, w, r, g b)  // cold, warm, red, green, blue
  unsigned char channelMap[] =
  { COLD, WARM, RED, GREEN, BLUE };
  length = min(length, sizeof(channelMap) / sizeof(channelMap[0]));
  for (size_t i = 0; i < length; i++)
  {
    Serial.print ("idx: ");
    Serial.print (i);
    Serial.print (" val: ");
    Serial.println (values[i]);
    if (i >= sizeof(channelMap) / sizeof(channelMap[0]))
      break;

    analogWrite(channelMap[i], values[i]);
  }
}

void BrihomeColorControl::off()
{
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(COLD, LOW);
  digitalWrite(WARM, LOW);
}

void BrihomeColorControl::red(int brightness)
{
      analogWrite(RED, brightness);
}
void BrihomeColorControl::green(int brightness)
{
      analogWrite(GREEN, brightness);
}
void BrihomeColorControl::blue(int brightness)
{
      analogWrite(BLUE, brightness);
}
void BrihomeColorControl::cold(int brightness)
{
      analogWrite(COLD, brightness);
}
void BrihomeColorControl::warm(int brightness)
{
      analogWrite(WARM, brightness);
}