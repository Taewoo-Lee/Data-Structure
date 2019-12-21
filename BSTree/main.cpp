#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef int NODE_DATA_TYPE;

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
		printf("%d ", node->info);
		preorder(node->left); 
		preorder(node->right);
	}
}

// ���� ��ȸ
void inorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		inorder(node->left);
		printf("%d ", node->info);
		inorder(node->right);
	}
}

// ���� ��ȸ
void postorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		printf("%d ", node->info); 
	}
}

// ���� ��ȸ
void levelorder(TREE_NODE_PTR node)
{
	QUEUE_PTR queue = Create_q(4*2);
	TREE_NODE_PTR temp_Node;
	if (node == NULL)
		return;

	Add_q(queue, node);
	while (!IsEmpty_q(queue))
	{
		temp_Node = (TREE_NODE_PTR)Delete_q(queue);

		if (temp_Node) {
			printf("%d ", temp_Node->info);
			Add_q(queue, temp_Node->left);
			Add_q(queue, temp_Node->right);
		}
		else {
			printf("0 ");
		}
	}

	printf("\n");

	delete_q(queue);
}

// ����
TREE_NODE_PTR addData_BSTree(TREE_NODE_PTR node, int data)
{
	if (node == NULL) {
		return createBNode(data, NULL, NULL);
	}

	if (node->info == data)
		return node;
	else if (node->info > data)
		node->left = addData_BSTree(node->left, data);
	else
		node->right = addData_BSTree(node->right, data);

	return node;
}

// �˻�
TREE_NODE_PTR search_BSTree(TREE_NODE_PTR node, int data)
{
	if (node == NULL)
		return NULL;

	if (node->info == data)
		return node;
	else if (node->info > data)
		return search_BSTree(node->left, data);
	else
		return search_BSTree(node->right, data);
}

TREE_NODE_PTR firstNode_inorder(TREE_NODE_PTR node)
{
	if (node == NULL)
		return NULL;

	while (node->left != NULL)
		node = node->left;

	return node;
}

// ����
TREE_NODE_PTR deleteData_BSTree(TREE_NODE_PTR node, int data)
{	
	TREE_NODE_PTR temp_Node = NULL;

	if (node == NULL)
		return NULL;

	if (node->info == data) {
		if (node->left != NULL && node->right != NULL) {
			temp_Node = firstNode_inorder(node->right);
			node->info = temp_Node->info;
			node->right = deleteData_BSTree(node->right, temp_Node->info);
		}
		else {
			temp_Node = (node->right == NULL) ? node->left : node->right;
			deleteBNode(node);
			return temp_Node;
		}
	}
	else if (node->info > data)
		node->left = deleteData_BSTree(node->left, data);
	else
		node->right = deleteData_BSTree(node->right, data);

	return node;
}

int main()
{
	BIN_TREE_PTR pBTree = createBTree();

	pBTree->root = addData_BSTree(pBTree->root, 5);
	levelorder(pBTree->root);

	pBTree->root = addData_BSTree(pBTree->root, 3);
	levelorder(pBTree->root);

	pBTree->root = addData_BSTree(pBTree->root, 7);
	levelorder(pBTree->root);

	pBTree->root = addData_BSTree(pBTree->root, 1);
	levelorder(pBTree->root);
	
	pBTree->root = addData_BSTree(pBTree->root, 9);
	levelorder(pBTree->root);

	pBTree->root = addData_BSTree(pBTree->root, 6);
	levelorder(pBTree->root);

	pBTree->root = deleteData_BSTree(pBTree->root, 7);
	levelorder(pBTree->root);

	pBTree->root = addData_BSTree(pBTree->root, 2);
	levelorder(pBTree->root);

	pBTree->root = deleteData_BSTree(pBTree->root, 2);
	levelorder(pBTree->root);

	return 0;
}