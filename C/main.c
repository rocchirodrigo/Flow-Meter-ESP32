/* Includes ------------------------------------------------------------------*/
#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ContaPulso = 0;
uint32_t Calibracao = 0.00225;
uint32_t Tempo = 0;
uint32_t Litros = 0;
uint32_t Total = 0;
uint32_t Vazao;
TIM_HandleTypeDef hTIM2;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	
static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is 
	   clocked below the maximum system frequency, to update the voltage scaling value 
	   regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		for (;;) ;
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
	   clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		/* Initialization Error */
		for (;;) ;
	}

	/* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
	if (HAL_GetREVID() == 0x1001)
	{
		/* Enable the Flash prefetch */
		__HAL_FLASH_PREFETCH_BUFFER_ENABLE();
	}
}

void Button_Config()
{
	__GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED_Config()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Timer_Config()
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	
	hTIM2.Instance = TIM2;
	hTIM2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	hTIM2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hTIM2.Init.CounterMode = TIM_COUNTERMODE_DOWN;
	hTIM2.Init.Period = 8400 - 1;
	hTIM2.Init.Prescaler = 5000 - 1;
	hTIM2.Init.RepetitionCounter = 11;
	
	HAL_TIM_Base_Init(&hTIM2);
	HAL_TIM_Base_Start(&hTIM2);
}

int main(void)
{
	/* Variaveis */
	int tickProximo;
	int taxaMedicao = 1000;
		
	HAL_Init();
	SystemClock_Config();
	
	LED_Config();
	Button_Config();
	Timer_Config();
	
	tickproximo = HAL_GetTick() + taxaMedicao;	// Taxa de atualização de 1seg
	
	/* Loop Embarcado */
	for (;;)
	{
		// Contagem dos Pulsos
		if()
		{
			Contador_Pulso = Contador_Pulso + 1;
		}
		
		/* Caso chegue a 1 segundo, calcula a vazão e reseta a contagem */
		if(HAL_GetTick() >= tickProximo)
		{
			Litros = ContaPulso * Calibracao;
			Total = Total + Litros;
			Vazao = Litros * 60;
			Litros = 0;
			ContaPulso = 0;
		}
	}
}
