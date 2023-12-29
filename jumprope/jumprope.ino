#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050_tockn.h>

#define SCREEN_WIDTH 128   // OLED display width, in pixels
#define SCREEN_HEIGHT 32   // OLED display height, in pixels

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MPU6050 mpu6050(Wire);

float result = 0;
int vib = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen
  display.display();
  delay(2000); // Pause for 2 seconds
}

void loop() {
  mpu6050.update();
  result = pow(pow(mpu6050.getGyroX(), 2) + pow(mpu6050.getGyroY(), 2) + pow(mpu6050.getGyroZ(), 2), 0.5);

  if (result > 300) {
    vib++;
    Serial.println("움직임!");
  }

  updateDisplay();

  // 추가된 부분: getAngleX()의 값이 36000이 되면 "솜사탕 완성!" 출력
  if (mpu6050.getAngleX() == 36000) {
    Serial.println("솜사탕 완성!");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 10);
    display.println(F("솜사탕"));
    display.println(F("완성!"));
    display.display();
    delay(2000); // 2초간 표시
  }
}

void updateDisplay() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Movement: "));
  display.println(result);

  display.print("Count: ");
  display.println(vib);

  display.print("Xangle: ");
  display.println(mpu6050.getAngleX());

  display.display();
  delay(100); // Delay for better readability; adjust as needed
}
