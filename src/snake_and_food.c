#include "snake_and_food.h"

void moveSnake(int **collision_array, struct fifo_pointers fifo, int speed_x, int speed_y, bool walls_effect, int width, int height)
{
	if (fifo.tail->x != fifo.tail->prev->x || fifo.tail->y != fifo.tail->prev->y)
		removeObjectFromCollisionArray(collision_array, fifo.tail->x, fifo.tail->y);
	while (fifo.tail->prev) {
		fifo.tail->x = fifo.tail->prev->x;
		fifo.tail->y = fifo.tail->prev->y;
		fifo.tail = fifo.tail->prev;
	}
	if (fifo.head)
	{
		fifo.head->x += speed_x;
		fifo.head->y += speed_y;

		if (walls_effect)
		{
			if (fifo.head->x > width - 30)
			{
				fifo.head->x = 30;
			}
			else if (fifo.head->x < 30)
			{
				fifo.head->x = width - 30;
			}
			else if (fifo.head->y > height - 30)
			{
				fifo.head->y = 30;
			}
			else if (fifo.head->y < 30)
			{
				fifo.head->y = height - 30;
			}

		}

	}
	addObjectToCollisionArray(collision_array, fifo.head->x, fifo.head->y);


}

void randomizeFoodPosition(int **collision_array, int *x, int *y, int width, int height)
{
	do
	{
		*x = (1 + (2 * (1 + rand() % ((width / 20) - 2)))) * 10;
		*y = (1 + (2 * (1 + rand() % ((width / 20) - 2)))) * 10;
	} while (collision_array[(*y - 30) / 20][(*x - 30) / 20] == 1);
}

void spawnFoodObject(struct list_node **food_to_spawn, int*occupied_space, int** collision_array, int window_width, int window_height)
{

	if (*occupied_space < 1444)
	{
		int x = 0;
		int y = 0;
		randomizeFoodPosition(collision_array, &x, &y, window_width, window_height);
		addNode(food_to_spawn, x, y);
		addObjectToCollisionArray(collision_array, x, y);
		*occupied_space = checkOccupiedSpaceAmount(collision_array);
	}
}

void spawnNextFood(struct list_node **eaten_food, struct list_node **other_food, int *occupied_space, int**collision_array, int window_width, int window_height)
{
	if (!(*eaten_food)->next)
	{

		if (rand() % 2 == 1)
		{
			spawnFoodObject(eaten_food, occupied_space, collision_array, window_width, window_height);
		}
		else
		{
			spawnFoodObject(other_food, occupied_space, collision_array, window_width, window_height);
		}
	}
}

void eatSmallFood(int* score, struct fifo_pointers *fifo, struct list_node **small_food, struct list_node **big_food, int* occupied_space, int** collision_array, int window_width, int window_height)
{
	*score += 10;
	enqueue(fifo, fifo->tail->x, fifo->tail->y);

	spawnNextFood(small_food, big_food, occupied_space, collision_array, window_width, window_height);

	deleteNode(small_food, fifo->head->x, fifo->head->y);
}

void eatBigFood(int* score, struct fifo_pointers *fifo, struct list_node **big_food, struct list_node **small_food, int* occupied_space, int** collision_array, int window_width, int window_height)
{
	*score += 20;
	enqueue(fifo, fifo->tail->x, fifo->tail->y);
	enqueue(fifo, fifo->tail->x, fifo->tail->y);

	spawnNextFood(big_food, small_food, occupied_space, collision_array, window_width, window_height);

	deleteNode(big_food, fifo->head->x, fifo->head->y);
}

void eatRandomBonus(struct list_node **random_bonus, struct fifo_pointers fifo, bool* food_spawn_bonus_effect, int* food_spawn_bonus_effect_timer, char* snake_speed, bool* walls_bonus_effect, int* walls_bonus_effect_timer, bool* negative_effect, int* negative_effect_timer)
{
	int tmp = rand() % 3;
	if (tmp == 0)
	{
		*food_spawn_bonus_effect = true;
		*food_spawn_bonus_effect_timer += 300;
		*snake_speed = 3;
	}
	else if (tmp == 1)
	{
		*walls_bonus_effect = true;
		*walls_bonus_effect_timer += 600;
	}
	else
	{
		*negative_effect = true;
		*negative_effect_timer += 600;
	}
	deleteNode(random_bonus, fifo.head->x, fifo.head->y);
}

