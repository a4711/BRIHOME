#include <Arduino.h>
class BrihomeColorControl {

// these are the PINs used by BRIHOME light bulb:
enum Color
{
  RED = 4, // ok
  GREEN = 12,
  BLUE = 14,  // ok
  COLD = 5, // ok
  WARM = 13 // ok
};

public:
  void setup_bulb();

  /// give a string in the following format "<COLD>,<WARM>,<RED>,<GREEN>,<BLUE>"
  void controlLeds (const char* message);

  void off();
  void red(int brightness);
  void green(int brightness);
  void blue(int brightness);
  void cold(int brightness);
  void warm(int brightness);

private:
  void controlLeds (const unsigned int* values, size_t length);
};