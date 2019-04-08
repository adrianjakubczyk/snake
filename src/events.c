#include "events.h"

void handleEscapeKeyEvent(bool* done, int* game_state,ALLEGRO_SAMPLE*menu_up)
{
	if (*game_state == MAIN_MENU)
	{
		*done = true;
	}
	else if (*game_state == GAME)
	{
		al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		*game_state = PAUSE;
	}
	else if (*game_state == PAUSE)
	{
		al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		*game_state = MAIN_MENU;
	}
	else if(*game_state!= GAME_OVER)
	{
		al_play_sample(menu_up, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		*game_state = MAIN_MENU;
	}
}