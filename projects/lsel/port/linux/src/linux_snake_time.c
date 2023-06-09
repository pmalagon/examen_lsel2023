#include "snake_time.h"

#include <unistd.h>

int 
snake_time_init (snake_game_t* p_game) 
{
    return 1;
}

void 
snake_time_close () 
{
}

void 
snake_time_delay_ms (uint32_t ms) 
{
  usleep(1000*ms)
;}
