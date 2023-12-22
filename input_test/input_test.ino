char e[4] = {'a', 'b', 'c', 'd'};

void setup() {
  Serial.begin(115200);
}

void loop() {
  // check if data has been sent from the computer:
  if (Serial.available()>0) {
    String input = Serial.readStringUntil('\n');
    for(int i=0;i<3;i++){
        int start=input.indexOf(e[i])+1;
        int end=input.indexOf(e[i+1]);
        String val = input.substring(start,end);
       Serial.println(String(e[i]) + "의 값: " + val);
    }
  }
}