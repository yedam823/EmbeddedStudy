빠른 데이터 전송속도를 제공하는 동기식 직렬 통신 방식. 주로 센서, 디스플레이, 메모리 같은 장치와 MCU 간의 데이터 전송에 사용됨

### SPI 통신

1. 마스터 - 슬레이브 구조 : 하나의 마스터와 여러개의 슬레이브
2. 4개의 신호라인
    1. MOSI : 마스터 → 슬레이브
    2. MISO : 슬레이브 → 마스터
    3. SCK :  클럭 신호
    4. SS : 슬레이브 선택 신호

### 설정

1. 아두이노 1 (마스터)
- MOSI : 2의 MOSI 핀에 연결
- MISO : 2의 MISO 핀에 연결
- SCK :  2의 SCK 핀에 연결
- SS : 2의 SS 핀에 연결
- GND : 2의 GND 핀에 연결
1. 아두이노 2 (슬레이브)
- MOSI : 1의 MOSI 핀에 연결
- MISO : 1의 MISO 핀에 연결
- SCK :  1의 SCK 핀에 연결
- SS : 1의 SS 핀에 연결
- GND : 1의 GND 핀에 연결

<aside>

마스터 코드

```cpp
#include<SPI.h>

const int ssPin = 10; //Slave Select 핀

void setup(){
	Serial.begin(9600);
	pinMode(ssPin, OUTPUT);
	SPI.begin(); //마스터 시작
}

void loop(){
	digitalWrite(ssPin, LOW); //슬레이브 선택
	SPI.transfer("카게야마 귀여웡"); //데이터 송신
	digitalWrite(ssPin, HIGH); //슬레이브 선택 해제
	delay(1000);
}
```

슬레이브 코드

```cpp
#include<SPI.h>

volatile boolean received = false;
char data;

void setup(){
	Serial.begin(9600);
	pintMode(MISO, OUTPUT);
	SPI.attachInterrupt();
	SPI.begin();
}

ISR(SPI_STC_vect){
	data = SRDR; //수신된 데이터 읽기
	received = true; //수신 플래그 설정
}

void loop(){
	if(received){
		Serial.print("received: ");
		Serial.println(data); //수신된 데이터 출력
		received = false; //플래그 재설정
	}
}
```

</aside>
