#UART
---
직렬통신의 한 형태로, 널리 쓰이는 통신 방식. MCU 간의 데이터 송수신이 가능함

### 특징

1. 비동기 통신 : 송신, 수신기 간에 클럭신호가 필요X
2. 시작비트와 정지비트 : 데이터 프레임의 시작과 끝을 표시
3. 패리티 비트 : 오류 검출을 위해 추가되는 비트

### 설정

- Baud rate : 9600
- Data bits : 8
- Parity : None
- Stop bits : 1

### 기본 UART 통신

```cpp
void setup(){
	if(Serial.available()>0){ //수신된 데이터가 있는지 확인
		char receivedChar = Serial.read(); //수신된 데이터 읽기
		Serial.print("받은 거: ");
		Serial.println(receivedChar);
	}
	
	Serial.println("Hello UART!!!!!!!!!");
	delay(1000);
}
```

### 두 아두이노 간의 통신

하나의 보드는 데이터 송신, 또다른 하나는 데이터를 수신함

> 하드웨어 연결
> 
1. Arduino1 (송신기)
- TX 핀 : 2의 RX핀에 연결
- GND : 2의 GND 핀에 연결
1. ARduino2(수신기)
- RX : 1의 TX핀에 연결
- GND : 1의 GND핀에 연결

<aside>

송신기 코드

```cpp
void setup(){
	Serial.begin(9600);
}

void loop(){
	Serial.println("세바 나츠키 짱"); //얘가 송신해서
	delay(1000);
}
```

---

수신기 코드

```cpp
void setup(){
	Serial.begin(9600);
}

void loop(){
	if(Serial.available()>0){
		String receivedData = Serial.readString();
		Serial.print("받은 것: ");
		Serial.println(receivedData); //여기서 시리얼 출력
	}
}
```

</aside>

### 소프트웨어 시리얼

하드웨어 시리얼 포트가 부족한 경우, 이걸 이용해서 추가적인 시리얼 포트 생성 가능
