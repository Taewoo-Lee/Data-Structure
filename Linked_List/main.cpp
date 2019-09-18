#include <stdio.h>
#include <stdlib.h>

typedef struct _linked_list_node {
	int data;
	struct _linked_list_node * link;
} LINKED_LIST_NODE;

typedef LINKED_LIST_NODE* LINKED_LIST_NODE_PTR;
typedef LINKED_LIST_NODE_PTR LINKEDLIST_HEAD;

typedef LINKEDLIST_HEAD* LINKEDLIST_HEAD_PTR;

LINKEDLIST_HEAD head = NULL;

// ���ο� ��� ����
// ��ȯ�� : ������ ����� ������
LINKED_LIST_NODE_PTR newNode(int data);

// ��� ����
// ��ȯ�� : ���� ��Ʈ�� ��� �ִ� ��
int deleteNode(LINKED_LIST_NODE_PTR prevNode);

// ����Ʈ�� ������ ���
// ��ȯ�� : ������ ����� ������
LINKED_LIST_NODE_PTR getLastNode(LINKEDLIST_HEAD_PTR H);

// ������ ����� ���� ���
// ��ȯ�� : ������ ����� ���� ����� ������
LINKED_LIST_NODE_PTR getPrevNodeOfLastNode(LINKEDLIST_HEAD_PTR H);

// Ư������� ���� ���
// ��ȯ�� : Ư������� ���� ����� ������
LINKED_LIST_NODE_PTR getPrevNode(LINKEDLIST_HEAD_PTR H, LINKED_LIST_NODE_PTR itNode);

// data �� ���� ���
// ��ȯ�� : data �� ���� ���, ������ NULL
LINKED_LIST_NODE_PTR getNode(LINKEDLIST_HEAD_PTR H, int data);

// ����Ʈ �������� ��Ʈ �߰�
void addNode(LINKEDLIST_HEAD_PTR H, int data);

// Ư�����(prevNode) ������ ��Ʈ �߰�
void additNode(LINKED_LIST_NODE_PTR prevNode, int data);

// ����Ʈ �������� ��Ʈ ����
// ��ȯ�� : ���� ��Ʈ�� ��� �ִ� ��
int removeNode(LINKEDLIST_HEAD_PTR H);

// Ư����� ����
// ��ȯ�� : ���� ��Ʈ�� ��� �ִ� ��
int removeitNode(LINKEDLIST_HEAD_PTR H, LINKED_LIST_NODE_PTR itNode);


LINKED_LIST_NODE_PTR newNode(int data)
{
	LINKED_LIST_NODE_PTR newnode = (LINKED_LIST_NODE_PTR)malloc(sizeof(LINKED_LIST_NODE));
	newnode->data = data;
	newnode->link = NULL;
	return newnode;
}

int deleteNode(LINKED_LIST_NODE_PTR prevNode)
{
	int data = prevNode->data;
	free(prevNode);
	return data;
}

LINKED_LIST_NODE_PTR getLastNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR lastNode = *H;

	if (lastNode != NULL)
		while (lastNode->link != NULL)
			lastNode = lastNode->link;

	return lastNode;
}

LINKED_LIST_NODE_PTR getPrevNodeOfLastNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR prevNode = *H;

	if (prevNode != NULL && prevNode->link != NULL)
		while (prevNode->link->link != NULL)
			prevNode = prevNode->link;

	return prevNode;
}

LINKED_LIST_NODE_PTR getPrevNode(LINKEDLIST_HEAD_PTR H, LINKED_LIST_NODE_PTR itNode)
{
	LINKED_LIST_NODE_PTR prevNode = *H;

	if (prevNode != NULL)
		while (prevNode->link != NULL && prevNode->link != itNode)
			prevNode = prevNode->link;

	return prevNode;
}

LINKED_LIST_NODE_PTR getNode(LINKEDLIST_HEAD_PTR H, int data)
{
	LINKED_LIST_NODE_PTR find_Node = *H;

	if (find_Node != NULL)
		while (find_Node->link != NULL && !(find_Node->data == data))
			find_Node = find_Node->link;

	return find_Node;
}

void addNode(LINKEDLIST_HEAD_PTR H, int data)
{
	LINKED_LIST_NODE_PTR new_Node = newNode(data);

	LINKED_LIST_NODE_PTR lastNode = getLastNode(H);
	if (lastNode == NULL) {
		*H = new_Node;
		return;
	}	

	lastNode->link = new_Node;
}

void additNode(LINKED_LIST_NODE_PTR prevNode, int data)
{
	LINKED_LIST_NODE_PTR new_Node = newNode(data);
	new_Node->link = prevNode->link;
	prevNode->link = new_Node;
}

int removeNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR prev_Node = getPrevNodeOfLastNode(H);
	LINKED_LIST_NODE_PTR last_Node = NULL;
	
	if (prev_Node == NULL) {
		printf("The last node cannot be removed because it is an empty list!!!");
		return -1;
	}

	if (*H == prev_Node) {
		*H = NULL;
		return deleteNode(last_Node);
	}

	last_Node = prev_Node->link;

	prev_Node->link = NULL;
	return deleteNode(last_Node);
}

int removeitNode(LINKEDLIST_HEAD_PTR H, LINKED_LIST_NODE_PTR itNode)
{
	LINKED_LIST_NODE_PTR prev_Node = getPrevNode(H, itNode);

	if (prev_Node == NULL || prev_Node->link == NULL) {
		printf("�����Ϸ��� ��带 ã�� �� �����ϴ�!!!");
		return -1;
	}

	prev_Node->link = itNode->link;
	return deleteNode(itNode);
}

void PrintList(const LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR pNode = *H;

	printf("Head ->");

	while (pNode != NULL) {
		printf("| %d : Nest | -> ", pNode->data);
		pNode = pNode->link;
	}

	printf("| NULL |\n");
}

int main()
{
	PrintList(&head);

	addNode(&head, 100);
	printf("\n");
	printf("addNode(&head, 100);\n");
	PrintList(&head);

	addNode(&head, 200);
	printf("\n");
	printf("addNode(&head, 200);\n");
	PrintList(&head);

	addNode(&head, 300);
	printf("\n");
	printf("addNode(&head, 300);\n");
	PrintList(&head);

	addNode(&head, 400);
	printf("\n");
	printf("addNode(&head, 400);\n");
	PrintList(&head);

	addNode(&head, 500);
	printf("\n");
	printf("addNode(&head, 500);\n");
	PrintList(&head);

	removeNode(&head);
	printf("\n");
	printf("removeNode(&head);\n");
	PrintList(&head);

	additNode(getNode(&head, 100), 150);
	printf("\n");
	printf("additNode(getNode(&head, 100), 150);\n");
	PrintList(&head);

	removeitNode(&head, getNode(&head, 300));
	printf("\n");
	printf("removeitNode(&head, getNode(&head, 300));\n");
	PrintList(&head);

	additNode(getNode(&head, 200), 250);
	printf("\n");
	printf("additNode(getNode(&head, 200), 250);\n");
	PrintList(&head);

	return 0;
}