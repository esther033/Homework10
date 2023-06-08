#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

#define MAX_STACK_SIZE	20 //MAX_STACK_SIZE=20
Node* stack[MAX_STACK_SIZE]; //Node 포인터 구조체 stack[20]선언
int top = -1; //top변수 선언후 -1 저장

Node* pop(); //Node 포인터 함수 pop선언
void push(Node* aNode); //push함수 선언

#define MAX_QUEUE_SIZE	20 //MAX_QUEUE_SIZE=20
Node* queue[MAX_QUEUE_SIZE]; //Node 포인터 구조체 queue[20]선언
int front = -1; //front 선언 후 -1저장
int rear = -1; //rear 선언 후 -1 저장

Node* deQueue(); //Node 포인터 함수 deQueue선언s
void enQueue(Node* aNode); //enQueue함수 선언


int initializeBST(Node** h); //노드를 동적할당하여 초기화 하는 함수

void recursiveInorder(Node* ptr);//재귀적 중위순회 함수
void iterativeInorder(Node* node);//반복적 중위순회 함수
void levelOrder(Node* ptr);	//level order 중위순회 함수
int insert(Node* head, int key);//노0드를 삽입하는 함수
int deleteNode(Node* head, int key);//노드를 삭제하는 함수
int freeBST(Node* head); //메모리를 해제하는 함수

void printStack(); //printStack함수 선언



int main()
{
	printf("[----- [박에스더]  [2022041054] -----]\n"); 
	char command; //사용자에게 메뉴를 입력받을 변수
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); 

		switch(command) {//commad의 값에 따라 실행
		case 'z': case 'Z': //command가 z  or Z일때
			initializeBST(&head); //initailizeBST 함수 호출
			break;
		case 'q': case 'Q': //command가 q  or Q일때
			freeBST(head); //freeBST 함수 호출
			break;
		case 'i': case 'I': //command가 i or I일때
			printf("Your Key = "); 
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			insert(head, key); //key를 삽입하는 insert함수 호출
			break;
		case 'd': case 'D': //command가 d  or D일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key를 입력받는다
			deleteNode(head, key); //deleyeNode를 선언하여 key값 삭제
			break;

		case 'r': case 'R': //command가 r  or R일때
			recursiveInorder(head->left); //recursiveInorder함수를 호출하여 재귀적 중위순회 
			break;
		case 't': case 'T': //command가 t  or T일때
			iterativeInorder(head->left); //iterativeInorder함수를 호출하여 반복적 중휘순회
			break;

		case 'l': case 'L': //command가 t  or T일때
			levelOrder(head->left); //levelOrder함수를 호출하여 level order 중위순회
			break;

		case 'p': case 'P': //command가 p  or P일때
			printStack(); //printStack함수 호출
			break;

		default: //command가 위의 값들과 다를때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q or Q일때 반복문 종료

	return 1; //함수 종료
}

int initializeBST(Node** h) {
	if(*h != NULL)//*h가 NULL이 아니면 메모리 해제
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //*h를 동적할당한다
	(*h)->left = NULL;	//h의 멤버 구조체 left에 NULL저장
	(*h)->right = *h; //h의 멤버 구조체 right에 *h 저장
	(*h)->key = -9999; //h의 멤버변수 key에 -9999저장

	top = -1; //top에 -1저장

	front = rear = -1; //front,rear에 -1저장

	return 1; //함수종료
}



void recursiveInorder(Node* ptr)
{
	if(ptr) { //재귀호출을 통해 노드를 왼쪽노드->뿌리-> 오른쪽 노드 순으로 출력한다
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node)
{
	for(;;) //반복문을 사용하여 node의 왼쪽노드->뿌리->오른쪽 노드 순으로 출력
	{
		for(; node; node = node->left)
			push(node);
		node = pop();

		if(!node) break;
		printf(" [%d] ", node->key);

		node = node->right;
	}
}

void levelOrder(Node* ptr)
{

	if(!ptr) return; //tree가 비어있으면 함수 종료

	enQueue(ptr); //enQueue함수를 호출하여 ptr 추가

	for(;;)
	{
		ptr = deQueue(); //ptr에 deQueue()저장
		if(!ptr)  //노드를 레벨에 따라 왼쪽노드 오른쪽 노드 순으로 출력한다
			break;
			printf(" [%d] ", ptr->key);

			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		

	}

}


int insert(Node* head, int key) //노드를 삽입하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node구조체 포인터 newNode 선언후 동적할당
	newNode->key = key; //newNode의 key에 매개변수key값 저장
	newNode->left = NULL; //newNode의 left에 NULL저장
	newNode->right = NULL; //newNode의 right에 NULL저장

	if (head->left == NULL) { //head의 left가 NULL이면
		head->left = newNode; //head의 left에 newNode저장
		return 1; //함수 종료
	}

	Node* ptr = head->left; //Node 구조체 포인터 ptr에 head의 left저장

	Node* parentNode = NULL; //Node 구조체 포인터 parentNode에 NULL저장
	while(ptr != NULL) { //ptr의 key와 매개변수 key가 같을때 함수 종료

		if(ptr->key == key) return 1; //ptr의 key와 매개변수 key가 같을때 함수 종료

		parentNode = ptr; //부모노드에 ptr 저장

		if(ptr->key < key) //ptr의 key보다 매개변수 key가 더 클때
			ptr = ptr->right; //ptr에 ptr의 right저장
		else
			ptr = ptr->left; //ptr에 ptr의 left저장
	}

	if(parentNode->key > key) //부모노드의 key값이 key보다 클때
		parentNode->left = newNode; //부모노드의 left에 newNode 저장
	else
		parentNode->right = newNode; //부모노드의 right에 newNode 저장
	return 1;//함수종료
}


