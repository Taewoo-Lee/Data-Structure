#include <stdio.h>
#include <stdlib.h>

typedef char NODE_DATA_TYPE;

typedef struct _node {		// Ʈ���� ���
	struct _node * left;
	struct _node * right;
	NODE_DATA_TYPE info;
	bool isThread;
} TREE_NODE;
typedef TREE_NODE * TREE_NODE_PTR;

typedef struct _Tree {			// ���� ���� ����Ʈ�� ��� ��� ���� ����
	TREE_NODE_PTR root;
} BIN_TREE;
typedef BIN_TREE * BIN_TREE_PTR;

// ����Ʈ�� ��� ����
TREE_NODE_PTR createBNode(NODE_DATA_TYPE data, TREE_NODE_PTR left, TREE_NODE_PTR right)
{
	TREE_NODE_PTR newBNode = (TREE_NODE_PTR)malloc(sizeof(TREE_NODE));

	newBNode->info = data;
	newBNode->left = left;
	newBNode->right = right;
	newBNode->isThread = false;

	return newBNode;
}

// ����Ʈ�� ��� ����
void deleteBNode(TREE_NODE_PTR node)
{
	if (node == NULL)
		return;

	deleteBNode(node->left);
	deleteBNode(node->right);
	free(node);
}

// Ʈ�� ����
BIN_TREE_PTR createBTree()
{
	BIN_TREE_PTR newTree = (BIN_TREE_PTR)malloc(sizeof(BIN_TREE));
	newTree->root = NULL;
	return newTree;
}

// Ʈ�� ����
void deleteBTree(BIN_TREE_PTR tree)
{
	deleteBNode(tree->root);
	free(tree);
}

// ������ ��� ����
bool isThreadNode(const TREE_NODE_PTR node)
{
	return node->isThread;
}

// ������ ��� ����
void setThreadNode(TREE_NODE_PTR node)
{
	node->isThread = true;
}

// ���� ��ȸ
void preorder(TREE_NODE_PTR node)
{
	while (node) {
		printf("%c", node->info);

		if (node->left != NULL)
			node = node->left;
		else
			node = node->right;
	}
}

TREE_NODE_PTR nextNode_inorder(TREE_NODE_PTR node)
{
	TREE_NODE_PTR next_Node = node->right;

	if (next_Node == NULL || isThreadNode(node))
		return next_Node;

	while (next_Node->left != NULL)
		next_Node = next_Node->left;

	return next_Node;
}

void inorder(TREE_NODE_PTR node)
{
	TREE_NODE_PTR tempNode = node;
	while (tempNode->left != NULL)
		tempNode = tempNode->left;

	do {
		printf("%c", tempNode->info);
		tempNode = nextNode_inorder(tempNode);
	} while (tempNode != NULL);
}




int main()
{
	BIN_TREE_PTR pBTree = createBTree();

	// �׸� 7-14 ��Ģ����
	TREE_NODE_PTR pNode_A = createBNode('A', NULL, NULL);
	TREE_NODE_PTR pNode_B = createBNode('B', NULL, NULL);
	TREE_NODE_PTR pNode_C = createBNode('C', NULL, NULL);
	TREE_NODE_PTR pNode_D = createBNode('D', NULL, NULL);
	TREE_NODE_PTR pNode_E = createBNode('E', NULL, NULL);

	TREE_NODE_PTR pNode_Div = createBNode('/', NULL, NULL);
	TREE_NODE_PTR pNode_Sub = createBNode('-', NULL, NULL);
	TREE_NODE_PTR pNode_Plus = createBNode('+', NULL, NULL);
	TREE_NODE_PTR pNode_Mul = createBNode('*', NULL, NULL);

	pBTree->root = pNode_Mul;
	pNode_Mul->left = pNode_Sub;
	pNode_Mul->right = pNode_D;

	pNode_Sub->left = pNode_Div;
	pNode_Sub->right = pNode_C;

	pNode_Div->left = pNode_E;
	pNode_Div->right = pNode_Plus;

	pNode_Plus->left = pNode_A;
	pNode_Plus->right = pNode_B;

	// ������ ��� ����
	setThreadNode(pNode_E);
	setThreadNode(pNode_A);
	setThreadNode(pNode_B);
	setThreadNode(pNode_C);
	setThreadNode(pNode_D);

	// ���� ��ȸ ������ ����
	pNode_E->right = pNode_Plus;
	pNode_A->right = pNode_B;
	pNode_B->right = pNode_C;
	pNode_C->right = pNode_D;

	// ���� ��ȸ
	preorder(pBTree->root);
	printf("\n");

	// ���� ��ȸ ������ ����
	pNode_E->right = pNode_Div;
	pNode_A->right = pNode_Plus;
	pNode_B->right = pNode_Sub;
	pNode_C->right = pNode_Mul;

	// ���� ��ȸ
	inorder(pBTree->root);
	printf("\n");


	return 0;
}