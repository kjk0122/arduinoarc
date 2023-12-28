#include <MUIU8g2.h>
#include <U8g2lib.h>
#include <U8x8lib.h>

#include <MorseUga.h>

MorseUga morse(13);

void setup()
{
  morse.begin();
}

void loop()
{
  morse.dot(); morse.dot(); morse.dot();
  morse.dash(); morse.dash(); morse.dash();
  morse.dot(); morse.dot(); morse.dot();
  delay(3000);
}
