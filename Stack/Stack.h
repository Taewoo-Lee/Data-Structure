#pragma once

typedef struct _stack
{
	int top;
	int stackSize;
	char* pData;
} STACK;

typedef STACK* STACK_PTR;

STACK CreateS(int stackSize);				// ������ ����� �Լ�
bool is_stack_emuty(STACK_PTR pStack);		// �� ���� �ΰ�?
bool is_stack_full(STACK_PTR pStack);		// ������ ���� �ΰ�?
void Push(STACK_PTR pStack, char data);		
char Pop(STACK_PTR pStack);
void PrintStack(STACK_PTR const pStack);	// ���� ��� �Լ�

