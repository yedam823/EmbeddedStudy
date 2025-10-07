단거리 무선 통신 기술, 두 장치 간의 데이터를 무선으로 송수신 가능

→ 스마트폰 같은 장치와 데이터를 주고받거나 여러 임베 장치 간의 통신 구현 할수잇음!

### 기본 개념

> 블루투스 모듈
> 

HC-05 : 마스터 및 슬레이브 모두 지원

HC-06 : 슬레이브 모드만 지원

> 모듈 설정
> 

UART 인터페이스를 통해 설정하고 통신함

> 모듈 연결
> 
1. HC-05 블루투스 모듈
- VCC : 5V
- GND : GND
- TX : 아두이노 디지털핀 0(RX)
- RX : 아두이노 디지털 핀 1(TX)

### 블루투스 데이터 송수신

```cpp
void setup(){
	Serial.begin(9600); //블루투스 모듈과 시리얼 통신
}

void loop(){
	//데이터 수신
	if(Serial.available()>0){
		char receivedChar = Serial.read(); //수신된 데이터 읽기
		Serial.print("received: ");
		Serial.println(receivedChar); //수신된 데이터 출력
	}
	
	Serial.println("Hellon from Arduino!");
	delay(1000);
}
```

### 스마트폰을 통해 LED 제어

```cpp
const int ledPin = 13;

void setup(){
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT);
}

void loop(){
	//데이터 수신
	if(Serial.available()>0){
		char receivedChar = Serial.read(); //수신된 데이터 읽기
		Serial.print("received: ");
		Serial.println(receivedChar); //수신된 데이터 출력
		
		if(receivedChar == '1'){
			digitalWrite(ledPin, HIGH); //켜고
		}else if(receivedChar == '0'){
			digitalWrite(ledPin, LOW); //끄기
		}
	}
}
```
