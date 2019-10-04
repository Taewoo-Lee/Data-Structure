#include <stdio.h>
#include <stdlib.h>

typedef int NODE_DATA_TYPE;

typedef struct _node {		// Ʈ���� ���
	struct _node * left;
	struct _node * right;
	NODE_DATA_TYPE info;
} TREE_NODE;
typedef TREE_NODE * TREE_NODE_PTR;

typedef struct _Tree {			// Ʈ�� ����ü
	TREE_NODE_PTR root;			// ��Ʈ ��� ������
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
		printf("%d", node->info);
		preorder(node->left);
		preorder(node->right);
	}
}

// ���� ��ȸ
void inorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		inorder(node->left);
		printf("%d", node->info);
		inorder(node->right);
	}
}

// ���� ��ȸ
void postorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		printf("%d", node->info);
	}
}
 
// �˻�
TREE_NODE_PTR search(TREE_NODE_PTR node, NODE_DATA_TYPE data)
{
	if (node == NULL)
		return NULL;
		
	if (node->info > data)
		return search(node->left, data);
	else if (node->info < data)
		return search(node->right, data);

	return node;
}


// Ʈ���� node �߰�
TREE_NODE_PTR add_Node(TREE_NODE_PTR node, NODE_DATA_TYPE data)
{	
	if (node == NULL)
		return createBNode(data, NULL, NULL);

	if (node->info > data) {
		node->left = add_Node(node->left, data);
	}
	else if (node->info < data) {
		node->right = add_Node(node->left, data);
	}

	return node;
}

TREE_NODE_PTR inorder_first_Node(TREE_NODE_PTR node)
{
	TREE_NODE_PTR res_node = node;
	if (node == NULL)
		return node;

	while (res_node->left != NULL)
		res_node = res_node->left;

	return res_node;
}

TREE_NODE_PTR inorder_last_Node(TREE_NODE_PTR node)
{
	TREE_NODE_PTR res_node = node;
	if (node == NULL)
		return node;

	while (res_node->right != NULL)
		res_node = res_node->right;

	return res_node;
}

// Ʈ������ node ����
void delete_Node(TREE_NODE_PTR node, NODE_DATA_TYPE data) // Ʈ������ data �� ���� node �� ã�� ����
{
	TREE_NODE_PTR del_Node = search(node, data);		// �����Ϸ��� node
	TREE_NODE_PTR chage_Node = NULL;
	
	if (del_Node == NULL)
		return;

	// ������ ���� Ʈ������ ���� ��ȸ ù��° node �˻�
	if ((chage_Node = inorder_first_Node(del_Node->right)) == NULL) {
		// ���� Ʈ���� ���� ��ȸ ������ node �˻�
		chage_Node = inorder_last_Node;
	}

	// �ڽ� ��尡 ���� ��� �׳� ����
	if (chage_Node == NULL)
		deleteBNode(del_Node);

	
}




int main()
{


	return 0;
}