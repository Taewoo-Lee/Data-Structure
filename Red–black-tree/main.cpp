#include <stdio.h>
#include <stdlib.h>

// ����� Ű �ڷ���
typedef int NODE_DATA_TYPE;

// ��� ��
typedef enum _node_color {
	RED,
	BLACK
} N_Color;

// ��� �ڷ� ����
typedef struct _node {
	_node * parent;				// �θ� ���
	_node * left;				// ���� �ڽ� ���
	_node * right;				// ������ �ڽ� ���
	N_Color color;				// ��� ��
	
	NODE_DATA_TYPE key;			// Ű ��
} TREE_NODE;

// ��� ������ 
typedef TREE_NODE * TREE_NODE_PTR;

// Ʈ�� �ڷ� ����
typedef struct _Tree {		
	TREE_NODE_PTR root;
} BIN_TREE;
typedef BIN_TREE * BIN_TREE_PTR;

// �θ� ��带 ���ϴ� �Լ�
TREE_NODE_PTR getParent(TREE_NODE_PTR node)
{
	return node == NULL ? NULL : node->parent;
}

// ���θ� ��带 ���ϴ� �Լ�
TREE_NODE_PTR getGrandParent(TREE_NODE_PTR node)
{
	return getParent(getParent(node));
}

// ���� ��带 ���ϴ� �Լ�
TREE_NODE_PTR getSibling(TREE_NODE_PTR node)
{
	TREE_NODE_PTR parent = getParent(node);

	if (parent == NULL)
		return NULL;

	return node == parent->left ? parent->right : parent->left;
}

// �θ��� ���� ���(����?)�� ���ϴ� �Լ�
TREE_NODE_PTR getParentSibling(TREE_NODE_PTR node)
{
	return getSibling(getParent(node));
}

// ����Ʈ�� ��� ����
TREE_NODE_PTR createBNode(NODE_DATA_TYPE key, TREE_NODE_PTR left, TREE_NODE_PTR right)
{
	TREE_NODE_PTR newNode = (TREE_NODE_PTR)malloc(sizeof(TREE_NODE));

	newNode->key = key;
	newNode->left = left;
	newNode->right = right;

	newNode->color = RED;
	newNode->parent = NULL;

	return newNode;
}

#define NewNode(Key) createBNode((Key), NULL, NULL)

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
	TREE_NODE_PTR child = NULL;

	if (parent == NULL)
		return NULL;

	child = parent->left;
	if (child == NULL)
		return NULL;

	parent->left = child->right;
	child->right = parent;

	child->parent = parent->parent;
	parent->parent = child;

	if (parent->left != NULL)
		parent->left->parent = parent;

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
	TREE_NODE_PTR child = NULL;

	if (parent == NULL)
		return NULL;

	child = parent->right;
	if (child == NULL)
		return NULL;

	parent->right = child->left;
	child->left = parent;

	child->parent = parent->parent;
	parent->parent = child;

	if (parent->right != NULL)
	parent->right->parent = parent;

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
	TREE_NODE_PTR child = NULL;
	if (parent == NULL)
		return NULL;

	child = parent->right;
	if (child == NULL)
		return NULL;

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
	TREE_NODE_PTR child = NULL;
	if (parent == NULL)
		return NULL;

	child = parent->left;
	if (child == NULL)
		return NULL;

	parent->left = rotate_RR(child);
	return rotate_LL(parent);
}

// ���� Ʈ���� ����� �Լ�
TREE_NODE_PTR balance_tree(TREE_NODE_PTR node)
{
	TREE_NODE_PTR parent = getParent(node);

	if (parent == NULL)	// ��Ʈ ����� ���
	{
		if (node != NULL)
			node->color = BLACK;
	}
	else if(parent->color == BLACK)
	{
		node = parent;
	}
	else		// �θ� ��尡  ����(RED)�� ���
	{
		// �θ��� ���� ��尡 ����(RED)�� ���
		if (getParentSibling(node) != NULL && getParentSibling(node)->color == RED)
		{
			parent->color = BLACK;
			getParentSibling(node)->color = BLACK;
			getGrandParent(node)->color = RED;
			node = balance_tree(getGrandParent(node));
		}
		else // �θ��� ���� ��尡 ���ų� ��(BLACK)�� ���
		{
			TREE_NODE_PTR tempNode = NULL;

			if (node == parent->right && getGrandParent(node) != NULL && parent == getGrandParent(node)->left) {
				node = rotate_LR(parent);
				tempNode = node->left;
			}
			else if (node == parent->left && parent == getGrandParent(node)->right) {
				node = rotate_RL(parent);
				tempNode = node->right;
			}
			else
				tempNode = node;

			if (tempNode != NULL)
			{
				TREE_NODE_PTR temp_Parent = getParent(tempNode);
				TREE_NODE_PTR temp_GrandParent = getGrandParent(tempNode);

				if (tempNode == temp_Parent->left) {
					node = rotate_LL(temp_GrandParent);
				}
				else {
					node = rotate_RR(temp_GrandParent);
				}

				temp_Parent->color = BLACK;
				temp_GrandParent->color = RED;
				node = balance_tree(node);
			}
		}
	}

	return node;
}

// Ʈ���� ���� ����
// key�� ���� ��ȯȣ���� �ݺ��ϹǷν� Ʈ���� ���� �� �� ����ȭ �Լ��� ȣ���Ѵ�.
TREE_NODE_PTR RBTree_Insert(TREE_NODE_PTR* root, TREE_NODE_PTR node)
{
	if (root == NULL || node == NULL)
		return NULL;

	if ((*root) == NULL)	// ��Ʈ�� �߰��ϴ� ���				
	{
		(*root) = node;
		node->color = BLACK;
	} 
	else if (node->key < (*root)->key)	// ���ʿ� �߰��ϴ� ���
	{
		if ((*root)->left == NULL)	// ������ ��� ������
		{
			(*root)->left = node;
			node->parent = (*root);
		}
		else
		{
			RBTree_Insert(&(*root)->left, node);
		}
	}
	else if (node->key > (*root)->key)	// �����ʿ� �߰��ϴ� ���
	{
		if ((*root)->right == NULL)	// �������� ��� ������
		{
			(*root)->right = node;
			node->parent = (*root);
		}
		else
		{
			RBTree_Insert(&(*root)->right, node);
		}
	}

	return (node);
}

TREE_NODE_PTR RBTree_add(TREE_NODE_PTR* root, NODE_DATA_TYPE key)
{
	TREE_NODE_PTR node = NewNode(key);
	RBTree_Insert(root, node);

	(*root) = balance_tree(node);

	return (*root);
}

int main()
{
	BIN_TREE_PTR pBTree = createBTree();

	RBTree_add(&pBTree->root, 1);
	RBTree_add(&pBTree->root, 2);
	RBTree_add(&pBTree->root, 3);
	RBTree_add(&pBTree->root, 4);
	RBTree_add(&pBTree->root, 5);
	RBTree_add(&pBTree->root, 6);
	RBTree_add(&pBTree->root, 7);
	RBTree_add(&pBTree->root, 8);
	RBTree_add(&pBTree->root, 9);
	RBTree_add(&pBTree->root, 10);
	RBTree_add(&pBTree->root, 11);


	return 0;
}