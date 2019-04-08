#include "queue.h"

void enqueue(struct fifo_pointers *fifo, int x, int y)
{
	struct fifo_node *new_node = (struct fifo_node *)malloc(sizeof(struct fifo_node));
	if (new_node) {
		new_node->x = x;
		new_node->y = y;
		new_node->next = NULL;
		new_node->prev = NULL;
		if (fifo->head == NULL)
			fifo->head = fifo->tail = new_node;
		else {
			new_node->prev = fifo->tail;
			fifo->tail->next = new_node;
			fifo->tail = new_node;
		}
	}
	else
		abortGame("Could not create element");
}

void dequeue(struct fifo_pointers *fifo)
{
	if (fifo->head) {
		struct fifo_node *tmp = fifo->head->next;
		free(fifo->head);
		fifo->head = tmp;
		if (tmp == NULL)
			fifo->tail = NULL;
	}
}