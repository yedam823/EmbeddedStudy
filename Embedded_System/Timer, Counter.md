# 타이머와 카운터

타이머 : 설정된 시간 간격마다 인터럽트를 발생시키는 기능을 제공

→주로 일정한 시간 간격으로 작업을 수행할 때 사용

카운터 : 외부 이벤트를 카운트하는 기능을 제공

→ 펄스신호 카운트, 이벤트 발생 횟수를 측정할 때 사용

## 1. 타이머 설정 및 사용

```cpp
#include<timerOne.h>

const int ledPin = 13;

void timerIsr(){
	static bool ledState = false;
	ledState = !ledState;
	digitalWrite(ledPin, ledState ? HIGH : LOW);
}

void setup(){
	pinMode(ledPin, OUTPUT); 
	Timer1.initialize(1000000); //타이머 주기 1초(1000000마이크로초)로 설정
	Timer1.attachInterrupt(timerIsr); //타이머 인터럽트 설정
}

void loop(){
	//메인 루프 비워둠. 여기서 다른코드 실행하면서 동시에 LED제어 가능
}
```

## 2. 카운터 설정 및 사용

외부 이벤트를 카운트 하는데 사용됨(내부: 타이머, ADC 변환 등 MCU가 발생, 외부: 버튼, 신호변화)

```cpp
const int buttonPin = 2;
volatile int counter = 0;

//ISR
void countEvent(){
	counter++;
}

void setup(){
	pinMode(buttonPin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(buttonPin), countEvent, FALLING); //인터럽트
	Serial.begin(9600);
}

void loop(){
	Serial.println(counter); //버튼이 눌릴때마다 counter 증가
	delay(1000);
}
```

## 4. 고급 타이머 사용

PWM 신호 생성, 타이머 캡쳐 등 사용가능
```cpp
const int pwmPin = 9;

void setup(){
	pinMode(pwmPin, OUTPUT);
}

void loop(){
	for(int i=0; i<256;i++){
		analogWrite(pwmPin, i); //PWM 신호 생성, LED 밝기 조절
		delay(10);
	}
	
	for(int i=255;i>=0; i--){
		analogWrite(pwmPin, i);
		delay(10);
	}
}
```