int deleteNode(Node* head, int key) //노드를 삭제하는 함수
{
	if (head == NULL) { //head가 NULL일때
		printf("\n Nothing to delete!!\n"); //삭제할것이 없다
		return -1; //함수종료
	}

	if (head->left == NULL) { //head의 left가 NULL일때
		printf("\n Nothing to delete!!\n"); // 삭제할것이 없다
		return -1;//함수종료
	}

	Node* root = head->left;//Node구조체 포인터 root 선언 후 head의 left저장



	Node* parent = NULL; //Node 구조체 포인터 parent에 NULL저장
	Node* ptr = root; //Node 구조체 포인터 ptr에 root저장

	while((ptr != NULL)&&(ptr->key != key)) { //ptr이 NULL이 아니거나 key가 key가 아닐때
		if(ptr->key != key) { //ptr의 key값이 key값이 아닐때

			parent = ptr;	//parent에 ptr저장

			if(ptr->key > key) //ptr의 key값이 key값보다 클때
				ptr = ptr->left; //ptr에 ptr의 left저장
			else
				ptr = ptr->right; //ptr에 ptr의 right저장
		}
	}

	if(ptr == NULL) //ptr이 NULL일때
	{
		printf("No node for key [%d]\n ", key); //삭제할것이 없다
		return -1;
	}

	if(ptr->left == NULL && ptr->right == NULL) //ptr의left가 NULL이 아니거나 ptr의right가 NULL이 아닐때
	{
		if(parent != NULL) { //parent가 NULL이 아니면
			if(parent->left == ptr) //parent의 left가 ptr과 같을때
				parent->left = NULL; //parent의 left에 NULL저장
			else
				parent->right = NULL; //parent의 right에 NULL저장
		} else {
			head->left = NULL; //head의 left에 NULL저장

		}

		free(ptr); //ptr메모리 해제
		return 1; //함수 종료
	}

	if ((ptr->left == NULL || ptr->right == NULL)) //ptr의 left가 NULL이고 ptr의 right가 NULL일때
	{
		Node* child; //Node 포인터 구조체 child 선언
		if (ptr->left != NULL) //ptr의 left가 NULL이 아닐때
			child = ptr->left; //child에 ptr의 left저장
		else
			child = ptr->right; //child에 ptr의 right저장

		if(parent != NULL) //parent가 NULL이 아닐때
		{
			if(parent->left == ptr) //parent의 left가 ptr과 같을때
				parent->left = child; //parent의 left에 child 저장
			else
				parent->right = child; //parent의 right에 child 저장
		} else {
			root = child; //root에 child 저장
		}

		free(ptr); //ptr메모리 해제
		return 1; //함수종료
	}

	Node* candidate; //Node 포인터 구조체 candidate 선언
	parent = ptr; //parent에 ptr 저장


	candidate = ptr->right; //candidate에 ptr의 right 저장

	while(candidate->left != NULL) //candidate의 left가 NULL일때 까지 반복
	{
		parent = candidate; //parent에 candidate저장
		candidate = candidate->left;//candidate에 candidate의 left 저장
	}


	if (parent->right == candidate) //parent의 right가 candidate와 같을때
		parent->right = candidate->right; //parent의 right에 candidate의 right저장
	else
		parent->left = candidate->right; //parent의 left에 candidate의 right저장

	ptr->key = candidate->key;//ptr의 key에 candidate의 key 저장

	free(candidate); //candidate메모리 해제
	return 1; //함수 종료
}


void freeNode(Node* ptr) 
{
	if(ptr) { //왼쪽노드, 오른쪽노드 뿌리를 메모리 해제하는 함수
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head) 
{

	if(head->left == head) //head의 left와 head가 같을때
	{
		free(head); //head 메모리해제
		return 1; //함수종료
	}

	Node* p = head->left;  //Node 포인터 구조체 p선언 후 head의 left에 저장

	freeNode(p); //p 메모리해제

	free(head); //head 메모리해제
	return 1; //함수종료
}



Node* pop()
{
	if (top < 0) return NULL; //top이 음수면 NULL 리턴
	return stack[top--]; //stack[top--]리턴
}

void push(Node* aNode)
{
	stack[++top] = aNode; //stack[++top]에 aNode 저장
}


void printStack()
{
	int i = 0; 
	printf("--- stack ---\n");
	while(i <= top) //반복문을 사용하여 stack 출력
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue() 
{
	if (front == rear) { //front와 rear과 같을때
		return NULL; //NULL 리턴
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front에 (front + 1) % 20저장
	return queue[front]; // queue[front]리턴

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear에 (rear + 1) % 20 저장
	if (front == rear) { //다차있을때
		return; //함수 종료
	}

	queue[rear] = aNode; //queue[rear] 에 aNode저장
}





