#include <stdio.h>
#include <stdlib.h>
#include "Circular_Linked_List.h"

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

// head �� ����Ű�� ù��° ���
// ��ȯ�� : ù��° ����� ������
LINKED_LIST_NODE_PTR getFirstNode(LINKEDLIST_HEAD_PTR H)
{
	return H->head;
}

bool IsLastNode(LINKED_LIST_NODE_PTR pNode, LINKEDLIST_HEAD_PTR H)
{
	if (pNode == NULL)
		return false;

	return (pNode->link == getFirstNode(H));
}

LINKEDLIST_HEAD_PTR createCircularLinkedList_h()
{
	LINKEDLIST_HEAD_PTR pHead = (LINKEDLIST_HEAD_PTR)malloc(sizeof(LINKEDLIST_HEAD));
	pHead->head = NULL;
	return pHead;
}

void PrintList(const LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR pNode = getFirstNode(H);

	printf("Head -> ");

	if (pNode != NULL) {
		while (true) {
			printf("| %d : Nest | -> ", pNode->data);
			if (IsLastNode(pNode, H))
				break;

			pNode = pNode->link;
		}
	}

	printf("| First Node |\n");
}

void addFirstNode(LINKEDLIST_HEAD_PTR H, int data)
{
	LINKED_LIST_NODE_PTR pNew_Node = newNode(data);
	LINKED_LIST_NODE_PTR pNode = getLastNode(H);
	if (pNode == NULL) {
		H->head = pNew_Node;
		pNew_Node->link = pNew_Node;
		return;
	}
		
	pNew_Node->link = pNode->link;
	pNode->link = pNew_Node;
	H->head = pNew_Node;
}

void addNode(LINKEDLIST_HEAD_PTR H, int data)
{
	LINKED_LIST_NODE_PTR pNew_Node = newNode(data);
	LINKED_LIST_NODE_PTR lastNode = getLastNode(H);
	if (lastNode == NULL) {
		H->head = pNew_Node;
		return;
	}

	pNew_Node->link = lastNode->link;
	lastNode->link = pNew_Node;
}

void removeFirstNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR pNode = getLastNode(H);

	if (pNode == NULL) {
		printf("The last node cannot be removed because it is an empty list!!!");
		return ;
	}

	// ��尡 �ϳ����� ���!
	if (pNode->link == pNode) {
		H->head = NULL;
		deleteNode(pNode);
		return;
	}

	// ����� �ι�° ��带 ����ġ���� �ϰ� (ù��° ��� ��ü)
	H->head = pNode->link->link;
	deleteNode(pNode->link);
	pNode->link = H->head;
}

int removeNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR prev_Node = getPrevNodeOfLastNode(H);
	LINKED_LIST_NODE_PTR last_Node = NULL;

	if (prev_Node == NULL) {
		printf("The last node cannot be removed because it is an empty list!!!");
		return -1;
	}

	// ��尡 �ϳ����� ���!!
	if (prev_Node->link == H->head) {
		H->head = NULL;
		return deleteNode(prev_Node);
	}

	last_Node = prev_Node->link;

	prev_Node->link = last_Node->link;
	return deleteNode(last_Node);
}

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
	LINKED_LIST_NODE_PTR pNode = getFirstNode(H);

	if (pNode != NULL)
		while (!IsLastNode(pNode, H))
			pNode = pNode->link;

	return pNode;
}

void RemoveList(LINKEDLIST_HEAD_PTR H)
{
	while (getLastNode(H) != NULL) {
		removeFirstNode(H);
	}

	free(H);
}

LINKED_LIST_NODE_PTR getPrevNodeOfLastNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR pNode = getFirstNode(H);

	if (pNode != NULL && !IsLastNode(pNode, H))
		while (!IsLastNode(pNode->link, H))
			pNode = pNode->link;

	return pNode;
}