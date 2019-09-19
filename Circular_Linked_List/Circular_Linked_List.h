#pragma once

typedef struct _linked_list_node {
	int data;
	struct _linked_list_node * link;
} LINKED_LIST_NODE;

typedef LINKED_LIST_NODE* LINKED_LIST_NODE_PTR;

typedef struct _linkedList_h {
	LINKED_LIST_NODE_PTR head;
}LINKEDLIST_HEAD;

typedef LINKEDLIST_HEAD* LINKEDLIST_HEAD_PTR;

// ���� ����Ʈ head �� ����
LINKEDLIST_HEAD_PTR createCircularLinkedList_h();

// ����Ʈ ���
void PrintList(const LINKEDLIST_HEAD_PTR H);

// ù��° ��忡 ��� �߰�
void addFirstNode(LINKEDLIST_HEAD_PTR H, int data);

// ����Ʈ �������� ��Ʈ �߰�
void addNode(LINKEDLIST_HEAD_PTR H, int data);

// ����Ʈ �������� ��Ʈ ����
// ��ȯ�� : ���� ��Ʈ�� ��� �ִ� ��
void removeFirstNode(LINKEDLIST_HEAD_PTR H);

// ����Ʈ �������� ��Ʈ ����
// ��ȯ�� : ���� ��Ʈ�� ��� �ִ� ��
int removeNode(LINKEDLIST_HEAD_PTR H);

// ����Ʈ ����
void RemoveList(LINKEDLIST_HEAD_PTR H);