void eatFoodSpawnBonus(struct list_node **food_spawn_bonus, struct fifo_pointers fifo, bool* food_spawn_bonus_effect, int* food_spawn_bonus_effect_timer, char* snake_speed)
{
	*food_spawn_bonus_effect = true;
	*food_spawn_bonus_effect_timer += 300;
	*snake_speed = 3;
	deleteNode(food_spawn_bonus, fifo.head->x, fifo.head->y);
}

void eatWallsBonus(struct list_node **walls_bonus, struct fifo_pointers fifo, bool*walls_bonus_effect, int*walls_bonus_effect_timer)
{
	*walls_bonus_effect = true;
	*walls_bonus_effect_timer += 600;
	deleteNode(walls_bonus, fifo.head->x, fifo.head->y);
}

void eatNegativeBonus(struct list_node **negative_bonus, struct fifo_pointers fifo, bool* negative_effect, int*negative_effect_timer)
{
	*negative_effect = true;
	*negative_effect_timer += 600;
	deleteNode(negative_bonus, fifo.head->x, fifo.head->y);
}

void setMovementDirection(int* last_move, int* next_move, int* next_next_move, int* speed_x, int* speed_y)
{
	if (*last_move != *next_move)
	{
		*last_move = *next_move;
		if (*next_next_move != -1)
		{
			*next_move = *next_next_move;
		}
	}
	*next_next_move = -1;

	if (*last_move == UP)
	{
		if (*speed_x != 0)
		{
			*speed_x = 0;
		}
		if (*speed_y != -20)
		{
			*speed_y = -20;
		}
	}
	else if (*last_move == RIGHT)
	{
		if (*speed_x != 20)
		{
			*speed_x = 20;
		}
		if (*speed_y != 0)
		{
			*speed_y = 0;
		}
	}
	else if (*last_move == DOWN)
	{
		if (*speed_x != 0)
		{
			*speed_x = 0;
		}
		if (*speed_y != 20)
		{
			*speed_y = 20;
		}
	}
	else if (*last_move == LEFT)
	{
		if (*speed_x != -20)
		{
			*speed_x = -20;
		}
		if (*speed_y != 0)
		{
			*speed_y = 0;
		}
	}
}

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
	struct list_node **negative_bonus)
{
	*snake_speed = 5;
	*speed_x = 0;
	*speed_y = 0;
	*last_move = -1;
	*next_move = -1;
	*next_next_move = -1;
	*food_spawn_bonus_effect = false;
	*walls_bonus_effect = false;
	*negative_effect = false;

	*food_spawn_bonus_effect_timer = 0;
	*walls_bonus_effect_timer = 0;
	*negative_effect_timer = 0;

	player->score = 30;
	player->name[0] = 'A';
	player->name[1] = 'A';
	player->name[2] = 'A';
	*occupied_space = 0;

	for (int i = 0; i < 38; ++i)
	{
		for (int j = 0; j < 38; ++j)
		{
			collision_array[i][j] = 0;
		}
	}
	removeListsAndQueue(fifo, small_food, big_food, obstacle, food_spawn_bonus, walls_bonus, random_bonus, negative_bonus);

}

void startGame(int** collision_array, struct fifo_pointers* fifo, struct list_node **first_food, int* occupied_space, int window_width, int window_height)
{


	enqueue(fifo, 390, 290);
	enqueue(fifo, 390, 310);
	enqueue(fifo, 390, 330);

	addObjectToCollisionArray(collision_array, 390, 290);
	addObjectToCollisionArray(collision_array, 390, 310);
	addObjectToCollisionArray(collision_array, 390, 330);

	spawnFoodObject(first_food, occupied_space, collision_array, window_width, window_height);

}

void handleFoodSpawnBonus(bool* food_spawn_bonus_effect, int* food_spawn_bonus_effect_timer, struct list_node **small_food, struct list_node **big_food, int* occupied_space, int**collision_array, char*snake_speed, int window_width, int window_height)
{
	if (*food_spawn_bonus_effect&&*food_spawn_bonus_effect_timer > 0)
	{

		if (*food_spawn_bonus_effect_timer % 10 == 0)
		{
			if (rand() % 3 == 2)
			{
				spawnFoodObject(big_food, occupied_space, collision_array, window_width, window_height);

			}
			else
			{
				spawnFoodObject(small_food, occupied_space, collision_array, window_width, window_height);
			}


		}
		*food_spawn_bonus_effect_timer -= 1;
	}
	else if (*food_spawn_bonus_effect)
	{
		*food_spawn_bonus_effect = false;
		*snake_speed = 5;
	}
}

