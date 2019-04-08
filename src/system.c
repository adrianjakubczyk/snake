#include "system.h"

void abortGame(const char* message)
{
	MessageBox(0, message, "Error", MB_OK);
	exit(1);
}
void initAllegro(ALLEGRO_TIMER** timer,ALLEGRO_SAMPLE**menu_up, ALLEGRO_SAMPLE**menu_down, ALLEGRO_SAMPLE**eat_food,ALLEGRO_SAMPLE** eat_bonus, ALLEGRO_SAMPLE** hit, ALLEGRO_SAMPLE** game_over, ALLEGRO_SAMPLE** game_music,ALLEGRO_SAMPLE_INSTANCE**game_music_instance, ALLEGRO_DISPLAY** display, ALLEGRO_EVENT_QUEUE** event_queue, bool * done, int width, int height)
{
	if (!al_init())
		abortGame("Failed to initialize allegro");

	if (!al_install_audio()) {
		abortGame("Failed to initialize audio!");
	}

	if (!al_init_acodec_addon()) {
		abortGame("Failed to initialize audio codecs!");
	}

	if (!al_reserve_samples(10)) {
		abortGame("failed to reserve samples!");
	}

	*menu_up = al_load_sample("res/music/menu_up.wav");

	if (!(*menu_up)) {
		abortGame("Audio clip menu_up not loaded!");
	}
	*menu_down = al_load_sample("res/music/menu_down.wav");

	if (!(*menu_down)) {
		abortGame("Audio clip menu_down not loaded!");
	}

	*eat_food = al_load_sample("res/music/eat_food.wav");

	if (!(*eat_food)) {
		abortGame("Audio clip eat_food not loaded!");
	}

	*eat_bonus = al_load_sample("res/music/eat_bonus.wav");

	if (!(*eat_bonus)) {
		abortGame("Audio clip eat_bonus not loaded!");
	}

	*hit = al_load_sample("res/music/hit.wav");

	if (!(*hit)) {
		abortGame("Audio clip hit not loaded!");
	}
	*game_over = al_load_sample("res/music/game_over.wav");

	if (!(*game_over)) {
		abortGame("Audio clip game_over not loaded!");
	}
	*game_music = al_load_sample("res/music/game_music.wav");

	if (!(*game_music)) {
		abortGame("Audio clip game_music not loaded!");
	}
	*game_music_instance = al_create_sample_instance(*game_music);
	if (!(*game_music_instance)) {
		abortGame("Audio clip game_music_instance not loaded!");
	}
	al_set_sample_instance_playmode(*game_music_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(*game_music_instance, al_get_default_mixer());
	if (!al_init_font_addon())
		abortGame("Failed to initialize font addon");

	if (!al_init_ttf_addon())
		abortGame("Failed to initialize true type font addon");

	if (!al_init_primitives_addon())
		abortGame("Failed to initialize primitives addon");

	if (!al_install_keyboard())
		abortGame("Failed to install keyboard");

	(*timer) = al_create_timer(1.0 / 60);
	if (!(*timer))
		abortGame("Failed to create timer");

	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	(*display) = al_create_display(width, height);
	if (!(*display))
		abortGame("Failed to create display");

	(*event_queue) = al_create_event_queue();
	if (!(*event_queue))
		abortGame("Failed to create event queue");

	al_register_event_source((*event_queue), al_get_keyboard_event_source());
	al_register_event_source((*event_queue), al_get_timer_event_source((*timer)));
	al_register_event_source((*event_queue), al_get_display_event_source((*display)));

	*done = false;
}
void shutdownAllegro(ALLEGRO_DISPLAY**display, ALLEGRO_TIMER**timer, ALLEGRO_EVENT_QUEUE**event_queue, ALLEGRO_FONT**title_font, ALLEGRO_FONT**small_font, ALLEGRO_FONT**medium_font)
{
	al_destroy_display(*display);
	al_uninstall_keyboard();
	al_destroy_timer(*timer);
	al_destroy_event_queue(*event_queue);
	al_destroy_font(*title_font);
	al_destroy_font(*small_font);
	al_destroy_font(*medium_font);
}
void removeListsAndQueue(struct fifo_pointers* fifo, struct list_node **small_food, struct list_node **big_food, struct list_node **obstacle, struct list_node **food_spawn_bonus, struct list_node **walls_bonus, struct list_node **random_bonus, struct list_node **negative_bonus)
{
	while (fifo->head)
		dequeue(fifo);
	removeList(small_food);
	removeList(big_food);
	removeList(obstacle);
	removeList(food_spawn_bonus);
	removeList(walls_bonus);
	removeList(random_bonus);
	removeList(negative_bonus);
}