#include<stdlib.h>
#pragma once
#ifndef QUEUE_H
#define QUEUE_H

///snake
struct fifo_node
{
	int x;
	int y;
	struct fifo_node *next;
	struct fifo_node *prev;
};

struct fifo_pointers
{
	struct fifo_node *head;
	struct fifo_node *tail;
};

void enqueue(struct fifo_pointers *fifo, int x, int y);
void dequeue(struct fifo_pointers *fifo);
#endif