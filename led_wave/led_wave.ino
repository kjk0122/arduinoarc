#include "FadeColor.h"

const int r = 11;
const int g = 10;
const int b = 9;

FadeColor fadeColor(r, g, b);

void setup() {
  fadeColor.setup();
}

void loop() {
  fadeColor.loop();
}
