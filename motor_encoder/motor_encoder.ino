#define ENCODER 2         // 엔코더를 연결한 핀 번호
 
volatile int encoder = 0;  // 엔코더를 지나간 디스크의 구멍 수를 저장하는 변수
 
void ISR_encoder() {
  encoder++;               // 구멍 수 +1
}
 
void setup() {
  Serial.begin(115200);              // 57600bps 속도로 시리얼 통신 시작
  pinMode(ENCODER, INPUT_PULLUP);   // 엔코더를 내부 풀업 저항을 사용하는 입력으로 설정
  attachInterrupt(digitalPinToInterrupt(ENCODER), ISR_encoder, FALLING);  
}
 
unsigned long timePrev = 0;         // 이전 시간을 저장하는 변수 (0으로 초기화)
unsigned long timeCurr = 0;         // 현재 시간을 저장하는 변수 (0으로 초기화)
 
void loop() {
  timeCurr = millis();               // ms단위로 현재 시간 받아오기
  if (timeCurr - timePrev > 1000) {  // 1초마다 출력(1000ms = 1s)
    timePrev = timeCurr;             // 이전 시간을 현재 시간으로 업데이트
    noInterrupts();
    Serial.print(timeCurr/1000);          // 현재 시간을 초 단위로 출력
    Serial.print(": ");
    Serial.println(encoder);         // 엔코더를 지나간 디스크의 구멍 수 출력
    interrupts();
  }
}