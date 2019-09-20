#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {		// ���� ���� ����Ʈ�� ��� ���� ����
	struct ListNode* Llink;
	int data;
	struct ListNode* Rlink;
} listNode;

typedef struct _head {			// ���� ���� ����Ʈ�� ��� ��� ���� ����
	listNode* Lhead;
	listNode* Fhead;
} linkedList_h;

// ���� ���� ����Ʈ�� ��� ��� ����
linkedList_h* createLinkedList_h(void)
{
	linkedList_h* H;
	H = (linkedList_h *)malloc(sizeof(linkedList_h));
	H->Lhead = NULL;
	H->Fhead = NULL;
	return H;
}

// ���� ���� ����Ʈ ��� ���� ����
void addDNode(linkedList_h* H, ListNode* prevNode, int data)
{
	listNode* NewNode;
	if (prevNode == NULL)
		return;

	NewNode = (listNode *)malloc(sizeof(listNode));
	NewNode->Llink = NULL;
	NewNode->data = data;
	NewNode->Rlink = NULL;
	
	NewNode->Rlink = prevNode->Rlink;
	prevNode->Rlink = NewNode;
	NewNode->Llink = prevNode;

	// ������ ��尡 �ƴϸ�
	if (NewNode->Rlink != NULL)
		NewNode->Rlink->Llink = NewNode;
	else
		H->Lhead = NewNode;
}

void deleteDNode(linkedList_h* H, listNode* delNode)
{
	if (delNode->Llink != NULL)	// ù ��尡 �ƴ� ���
		delNode->Llink->Rlink = delNode->Rlink;
	else						// ù ����� ���                             
		H->Fhead = delNode->Rlink;

	if (delNode->Rlink != NULL)	// ������ ��尡 �ƴ� ���
		delNode->Rlink->Llink = delNode->Llink;
	else						// ������ ����� ���
		H->Lhead = delNode->Llink;

	free(delNode);
}

//
void addDNodeAtFirst(linkedList_h* H, int data)    
{
	listNode* NewNode;
	
	NewNode = (listNode *)malloc(sizeof(listNode));
	NewNode->Llink = NULL;
	NewNode->data = data;
	NewNode->Rlink = NULL;

	NewNode->Rlink = H->Fhead;
	if (H->Fhead != NULL) {	// �� ����Ʈ�� �ƴ� ���
		H->Fhead->Llink = NewNode;
	}
	else {					// �� ����Ʈ�� ���
		H->Lhead = NewNode;
	}

	H->Fhead = NewNode;
}

void PrintList(const linkedList_h* H)
{
	listNode* pNode = H->Fhead;

	printf("Head -> ");

	while (pNode != NULL) {
		printf("| %d : Nest | -> ", pNode->data);
		pNode = pNode->Rlink;
	}

	printf("| NULL |\n");
}

void RemoveList(linkedList_h* H)
{
	listNode* pNode = H->Fhead;
	listNode* pNext_Node = NULL;

	while (pNode != NULL) {
		pNext_Node = pNode->Rlink;
		deleteDNode(H, pNode);
		pNode = pNext_Node;
	}

	free(H);
}

int main()
{
	linkedList_h* head = createLinkedList_h();
	PrintList(head);

	addDNodeAtFirst(head, 100);
	printf("\n");
	printf("addDNodeAtFirst(head, 100);\n");
	PrintList(head);

	addDNodeAtFirst(head, 50);
	printf("\n");
	printf("addDNodeAtFirst(head, 50);\n");
	PrintList(head);

	addDNode(head, head->Lhead, 200);
	printf("\n");
	printf("addDNode(head, head->Lhead, 200);\n");
	PrintList(head);

	addDNode(head, head->Lhead->Llink, 150);
	printf("\n");
	printf("addDNode(head, head->Lhead->Llink, 150);\n");
	PrintList(head);

	addDNode(head, head->Fhead->Rlink, 120);
	printf("\n");
	printf("addDNode(head, head->Fhead->Rlink, 120);\n");
	PrintList(head);

	deleteDNode(head, head->Fhead->Rlink);
	printf("\n");
	printf("deleteDNode(head, head->Fhead->Rlink);\n");
	PrintList(head);

	deleteDNode(head, head->Lhead);
	printf("\n");
	printf("deleteDNode(head, head->Lhead);\n");
	PrintList(head);

	deleteDNode(head, head->Fhead);
	printf("\n");
	printf("deleteDNode(head, head->Fhead);\n");
	PrintList(head);

	RemoveList(head);
	return 0;

}