I2C

두개이상의 장치가 송수신 할 수 있도록 하는 직렬통신 방식

SDA(데이터), SCL(클럭) 두개의 라인을 사용하여 여러 장치를 연결할 수 있으며, 하나의 마스터와 여러 슬레이브 간의 통신을 지원함

### 기본개념

- 멀티마스터/슬레이브 구조 : 하나의 마스터와 여러 슬레이브 장치 간의 통신을 지원
- 2개의 와이어 사용 : SDA, SCL를 사용
- 주소 지정 : 각 슬레이브는 고유한 주소를 가지며, 마스터는 주소를 통해 특정 슬레이브와 통신함

### 통신 설정

SDA, SCL 설정 후슬레이브 장치의 주소 알기

아두이노에서는 Wire, ESP-idf 에서는 driver/i2c 사용

### I2C LCD

LiquidCrystal_I2C 라이브러리 설치

```cpp
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // lcd 주소와 크기 설정

void setup(){
	lcd.begin(16, 2); //lcd 초기화 (16x2크기)
	lcd.print("HELLO NATSUKI..!!!!!");
}

void loop(){
	//메인 루프 비워둠
}
```

---

### 두 아두이노 간의 통신

> 하드웨어 연결
> 
1. 아두이노1 (마스터)
- SDA : 2의 SDA핀에 연결
- SCL : 2의 SCL핀에 연결
- GND : 2의 GND핀에 연결
1. 아두이노2 (슬레이브)
- SDA : 1의 SDA핀에 연결
- SCL : 1의 SCL핀에 연결
- GND : 1의 GND핀에 연결

<aside>

마스터 코드

```cpp
#include<Wire.h>

void setup(){
	Wire.begin(); //I2C 마스터 시작
	Serial.begin(9600);
}

void loop(){
	Wire.beginTransmission(8); //슬레이브 주소 8
	Wire.write("마스터가 말합니다. 나츠키는 짱"); //데이터 송신
	Wire.endTransmission(); //전송 끝
	delay(1000);
}
```

---

슬레이브 코드

```cpp
#include<Wire.h>

void setup(){
	Wire.begin(8); //I2C 슬레이브 시작(주소: 8)
	Wire.onReceive(receiveEvent); //데이터 수신 이벤트 핸들러 설정
	Serial.begin(9600);
}

void loop(){
	delay(1000);
}

//데이터 수신 이벤트 핸들러
void receiveEvent(int howMany){
	while(Wire.available){
		char c = Wire.read(); // 수신된 데이터 읽기
		Serial.print(c); //데이터 출력
	}
	Serial.println();
}
```

</aside>
