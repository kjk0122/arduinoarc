class Led {
public:
  Led(int pinNum)
    : PinNum(pinNum) {
    pinMode(pinNum, OUTPUT);
    Serial.println(String(PinNum) + "번 핀 설정 완료");
  }

  void turnOff() {
    digitalWrite(PinNum, LOW);
  }

  void turnOn() {
    digitalWrite(PinNum, HIGH);
  }

private:
  int PinNum;
};

const int numLeds = 8;
Led leds[numLeds] = {2, 3, 4, 5, 6, 7, 8, 9}; // 8개의 Led 객체 배열

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < numLeds; ++i) {
    // 아래 부분을 추가하여 각 Led 객체의 설정을 확인합니다.
    leds[i].turnOn();
    delay(500);
    leds[i].turnOff();
    delay(500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
