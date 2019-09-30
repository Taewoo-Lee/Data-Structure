#pragma once

typedef struct _stack
{
	int top;
	int stackSize;
	char* pData;
} STACK;

typedef STACK* STACK_PTR;

STACK_PTR CreateS(int stackSize);			// ������ ����� �Լ�
void deleteS(STACK_PTR pStack);				// ���� ����
bool is_stack_emuty(STACK_PTR pStack);		// �� ���� �ΰ�?
bool is_stack_full(STACK_PTR pStack);		// ������ ���� �ΰ�?
void Push(STACK_PTR pStack, char data);		
char Pop(STACK_PTR pStack);
void PrintStack(const STACK_PTR pStack);	// ���� ��� �Լ�

