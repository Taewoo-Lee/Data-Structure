#include <stdio.h>
#include <stdlib.h>

typedef char NODE_DATA_TYPE;

typedef struct _node {		// Ʈ���� ���
	struct _node * left;
	struct _node * right;
	NODE_DATA_TYPE info;
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

// ���� ��ȸ
void preorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		printf("%c", node->info);
		preorder(node->left);
		preorder(node->right);
	}
}

// ���� ��ȸ
void inorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		inorder(node->left);
		printf("%c", node->info);
		inorder(node->right);
	}
}

// ���� ��ȸ
void postorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		printf("%c", node->info);
	}
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

	TREE_NODE_PTR pNode_Div = createBNode('/', pNode_B, pNode_C);
	TREE_NODE_PTR pNode_Sub_1 = createBNode('-', pNode_A, pNode_Div);
	TREE_NODE_PTR pNode_Mul = createBNode('*', pNode_D, pNode_E);

	pBTree->root = createBNode('-', pNode_Sub_1, pNode_Mul);

	preorder(pBTree->root);
	printf("\n");

	inorder(pBTree->root);
	printf("\n");

	postorder(pBTree->root);
	printf("\n");
	return 0;
}