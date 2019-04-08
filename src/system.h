#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include<stdlib.h>
#include "queue.h"
#include "list.h"
#include <Windows.h>
#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

struct ranking_record
{
	int score;
	char name[3];
};

enum { UP, RIGHT, DOWN, LEFT };

enum { MAIN_MENU, GAME, GAME_OVER, RANKING, PAUSE, HELP };

void abortGame(const char* message);

void initAllegro(ALLEGRO_TIMER** timer, ALLEGRO_SAMPLE**menu_up, ALLEGRO_SAMPLE**menu_down, ALLEGRO_SAMPLE**eat_food, ALLEGRO_SAMPLE** eat_bonus, ALLEGRO_SAMPLE** hit, ALLEGRO_SAMPLE** game_over, ALLEGRO_SAMPLE** game_music, ALLEGRO_SAMPLE_INSTANCE**game_music_instance, ALLEGRO_DISPLAY** display, ALLEGRO_EVENT_QUEUE** event_queue, bool * done, int width, int height);

void shutdownAllegro(ALLEGRO_DISPLAY**display, ALLEGRO_TIMER**timer, ALLEGRO_EVENT_QUEUE**event_queue, ALLEGRO_FONT**title_font, ALLEGRO_FONT**small_font, ALLEGRO_FONT**medium_font);

void removeListsAndQueue(struct fifo_pointers* fifo, struct list_node **small_food, struct list_node **big_food, struct list_node **obstacle, struct list_node **food_spawn_bonus, struct list_node **walls_bonus, struct list_node **random_bonus, struct list_node **negative_bonus);

#endif