#include "list.h"
#include "queue.h"
#include "system.h"
#include "collisions.h"
#pragma once
#ifndef SNAKE_AND_FOOD_H
#define SNAKE_AND_FOOD_H


void moveSnake(int **collision_array, struct fifo_pointers fifo, int speed_x, int speed_y, bool walls_effect, int width, int height);

void randomizeFoodPosition(int **collision_array, int *x, int *y, int width, int height);

void spawnFoodObject(struct list_node **food_to_spawn, int*occupied_space, int** collision_array, int window_width, int window_height);

void spawnNextFood(struct list_node **eaten_food, struct list_node **other_food, int *occupied_space, int**collision_array, int window_width, int window_height);

void eatSmallFood(int* score, struct fifo_pointers *fifo, struct list_node **small_food, struct list_node **big_food, int* occupied_space, int** collision_array, int window_width, int window_height);

void eatBigFood(int* score, struct fifo_pointers *fifo, struct list_node **big_food, struct list_node **small_food, int* occupied_space, int** collision_array, int window_width, int window_height);

void eatRandomBonus(struct list_node **random_bonus, struct fifo_pointers fifo, bool* food_spawn_bonus_effect, int* food_spawn_bonus_effect_timer, char* snake_speed, bool* walls_bonus_effect, int* walls_bonus_effect_timer, bool* negative_effect, int* negative_effect_timer);

void eatFoodSpawnBonus(struct list_node **food_spawn_bonus, struct fifo_pointers fifo, bool* food_spawn_bonus_effect, int* food_spawn_bonus_effect_timer, char* snake_speed);

void eatWallsBonus(struct list_node **walls_bonus, struct fifo_pointers fifo, bool*walls_bonus_effect, int*walls_bonus_effect_timer);

void eatNegativeBonus(struct list_node **negative_bonus, struct fifo_pointers fifo, bool* negative_effect, int*negative_effect_timer);

void setMovementDirection(int* last_move, int* next_move, int* next_next_move, int* speed_x, int* speed_y);

void prepareForStart(char* snake_speed,
	int* speed_x,
	int* speed_y,
	int* last_move,
	int* next_move,
	int* next_next_move,
	bool* food_spawn_bonus_effect,
	bool* walls_bonus_effect,
	bool* negative_effect,
	int* food_spawn_bonus_effect_timer,
	int* walls_bonus_effect_timer,
	int* negative_effect_timer,
	struct ranking_record *player,
	int* occupied_space,
	int** collision_array,
	struct fifo_pointers* fifo,
	struct list_node **small_food,
	struct list_node **big_food,
	struct list_node **obstacle,
	struct list_node **food_spawn_bonus,
	struct list_node **walls_bonus,
	struct list_node **random_bonus,
	struct list_node **negative_bonus);

void startGame(int** collision_array, struct fifo_pointers* fifo, struct list_node **first_food, int* occupied_space, int window_width, int window_height);

void handleFoodSpawnBonus(bool* food_spawn_bonus_effect, int* food_spawn_bonus_effect_timer, struct list_node **small_food, struct list_node **big_food, int* occupied_space, int**collision_array, char*snake_speed, int window_width, int window_height);

void handleWallsBonus(bool* walls_bonus_effect, int*walls_bonus_effect_timer);

void handleNegativeBonus(bool* negative_effect, int* negative_effect_timer, int* occupied_space, int** collision_array, int window_width, int window_height, struct fifo_pointers fifo, struct list_node** obstacle);

void respawnBonusesPeriodically(int** collision_array, int* occupied_space, ALLEGRO_TIMER* timer, struct list_node **food_spawn_bonus, struct list_node **walls_bonus, struct list_node **negative_bonus, struct list_node **random_bonus, int window_width, int window_height);
#endif