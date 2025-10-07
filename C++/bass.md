### 표준 라이브러리

**`#include <iostream>`**

### 입력과 출력

입력 : `std::cin >>`

출력 : `std::cout <<` “하나 더 붙이면 : ” << “얘도 같이 출력됨”  // 하나 더 붙이면 : 얘도 같이 출력됨 

\n : `<< std::endl`

### 심볼릭

#define로 빔볼릭 만들어서 사용했다가 충돌 일어나면 : constexpr 쓰도록

### 리터럴

유형 결정의 접미사 포함 가능.

u U : unsigned  /  l L : long

### 제어문

C랑 다른게 없다…

**+++** 

```cpp
 for (const auto &element : myArray)
        std::cout << element << ' ';
```

이건 배열 원소 하나하나 꺼내서 세는건데 autp가 타입 추론 하는 역할, const로 변경X 읽기만 하는거

기억해두라고!!!!!1

### 배열

일단 라이브러리 include<array> 추가

`std::array<자료형, 배열크기>배열이름`

이런 형태

함수에서 호출할 떄는 포인터 형변환 안돼서 & 붙여야함(>랑 이름 사이에)
