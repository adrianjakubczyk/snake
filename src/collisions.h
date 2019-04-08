#include<stdlib.h>
#include<stdbool.h>
#include"system.h"
#pragma once
#ifndef COLLISIONS_H
#define COLLISIONS_H

int checkOccupiedSpaceAmount(int **collision_array);

void addObjectToCollisionArray(int **collision_array, int x, int y);

void removeObjectFromCollisionArray(int **collision_array, int x, int y);

bool checkSelfCollision(struct fifo_pointers fifo, int speed_x, int speed_y);

bool checkFoodPieceCollision(int x, int y, struct list_node *food);

bool checkScoreCollision(int **collision_array);

bool checkWallsCollision(int speed_x, int speed_y, struct fifo_pointers fifo, int width, int height);

void checkDeadlyCollisions(int*game_state, bool walls_bonus_effect, int speed_x, int speed_y, struct fifo_pointers fifo, struct list_node*obstacle, int window_width, int window_height);


#endif