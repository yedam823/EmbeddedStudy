펄스 폭 변조

전압을 직접 바꾸지 않고, 신호가 켜져있는 시간(펄스 폭)을 조절해서 출력 전압의 평균값을 바꾸는 기술

빠르게 켰다껐다 하면서 밝기가 세진거처럼 보이게 하는 거

### 듀티 사이클(duty cycle)

0% 꺼짐

50% 절반 켜짐

100% 완전 켜짐

트랜지스터로 on off 스위치를 만들어 조절

### PWM 제어

AVR MCU에 타이머/카운터를 사용해 제어 가능

핀 D3, D5, D6, D9, D10, D11 보통 사용한다

```cpp
int led = 9; // PWM 가능한 핀

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 255; i++) {  
    analogWrite(led, i); // PWM으로 밝기 조절
    delay(10);
  }
}
```
