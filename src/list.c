#include "list.h"

int addNode(struct list_node **list_pointer, int x, int y)
{
	struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));

	if (!new_node)
		return -1;
	new_node->x = x;
	new_node->y = y;
	if (*list_pointer)
	{
		new_node->next = *list_pointer;
	}
	else
	{
		new_node->next = NULL;
	}
	*list_pointer = new_node;
	return 0;
}



struct list_node * deleteFront(struct list_node * front)
{
	struct list_node * next = front->next;
	free(front);
	return next;
}

struct list_node * findPrevNode(struct list_node *front, int x, int y)
{
	struct list_node * prev = NULL;
	while ((front) && ((front->x != x) || (front->y != y)))
	{
		prev = front;
		front = front->next;
	}
	return prev;
}


void deleteMiddleOrLastNode(struct list_node *previous)
{
	struct list_node *node = previous->next;
	if (node) {
		previous->next = node->next;
		free(node);
	}
}

bool deleteNode(struct list_node **front, int x, int y)
{
	if (*front)
	{
		if (((*front)->x == x) && ((*front)->y == y))
		{
			*front = deleteFront(*front);
			return true;
		}


		struct list_node *prev = findPrevNode(*front, x, y);
		deleteMiddleOrLastNode(prev);
		return true;
	}
	return false;
}





void removeList(struct list_node **list_pointer)
{
	while (*list_pointer) {
		struct list_node *next = (*list_pointer)->next;
		free(*list_pointer);
		*list_pointer = next;
	}
}