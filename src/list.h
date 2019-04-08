#include<stdbool.h>
#include<stdlib.h>
#pragma once
#ifndef LIST_H
#define LIST_H

///food
struct list_node {
	int x;
	int y;
	struct list_node *next;
};

int addNode(struct list_node **list_pointer, int x, int y);

struct list_node * deleteFront(struct list_node * front);

struct list_node * findPrevNode(struct list_node *front, int x, int y);

void deleteMiddleOrLastNode(struct list_node *previous);

bool deleteNode(struct list_node **front, int x, int y);

void removeList(struct list_node **list_pointer);
#endif