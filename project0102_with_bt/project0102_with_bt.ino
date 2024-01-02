#include <SoftwareSerial.h>

#define blueTX 2
#define blueRX 3
char ser = 0;
char ble = 0;

SoftwareSerial HC06(blueTX, blueRX);

int A1Pin = 5;
int A2Pin = 6;
int B1Pin = 10;
int B2Pin = 11;
int time = 0;
String input = "";

void setup() {
  Serial.begin(9600);
  HC06.begin(9600);

  pinMode(A1Pin, OUTPUT);
  pinMode(A2Pin, OUTPUT);
}

void loop() {
  HC06proc();

  if (Serial.available() > 0) {
    input = Serial.readString();
    input.trim();

    if (input.length() > 0 && isDigit(input.charAt(0))) {
      time = input.toInt();
      move(time);
      Serial.print("Received time: ");
      Serial.println(time);
    } else {
      Serial.println("다시!");
    }
  } else {
    time = 0;
  }
}

void move(int time) {
  Serial.println(time);
  analogWrite(A1Pin, 160);
  analogWrite(A2Pin, 0);
  analogWrite(B1Pin, 120);
  analogWrite(B2Pin, 0);
  delay(time*1000);  // 1sec
  analogWrite(A1Pin, 0);
  analogWrite(A2Pin, 0);
  analogWrite(B1Pin, 0);
  analogWrite(B2Pin, 0);
}

void HC06proc() {
  if (Serial.available() > 0) {
    ser = Serial.read();
    HC06.write(ser);
  }
  if (HC06.available() > 0) {
    ble = HC06.read();
    Serial.write(ble);
  }
}
