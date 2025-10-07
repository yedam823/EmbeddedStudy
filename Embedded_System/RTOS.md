일정한 시간 내에 작업을 수행할 수 있도록 보장하는 시스템

### 기본 개념

- 실시간 성능 : 정해진 시간 내에 완료할 수 있도록 보장
- 멀티 태스킹 : 여러 작업 동시 실행
- 우선순위 스케줄링 : 우선 순위에 따라 작업 실행 순서 결정
- 자원 관리 : 메모리, CPU 등 시스템 자원 효율적이게 관리

### FreeRTOS

오픈소스 실시간 운영체제, 작은 메모리 풋프린트(자원 크기)와 유연한 스케줄링 기능 제공

아두이노에서는 FreeRTOS라이브러리, ESP-idf에선 freertos/FreeRTOS 헤더파일

```cpp
#include<Arduino_FreeRTOS.h>

void TaskBlink(void *pvParams);
void TaskPrint(void *pvParams);

const int ledPin = 13;

void setup(){
	pinMode(ledPin, OUTPUT);
	Serial.begin(9600);
	
	//태스크 생성
	xTaskCreate(TaskBlink, "Blink", 128, NULL, 1, NULL);
	xTaskCreate(TaskPrint, "Print", 128, NULL, 1, NULL);
	
	vTaskStartScheduler(); //스케줄러 시작
}

void loop(){
	//메인 루프 비워둠
}

void TaskBlink(void *pvParams){
	(void)pvParams;
	for(;;){
		digitalWrite(ledPin, HIGH);
		vTaskDelay(500 / portTICK_PERIOD_MS);
		digitalWrite(ledPin, LOW);
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}

void TaskPrint(void *pvParams){
	(void)pvParams;
	for(;;){
		Serial.println("태스크프린트");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
```
