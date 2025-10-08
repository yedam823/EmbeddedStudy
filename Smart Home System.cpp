//- 센서 : 온도, 조도
// 액추에이터: LED, 릴레이
// 통신 모듈: WiFi
// 컨트롤러: ESP8266

#include<DHT.h>
#include<ESP8266wiFi.h>
#include<ESP8266WebServer.h>

//와이파이 설정
const char *SSID = "SSID";
const char *PASSWORD = "PASSWORD";

//핀설정
const int ledPin = 12; //LED 핀
const int relayPin = 13; //릴레이 핀

//DHT 설정
#define DHTPIN 2 //DHT 데이터 핀
#define DHTTYPE DHT22 //데이터 타입
DHT dht(DHTPIN, DHTTYPE);

ESP8266WebServer server(80);

void setup(){
	Serial.begin(115200);
	setupWiFi();
	pinMode(ledPin, OUTPUT);
	pinMode(relayPin, OUTPUT);
	dht.begin();
	
	//웹서버 핸들러 수정
	server.on("/", handleRoot);
	server.on("/toggleLED", handleToggleLED);
	server.on("/toggleRelay", handleToggleRelay);
	server.begin();
	Serial.println("http 서버 시작");
}

void loop(){
	server.handleClient(); //클라이언트 요청 처리
}

void handleRoot(){
	//센서 데이터 읽기
	float humidity = readHumidity();
	float temperature = readTemperature();
	int ldr = analogRead(A0);
	
	if(isnan(humidity) || isnan(temperature)){ //센서값이 들어오지 않으면
		Serial.println("DHT 센서 값을 읽지 못했습니다.");
		return;
	}
	
	String html = "<html><body>";
	html += "<h1>Smart Home System</h1>";
	html += "<p>습도 : " + String(humidity)+ " %</p>";
	html += "<p>온도 : " + String(temperature) + "*C</p>";
	html += "<p>조도 : " + String(ldr) + "</p>";
	html += "<p><a href=\"/toggleLED\">Toggle LED</a></p>";
	html += "<p><a href=\"/toggleRelay\">Toggle Relay</a></p>";
	html += "</body></html>";
	
	server.send(200, "text/html, html");
}

void handleToggleLED(){
	static bool ledState = false;
	ledState = !ledState;
	digitalWrite(ledPin, ledState ? HIGH : LOW);
	server.sendHeader("Location", "/");
	server.send(303);
}

void handleToggleRelay(){
	static bool relayState = false;
	relayState = !relayState;
	digitalWrite(relayPin, relayState ? HIGH : LOW);
	server.sendHeader("Location", "/");
	server.send(303);
}


void setupWiFi(){
	delay(10);
	
	Serial.println();
	Serial.println();
	Serial.print("연결할 와이파이: ");
	Serial.println(SSID);
	
	WiFi.begin(SSID, PASSWORD);
	
	while(WiFi.status() != WL_CONNECTED){ //연결 될때까지
		delay(10);
		println(".");
	}
	
	Serial.println("");
	Serial.println("WiFi 연결되었습니다.");
	Serial.print("ip 주소: ");
	Serial.println(WiFi.localIP()); //ip주소 출력
}
