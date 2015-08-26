#include "stm32f4xx.h"
#include "tm_stm32f4_ili9341_ltdc.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_exti.h"
#include "tm_stm32f4_gpio.h"
#include <stdio.h>

#define BUTTON_TYPE GPIOC
#define BUTTON_RCC RCC_AHB1Periph_GPIOC
#define BUTTON_PIN GPIO_Pin_14
volatile uint8_t Button_Pressed = 0; 

int main(void){
	SystemInit();
	TM_DELAY_Init();
	TM_ILI9341_Init();
	TM_ILI9341_SetLayer1();

	/* Initialize USART2 at 115200 baud, TX: PD5, RX: PD6 */
	TM_USART_Init(USART2, TM_USART_PinsPack_2, 115200);
	
	/* Attach interrupt on pin PC14 = External line 14 */
	TM_EXTI_Attach(BUTTON_TYPE, BUTTON_PIN, TM_EXTI_Trigger_Rising);

	char str[32] = {0};
	while(1){

		TM_ILI9341_Fill(ILI9341_COLOR_WHITE);

		if (!GPIO_ReadInputDataBit( BUTTON_TYPE, BUTTON_PIN))
		{
			sprintf(str,"button on press");
		}else if (GPIO_ReadInputDataBit( BUTTON_TYPE, BUTTON_PIN) && Button_Pressed)
		{
			sprintf(str, "button on release");
			Button_Pressed = 0;
		}else
		{
			sprintf(str, "button released");
		}
		TM_ILI9341_Puts(50, 130, str, &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLUE);
		TM_USART_Puts(USART2, str); 
		TM_USART_Puts("\n\r", str); 
		Delayms(100);
	}

}

void TM_EXTI_Handler_14(void)
{
	if (GPIO_ReadInputDataBit(BUTTON_TYPE, BUTTON_PIN) && !Button_Pressed){
		Button_Pressed = 1;
	}
}

uint32_t L3GD20_TIMEOUT_UserCallback(void)
{
	return 0;
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	while (1) { } 
}
#endif

