#include "stm32f4xx.h"
#include "tm_stm32f4_ili9341_ltdc.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_usart.h"
#include <stdio.h>

int main(void){
	SystemInit();
	TM_DELAY_Init();
	TM_ILI9341_Init();
	TM_ILI9341_SetLayer1();

	/* Initialize USART2 at 115200 baud, TX: PD5, RX: PD6 */
	TM_USART_Init(USART2, TM_USART_PinsPack_2, 115200);

	char str[16] = {0};
	while(1){

		sprintf(str, "hello world!!");
		TM_ILI9341_Puts(30, 30, str, &TM_Font_11x18, ILI9341_COLOR_BLUE2, ILI9341_COLOR_WHITE);
		TM_USART_Puts(USART2, str); 
		Delayms(100);
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