void handleWallsBonus(bool* walls_bonus_effect, int*walls_bonus_effect_timer)
{
	if (*walls_bonus_effect&&*walls_bonus_effect_timer > 0)
	{
		*walls_bonus_effect_timer -= 1;
	}
	else if (*walls_bonus_effect)
	{
		*walls_bonus_effect = false;
	}
}

void handleNegativeBonus(bool* negative_effect, int* negative_effect_timer, int* occupied_space, int** collision_array, int window_width, int window_height, struct fifo_pointers fifo, struct list_node** obstacle)
{
	if (*negative_effect&&*negative_effect_timer > 0)
	{
		if (*negative_effect_timer > 120 - (1444 - *occupied_space) / 20)
		{

			if (*negative_effect_timer % 20 == 0)
			{
				if (*occupied_space < 1420)
				{
					int x = 0;
					int y = 0;
					do
					{

						randomizeFoodPosition(collision_array, &x, &y, window_width, window_height);
					} while (x<fifo.head->x + 60 && x>fifo.head->x - 60 && y<fifo.head->y + 60 && y>fifo.head->y - 60);
					addNode(obstacle, x, y);
					addObjectToCollisionArray(collision_array, x, y);
					*occupied_space = checkOccupiedSpaceAmount(collision_array);
				}
			}

		}


		*negative_effect_timer -= 1;
	}
	else if (*negative_effect)
	{
		*negative_effect = false;
	}
	else if (*obstacle)
	{
		struct list_node *tmp = *obstacle;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		removeObjectFromCollisionArray(collision_array, tmp->x, tmp->y);
		deleteNode(obstacle, tmp->x, tmp->y);
	}
}

void respawnBonusesPeriodically(int** collision_array, int* occupied_space, ALLEGRO_TIMER* timer, struct list_node **food_spawn_bonus, struct list_node **walls_bonus, struct list_node **negative_bonus, struct list_node **random_bonus, int window_width, int window_height)
{
	if (*occupied_space<1200 && al_get_timer_count(timer) % 900 == 0 && (!(*food_spawn_bonus) || !(*walls_bonus) || !(*negative_bonus) || !(*random_bonus)))
	{
		if (*negative_bonus)
		{
			struct list_node *tmp = *negative_bonus;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			removeObjectFromCollisionArray(collision_array, tmp->x, tmp->y);
			deleteNode(negative_bonus, tmp->x, tmp->y);
		}
		else if (*food_spawn_bonus)
		{
			struct list_node *tmp = *food_spawn_bonus;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			removeObjectFromCollisionArray(collision_array, tmp->x, tmp->y);
			deleteNode(food_spawn_bonus, tmp->x, tmp->y);
		}
		else if (*walls_bonus)
		{
			struct list_node *tmp = *walls_bonus;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			removeObjectFromCollisionArray(collision_array, tmp->x, tmp->y);
			deleteNode(walls_bonus, tmp->x, tmp->y);
		}
		else if (*random_bonus)
		{
			struct list_node *tmp = *random_bonus;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			removeObjectFromCollisionArray(collision_array, tmp->x, tmp->y);
			deleteNode(random_bonus, tmp->x, tmp->y);
		}
		int tmp = rand() % 5;
		if (tmp == 0)
		{
			spawnFoodObject(food_spawn_bonus, occupied_space, collision_array, window_width, window_height);
		}
		else if (tmp == 1)
		{
			spawnFoodObject(walls_bonus, occupied_space, collision_array, window_width, window_height);
		}
		else if (tmp == 2)
		{
			spawnFoodObject(negative_bonus, occupied_space, collision_array, window_width, window_height);
		}
		else
		{
			spawnFoodObject(random_bonus, occupied_space, collision_array, window_width, window_height);
		}
		*occupied_space = checkOccupiedSpaceAmount(collision_array);

	}
}