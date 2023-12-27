const int trigPin = 6;  
const int echoPin = 7; 
const int ledPin = 3;
float duration, distance;  

void setup() {
  // put your setup code here, to run once:
	pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
	pinMode(ledPin, OUTPUT);    
	Serial.begin(115200);  

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  analogWrite(ledPin, distance*3);

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
