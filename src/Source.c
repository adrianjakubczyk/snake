#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "list.h"
#include "queue.h"
#include "collisions.h"
#include "snake_and_food.h"
#include "system.h"
#include "file.h"


int main()
{
	
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_SAMPLE *menu_up;
	ALLEGRO_SAMPLE *menu_down;
	ALLEGRO_SAMPLE *eat_food;
	ALLEGRO_SAMPLE *eat_bonus;
	ALLEGRO_SAMPLE *hit;
	ALLEGRO_SAMPLE *game_over;
	ALLEGRO_SAMPLE *game_music;
	ALLEGRO_SAMPLE_INSTANCE *game_music_instance;

	ALLEGRO_DISPLAY* display;

	bool done;
	int window_width = 800;
	int window_height = 800;

	initAllegro(&timer,&menu_up,&menu_down,&eat_food,&eat_bonus,&hit,&game_over,&game_music,&game_music_instance,&display,&event_queue,&done, window_width, window_height);
	srand(time(0));
	
	ALLEGRO_FONT* title_font = al_load_ttf_font("res/fonts/foo.ttf", 156, 0);
	ALLEGRO_FONT* small_font = al_load_ttf_font("res/fonts/autobus-bold.ttf", 24, 0);
	ALLEGRO_FONT* medium_font = al_load_ttf_font("res/fonts/autobus-bold.ttf",64,0);

	struct fifo_pointers fifo = { NULL,NULL };

	struct list_node *small_food = NULL;
	struct list_node *big_food = NULL;
	struct list_node *obstacle = NULL;

	struct list_node *food_spawn_bonus = NULL;
	struct list_node *walls_bonus = NULL;
	struct list_node *negative_bonus = NULL;
	struct list_node *random_bonus = NULL;
	
	struct ranking_record player;
	player.score = 30;
	player.name[0] = 'A';
	player.name[1] = 'A';
	player.name[2] = 'A';
	char snake_speed = 5;
	
	int speed_x = 0;
	int speed_y = 0;

	int last_move = -1;
	int next_move = -1;
	int next_next_move = -1;
	
	float big_food_radius = 0;
	int big_food_radius_flag = 0;

	float small_food_radius = 0;
	int small_food_radius_flag = 0;

	struct color_flags color_flag;
	color_flag.r = 0;
	color_flag.g = 0;
	color_flag.b = 0;

	unsigned char r = 200;
	unsigned char g = 100;
	unsigned char b = 0;
	int alpha = 255;

	bool food_spawn_bonus_effect = false;
	bool walls_bonus_effect = false;
	bool negative_effect = false;

	int food_spawn_bonus_effect_timer = 0;
	int walls_bonus_effect_timer = 0;
	int negative_effect_timer = 0;

	int game_state = MAIN_MENU;
	int menu_choice=0;
	
	int **collision_array;
	collision_array = (int **)calloc(38, sizeof(int*));
	for (int i = 0; i < 38; i++)
		collision_array[i] = (int*)calloc(38, sizeof(int));
	int occupied_space = 0;

	int records_number = 0;
	struct ranking_record *records = NULL;
	
	bool redraw = true;
	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;

			animateRainbowColorChange(&color_flag, &r, &g, &b);

			if (game_state == GAME)
			{
				al_play_sample_instance(game_music_instance);
				animateFoodSizeChange(&small_food_radius, &small_food_radius_flag, 7, 5, 0.1f);
				animateFoodSizeChange(&big_food_radius, &big_food_radius_flag, 10, 5, 0.3f);

				if (fifo.head)
				{
					if (al_get_timer_count(timer) % snake_speed == 0)
					{
						setMovementDirection(&last_move, &next_move, &next_next_move, &speed_x, &speed_y);

						checkDeadlyCollisions(&game_state, walls_bonus_effect, speed_x, speed_y, fifo, obstacle, window_width, window_height);
						

						if (game_state != GAME_OVER)
						{
							
							if ((speed_x || speed_y))
							{
								moveSnake(collision_array, fifo, speed_x, speed_y, walls_bonus_effect, window_width, window_height);
								occupied_space = checkOccupiedSpaceAmount(collision_array);
							}
							if (checkFoodPieceCollision(fifo.head->x, fifo.head->y, small_food))
							{
								al_play_sample(eat_food, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								eatSmallFood(&player.score, &fifo, &small_food, &big_food, &occupied_space, collision_array, window_width, window_height);
							}
							if (checkFoodPieceCollision(fifo.head->x, fifo.head->y, big_food))
							{
								al_play_sample(eat_food, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								eatBigFood(&player.score, &fifo, &big_food, &small_food, &occupied_space, collision_array, window_width, window_height);
							}
							if (checkFoodPieceCollision(fifo.head->x, fifo.head->y, random_bonus))
							{
								al_play_sample(eat_bonus, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								eatRandomBonus(&random_bonus, fifo, &food_spawn_bonus_effect, &food_spawn_bonus_effect_timer,&snake_speed, &walls_bonus_effect, &walls_bonus_effect_timer, &negative_effect, &negative_effect_timer);
							}
							if (checkFoodPieceCollision(fifo.head->x, fifo.head->y, food_spawn_bonus))
							{
								al_play_sample(eat_bonus, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								eatFoodSpawnBonus(&food_spawn_bonus, fifo, &food_spawn_bonus_effect, &food_spawn_bonus_effect_timer,&snake_speed);
							}
							if (checkFoodPieceCollision(fifo.head->x, fifo.head->y, walls_bonus))
							{
								al_play_sample(eat_bonus, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								eatWallsBonus(&walls_bonus, fifo, &walls_bonus_effect, &walls_bonus_effect_timer);
							}
							if (checkFoodPieceCollision(fifo.head->x, fifo.head->y, negative_bonus))
							{
								al_play_sample(eat_bonus, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								eatNegativeBonus(&negative_bonus, fifo, &negative_effect, &negative_effect_timer);
							}
						}
						
					}
					if (game_state==GAME_OVER)
					{
						al_stop_sample_instance(game_music_instance);
						al_play_sample(hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						al_play_sample(game_over, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						if (walls_bonus_effect)
						{
							walls_bonus_effect = false;
						}
					}
						
					handleFoodSpawnBonus(&food_spawn_bonus_effect, &food_spawn_bonus_effect_timer, &small_food, &big_food, &occupied_space, collision_array,&snake_speed, window_width, window_height);
					handleWallsBonus(&walls_bonus_effect, &walls_bonus_effect_timer);
					handleNegativeBonus(&negative_effect, &negative_effect_timer, &occupied_space, collision_array, window_width, window_height, fifo, &obstacle);

					respawnBonusesPeriodically(collision_array, &occupied_space, timer, &food_spawn_bonus, &walls_bonus, &negative_bonus, &random_bonus, window_width, window_height);
				}
			}	
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) 
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				handleEscapeKeyEvent(&done, &game_state,menu_up);
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_UP && game_state!=PAUSE)
			{
				if (game_state == MAIN_MENU&&menu_choice > 0)
				{
					al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu_choice--;
					
				}
				else if (game_state == GAME)
				{
					if (last_move != DOWN&& last_move != UP)
					{
						next_move = UP;
					}
					else if (last_move == DOWN || last_move == UP)
					{
						next_next_move = UP;
					}
				}
				else if (game_state == GAME_OVER)
				{
					if (player.name[menu_choice] - 1 < 'A')
					{
						al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						player.name[menu_choice] = 'Z';
					}
					else
					{
						al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						player.name[menu_choice] -= 1;
					}
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN  && game_state != PAUSE)
			{
				if (game_state == MAIN_MENU&&menu_choice < 3)
				{
					al_play_sample(menu_down, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu_choice++;
				}
				else if (game_state == GAME)
				{
					if (last_move != -1 && last_move != UP && last_move != DOWN)
						next_move = DOWN;
					else if (last_move == UP || last_move == DOWN)
						next_next_move = DOWN;
				}
				else if (game_state == GAME_OVER)
				{
					if (player.name[menu_choice] + 1 > 'Z')
					{
						al_play_sample(menu_down, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						player.name[menu_choice] = 'A';
					}
					else
					{
						al_play_sample(menu_down, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						player.name[menu_choice] += 1;
					}
				}

			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT  && game_state != PAUSE)
			{
				if (game_state == GAME)
				{
					if (last_move != RIGHT && last_move != LEFT)
					{
						next_move = LEFT;
					}
						
					else if (last_move == RIGHT || last_move == LEFT)
					{
						next_next_move = LEFT;
					}
				}
				else if (game_state == GAME_OVER&&menu_choice>0)
				{
					al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu_choice--;
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && game_state != PAUSE)
			{
				if (game_state == GAME)
				{
					if (last_move != LEFT && last_move != RIGHT)
					{
						next_move = RIGHT;
					}	
					else if (last_move == LEFT || last_move == RIGHT)
					{
						next_next_move = RIGHT;
					}
						
				}
				else if (game_state == GAME_OVER&&menu_choice<2)
				{
					al_play_sample(menu_down, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu_choice++;
				}
				
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_P)
			{
				if (game_state == PAUSE)
				{
					al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					game_state = GAME;
				}
				else
				{
					al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					game_state = PAUSE;
				}
					
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_SPACE)
			{
				if (game_state == MAIN_MENU)
				{
					if (menu_choice == 0)
					{
						al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						prepareForStart(&snake_speed,
							&speed_x,
							&speed_y,
							&last_move,
							&next_move,
							&next_next_move,
							&food_spawn_bonus_effect,
							&walls_bonus_effect,
							&negative_effect,
							&food_spawn_bonus_effect_timer,
							&walls_bonus_effect_timer,
							&negative_effect_timer,
							&player,
							&occupied_space,
							collision_array,
							&fifo,
							&small_food,
							&big_food,
							&obstacle,
							&food_spawn_bonus,
							&walls_bonus,
							&random_bonus,
							&negative_bonus);
						startGame(collision_array,&fifo,&small_food,&occupied_space, window_width, window_height);

						game_state = GAME;
					}
					if (menu_choice == 1)
					{
						al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						game_state = RANKING;
						
						if (!records)
						{
							readFromFile(&records_number, &records);
						}
						
					}
					if (menu_choice == 2)
					{
						al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						game_state = HELP;
					}
					if (menu_choice == 3)
					{
						done=true;
					}
				}
				else if (game_state == GAME_OVER)
				{
					al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					game_state = RANKING;
					

					if (!records)
					{
						readFromFile(&records_number, &records);
					}
					

					saveToFile(records_number, records, player);
					readFromFile(&records_number, &records);
				}
				else if (game_state == PAUSE)
				{
					al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					game_state = GAME;
				}
				else if (game_state == RANKING)
				{
					al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					game_state = MAIN_MENU;
					menu_choice = 0;
				}
				
			}
			
		}
		

		

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (!walls_bonus_effect)
			{
				al_draw_rectangle(10, 10, window_width - 10, window_height - 10, al_map_rgb(255, 255, 255), 20);
			}
			else
			{
				al_draw_rectangle(10, 10, window_width - 10, window_height - 10, al_premul_rgba(24, 240, 180, r), 20);
			}
			
			if (game_state == GAME||game_state==PAUSE)
			{
				drawBonusTimer(medium_font, walls_bonus_effect, walls_bonus_effect_timer, negative_effect, negative_effect_timer, food_spawn_bonus_effect, food_spawn_bonus_effect_timer, window_width, window_height);

				drawSmallFood(small_food, small_food_radius);
				drawBigFood(big_food, big_food_radius);
				drawFoodSpawnBonus(food_spawn_bonus, r);
				drawWallsBonus(walls_bonus, r);
				drawNegativeBonus(negative_bonus, b);
				drawRandomBonus(random_bonus, r, g, b);
				drawObstacle(obstacle);

				drawSnake(fifo, r, g, b);

				drawInGameScore(medium_font, collision_array, player, window_width, window_height,&alpha);

				if (game_state==PAUSE)
				{
					drawPause( medium_font, small_font, fifo, window_width, window_height, speed_x, speed_y);
				}
				
			}
			else if (game_state == GAME_OVER)
			{
				drawGameOver(title_font, medium_font, small_font, player, menu_choice, window_width, window_height, r, g, b);

			}
			else if (game_state == MAIN_MENU)
			{
				drawMenu(title_font, medium_font, r, g, b, menu_choice, window_width, window_height);
			}
			else if (game_state == RANKING)
			{
				drawRanking( medium_font, small_font, records, records_number, window_width);
			}
			else if (game_state == HELP)
			{
				drawHelp(small_font,medium_font,r,g,b);
			}

			al_flip_display();
		}
	}
	
	removeListsAndQueue(&fifo, &small_food, &big_food, &obstacle, &food_spawn_bonus, &walls_bonus, &random_bonus, &negative_bonus);
	for (int i = 0; i < 38; i++)
		free(collision_array[i]);
	free(collision_array);
	if (records)
		free(records);
	shutdownAllegro(&display, &timer, &event_queue, &title_font, &small_font, &medium_font);
	return 0;
}