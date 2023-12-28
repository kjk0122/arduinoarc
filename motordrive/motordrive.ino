// 3번과 4번 핀은 모터 제어에 관한 핀
int IN1Pin = 11;
int IN2Pin = 13;
int time = 0;
String input = ""; // 여기에 선언하여 전역으로 사용 가능하도록 함

void setup() {
  Serial.begin(115200);
  pinMode(8, INPUT);

    pinMode(IN1Pin, OUTPUT);
    pinMode(IN2Pin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0 && digitalRead(8) == LOW) {
    input = Serial.readStringUntil('\n');
    input.trim();  // 앞뒤 공백 제거

    // 입력이 숫자인지 확인
    if (input.length() > 0 && isDigit(input.charAt(0))) {
      // 숫자로 변환
      time = input.toInt();
      move(time);
      Serial.print("Received time: ");
      Serial.println(time);
    } else {
      Serial.println("다시!");
    }
  } else {
    // 8번 핀이 0이 아닌 경우, time 변수를 초기화
    time = 0;
  }
}

void move(int time) {
  Serial.println(time);
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  delay(time);  // 1sec
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, LOW);
}
