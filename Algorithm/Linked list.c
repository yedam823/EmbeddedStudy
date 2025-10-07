#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	Node* next;
}Node;

//헤드 만들기
Node* makeHead() {
	Node* Head = (Node*)malloc(sizeof(Node));
	if (!Head) {
		printf("메모리 할당 실패ㅠ");
		return;
	}
	Head->data = 0;
	Head->next = NULL;
	return Head;
}


//노드 추가하는 코드
Node* InsertNode(Node *Head, int index, int data) {
	int idx = index;
	Node* preNode = Head;
	Node* insertNode = (Node*)malloc(sizeof(Node));
	insertNode->data = data;
	insertNode->next = NULL;

	if (idx == 0) {
		insertNode->next = Head;
		return insertNode;
	}

	for (int i = 0; i < idx - 1 && preNode != NULL; i++) {
		preNode = preNode->next;

		if (preNode == NULL) {
			free(insertNode);
			return Head;
		}
	}
	insertNode->next = preNode->next;
	preNode->next = insertNode;
	return Head;
}

//노드 지우기
Node* DeleteNode(Node* Head, int index) {
	Node* preNode = Head;
	Node* deleteNode = NULL;

	if (index <= 0) {
		deleteNode = Head;
		Head = Head->next;
		free(deleteNode);
		return Head;
	}

	for (int i = 0; i < index - 1 && preNode != NULL; i++) {
		preNode = preNode->next;

		if (preNode == NULL) {
			printf("삭제할 노드가 없습니다");
			return Head;
		}
	}

	deleteNode = preNode->next;
	preNode->next = deleteNode->next;
	free(deleteNode);

	return Head;
}

//이 값, 어디 인덱스에 이써요? 물음에 답하는 서치함수
int searchIdx(Node* Head, int data) {
	int index = 0;
	Node* tempNode = Head;
	while (tempNode->data != data) {
		index++;
		tempNode = tempNode->next;
		if (tempNode == NULL) {
			printf("찾고자 하는 데이터가 없습니다.");
			return -1;
		}
	 }

	return index; //요 인덱스에 이써요^^
}

//이 인덱스, 무슨 값이에용? 물음에 답하는 서치함수
int searchData(Node* Head, int index) {
	Node* tempNode = Head;

	for (int i = 0; i < index && tempNode != NULL; i++) {
		tempNode = tempNode->next;

		if (tempNode == NULL) {
			printf("찾고자 하는 데이터가 없습니다.");
			return -1;
		}
	}
	return tempNode->data;
}

//리스트의 길이, 노드의 개수를 반환하는 함수
int Size(Node* Head) {
	Node* tempNode = Head;
	int index = 0;
	
	while (tempNode != NULL) {
		index++;
		tempNode = tempNode->next;
	}

	return index;
}

int main() {
	//이정도면 됐겠지
}
