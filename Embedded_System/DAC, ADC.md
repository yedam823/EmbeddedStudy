## 1. ADC(아날로그→디지털)

연속적인 아날로그 신호를 디지털 값으로 변환

TMP36 센서를 사용하여 온도를 측정하고 시리얼 모니터에 출력

```cpp
const int tempPin = A0;

void setup(){
	Serial.begin(9600);
}

void loop(){
	int analogValue = analogRead(TempPin); //아날로그 값 읽기
	float voltage = analogValue * (5.0/1023.0); //전압으로 변환
	float temperatureC = (voltage - 0.5) * 100.0; //온도로 변환
	Serial.print("Temperature: ");
	Serial.print(temperatureC);
	Serial.println(" C");
	delay(1000);
}
```

## 2. DAC(디지털→아날로그)

디지털값을 아날로그 값으로 변환, 오디오 신호 출력, 아날로그 센서 신호 생성 등에 사용

외부 DAC칩을 이용하여 기능 구현 가능

> MCP4725
> 

I2C 인터페이스를 사용하는 12비트 DAC임

```cpp
#include<Wire.h>
#include<Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

void setup(){
	Serial.begin(9600);
	dac.degin(0x60); //I2C 주소가 0x60인 MCP4725 초기화
}

void loop(){
	for(uint16_t i=0; i<4096; i++){
		dac.setVoltage(i, false); //디지털값을 아날로그 출력으로 설정
		delay(10);
	}
	delay(1000);
}
```
