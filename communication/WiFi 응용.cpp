//간단한 웹서버 만들어서 LED제어

#include<ESP8266WiFi.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";
const int ledPin = 2;

WiFiServer server(80); //포트번호 80

void setup(){
	Serial.begin(115200);
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
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
	
	server.begin(); //웹서버 시작
}

void loop(){
	WiFiClient client = server.available(); //클라이언트 연결 확인
	if(client){ //클라이언트가 유효하면
		Serial.println("New Client!");
		String currentLine = ""; //현재 수신중인 요청라인, HTTP요청은 문자 단위로 전달->한줄씩 찾아서 처리
		while(client.connected()){
			if(client.available()){ //보낸 데이터가 있으면
				char c = client.read(); //한 문자 읽기
				Serial.write(c); //데이터 출력, 다른 장치와 통신할 때 주로 이용
				if(c == '\n'){
					if(currentLine.length() == 0){
						//HTTP요청 처리, 빈줄 -> HTTP 헤더 끝 -> 서버 응답 전송
						client.println("HTTP/1.1 200 OK");
						client.println("Content-Type: text/html"); //헤더
						client.println();
						//본문
						client.print("Click <a href=\"/LED=ON\">here</a> to turn the LED on. <br>");
						client.print("Click <a href=\"/LED=OFF\">here</a> to turn the LED off. <br>");
						client.println();
						break;
					}else{
						currentLine = "";
					}
				}else if(c != '\r'){
					currentLine += c; //현재 줄에 문자 추가
				}
				
				if(currentLine.endsWith("GET /LED=ON")){ //URL 확인 후 led 제어 
					digitalWrite(ledPin, HIGH);
				}
				if(currentLine.endsWith("GET /LED=OFF")){
					digitalWrite(ledPin, LOW);
				}
			}
		}
		client.stop();
		Serial.println("Client Disconnected");
	}
}
```
