//맵을 이용

```cpp
#include<iostream>
#include<map>

int main(){
	std::map< std::string, int> student_scores; //맵 생성
	student_scores["natsuki"] = 20; //원소 추가
	student_scores["shin"] = 22;
	student_scores["mahuyu"] = 14;
	student_scores["nagumo"] = 28;
	
	for(const auto&pair : student_scores){ //원소 하나씩 돌리면서 출력
		stdd::cout << pair.first << ": " << pair.second << std::endl;
	}
}
```
