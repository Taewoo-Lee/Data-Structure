#include "queue.h"

int main()
{
	QUEUE_PTR queue = Create_q(4);
	PrintQueue(queue);

	Add_q(queue, 'A');
	PrintQueue(queue);

	Add_q(queue, 'B');
	PrintQueue(queue);

	Add_q(queue, 'C');
	PrintQueue(queue);

	Delete_q(queue);
	PrintQueue(queue);

	Delete_q(queue);
	PrintQueue(queue);

	Delete_q(queue);
	PrintQueue(queue);

	Add_q(queue, 'D');
	PrintQueue(queue);

	Add_q(queue, 'E');
	PrintQueue(queue);

	delete_q(queue);

	return 0;
}