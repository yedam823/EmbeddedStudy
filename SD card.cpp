### SD카드에 데이터 저장 구현

1. SD카드 모듈 연결
- VCC : 5V
- GND : GND
- MOSI : 11
- MISO : 12
- SCK : 13
- CS : 10
1. SD 라이브러리 설치

```cpp
#include<SPI.h>
#include<SD.h>

const int csPin = 10; //chip Select 핀

void setup(){
	Serial.begin(9600);
	if(!SD.begin(csPin)){
		Serial.println("SD card initialization failed!");
		return;
	}
	Serial.println("SD card initialized.");
}

void loop(){
	File dataFile = SD.open("data.txt", FILE_WRITE);
	
	if(dataFile){
		dataFile.println("HELLO, SD card!"); //데이터 저장
		dataFile.close();
		Serial.println("Data written to file");
	}else{
		Serial.println("Error opening file");
	}
	
	delay(1000);
}
```
