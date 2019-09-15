#include <stdio.h>
#include <string.h>
#include "Stack.h"

#define INPUT_SIZE		256

// ����ǥ��� -> ����ǥ���
// Infix -> Postfix ��ȯ �Լ�

void Infix2Postfix(char* const input, char* output);
bool isOperator(char input);
bool Oper_Precedence(char oper1, char oper2);

int main()
{
	/*char input[INPUT_SIZE] = { '\0', };
	scanf("%s", input);*/

	char input[INPUT_SIZE] = "A-B/C-D*E";
	char output[INPUT_SIZE] = { '\0', };

	printf("%s\n", input);

	Infix2Postfix(input, output);

	printf("%s\n", output);

	return 0;
}

void Infix2Postfix(char* const input, char* output)
{
	int i = 0;
	int inputSize = strlen(input);
	STACK stack = CreateS(inputSize);

	char stackTop;

	while (i < inputSize) {
		if (isOperator(input[i])) {				// ������ �ΰ�?
			stackTop = GetTopData(&stack);

			// ���ؿ� �ִ� ������ ���� input[i] �� �켱������ ������
			// ���ؿ� �ִ� �����ڸ� ��� Pop �մϴ�.
			if (Oper_Precedence(stackTop, input[i])) {
				while (!is_stack_emuty(&stack)) {
					*output = Pop(&stack);
					output++;
				}
			}
			Push(&stack, input[i]);
		}
		else {
			*output = input[i];
			output++;
		}
		i++;
	}

	// ���� ������ ���
	while (!is_stack_emuty(&stack)) {
		*output = Pop(&stack);
		output++;
	}
}

bool isOperator(char input)
{
	if (input == '+' || input == '-' || input == '*' || input == '/')
		return true;

	return false;
}


bool Oper_Precedence(char oper1, char oper2)
{
	switch (oper1)
	{
	case '*':
	case '/':
		return true;
	case '+':
	case '-':
		if (oper2 == '+' && oper2 == '-')
			return true;

	default:
		break;
	}

	return false;
}