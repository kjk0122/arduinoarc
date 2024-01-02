  int A1Pin = 5; int A2Pin = 6;
  int B1Pin = 10; int B2Pin = 11;
  int time = 0;
  String input = ""; // 여기에 선언하여 전역으로 사용 가능하도록 함

  void setup() {
    Serial.begin(115200);

      pinMode(A1Pin, OUTPUT);
      pinMode(A2Pin, OUTPUT);
  }

  void loop() {
    if (Serial.available() > 0) {
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
    analogWrite(A1Pin, 160);
    analogWrite(A2Pin, 0);
    analogWrite(B1Pin, 120);
    analogWrite(B2Pin, 0);
    delay(time);  // 1sec
    analogWrite(A1Pin, 0);
    analogWrite(A2Pin, 0);
    analogWrite(B1Pin, 0);
    analogWrite(B2Pin, 0);
  }
