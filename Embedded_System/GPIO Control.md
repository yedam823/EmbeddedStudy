## 1. GPIO 핀모드 설정

```cpp
pinMode(pin, INPUT); //입력모드, 버튼이나 센서의 상태 읽을 때 사용

pinMode(pin, OUTPUT); //출력모드, LED나 모터를 제어할 때 사용

pinMode(pin, INPUT_PULLUP); //풀업 모드(기본값 HIGH), 내부 풀업 저항을 활성화 하여 입력핀이 풀업된 상태를 유지 하도록 함
pinMode(pin, INPUT_PULLDOWN); //풀다운모드(기본값 LOW), 풀업의 반대
```

### 풀업, 풀다운 저항을 사용하는 이유?

MCU의 GPIO핀은 전기적으로 떠있는 플로팅 상태일 수 있음. →잡음타고 값이 변할 수도

아무 입력이 없을 때 기본값을 정해주는 저항이 풀업 풀다운 저항

## 2. GPIO 핀 제어

```cpp
digitalWrite(pin, HIGH); //디지털 출력, 핀을 HIGH상태로 설정
digitalWrite(pin, LOW); // 핀을 LOW 상태로 출력

int state = digitalRead(pin); //디지털 입력, 핀의 상태를 읽음
```

## 3. LED 제어 예제

눌렀을 때 켜지고, 한번더 누르면 꺼지는 예제
const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;
int lastButtonState = 0;
bool ledState = false;

void setup(){
	pinMode(buttonPin, INPUT_PULLUP);
	pinMode(ledPin, OUTPUT);
}

void loop(){
	buttonState = digitalRead(buttonPin);
	
	if(buttonState != lastButtonState){ //버튼 상태 달라졌는지 확인
		if(buttonState == LOW){ //버튼이 눌렸는지 확인
			ledState = !ledState; //led 상태 바꾸기
			digitalWrite(ledPin, ledState ? HIGH : LOW);
		}
		lastButtonState = buttonState; //버튼 상태 업데이트
	}
}
