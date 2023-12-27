#include <Servo.h>

Servo servoMotor;  // 서보 객체 생성

void setup() {
  servoMotor.attach(9);  // 9번 핀에 서보 연결
}

void loop() {
  // 0도에서 180도까지 서보를 이동
  for (int angle = 0; angle <= 180; angle += 1) {
    servoMotor.write(angle);
    delay(15);  // 움직임이 자연스럽게 보이도록 딜레이 추가
  }

  delay(1000);  // 1초 대기

  // 180도에서 0도까지 서보를 이동
  for (int angle = 180; angle >= 0; angle -= 1) {
    servoMotor.write(angle);
    delay(15);  // 움직임이 자연스럽게 보이도록 딜레이 추가
  }

  delay(1000);  // 1초 대기
}
