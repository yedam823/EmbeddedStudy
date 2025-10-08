### 시리얼 모니터를 이용한 디버깅

시리얼 모니터로 상태 출력 및 변수 값 확인해서 흐름 추적하기

```cpp
void setup(){
	Serial.begin(115200);
	Serial.println("Serial initializing...");
	
	int initValue = initializeSystem();
	Serial.print("initialization Value: ");
	Serial.println(initValue);
}

void loop(){
	int sensorValue = readSensor();
	Serial.print("Sensor Value: ");
	Serial.println(sensorValue);
	
	delay(1000);
}

//시스템 초기화
int initializeSystem(){
	return 42; //임의의 초기화 값 반환
}

//센서 값 읽기
int readSensor(){
	return analogRead(A0);
}
```

### 로깅을 사용한 디버깅

로깅 : 프로그램 실행중 발생하는 이벤트를 기록. SD 카드나 EEPROM 같은 외부 저장 장치로 로그 기록 가능

```cpp
//SD 카드에 로그 기록
#include<SPI.h>
#include<SD.h>

const int chipSelect = 10;

void setup(){
	Serial.begin(115200);
	if(!SD.begin(chipSelect)){
		Serial.println("SD 카드 초기화 실패");
		return;
	}
	Serial.println("SD 카드 초기화 성공");
	
	logEvent("시스템 초기화"); //초기화 로그 기록
}

void loop(){
	int sensorValue = analogRead(A0);
	logEvent("센서 값: " + String(sensorValue));
	delay(1000);
}

void logEvent(String event){
	File logfile = SD.open("log.txt", FILE_WRITE);
	if(logFile){
		logFile.println(logFile);
		logFile.close();
	}else{
		Serial.println("로그 파일을 여는 데 실패");
	}
}
```

### 디버거 사용

프로그램 실행 중단하고 변수 값 확인해가며 단계별로 코드 추적하기

아두이노에서는 Atmel ICE 와 같은 하드웨어 디버거를 사용 가능

### 테스트 자동화

프로그램의 다양한 기능을 자동으로 테스트하는 방법

```cpp
void setup(){
	Serial.begin(115200);
	runTests();
}

void loop(){
	//비워둠
}

void runTests(){
	Serial.println("테스트 운영중...");
	 
	 //테스트1: 초기화 값 검증
	 int initValue = initializeSystem();
	 if(initValue == 42){
		 Serial.println("테스트1 통과");
	 }else{
		 Serial.println("테스트1 실패");
	 }
	 
	 //테스트2: 센서 값 범위 검증
	 int sensorValue = analogRead(A0);
	 if(sensorValue >= 0 && sensorValue <= 1023){
		 Serial.println("테스트2 통과");
	 }else{
		 Serial.println("테스트2 실패");
	 }
}

int initializeSystem(){
	return 42;
}
```

### 하드웨어 인 더 루프(HIL) 테스트

HIL 테스트 : 실제 하드웨어와 시뮬레이션 환경을 조합하여 시스템 동작을 검증하는 방법
