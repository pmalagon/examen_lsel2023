#include "snake_input.h"

#include "stm32f4xx_hal.h"

#define USER_BUTTON_PORT	GPIOC
#define USER_BUTTON_PIN	  GPIO_PIN_13

#define SHIELD_BUTTON_PORT	GPIOA
#define SHIELD_BUTTON_PIN	  GPIO_PIN_5

static int button_heading;

//TODO: flag variables

int
snake_input_init(snake_game_t* p_game)
{

  //TODO: Enable GPIOA and GPIOC clock

  //TODO: Configure PC.13 pin as input with falling Interrupt generation

  //TODO: Configure PA.5 pin as input with falling Interrupt generation

  //TODO: Enable and set EXTI line 15_10 Interrupt and 9_5 to the priority 3

  //TODO: init GPIO, EXTI and FLAGS

  button_heading = NONE;

  return 1;
}

void
HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  //TODO: act on flags depending on GPIO_Pin
}

void
EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(USER_BUTTON_PIN);
}

void
EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(SHIELD_BUTTON_PIN);
}

void
snake_input_update_new_heading (snake_game_t* p_game)
{
    p_game->new_heading = p_game->snake.heading;
    /* Global variable button_heading indicates last heading value of button */

    //TODO: check flags
    if (0) {
      /* Change: every USER button pressed, change button_heading COUNTERCLOCKWISE: */
      switch (button_heading) {
        case LEFT:  button_heading = DOWN;  break;
        case DOWN:  button_heading = RIGHT; break;
        case RIGHT: button_heading = UP;    break;
        case UP:    button_heading = LEFT;  break;
        default:    button_heading = UP;    break;
      }

      //TODO: User button update

    } else if (0) {
      /* Change: every SHIELD button pressed, change button_heading CLOCKWISE: */
      switch (button_heading) {
        case LEFT:  button_heading = UP;     break;
        case DOWN:  button_heading = LEFT;   break;
        case RIGHT: button_heading = DOWN;   break;
        case UP:    button_heading = RIGHT;  break;
        default:    button_heading = UP;     break;
      }

      //TODO: Shield button update

    }
}

void
snake_input_close(snake_game_t* p_game)
{
}

