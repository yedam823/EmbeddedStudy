#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node* right;
	struct Node* left;
}Node;

Node* makeNode(int data);
Node* insertNode(Node* root, int data);
Node* searchNode(Node* root, int data);
Node* deleteNode(Node* root, int data);
Node* minValue(Node* root);
Node* findParent(Node* root, int data);


Node* makeNode(int data) {
	Node* newRoot = (Node*)malloc(sizeof(Node));
	newRoot->data = data;
	newRoot->left = NULL;
	newRoot->right = NULL;
	return newRoot;
}

Node* insertNode(Node* root, int data) {
	if (root == NULL) { 
		return makeNode(data);
	}
	Node* tempNode = root;

	//작은 값부터 채워넣기
	if (tempNode->data > data) {
		tempNode->left = insertNode(tempNode->left, data); //재귀로 연결 시키기
	}
	//큰값
	else if (tempNode->data < data) {
		tempNode->right = insertNode(tempNode->right, data);
	}

	return root;
}

Node* searchNode(Node* root, int data) {
	if (root == NULL) {
		printf("값을 찾지 못했습니다.\n");
		return NULL; //재귀하다가 값 못찾으면 NULL반환
	}
	Node* tempNode = root;
	if (data == tempNode->data) {
		printf("값 찾기 성공\n");
		return tempNode; //찾으면 반환
	}
	else if (data < tempNode->data) {
		return searchNode(tempNode->left, data); 
	}
	else {
		return searchNode(tempNode->right, data);
	}
}

Node* deleteNode(Node* root, int data) {
	if (root == NULL) return NULL;
	Node* delNode = root;

	//원하는 노드를 찾는 과정, 찾으면 else로 분류되어 저 값에 들어가게 됨(재귀, 연결)
	if (data < delNode->data) {
		delNode->left = deleteNode(delNode->left, data); //값 지우고 찾은 자식의 값이 대입됨
	}
	else if (data > delNode->data) {
		delNode->right = deleteNode(delNode->right, data);
	}
	else {
		//노드를 찾았을 때만 실행되는
		if (delNode->left == NULL) { //왼쪽이 없을 때
			Node* temp = delNode->right; //temp 오른쪽 가리킴
			free(delNode);
			return temp;
		}
		else if (delNode->right == NULL) {
			Node* temp = delNode->left;
			free(delNode);
			return temp;
		}
		else { //자식이 두쪽 다 있을 때
			Node* minNode = minValue(delNode->right);
			delNode->data = minNode->data;
			delNode->right = deleteNode(delNode->right, minNode->data);
		}
	}
	return root; //그리고 처음 반환
}


//오른쪽 노드에서 가장 작은 값 찾기
Node* minValue(Node* root) { 
	Node* current = root;

	while (current != NULL && current->left != NULL) { //왼쪽 값이 없으면 그값이 가장 작은 값
		current = current->left;
	}
	return current;
}

//현재 노드의 부모 찾기
Node* findParent(Node* root, int data) {
	if (root == NULL || root->data == data) {
		return NULL;
	}
	Node* parent = NULL;
	Node* current = root;

	while (current != NULL && current->data != data) { //값을 찾기 전까지만 반복
		parent = current; //현재 값을 부모에 대입
		if (data < current->data) { 
			current = current->left; //현재 값을 변화시킴
		}
		else {
			current = current->right;
		}
	}
	
	return parent; //부모 반환
}
