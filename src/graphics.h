#include "system.h"
#include "list.h"
#include "queue.h"
#include "snake_and_food.h"
#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

struct color_flags
{
	unsigned char r : 1;
	unsigned char g : 1;
	unsigned char b : 1;
};

void drawMenu(ALLEGRO_FONT*title_font, ALLEGRO_FONT*font, unsigned char r, unsigned char g, unsigned char b, int choice, int width, int height);

void drawRanking(ALLEGRO_FONT* medium_font, ALLEGRO_FONT* small_font, struct ranking_record* records, int records_number, int window_width);

void drawGameOver(ALLEGRO_FONT* title_font, ALLEGRO_FONT* medium_font, ALLEGRO_FONT* small_font, struct ranking_record player, int menu_choice, int window_width, int window_height, unsigned char r, unsigned char g, unsigned char b);

void drawHelp(ALLEGRO_FONT* font, ALLEGRO_FONT* big_font, unsigned char r, unsigned char g, unsigned char b);

void drawPause(ALLEGRO_FONT* medium_font, ALLEGRO_FONT* small_font, struct fifo_pointers fifo, int window_width, int window_height, int speed_x, int speed_y);

void drawInGameScore(ALLEGRO_FONT* medium_font, int** collision_array, struct ranking_record player, int window_width, int window_height, int* alpha);

void drawSnake(struct fifo_pointers fifo);

void drawSmallFood(struct list_node *small_food, float food_radius);

void drawBigFood(struct list_node *big_food, float rect_rounding_radius);

void drawRandomBonus(struct list_node *random_bonus, unsigned char r, unsigned char g, unsigned char b);

void drawObstacle(struct list_node *obstacle);

void drawWallsBonus(struct list_node *diamond, unsigned char alpha);

void drawNegativeBonus(struct list_node *negative_bonus, unsigned char size);

void drawFoodSpawnBonus(struct list_node *food_spawn, unsigned char size);

void drawBonusTimer(ALLEGRO_FONT* font, bool walls_bonus_effect, int walls_bonus_effect_timer, bool negative_effect, int negative_effect_timer, bool food_spawn_bonus_effect, int food_spawn_bonus_effect_timer, int window_width, int window_height);

void animateRainbowColorChange(struct color_flags *color_flag, unsigned char *r, unsigned char *g, unsigned char *b);

void animateFoodSizeChange(float *radius, int *flag, int max_value, int min_value, float change_value);

#endif