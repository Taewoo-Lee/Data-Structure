#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

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

// head �� ����Ű�� ù��° ���
// ��ȯ�� : ù��° ����� ������
LINKED_LIST_NODE_PTR getFirstNode(LINKEDLIST_HEAD_PTR H)
{
	return H->head;
}

// pNode �� ������ ��� �ΰ�
bool IsLastNode(LINKED_LIST_NODE_PTR pNode)
{
	return (pNode->link == NULL);
}

LINKEDLIST_HEAD_PTR createLinkedList_h()
{
	LINKEDLIST_HEAD_PTR pHead = (LINKEDLIST_HEAD_PTR)malloc(sizeof(LINKEDLIST_HEAD));
	pHead->head = NULL;
	return pHead;
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
		while (!IsLastNode(pNode))
			pNode = pNode->link;

	return pNode;
}

LINKED_LIST_NODE_PTR getPrevNodeOfLastNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR pNode = getFirstNode(H);

	if (pNode != NULL && !IsLastNode(pNode))
		while (pNode->link->link != NULL)
			pNode = pNode->link;

	return pNode;
}

LINKED_LIST_NODE_PTR getPrevNode(LINKEDLIST_HEAD_PTR H, LINKED_LIST_NODE_PTR itNode)
{
	LINKED_LIST_NODE_PTR pNode = getFirstNode(H);

	if (pNode != NULL)
		while (pNode->link != itNode && !IsLastNode(pNode))
			pNode = pNode->link;

	return pNode;
}

LINKED_LIST_NODE_PTR getNode(LINKEDLIST_HEAD_PTR H, int data)
{
	LINKED_LIST_NODE_PTR pNode = getFirstNode(H);
	if (getFirstNode(H) == NULL)
		return NULL;

	if (pNode->data == data)
		return pNode;

	while (!IsLastNode(pNode)) {
		pNode = pNode->link;
		if (pNode->data == data)
			return pNode;
	}

	return NULL;
}

void addNode(LINKEDLIST_HEAD_PTR H, int data)
{
	LINKED_LIST_NODE_PTR new_Node = newNode(data);
	LINKED_LIST_NODE_PTR lastNode = getLastNode(H);
	if (lastNode == NULL) {
		H->head = new_Node;
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

	// ��尡 �ϳ����� ���!!
	if (prev_Node->link == NULL) {
		H->head = NULL;
		return deleteNode(prev_Node);
	}

	last_Node = prev_Node->link;

	prev_Node->link = NULL;
	return deleteNode(last_Node);
}

int removeitNode(LINKEDLIST_HEAD_PTR H, LINKED_LIST_NODE_PTR itNode)
{
	LINKED_LIST_NODE_PTR prev_Node = getPrevNode(H, itNode);

	if (prev_Node == NULL) {
		printf("�����Ϸ��� ��带 ã�� �� �����ϴ�!!!");
		return -1;
	}

	if (prev_Node->link == NULL) {
		H->head = NULL;
		return deleteNode(prev_Node);
	}

	prev_Node->link = itNode->link;
	return deleteNode(itNode);
}

void PrintList(const LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR pNode = getFirstNode(H);

	printf("Head -> ");

	while (pNode != NULL) {
		printf("| %d : Nest | -> ", pNode->data);
		pNode = pNode->link;
	}

	printf("| NULL |\n");
}

void RemoveList(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR pNext_Node = NULL;

	for (LINKED_LIST_NODE_PTR pNode = getFirstNode(H); pNode != NULL; ) {
		pNext_Node = pNode->link;
		deleteNode(pNode);
		pNode = pNext_Node;
	}

	free(H);
}

