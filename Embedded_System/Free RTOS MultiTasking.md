### 주요기능

- 태스크 관리 : 여러 개의 태스크 생성 및 스케줄링
- 태스크 간 통신 : 큐, 세마포어, 뮤텍스를 사용하여 태스크 간 데이터를 주고받고 동기화
- 타이머 : 주기적으로 실행되는 타이머 기능

### 큐를 사용한 태스크 통신

큐는 FIFO 저장방식이기에 한 태스크에서 데이터를 큐에 넣고 다른 태스크에서 꺼내쓸 수 있음

```cpp
#include<Arduino_FreeRTOS.h>
#include<queue.h>

QueueHandle_t xQueue;

void TaskSender(void *pvParams);
void TaskReceiver(void *pvParams);

void setup(){
	Serial.begin(115200);
	
	//큐 생성
	xQueue = xQueueCreate(10, sizeof(int));
	
	//태스크 생성
	xTaskCreate(TaskSender, "Sender", 128, NULL, 1, NULL);
	xTaskCreate(TaskReceiver, "Receiver", 128, NULL, 1, NULL);
	
	vTaskStartScheduler(); //스케줄러 시작
}

void loop(){
	//메인 비워둠
}

void Sender(void *pvParams){
	(void)pvParams;
	int valueToSend = 0;
	
	for(;;){
		valueToSend++;
		xQueueSend(xQueue, &valueToSend, portMAX_DELAY); //데이터 보내기
		Serial.print("Send: ");
		Serial.println(valueToSend);
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}

void Receiver(void *pvParams){
	(void)pvParams;
	int receivedValue = 0;
	
	for(;;){
		if(xQueueReceive(xQueue, &receivedValue, portMAX_DELAY)){ //받은게 있으면
			Serial.print("Received: ");
			Serial.println(receivedValue);
			vTaskDelay(500 / portTICK_PERIOD_MS);
		}
	}
}
```

### 태스크 간 동기화

세마포어나 뮤텍스를 이용해 동기화를 한다.

세마포어 : 공유 자원을 누가 쓸수있는지 허용/제어하는 도구

여러 태스크가 동시에 같은 자원 쓰면 꼬일 수 있으니 한번에 하나만 쓸수있도록 제어하는 거(이진 세마포어)

뮤텍스도 세마포어의 일종이고, 소유권을 가짐

```cpp
#include<Arduino_FreeRTOS.h>
#include<semphr.h>

SemaphoreHandle_t xSemphr;

void Task1(void *pvParams);
void Task1(void *pvParams);

void setup(){
	Serial.begin(115200);
	
	//세마포어 생성
	xSemphr = xSemaphoreCreateBinary();
	
	//태스크 생성
	xTaskCreate(Task1, "Task1", 128, NULL, 1, NULL);
	xTaskCreate(Task2,"Task2", 128, NULL, 1, NULL);
	
	vTaskStartScheduler(); //스케줄러 시작
}

void loop(){
	//메인 비워둠
}

void Task1(void *pvParams){
	(void) pvParams;
	
	for(;;){
		Serial.println("Task1 running");
		xSemaphoreGive(xSemphr); //세마포어 배치
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Task2(void *pvParams){
	(void) pvParams;
	
	for(;;){
		if(xSemaphoreTake(xSemphr, portMAX_DELAY)){ //세마포어를 얻으면 동작
			Serial.println("Task2 is Running");
		}
	}
}

```

### 타이머를 사용한 주기적 작업

콜백 함수로 주기적으로 깜빡거리는 LED(임베에서 콜백보니까 반갑다)

```cpp
#include<Arduino_FreeRTOS.h>
#include<timers.h>

const int ledPin = 13;
timerHandle_t xTimer; //타이머 변수

void vTimerCallback(timerHandle_t xTimer);

void setup(){
	pinMode(ledPin, OUTPUT);
	Serial.begin(115200);
	
	//타이머 생성(500ms 주기)
	xTimer = xTimerCreate("LEDTimer", pdMS_TO_TICK(500), pdTRUE, (void*)0, vTimerCallback);
	
	//타이머 시작
	if(xTimerStart(xTimer, 0) != pdPASS){
		Serial.println("Failed to start Timer");
	}
	
	//스케줄러 시작
	vTaskStartScheduler();
}

void loop(){
	//메인 루프 비워둠
}

void vTimerCallback(timerHandle_t xTimer){
	static bool ledState = false;
	ledState = !ledState;
	digitalWrite(ledPin, ledState ? HIGH : LOW);
}
```
