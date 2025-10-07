차량 내부의 여러 전자 제어 장치 간의 데이터 통신을 위해 개발된 직렬 통신 프로토콜

높은 신뢰성과 빠른 데이터 전송 속도 제공→자동차, 산업 자동화, 의료 기기 등에서 널리 사용

### 기본 개념

- 멀티 마스터/슬레이브 구조
- 메세지 프로토콜 : 각 메세지는 고유의 식별자(ID)를 가지며, 네트워크 상의 모든 장치가 메세지 수신 가능
- 고속 데이터 전송
- 오류 검출 처리

### CAN 통신

1. 아두이노 1 (송신기)
- VCC : 5V
- GND : GND
- CS : 10번 핀
- SO : 12번 핀
- SI : 11번 핀
- SCK : 13번 핀
- CANH : 2의 CANH에 연결
- CANL : 2의 CANL에 연결
1. 아두이노 2 (수신기)
- VCC : 5V
- GND : GND
- CS : 10번 핀
- SO : 12번 핀
- SI : 11번 핀
- SCK : 13번 핀
- CANH : 1의 CANH에 연결
- CANL : 1의 CANL에 연결

### MCP_CAN 라이브러리 설치

<aside>

송신기 코드

```cpp
#include<SPI.h>
#include<mcp_can.h> // MCP2515 CAN BUS 전용 라이브러리

const int SPI_CS_PIN = 10; //Cihp Select 핀 설정
MCP_CAN CAN(SPI_CS_PIN); //MCP_CAN 객체 생성

void setup(){
	Serial.begin(115200);
	// CAN 초기화: (모드, 속도, 클럭)
  // MCP_ANY : 어떤 필터 모드든 수신 가능
  // CAN_500KBPS : CAN 통신 속도 500 kbps
  // MCP_8MHZ : MCP2515 크리스탈 클럭 주파수 8MHz
	if(CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK){
		Serial.println("CAN BUS Shield init OK!"); //성공 시 메세지 출력
	}else{
		Serial.println("CAN BUS Shield init fail");
		while(1); //무한 루프 -> 프로그램 멈춤
	}
	CAN.setMode(MCP_NORMAL); // CAN모드를 노멀 모드로 설정
}

void loop(){
	byte data[8] = {'H', 'e', 'l', 'l', 'o', '!', ' ', ' '}; //송신할 데이터 배열
	// CAN 메시지 전송
  // 매개변수: (메시지 ID, RTR(원격 전송 요청), 데이터 길이, 데이터 배열)
  // 0x00  → CAN 메시지 ID (식별자)
  // 0     → 데이터 프레임(일반 메시지)임을 의미 (1이면 RTR 모드)
  // 8     → 데이터 길이
  // data  → 데이터 버퍼
	CAN.sendMsgBuf(0x00, 0, 8, data);
	Serial.println("Message sent: Hello!");
	delay(1000);
}
```

수신기 코드

```cpp
#include<SPI.h>
#include<mcp_can.h>

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

void setup(){
	Serial.begin(115200);
	if(CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK){
		Serial.println("CAN BUS Shield init OK!");
	}else{
		Serial.println("CAN BUS Shield init fail");
		while(1);
	}
	CAN.setMode(MCP_NORMAL);
}

void loop(){
	unsigned char len = 0; //수신한 데이터 길이 저장
	unsigned char buf[8]; //수신한 데이터 저장
	
	if(CAN_MSGAVAIL == CAN.checkReceive()){ //도착 했는지 확인
		CAN.readMsgBuf(&len, buf); //메세지 읽어서 buf에 저장, 길이는 len에 저장
		Serial.print("Message received: ");
		for(int i=0;i<len;i++){
			Serial.print((char)buf[i]); //문자로 변환해 출력
		}
		Serial.println();
	}
}
```

</aside>
