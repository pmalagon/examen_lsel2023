#include "snake_display.h"

#define _GNU_SOURCE

#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_X 16
#define MAX_Y 16

struct fb_t {
  char pixel[MAX_Y][MAX_X];
};
static struct fb_t fb_s;
static struct fb_t* fb = &fb_s;

static void
clear_screen()
{
  printf("\e[1;1H\e[2J");
}

static void
print_hlimit(snake_game_t* p_game)
{
  printf("+");
  for (int i = 0; i < p_game->limits.x; i++) {
    printf("-");
  }
  printf("+\r\n");
}

static void
print_row(snake_game_t* p_game, int y)
{
  printf("|");

  for (int i=0; i<p_game->limits.x; i++) {
    printf("%c", fb->pixel[y][i]);
  }

  printf("|\r\n");
}

void 
snake_display_render(snake_game_t* p_game)
{
  memset(fb, ' ', sizeof(struct fb_t));

  // Draw the apple
  fb->pixel[p_game->apple.y][p_game->apple.x] = '*';

  // Draw the snake body navigating through the linked list
  struct segment_t *seg_i;
  for(seg_i = p_game->snake.tail; seg_i->next; seg_i=seg_i->next) {
    fb->pixel[seg_i->y][seg_i->x] = 'o';
  }

  // Draw the snake head
  fb->pixel[seg_i->y][seg_i->x] = '@';
  
  clear_screen();

  /* Copy from linux solution */
  print_hlimit(p_game);
  for (int i=0; i<p_game->limits.y; i++) {
    print_row(p_game, i);
  }
  print_hlimit(p_game);
}

int
snake_display_init(snake_game_t* p_game)
{
  clear_screen();
  return ((p_game->limits.x <= MAX_X) && (p_game->limits.y <= MAX_Y));
}

void
snake_display_close(snake_game_t* p_game)
{
  clear_screen();
}
