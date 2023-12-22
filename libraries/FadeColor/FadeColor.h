// FadeColor.h

#ifndef FadeColor_h
#define FadeColor_h

#include "Arduino.h"

class FadeColor {
public:
  FadeColor(int rPin, int gPin, int bPin);
  void setup();
  void loop();

private:
  int _rPin;
  int _gPin;
  int _bPin;
  
  void fade(int red, int green, int blue);
};

#endif
