#include <SoftwareSerial.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#define blueTX 2
#define blueRX 3
char ser = 0;
char ble = 0;

MPU6050 mpu6050(Wire);
SoftwareSerial HC06(blueTX, blueRX);

const int A1Pin = 5;
const int A2Pin = 6;
const int B1Pin = 10;
const int B2Pin = 11;
int time = 0;
unsigned long moveStartTime = 0;

const int trigPin = 9;
const int echoPin = 8;
float duration, distance, output = 0;
float alpha = 0.8;

String input = "";  // 선언 추가

float low_pass_filter(float input) {
  output = alpha * input + (1 - alpha) * output;
  return output;
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
}

void loop() {
  HC06proc();  // 소프트웨어 시리얼 이벤트 처리
  mpu6050.update();
  Serial.println(mpu6050.getAngleX());
  if(mpu6050.getAngleX()>75){
    move(1);
  }else if(mpu6050.getAngleX()<20){
    reverse(1);
  }
  // Bluetooth and Motor Control
  if (Serial.available() > 0) {
    input = Serial.readString();
    input.trim();

    if (input.length() > 0 && isDigit(input.charAt(0))) {
      time = input.toInt();
      moveStartTime = millis();  // 모터 동작 시작 시간 기록
      move(time);
      Serial.print("Received time: ");
      Serial.println(time);
    } else {
      Serial.println("다시!");
    }
  } else {
    time = 0;
  }

  // Check if it's time to stop the motor
  if (moveStartTime > 0 && (millis() - moveStartTime >= time * 1000)) {
    stopMotors();
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
    Serial.print("Filtered Ultrasonic Distance: ");
    Serial.println(low_pass_filter(distance));
    if(low_pass_filter(distance)<15){
      reverse(30);
    }
  }
}

void HC06proc() {
  while (HC06.available() > 0) {
    ble = HC06.read();
    Serial.print("Received from Bluetooth: ");
    Serial.println(ble);

    if (isDigit(ble)) {
      time = ble - '0';  // char to int conversion
      moveStartTime = millis();  // 모터 동작 시작 시간 기록
      move(time);
      Serial.print("Received time: ");
      Serial.println(time);
    } else {
      Serial.println("다시!");
    }
  }
}

void move(int time) {
  Serial.println(time);
  motorControl(160, 0, 160, 0);
}

void back(int time) {
  Serial.println(time);
  motorControl(0, 110, 0, 110);
}

void left(int time) {
  Serial.println(time);
  motorControl(160, 0, 0, 160);
}

void right(int time) {
  Serial.println(time);
  motorControl(0, 160, 160, 0);
}

void motorControl(int a1, int a2, int b1, int b2) {
  analogWrite(A1Pin, a1);
  analogWrite(A2Pin, a2);
  analogWrite(B1Pin, b1);
  analogWrite(B2Pin, b2);
}

void stopMotors() {
  motorControl(0, 0, 0, 0);
  moveStartTime = 0;  // 모터 동작 시작 시
}