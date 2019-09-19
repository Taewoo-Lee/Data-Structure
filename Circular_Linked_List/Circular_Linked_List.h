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
