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

int vib = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ; // Loop forever if OLED initialization fails
  }

  display.display();
  delay(2000);
}

void loop() {
  mpu6050.update();
  updateDisplay();

  if (mpu6050.getAngleX() == 36000) {
    handleSweetsCompletion();
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.print("Xangle: ");
  display.println(mpu6050.getAngleX());
  display.display();
  delay(100);
}

void handleSweetsCompletion() {
  Serial.println("솜사탕 완성!");
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println(F("솜사탕"));
  display.println(F("완성!"));
  display.display();

  delay(2000);
}
