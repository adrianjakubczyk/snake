#include "graphics.h"

void drawMenu(ALLEGRO_FONT*title_font, ALLEGRO_FONT*font, unsigned char r, unsigned char g, unsigned char b, int choice, int width, int height) {
	enum { START, RANKING, HELP, EXIT };
	al_draw_text(title_font, al_map_rgb(255, 255, 255), width / 2, height / 2 - 300, ALLEGRO_ALIGN_CENTER, "SNAKE");
	switch (choice)
	{
	case START:
		al_draw_text(font, al_map_rgb(r, g, b), width / 2, height / 2 - 100, ALLEGRO_ALIGN_CENTER, "START");
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTER, "RANKING");
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2 + 100, ALLEGRO_ALIGN_CENTER, "HELP");
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2 + 200, ALLEGRO_ALIGN_CENTER, "EXIT");
		break;
	case RANKING:
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2 - 100, ALLEGRO_ALIGN_CENTER, "START");
		al_draw_text(font, al_map_rgb(r, g, b), width / 2, height / 2, ALLEGRO_ALIGN_CENTER, "RANKING");
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2 + 100, ALLEGRO_ALIGN_CENTER, "HELP");
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2 + 200, ALLEGRO_ALIGN_CENTER, "EXIT");
		break;
	case HELP:
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2 - 100, ALLEGRO_ALIGN_CENTER, "START");
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTER, "RANKING");
		al_draw_text(font, al_map_rgb(r, g, b), width / 2, height / 2 + 100, ALLEGRO_ALIGN_CENTER, "HELP");
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2 + 200, ALLEGRO_ALIGN_CENTER, "EXIT");
		break;
	case EXIT:
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2 - 100, ALLEGRO_ALIGN_CENTER, "START");
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTER, "RANKING");
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, height / 2 + 100, ALLEGRO_ALIGN_CENTER, "HELP");
		al_draw_text(font, al_map_rgb(r, g, b), width / 2, height / 2 + 200, ALLEGRO_ALIGN_CENTER, "EXIT");
		break;
	default:
		break;
	}
}
void drawRanking(ALLEGRO_FONT* medium_font, ALLEGRO_FONT* small_font,struct ranking_record* records,int records_number,int window_width)
{
	al_draw_text(medium_font, al_map_rgb(255, 255, 255), window_width / 2, 50, ALLEGRO_ALIGN_CENTER, "RANKING");
	if (records)
	{
		if (records_number >= 10)
		{
			for (int i = 0; i < 10; ++i)
			{
				al_draw_textf(small_font, al_map_rgb(255, 255, 255), window_width / 2 - 150, 150 + (i * 50), ALLEGRO_ALIGN_LEFT, "%02d. ", i + 1);
				al_draw_textf(small_font, al_map_rgb(255, 255, 255), window_width / 2 - 110, 150 + (i * 50), ALLEGRO_ALIGN_LEFT, "%c %c %c", records[i].name[0], records[i].name[1], records[i].name[2]);
				al_draw_textf(small_font, al_map_rgb(255, 255, 255), window_width / 2 + 120, 150 + (i * 50), ALLEGRO_ALIGN_RIGHT, "%d", records[i].score);
			}
		}
		else
		{
			for (int i = 0; i < records_number; ++i)
			{
				al_draw_textf(small_font, al_map_rgb(255, 255, 255), window_width / 2 - 150, 150 + (i * 50), ALLEGRO_ALIGN_LEFT, "%02d. ", i + 1);
				al_draw_textf(small_font, al_map_rgb(255, 255, 255), window_width / 2 - 110, 150 + (i * 50), ALLEGRO_ALIGN_LEFT, "%c %c %c", records[i].name[0], records[i].name[1], records[i].name[2]);
				al_draw_textf(small_font, al_map_rgb(255, 255, 255), window_width / 2 + 120, 150 + (i * 50), ALLEGRO_ALIGN_RIGHT, "%d", records[i].score);
			}
			for (int i = records_number; i < 10; ++i)
			{
				al_draw_textf(small_font, al_map_rgb(255, 255, 255), window_width / 2 - 150, 150 + (i * 50), ALLEGRO_ALIGN_LEFT, "%02d. ", i + 1);
				al_draw_text(small_font, al_map_rgb(255, 255, 255), window_width / 2 - 110, 150 + (i * 50), ALLEGRO_ALIGN_LEFT, "----");
				al_draw_text(small_font, al_map_rgb(255, 255, 255), window_width / 2 + 120, 150 + (i * 50), ALLEGRO_ALIGN_RIGHT, "-");
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; ++i)
		{
			al_draw_textf(small_font, al_map_rgb(255, 255, 255), window_width / 2 - 150, 150 + (i * 50), ALLEGRO_ALIGN_LEFT, "%02d. ", i + 1);
			al_draw_text(small_font, al_map_rgb(255, 255, 255), window_width / 2 - 110, 150 + (i * 50), ALLEGRO_ALIGN_LEFT, "----");
			al_draw_text(small_font, al_map_rgb(255, 255, 255), window_width / 2 + 100, 150 + (i * 50), ALLEGRO_ALIGN_LEFT, "-----");
		}
	}
	al_draw_text(small_font, al_map_rgb(255, 255, 255), window_width / 2, 700, ALLEGRO_ALIGN_CENTER, "press ESC / ENTER to exit to main menu");
}
void drawGameOver(ALLEGRO_FONT* title_font,ALLEGRO_FONT* medium_font, ALLEGRO_FONT* small_font,struct ranking_record player,int menu_choice,int window_width,int window_height,unsigned char r, unsigned char g, unsigned char b)
{
	al_draw_filled_rectangle(20, 20, window_width - 20, window_height - 20, al_premul_rgba(0, 0, 0, 200));
	al_draw_text(title_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2 - 300, ALLEGRO_ALIGN_CENTER, "YOU DIED");
	al_draw_text(medium_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2 - 100, ALLEGRO_ALIGN_CENTER, "YOUR SCORE:");
	al_draw_textf(medium_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2, ALLEGRO_ALIGN_CENTER, "%d", player.score);
	al_draw_textf(medium_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2, ALLEGRO_ALIGN_CENTER, "%d", player.score);
	if (menu_choice == 0)
	{

		al_draw_filled_triangle(window_width / 2 + 80, window_height / 2 + 115, window_width / 2 + 90, window_height / 2 + 125, window_width / 2 + 80, window_height / 2 + 135, al_map_rgb(255, 255, 255));

		al_draw_filled_triangle(window_width / 2 - 50, window_height / 2 + 90, window_width / 2 - 45, window_height / 2 + 80, window_width / 2 - 40, window_height / 2 + 90, al_map_rgb(r, g, b));
		al_draw_filled_triangle(window_width / 2 - 50, window_height / 2 + 160, window_width / 2 - 45, window_height / 2 + 170, window_width / 2 - 40, window_height / 2 + 160, al_map_rgb(r, g, b));
		al_draw_filled_triangle(window_width / 2 - 5, window_height / 2 + 90, window_width / 2, window_height / 2 + 80, window_width / 2 + 5, window_height / 2 + 90, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 - 5, window_height / 2 + 160, window_width / 2, window_height / 2 + 170, window_width / 2 + 5, window_height / 2 + 160, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 + 50, window_height / 2 + 90, window_width / 2 + 45, window_height / 2 + 80, window_width / 2 + 40, window_height / 2 + 90, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 + 50, window_height / 2 + 160, window_width / 2 + 45, window_height / 2 + 170, window_width / 2 + 40, window_height / 2 + 160, al_map_rgb(255, 255, 255));

		al_draw_textf(medium_font, al_map_rgb(r, g, b), window_width / 2 - 45, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "%c", player.name[0]);
		al_draw_textf(medium_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "%c", player.name[1]);
		al_draw_textf(medium_font, al_map_rgb(255, 255, 255), window_width / 2 + 45, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "%c", player.name[2]);

	}
	else if (menu_choice == 1)
	{
		al_draw_filled_triangle(window_width / 2 - 80, window_height / 2 + 115, window_width / 2 - 90, window_height / 2 + 125, window_width / 2 - 80, window_height / 2 + 135, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 + 80, window_height / 2 + 115, window_width / 2 + 90, window_height / 2 + 125, window_width / 2 + 80, window_height / 2 + 135, al_map_rgb(255, 255, 255));

		al_draw_filled_triangle(window_width / 2 - 50, window_height / 2 + 90, window_width / 2 - 45, window_height / 2 + 80, window_width / 2 - 40, window_height / 2 + 90, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 - 50, window_height / 2 + 160, window_width / 2 - 45, window_height / 2 + 170, window_width / 2 - 40, window_height / 2 + 160, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 - 5, window_height / 2 + 90, window_width / 2, window_height / 2 + 80, window_width / 2 + 5, window_height / 2 + 90, al_map_rgb(r, g, b));
		al_draw_filled_triangle(window_width / 2 - 5, window_height / 2 + 160, window_width / 2, window_height / 2 + 170, window_width / 2 + 5, window_height / 2 + 160, al_map_rgb(r, g, b));
		al_draw_filled_triangle(window_width / 2 + 50, window_height / 2 + 90, window_width / 2 + 45, window_height / 2 + 80, window_width / 2 + 40, window_height / 2 + 90, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 + 50, window_height / 2 + 160, window_width / 2 + 45, window_height / 2 + 170, window_width / 2 + 40, window_height / 2 + 160, al_map_rgb(255, 255, 255));

		al_draw_textf(medium_font, al_map_rgb(255, 255, 255), window_width / 2 - 45, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "%c", player.name[0]);
		al_draw_textf(medium_font, al_map_rgb(r, g, b), window_width / 2, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "%c", player.name[1]);
		al_draw_textf(medium_font, al_map_rgb(255, 255, 255), window_width / 2 + 45, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "%c", player.name[2]);
	}
	else if (menu_choice == 2)
	{
		al_draw_filled_triangle(window_width / 2 - 80, window_height / 2 + 115, window_width / 2 - 90, window_height / 2 + 125, window_width / 2 - 80, window_height / 2 + 135, al_map_rgb(255, 255, 255));


		al_draw_filled_triangle(window_width / 2 - 50, window_height / 2 + 90, window_width / 2 - 45, window_height / 2 + 80, window_width / 2 - 40, window_height / 2 + 90, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 - 50, window_height / 2 + 160, window_width / 2 - 45, window_height / 2 + 170, window_width / 2 - 40, window_height / 2 + 160, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 - 5, window_height / 2 + 90, window_width / 2, window_height / 2 + 80, window_width / 2 + 5, window_height / 2 + 90, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 - 5, window_height / 2 + 160, window_width / 2, window_height / 2 + 170, window_width / 2 + 5, window_height / 2 + 160, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(window_width / 2 + 50, window_height / 2 + 90, window_width / 2 + 45, window_height / 2 + 80, window_width / 2 + 40, window_height / 2 + 90, al_map_rgb(r, g, b));
		al_draw_filled_triangle(window_width / 2 + 50, window_height / 2 + 160, window_width / 2 + 45, window_height / 2 + 170, window_width / 2 + 40, window_height / 2 + 160, al_map_rgb(r, g, b));

		al_draw_textf(medium_font, al_map_rgb(255, 255, 255), window_width / 2 - 45, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "%c", player.name[0]);
		al_draw_textf(medium_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "%c", player.name[1]);
		al_draw_textf(medium_font, al_map_rgb(r, g, b), window_width / 2 + 45, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "%c", player.name[2]);
	}
	al_draw_text(small_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2 + 250, ALLEGRO_ALIGN_CENTER, "press ENTER to confirm");
}
void drawHelp(ALLEGRO_FONT* font, ALLEGRO_FONT* big_font,unsigned char r, unsigned char g, unsigned char b)
{
	al_draw_text(big_font, al_map_rgb(255, 255, 255), 400, 100, ALLEGRO_ALIGN_CENTER, "HELP");
	al_draw_filled_circle(250, 200, 5, al_map_rgb(181, 230, 29));
	al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200-9, ALLEGRO_ALIGN_LEFT, "-  small food - gives +1 snake length");
	al_draw_filled_rounded_rectangle(240, 240, 260, 260, 3, 3, al_map_rgb(0, 162, 232));
	al_draw_text(font, al_map_rgb(255, 255, 255), 300, 250 - 9, ALLEGRO_ALIGN_LEFT, "-  big food - gives +2 snake length");
	al_draw_filled_triangle(250 - 10, 300 - 5, 250, 300 + 10, 250 + 10, 300 - 5, al_map_rgb(r, g, b));
	al_draw_filled_triangle(250 - 10, 300 + 5, 250, 300 - 10, 250 + 10, 300 + 5, al_map_rgb(r, g, b));
	al_draw_text(font, al_map_rgb(255, 255, 255), 300, 300 - 9, ALLEGRO_ALIGN_LEFT, "-  random bonus");
	al_draw_filled_rectangle(250 - 10, 350 - 10, 250 + 10, 350 + 10, al_map_rgb(255, 255, 255));
	al_draw_text(font, al_map_rgb(255, 255, 255), 300, 350 - 9, ALLEGRO_ALIGN_LEFT, "-  obstacle - do not try to eat it");
	al_draw_filled_triangle(250 - 10, 400, 250, 400 + 10, 250 + 10, 400, al_premul_rgba(24, 240, 180, r));
	al_draw_filled_triangle(250 - 10, 400, 250, 400 - 10, 250 + 10, 400, al_premul_rgba(24, 240, 180, r));
	al_draw_text(font, al_map_rgb(255, 255, 255), 300, 400 - 9, ALLEGRO_ALIGN_LEFT, "-  bonus - lets you go through walls");
	al_draw_filled_rectangle(250 - (b / 20 + 2), 450 - (b / 20 + 2), 250 + (b / 20 + 2), 450 + (b / 20 + 2), al_map_rgb(250, 65, 20));
	al_draw_text(font, al_map_rgb(255, 255, 255), 300, 450 - 9, ALLEGRO_ALIGN_LEFT, "-  \"negative bonus\" - spawns obstacle");
	al_draw_filled_circle(250, 500, b / 45.0, al_map_rgb(181, 230, 29));
	al_draw_filled_circle(250 - 5, 500 - 5, b / 45.0, al_map_rgb(0, 162, 232));
	al_draw_filled_circle(250 - 5, 500 + 5, b / 45.0, al_map_rgb(181, 230, 29));
	al_draw_filled_circle(250 + 5, 500 + 5, b / 45.0, al_map_rgb(0, 162, 232));
	al_draw_filled_circle(250 + 5, 500 - 5, b / 45.0, al_map_rgb(181, 230, 29));
	al_draw_text(font, al_map_rgb(255, 255, 255), 300, 500 - 9, ALLEGRO_ALIGN_LEFT, "-  food bonus - speeds you up for");
	al_draw_text(font, al_map_rgb(255, 255, 255), 300, 530 - 9, ALLEGRO_ALIGN_LEFT, "a while and spawns lots of food");

	al_draw_text(font, al_map_rgb(255, 255, 255), 400, 650, ALLEGRO_ALIGN_CENTER, "press ESC to return");

}
void drawPause(ALLEGRO_FONT* medium_font, ALLEGRO_FONT* small_font,struct fifo_pointers fifo, int window_width,int window_height,int speed_x,int speed_y)
{
	al_draw_filled_rectangle(20, 20, window_width - 20, window_height - 20, al_premul_rgba(0, 0, 0, 200));

	if (speed_y == -20)
		al_draw_filled_triangle(fifo.head->x - 9, fifo.head->y - 11, fifo.head->x, fifo.head->y - 20, fifo.head->x + 9, fifo.head->y - 11, al_map_rgb(34, 177, 76));
	else if (speed_x == 20)
		al_draw_filled_triangle(fifo.head->x + 11, fifo.head->y - 9, fifo.head->x + 20, fifo.head->y, fifo.head->x + 11, fifo.head->y + 9, al_map_rgb(34, 177, 76));
	else if (speed_y == 20)
		al_draw_filled_triangle(fifo.head->x - 9, fifo.head->y + 11, fifo.head->x, fifo.head->y + 20, fifo.head->x + 9, fifo.head->y + 11, al_map_rgb(34, 177, 76));
	else if (speed_x == -20)
		al_draw_filled_triangle(fifo.head->x - 11, fifo.head->y - 9, fifo.head->x - 20, fifo.head->y, fifo.head->x - 11, fifo.head->y + 9, al_map_rgb(34, 177, 76));
	al_draw_text(medium_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2 - 100, ALLEGRO_ALIGN_CENTER, "PAUSE");
	al_draw_text(small_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2 + 100, ALLEGRO_ALIGN_CENTER, "ESC to exit to main menu");
	al_draw_text(small_font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2 + 200, ALLEGRO_ALIGN_CENTER, "P/ENTER to resume");
}
void drawInGameScore(ALLEGRO_FONT* medium_font,int** collision_array,struct ranking_record player, int window_width,int window_height,int* alpha)
{
	
	if (checkScoreCollision(collision_array))
	{
		if (*alpha > 100)*alpha -= 10;
		al_draw_text(medium_font, al_premul_rgba(255, 255, 255, *alpha), window_width - 150, 30, ALLEGRO_ALIGN_RIGHT, "SCORE:");
		al_draw_textf(medium_font, al_premul_rgba(255, 255, 255, *alpha), window_width - 30, 30, ALLEGRO_ALIGN_RIGHT, "%d", player.score);
	}
	else
	{
		if (*alpha < 255)*alpha += 10;
		if (*alpha > 255)*alpha = 255;
		al_draw_text(medium_font, al_premul_rgba(255, 255, 255, *alpha), window_width - 150, 30, ALLEGRO_ALIGN_RIGHT, "SCORE:");
		al_draw_textf(medium_font, al_premul_rgba(255, 255, 255, *alpha), window_width - 30, 30, ALLEGRO_ALIGN_RIGHT, "%d", player.score);
	}
}
void drawSnake(struct fifo_pointers fifo)
{
	while (fifo.head) {
		
		al_draw_filled_rectangle(fifo.head->x - 9, fifo.head->y - 9, fifo.head->x + 9, fifo.head->y + 9, al_map_rgb(34, 177, 76));
		fifo.head = fifo.head->next;
	}
}
void drawSmallFood(struct list_node *small_food, float food_radius)
{
	while (small_food)
	{
		al_draw_filled_circle(small_food->x, small_food->y, food_radius, al_map_rgb(181, 230, 29));
		small_food=small_food->next;
	}
	
}
void drawBigFood(struct list_node *big_food, float rect_rounding_radius)
{
	while (big_food)
	{
		al_draw_filled_rounded_rectangle(big_food->x - 10, big_food->y - 10, big_food->x + 10, big_food->y + 10, rect_rounding_radius, rect_rounding_radius, al_map_rgb(0, 162, 232));
		big_food = big_food->next;
	}
}
void drawRandomBonus(struct list_node *random_bonus, unsigned char r, unsigned char g, unsigned char b)
{
	while (random_bonus)
	{
		al_draw_filled_triangle(random_bonus->x - 10, random_bonus->y - 5, random_bonus->x, random_bonus->y + 10, random_bonus->x + 10, random_bonus->y - 5, al_map_rgb(r, g, b));
		al_draw_filled_triangle(random_bonus->x - 10, random_bonus->y + 5, random_bonus->x, random_bonus->y - 10, random_bonus->x + 10, random_bonus->y + 5, al_map_rgb(r, g, b));
		random_bonus = random_bonus->next;
	}
}
void drawObstacle(struct list_node *obstacle)
{
	while (obstacle)
	{
		al_draw_filled_rectangle(obstacle->x - 10, obstacle->y - 10, obstacle->x + 10, obstacle->y + 10, al_map_rgb(255, 255, 255));
		obstacle = obstacle->next;
	}
	
}
void drawWallsBonus(struct list_node *diamond,unsigned char alpha)
{
	while (diamond)
	{
		al_draw_filled_triangle(diamond->x - 10, diamond->y, diamond->x, diamond->y + 10, diamond->x + 10, diamond->y, al_premul_rgba(24,240,180,alpha));
		al_draw_filled_triangle(diamond->x - 10, diamond->y, diamond->x, diamond->y - 10, diamond->x + 10, diamond->y, al_premul_rgba(24, 240, 180, alpha));
		diamond = diamond->next;
	}

}
void drawNegativeBonus(struct list_node *negative_bonus, unsigned char size)
{
	while (negative_bonus)
	{
		al_draw_filled_rectangle(negative_bonus->x - (size / 20 + 2), negative_bonus->y - (size / 20 + 2), negative_bonus->x + (size / 20 + 2), negative_bonus->y + (size / 20 + 2), al_map_rgb(250, 65, 20));
		negative_bonus = negative_bonus->next;
	}
}
void drawFoodSpawnBonus(struct list_node *food_spawn, unsigned char size)
{
	while (food_spawn)
	{
		al_draw_filled_circle(food_spawn->x, food_spawn->y, size/45.0, al_map_rgb(181, 230, 29));
		al_draw_filled_circle(food_spawn->x - 5, food_spawn->y - 5, size/45.0, al_map_rgb(0, 162, 232));
		al_draw_filled_circle(food_spawn->x - 5, food_spawn->y + 5, size / 45.0, al_map_rgb(181, 230, 29));
		al_draw_filled_circle(food_spawn->x + 5, food_spawn->y + 5,size/45.0, al_map_rgb(0, 162, 232));
		al_draw_filled_circle(food_spawn->x + 5, food_spawn->y - 5, size / 45.0, al_map_rgb(181, 230, 29));

		food_spawn = food_spawn->next;
	}
}
void drawBonusTimer(ALLEGRO_FONT* font, bool walls_bonus_effect,int walls_bonus_effect_timer,bool negative_effect,int negative_effect_timer,bool food_spawn_bonus_effect, int food_spawn_bonus_effect_timer,int window_width,int window_height)
{
	if (walls_bonus_effect)
	{
		al_draw_textf(font, al_premul_rgba(24, 240, 180, 150), window_width / 2, window_height / 2 - 30, ALLEGRO_ALIGN_CENTER, "%d", walls_bonus_effect_timer / 60);
	}
	else if (negative_effect)
	{
		al_draw_textf(font, al_premul_rgba(250, 65, 20, 150), window_width / 2, window_height / 2 - 30, ALLEGRO_ALIGN_CENTER, "%d", negative_effect_timer / 60);
	}
	else if (food_spawn_bonus_effect)
	{
		al_draw_textf(font, al_premul_rgba(40, 180, 80, 150), window_width / 2, window_height / 2 - 30, ALLEGRO_ALIGN_CENTER, "%d", food_spawn_bonus_effect_timer / 60);
	}
}
void animateRainbowColorChange(struct color_flags *color_flag, unsigned char *r, unsigned char *g, unsigned char *b)
{
	if (color_flag->r == 0) (*r) += 5;
	if (color_flag->r == 1) (*r) -= 5;
	if (color_flag->g == 0) (*g) += 5;
	if (color_flag->g == 1) (*g) -= 5;
	if (color_flag->b == 0) (*b) += 5;
	if (color_flag->b == 1) (*b) -= 5;

	if ((*r) >= 255) color_flag->r = 1;
	if ((*r) <= 100) color_flag->r = 0;
	if ((*g) >= 255) color_flag->g = 1;
	if ((*g) <= 50) color_flag->g = 0;
	if ((*b) >= 150) color_flag->b = 1;
	if ((*b) <= 100) color_flag->b = 0;
}
void animateFoodSizeChange(float *radius, int *flag, int max_value, int min_value, float change_value)
{
	if (*flag == 0) *radius += change_value;
	if (*flag == 1) *radius -= change_value;

	if (*radius >= max_value) { *flag = 1; *radius = max_value; }
	if (*radius <= min_value) { *flag = 0; *radius = min_value; }
}
