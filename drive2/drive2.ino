#include <SoftwareSerial.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#define blueTX 2
#define blueRX 3
char ser = 0;
char ble = 0;

SoftwareSerial HC06(blueTX, blueRX);
MPU6050 mpu6050(Wire);

const int A1Pin = 5;
const int A2Pin = 6;
const int B1Pin = 10;
const int B2Pin = 11;
int time = 0;
unsigned long moveStartTime = 0;  // 모터 동작 시작 시간 저장

const int trigPin = 9;
const int echoPin = 8;
float duration, distance, output = 0;
float alpha = 0.8;

String input = "";  // 선언 추가

void motorControl(int a1, int a2, int b1, int b2) {
  analogWrite(A1Pin, a1);
  analogWrite(A2Pin, a2);
  analogWrite(B1Pin, b1);
  analogWrite(B2Pin, b2);
}

void stopMotors() {
  motorControl(0, 0, 0, 0);
  moveStartTime = 0;  // 모터 동작 시간 초기화
}

float low_pass_filter(float input) {
  output = alpha * input + (1 - alpha) * output;
  return output;
}

void HC06proc() {
  static String commandBuffer = "";  // 명령어 문자열을 저장할 버퍼
  while (HC06.available() > 0) {
    ble = HC06.read();
    Serial.print("Received from Bluetooth: ");
    Serial.println(ble);

    if (ble == '\n' || ble == '\r') {
      // 개행 문자가 나타나면 명령어를 처리
      if (commandBuffer.length() > 0) {
        processCommand(commandBuffer);
        commandBuffer = "";  // 버퍼 비우기
      }
    } else {
      commandBuffer += ble;  // 문자를 버퍼에 추가
    }
  }
}

void processCommand(String command) {
  if (command.length() > 0) {
    char commandType = command.charAt(0);
    if (commandType == 'L' || commandType == 'R' || commandType == 'M' || commandType == 'B') {
      int time = command.substring(1).toInt();
      moveStartTime = millis();  // 모터 동작 시작 시간 기록
      executeCommand(commandType, time * 120);
      Serial.print("Received command: ");
      Serial.println(commandType);
    } else {
      Serial.println("Invalid command!");
    }
  }
}



void setup() {
  Serial.begin(115200);
  HC06.begin(9600);  // Baud rate 맞춤

  pinMode(A1Pin, OUTPUT);
  pinMode(A2Pin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // 1초씩 left, right, move, back 실행
  executeCommand('L', 1);
  delay(400);
  executeCommand('R', 1);
  delay(400);
  executeCommand('M', 1);
  delay(400);
  executeCommand('B', 1);
  delay(400);
  stopMotors();
}

void loop() {
  HC06proc();  // 소프트웨어 시리얼 이벤트 처리
  mpu6050.update();

  // Bluetooth and Motor Control
  if (Serial.available() > 0) {
    input = Serial.readString();
    input.trim();

    if (input.length() > 0) {
      char command = input.charAt(0);
      if (command == 'L' || command == 'R' || command == 'M' || command == 'B') {
        time = input.substring(1).toInt();
        moveStartTime = millis();  // 모터 동작 시작 시간 기록
        executeCommand(command, time * 120);
        Serial.print("Received command: ");
        Serial.println(command);
      } else {
        Serial.println("다시!");
      }
    }
  } else {
    time = 0;
  }

  // Check if it's time to stop the motor
  if (moveStartTime > 0 && (millis() - moveStartTime >= time * 1000)) {
    stopMotors();
    moveStartTime = 0;
  }

  // Ultrasonic Sensor
  if (millis() % 1000 == 0) {  // 1초에 한 번씩 초음파 센서 값 출력
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.0343) / 2;

    Serial.print("Ultrasonic Distance: ");
    Serial.println(distance);
    Serial.print("Filtered Ultrasonic Distance: ");
    Serial.println(low_pass_filter(distance));
  }
}

void executeCommand(char command, int time) {
  switch (command) {
    case 'L':
      Serial.println("Left function called");
      left(time);
      break;
    case 'R':
      Serial.println("오른쪽");
      right(time);
      break;
    case 'M':
      Serial.println("앞으로");
      move(time);
      break;
    case 'B':
      Serial.println("뒤로");
      back(time);
      break;
    default:
      Serial.println("Invalid command!");
  }
}

void move(int time) {
  motorControl(160, 0, 160, 0);
  delay(time);
}

void left(int time) {
  motorControl(160, 0, 0, 160);
  delay(time);
}

void right(int time) {
  motorControl(0, 160, 160, 0);
  delay(time);
}

void back(int time) {
  motorControl(0, 110, 0, 110);
  delay(time);
}
