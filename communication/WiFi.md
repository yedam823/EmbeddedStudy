무선 네트워크 기술. 인터넷 연결 혹은 장치 간에 데이터를 무선으로 송수신 가능

### 기본 개념

ESP8266 :  wifi 모듈, 자체적으로 마이크로 컨트롤러 기능을 해 독립적으로 동작 가능

아두이노에서는 보드 매니저 열어서 esp8266 깔기

### WiFi 연결

<aside>

WiFi 네트워크에 연결하고 IP 주소를 시리얼 모니터에 출력하는 코드

```cpp
#include<ESP8266WiFi.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";

void setup(){
	Serial.begin(115200);
	delay(10);
	
	//와이파이 연결 시작
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	
	WiFi.begin(ssid, password);
	
	while(WiFi.status() != WL_CONNECTED){
		delay(500);
		Serial.print(".");
	}
	
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.print("IP주소: ");
	Serial.println(WiFi.localIP());
}

void loop(){
	//메인은 비워둠
}
```

</aside>
