## 1. 폴링

주기적으로 특정 조건을 검사하여 이벤트를 감지하는 방법. 루프를 통해 지속적으로 확인하며, 특정조건이 만족되면 해당 작업을 수행

- 단점: CPU자원을 많이 소모, 반응시간 늦을 수 있음

## 2. 인터럽트

외부 또는 내부 이벤트가 발생했을 때, CPU가 현재 작업을 중단하고 인터럽트 서비스 루틴을 실행하도록 함

이벤트 처리가 완료되면 원래 작업으로 돌아감

- 단점: 구현이 복잡

```cpp
const int buttonPin = 2;
const int ledPin = 13;
volatile bool ledState = false;

void handleButtonPress(){
	ledState = !ledState;
	digitalWrite(ledPin, ledState ? HIGH : LOW);
}

void setup(){
	pinMode(buttonPin, INPUT_PULLUP);
	pinMode(ledPin, OUTPUT);
	attachInterrupt(digitalPinInterrupt(buttonPin),handleButtonPress, FALLINGS);//인터럽트 설정
	//digitalPinInterrupt로 핀번호->인터럽트번호, ISR, HIGH->LOW의 트리거 조건
}

void loop(){
	//메인 비워둠. 이렇게 하면 여기서 다른코드랑 동시에 실행 가능
}
```

> 인터럽트 설정
> 
1. 인터럽트 핀 지정 : 인터럽트 사용할 핀 지정
2. 인터럽트 모드 설정 : 인터럽트가 트리거될 조건을 설정(RISING, FALLING, CHANGE)
3. 인터럽트 서비스 루틴 정의 : 인터럽트 발생 시 실행될 함수 정의
4. 인터럽트 활성화 : `attachInterrupt()` 함수를 사용하여 인터럽트 활성화
