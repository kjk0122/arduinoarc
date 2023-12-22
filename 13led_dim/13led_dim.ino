const int ledPin = 6;
int bright=0; int step=5;
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  analogWrite(ledPin, bright);
  bright=bright+step;
  if(bright<=0 || bright>=145){
    step=-step;
  }
  delay(100);
}
