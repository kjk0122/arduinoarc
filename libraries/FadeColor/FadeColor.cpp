// FadeColor.cpp

#include "Arduino.h"
#include "FadeColor.h"

FadeColor::FadeColor(int rPin, int gPin, int bPin) {
  _rPin = rPin;
  _gPin = gPin;
  _bPin = bPin;
}

void FadeColor::setup() {
  pinMode(_rPin, OUTPUT);
  pinMode(_gPin, OUTPUT);
  pinMode(_bPin, OUTPUT);
}

void FadeColor::loop() {
  fade(255, 0, 0);    // 빨강
  fade(0, 255, 0);    // 초록
  fade(0, 0, 255);    // 파랑
  fade(255, 255, 0);  // 노랑 (빨강 + 초록)
  fade(0, 255, 255);  // 청록 (초록 + 파랑)
  fade(255, 0, 255);  // 자홍 (빨강 + 파랑)
  fade(255, 255, 255);  // 흰색 (빨강 + 초록 + 파랑)
}

void FadeColor::fade(int red, int green, int blue) {
  for (int i = 0; i <= 255; i++) {
    analogWrite(_rPin, red * i / 255);
    analogWrite(_gPin, green * i / 255);
    analogWrite(_bPin, blue * i / 255);
    delay(10);
  }
  delay(1000);

  for (int i = 255; i >= 0; i--) {
    analogWrite(_rPin, red * i / 255);
    analogWrite(_gPin, green * i / 255);
    analogWrite(_bPin, blue * i / 255);
    delay(10);
  }
  delay(500);
}