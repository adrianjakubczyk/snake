#include "collisions.h"
int checkOccupiedSpaceAmount(int **collision_array)
{
	int acc = 0;
	for (int i = 0; i < 38; ++i)
	{
		for (int j = 0; j < 38; ++j)
		{
			if (collision_array[i][j] == 1)
				acc += 1;
		}
	}
	return acc;
}
void addObjectToCollisionArray(int **collision_array, int x, int y)
{
	collision_array[(y - 30) / 20][(x - 30) / 20] = 1;

}
void removeObjectFromCollisionArray(int **collision_array, int x, int y)
{
	collision_array[(y - 30) / 20][(x - 30) / 20] = 0;
}



bool checkSelfCollision(struct fifo_pointers fifo, int speed_x, int speed_y)
{
	if (fifo.head&&fifo.head->next)
	{
		struct fifo_node *tmp = fifo.head;
		fifo.head = fifo.head->next;
		while (fifo.head) {
			if (tmp->x + speed_x == fifo.head->x&&tmp->y + speed_y == fifo.head->y)
				return true;
			else
				fifo.head = fifo.head->next;
		}
	}
	return false;
}

bool checkFoodPieceCollision(int x, int y, struct list_node *food)
{
	while (food)
	{

		if (food&&x&&y)
		{

			if (y == food->y&&x == food->x)
			{
				return true;
			}

		}
		food = food->next;
	}
	return false;
}

bool checkScoreCollision(int **collision_array)
{
	for (int i = 0; i<6; ++i)
		for (int j = 22; j < 38; ++j)
		{
			if (collision_array[i][j] == 1)
			{
				return true;
			}
		}
	return false;
}
bool checkWallsCollision(int speed_x, int speed_y, struct fifo_pointers fifo, int width, int height)
{
	if (speed_x)
	{
		if (fifo.head->x + speed_x > width - 30 || fifo.head->x + speed_x < 30)
		{
			return true;
		}
	}
	else if (speed_y)
	{
		if (fifo.head->y + speed_y > height - 30 || fifo.head->y + speed_y < 30)
		{
			return true;
		}
	}
	return false;
}
void checkDeadlyCollisions(int*game_state, bool walls_bonus_effect, int speed_x, int speed_y, struct fifo_pointers fifo, struct list_node*obstacle, int window_width, int window_height)
{
	if (*game_state != GAME_OVER)
	{
		if (!walls_bonus_effect&&checkWallsCollision(speed_x, speed_y, fifo, window_width, window_height))
		{
			*game_state = GAME_OVER;
		}
		if (checkSelfCollision(fifo, speed_x, speed_y))
		{
			*game_state = GAME_OVER;
		}
		if (checkFoodPieceCollision(fifo.head->x + speed_x, fifo.head->y + speed_y, obstacle))
		{
			*game_state = GAME_OVER;
		}
	}

}