### 메모리 최적화의 중요성

임베디드 시스템은 제한된 메모리 자원을 가지고 있기에 최적화 중요!!

### 데이터 타입 최적화

필요한 경우 int 대신 byte 나 char 같은 작은 데이터 타입 사용

```cpp
//최적화 전
int temperature = 25;
int humidity = 60;

//최적화 후
byte temperature = 25;
byte humidity = 60;
```

### 배열과 문자열 최적화

필요한 경우 정적 배열 대신 동적 메모리 할당을 사용하여 메모리 사용 최적화

```cpp
//문자열 최적화 전
char message[] = "나츠키는 레전드로 잘생긴 남자이다." //수정 가능

//문자열 최적화 후
char *message  = "나츠키 존잘" //수정 불가능(상수)
```

### 동적 메모리 할당

필요한 시점에만 메모리 할당 후 해제 → 매우 효율적

```cpp
void setup(){
	Serial.begin(115200);
	
	char *buffer = (char*)malloc(sizeof(char) * 100); //동적으로 할당
	if(buffer == NULL){ //널이면 할당X 항상 확인 해주기
		Serial.println("메모리 할당 실패");
		return;
	}
	
	strcpy(buffer, "꼬깔콘"); //메모리 사용
	Serial.println(buffer);
	
	free(buffer); //메모리 반납
}

void loop(){
	//여긴 비움
}
```

### 플래시 메모리 사용

프로그램 메모리(플래시 메모리)를 사용하여 상수를 저장함으로써 SRAM 사용 줄임

쓰기 영역이 제한 되어 있기에 실행할 때마다 지우고 사용

```cpp
#include<avr/pgmspace.h>

//플래시 메모리에 문자열 '직접'저장
const char message[] PROGMEM = "애니보고싶다";

void setup(){
	Serial.begin(115200);
	
	//플래시 메모리에서 문자열 읽기
	char buffer[20];
	strcpy_P(buffer, message);
	Serial.println(buffer);
}

void loop(){
 //메인루프 비워둠
}
```

> 사용하는 상황
> 

프로그램 코드 저장(MCU 부팅 시에 실행될 펌웨어 저장)

설정값, 사용자 데이터 저장(와이파이 SSID, 교정값 등)

펌웨어 업데이트

### 메모리 풀(Memory Pool) 사용

메모리 풀 : 고정된 크기의 메모리 블록을 미리 할당해두고, 필요할 때 쓰고 반환

→ 메모리 할당 및 해제 오버헤드 줄임(왔다갔다 많이해서 생김), 메모리 파편화 방지(너무 자잘해져서 큰게X)

```cpp
#include<Arduino.h>

#define POOL_SIZE 10
#define BLOCK_SIZE 32

uint8_t memoryPool[POOL_SIZE][BLOCK_SIZE];
bool blockUsed[POOL_SIZE] = { false };

//메모리 블록 할당 함수
void* allocateBlock(){
	for(int i=0; i< POOL_SIZE; i++){
		if(!blockUsed[i]){ //비어있으면
			blockUsed[i] = true;
			return (void*)memoryPool[i];
		}
	}
	retrun NULL; //사용 가능한 블록X
}

//메모리 블록 해제 함수
void freeBlock(void* block){
	for(int i=0; i<POOL_SIZE; i++){
		if(memoryPool[i] == block){ //사용한 블록이면
			blockUsed[i] = false; //해제
			return;
		}
	}
}

void setup(){
	Serial.begin(115200);
	
	uint8_t* block1 = (uint8_t*)allocateBlock(); //메모리 블록 할당
	if(block1 != NULL){
		strcpy((char*)block1, "메모리 풀 사용"); //사용
		Serial.println(block1);
		freeBlock(block1); //해제
	} else{
		Serial.println("메모리 할당 실패");
	}
}

void loop(){
	 //비워둠
}
```
