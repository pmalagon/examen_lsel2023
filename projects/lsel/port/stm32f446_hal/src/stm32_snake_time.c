#include "snake_time.h"

#include "stm32f4xx_hal.h"

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while (1)
      ;
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    while (1)
      ;
  }
}

//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
void SysTick_Handler(void)
{
  /* TODO Update global tick variable */
  HAL_IncTick();
}
	
int 
snake_time_init (snake_game_t* p_game) 
{
  HAL_Init();

  SystemClock_Config();

  return 1;
}

uint32_t
snake_time_get_ms()
{
  return HAL_GetTick();
}

void 
snake_time_close () 
{
}

void 
snake_time_delay_ms (uint32_t ms) 
{
  HAL_Delay(ms);
}
