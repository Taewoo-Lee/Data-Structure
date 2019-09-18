#pragma once

typedef struct _linked_list_node {
	int data;
	struct _linked_list_node * link;
} LINKED_LIST_NODE;

typedef LINKED_LIST_NODE* LINKED_LIST_NODE_PTR;
typedef LINKED_LIST_NODE_PTR LINKEDLIST_HEAD;
typedef LINKEDLIST_HEAD* LINKEDLIST_HEAD_PTR;

extern LINKEDLIST_HEAD head;

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

// ����Ʈ ���
void PrintList(const LINKEDLIST_HEAD_PTR H);