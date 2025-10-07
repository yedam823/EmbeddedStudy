강아지가 시스템을 지켜용!

시스템을 감지하는 타이머이다.

CPU가 이상이 생기면 얘가 리셋시켜 정신차릴 수 있게 하는 구조

(무한루프나 통신 멈추거나 EMI에 의해 오작동 할때)

CPU가 켜질때 같이 켜지고, 일정 시간이 지나 타임아웃이 되면 MCU는 자동으로 리셋됨

만약 CPU가 문제없이 잘 돌아간다? 반대로 강아지한테 먹이(리셋)을 줘야함

이걸 킥한다, 클리어한다 라고 표현함

### AVR에서의 워치독

여기엔 WDT 라는 하드웨어 모듈이 내장되어 있음

- **WDTCSR** : 워치독 설정 레지스터
- **WDE** : 워치독을 켜는 비트
- **WDPx** : 타임아웃 시간을 설정하는 비트들

```cpp
#include <avr/wdt.h>

void setup() {
  wdt_enable(WDTO_2S);  // 2초 타임아웃 설정
}

void loop() {
//정상 동작
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);

  // 워치독 리셋
  wdt_reset();
}
```
