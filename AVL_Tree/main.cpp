#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define max(a,b)    (((a) > (b)) ? (a) : (b))

typedef int NODE_DATA_TYPE;

typedef struct _node {		// Ʈ���� ���
	_node * left;
	_node * right;
	NODE_DATA_TYPE info;
} TREE_NODE;
typedef TREE_NODE * TREE_NODE_PTR;

typedef struct _Tree {			// Ʈ�� �ڷ� ����
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

// LL ȸ�� (���������� ȸ���Ѵ�)
//     A
//    /                B
//   B        ->      / \
//  /                C   A
// C
//
// ��2�� ������ A�� �θ� �ǰ� A->left�� B�� child�� �ȴ�.
// A->left�� B�� ������ �ִ� right�� �����ϰ� B�� right�� A�� �����Ѵ�.

TREE_NODE_PTR rotate_LL(TREE_NODE_PTR parent)
{
	TREE_NODE_PTR child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}

// RR ȸ�� (�������� ȸ���Ѵ�)
//     A
//      \               B
//       B     ->      / \
//        \           A   C
//         C
//
// ��2�� ������ A�� �θ� �ǰ� A->right�� B�� child�� �ȴ�.
// A->right�� B�� ������ �ִ� left�� �����ϰ� B�� left�� A�� �����Ѵ�.

TREE_NODE_PTR rotate_RR(TREE_NODE_PTR parent)
{
	TREE_NODE_PTR child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}

// RL ȸ�� (������-�������� ȸ���Ѵ�)
//     A                A              
//      \                \                C
//       B      ->        C      ->      / \
//      /                  \            A   B
//     C                    B
//
// ��2�� ������ A�� �θ� �ǰ� A->right�� B�� child�� �ȴ�.
// A->right�� rotate_LL(B)�� ��ȯ�ϴ� ���� �����Ѵ�. (B,C�� ���� ������ ȸ��)
// rotate_LL(B)ȣ��� B�� C�� ��ȭ�� ����� �ٽ� rotate_RR(A)�� ȣ���ϸ� ����Ʈ���� �ȴ�. 

TREE_NODE_PTR rotate_RL(TREE_NODE_PTR parent)
{
	TREE_NODE_PTR child = parent->right;
	parent->right = rotate_LL(child);
	return rotate_RR(parent);
}

// LR ȸ�� (����-���������� ȸ���Ѵ�)
//     A                 A              
//	  /                 /                  C
//   B         ->      C          ->      / \
//    \               /                  A   B
//     C             B      
//
// ��2�� ������ A�� �θ� �ǰ� A->left�� B�� child�� �ȴ�.
// A->left�� rotate_RR(B)�� ��ȯ�ϴ� ���� �����Ѵ�. (B,C�� ���� ���� ȸ��)
// rotate_RR(B)ȣ��� B�� C�� ��ȭ�� ����� �ٽ� rotate_LL(A)�� ȣ���ϸ� ����Ʈ���� �ȴ�. 

TREE_NODE_PTR rotate_LR(TREE_NODE_PTR parent)
{
	TREE_NODE_PTR child = parent->left;
	parent->left = rotate_RR(child);
	return rotate_LL(parent);
}

// Ʈ���� ���� ���� �Լ�
// ��ȯȣ��� ������ ���̸� ���ϰ� �̵� �߿��� �� ū���� 1�� ���ϸ� Ʈ���� ���̰� �ȴ�.
int get_height(TREE_NODE_PTR node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

// ����� �����μ� ��ȯ �Լ�
// ���� ����Ʈ�� ���� - ������ ����Ʈ�� ����
int get_balance(TREE_NODE_PTR node)
{
	if (node == NULL) return 0;
	return get_height(node->left) - get_height(node->right);
}

// ���� Ʈ���� ����� �Լ�
TREE_NODE_PTR balance_tree(TREE_NODE_PTR node)
{
	int height_diff = get_balance(node);

	if (height_diff > 1) // ���� ����Ʈ���� ������ �����
	{
		if (get_balance(node->left) > 0)
			node = rotate_LL(node);
		else
			node = rotate_LR(node);
	}
	else if (height_diff < -1) // ������ ����Ʈ���� ������ �����
	{
		if (get_balance(node->right) < 0)
			node = rotate_RR(node);
		else
			node = rotate_RL(node);
	}
	return node;
}

// AVL Ʈ���� ���� ����
// key�� ���� ��ȯȣ���� �ݺ��ϹǷν� Ʈ���� ���� �� �� ����ȭ �Լ��� ȣ���Ѵ�.
TREE_NODE_PTR avl_add(TREE_NODE_PTR* node, int key)
{
	if (node == NULL)
		return NULL;

	if ((*node) == NULL)
	{
		(*node) = createBNode(key, NULL, NULL);
		return *node;
	}

	if (key < (*node)->info)
		(*node)->left = avl_add(&(*node)->left, key);
	else if (key > (*node)->info)
		(*node)->right = avl_add(&(*node)->right, key);
	
	(*node) = balance_tree((*node));
	return (*node);
}

// AVL Ʈ�� Ž�� �Լ�
// �Ϲ� ���� ���� Ʈ���� Ž�� �Լ��� ����. AVL�� ���� Ž�� Ʈ���� �����̴�.
TREE_NODE_PTR avl_search(TREE_NODE_PTR node, int key)
{
	if (node == NULL) return NULL;

	printf("%d->", node->info);

	if (key == node->info)
		return node;
	else if (key < node->info)
		return avl_search(node->left, key);
	else
		avl_search(node->right, key);

	return node;
}

// ���� ��ȸ
void levelorder(TREE_NODE_PTR node)
{
	QUEUE_PTR queue = Create_q(5 * 2);
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
			printf("NULL ");
		}
	}

	printf("\n");

	delete_q(queue);
}

int main()
{
	BIN_TREE_PTR pBTree = createBTree();
	//TREE_NODE_PTR node;

	avl_add(&pBTree->root, 1);
	avl_add(&pBTree->root, 2);
	avl_add(&pBTree->root, 3);
	avl_add(&pBTree->root, 4);
	avl_add(&pBTree->root, 5);
	avl_add(&pBTree->root, 6);
	avl_add(&pBTree->root, 7);
	avl_add(&pBTree->root, 8);
	avl_add(&pBTree->root, 9);
	avl_add(&pBTree->root, 10);
	avl_add(&pBTree->root, 11);
	avl_add(&pBTree->root, 12);

	//node = avl_search(pBTree->root, 12);

	levelorder(pBTree->root);

	return 0;
}
