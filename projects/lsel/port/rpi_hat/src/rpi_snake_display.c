#include "snake_display.h"

#define _GNU_SOURCE

#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define DEV_FB "/dev"
#define FB_DEV_NAME "fb"

#define MAX_X	8
#define MAX_Y	8

struct fb_t {
	uint16_t pixel[MAX_Y][MAX_X];
};

static int is_framebuffer_device(const struct dirent *dir)
{
	return strncmp(FB_DEV_NAME, dir->d_name,
		       strlen(FB_DEV_NAME)-1) == 0;
}

static int open_fbdev(const char *dev_name)
{
	struct dirent **namelist;
	int i, ndev;
	int fd = -1;
	struct fb_fix_screeninfo fix_info;

	ndev = scandir(DEV_FB, &namelist, is_framebuffer_device, versionsort);
	if (ndev <= 0)
		return ndev;

	for (i = 0; i < ndev; i++)
	{
		char fname[64];

		snprintf(fname, sizeof(fname),
			 "%s/%s", DEV_FB, namelist[i]->d_name);
		fd = open(fname, O_RDWR);
		if (fd < 0)
			continue;
		ioctl(fd, FBIOGET_FSCREENINFO, &fix_info);
		if (strcmp(dev_name, fix_info.id) == 0)
			break;
		close(fd);
		fd = -1;
	}
	for (i = 0; i < ndev; i++)
		free(namelist[i]);

	return fd;
}

static int fbfd = 0;
static struct fb_t* fb = NULL;

void 
snake_display_render(snake_game_t* p_game)
{
	// Clear
	memset(fb, 0, 128);

	// Draw the apple
	fb->pixel[p_game->apple.y][p_game->apple.x] = 0x07E0;

	// Draw the snake body navigating through the linked list
	struct segment_t *seg_i;
	for(seg_i = p_game->snake.tail; seg_i->next; seg_i=seg_i->next) {
		fb->pixel[seg_i->y][seg_i->x] = 0xF800;
	}

	// Draw the snake head
	fb->pixel[seg_i->y][seg_i->x] = 0x001F;
}

int
snake_display_init(snake_game_t* p_game)
{
  if ((p_game->limits.x > MAX_X) || (p_game->limits.y > MAX_Y)) {
	return 0;
  }

  fbfd = open_fbdev("RPi-Sense FB");
  if (fbfd <= 0) {
    return 0;
  }

  // Memory-map the framebuffer
  fb = mmap(0, 128, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
  if (!fb) {
    close(fbfd);
    return 0;
  }

  // Clear screen	
  memset(fb, 0, 128);

  //Success
  return 1;
}

void
snake_display_close(snake_game_t* p_game)
{
	if(fb) {
		//Clear screen
		memset(fb, 0, 128);

		// Unmap framebuffer
		munmap(fb, 128);
	}

	// Close device file
	if(fbfd > 0) {
		close(fbfd);
	}
}
