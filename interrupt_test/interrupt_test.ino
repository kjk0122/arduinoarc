volatile bool buttonState = false;  // 버튼 상태를 나타내는 변수 (volatile 키워드를 사용하여 최적화 방지)

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  // 2번 핀을 인터럽트로 설정 (falling edge에 반응)
  attachInterrupt(digitalPinToInterrupt(2), buttonInterrupt, FALLING);
}

void loop() {
  // 6번 핀을 껐다 켰다 반복
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6, LOW);
  delay(500);
}

// 2번 핀에 대한 인터럽트 처리 함수
void buttonInterrupt() {
  // 버튼 상태를 토글
  buttonState = !buttonState;

  // 7번 LED 상태를 버튼 상태에 따라 토글
  digitalWrite(7, buttonState);
  Serial.print("예");
}
