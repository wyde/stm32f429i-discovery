#include "stm32f4xx.h"
#include "tm_stm32f4_ili9341_ltdc.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_i2c.h"
#include <stdio.h>

int main(void){
	SystemInit();
	TM_DELAY_Init();
	TM_ILI9341_Init();
	TM_ILI9341_SetLayer1();

	/* Initialize USART2 at 115200 baud, TX: PD5, RX: PD6 */
	TM_USART_Init(USART2, TM_USART_PinsPack_2, 115200);
	
	uint8_t wacc = 0x3A; // 0xA6
	uint8_t racc = 0x3B; // 0xA7

	// 0x2D POWER_CTL: Power-saving features control
	TM_I2C_Write(I2C2, wacc, 0x2D, 0x08);
	// 0x31 DATA_FORMAT: Data format control
	//TM_I2C_Write(I2C1, wacc, 0x31, 0x0B); // FULL_RES and +- 16g
	TM_I2C_Write(I2C2, wacc, 0x31, 0x01); // fixed resolution and +- 4g
	// 0x2C BW_RATE: Data rate and power mode control
	TM_I2C_Write(I2C2, wacc, 0x2C, 0x0A);
	
	char str[16] = {0};
	sprintf(str, "delay = 100");
	TM_USART_Puts(USART2, str); 
	while(1){

		TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
		TM_ILI9341_Puts(30, 30, str, &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLUE2);
		uint8_t buff[6] = {0};
		int16_t tri[3] = {0};
		TM_I2C_ReadMulti(I2C2, racc, 0x32, buff, 6);
		
		// original read digit
		tri[0] = (int16_t) ((uint16_t)buff[1] << 8 | (uint16_t)buff[0]);	
		tri[1] = (int16_t) ((uint16_t)buff[3] << 8 | (uint16_t)buff[2]);	
		tri[2] = (int16_t) ((uint16_t)buff[5] << 8 | (uint16_t)buff[4]);	
		
		float ftri[3] = {0}, divisor = 128.0f;
		ftri[0] = (float) tri[0] / divisor;
		ftri[1] = (float) tri[1] / divisor;
		ftri[2] = (float) tri[2] / divisor;
	
		sprintf(str, "%.3f,%.3f,%.3f\n\r", ftri[0], ftri[1], ftri[2]);
		TM_USART_Puts(USART2, str); 
		TM_ILI9341_Puts(30, 50, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		
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

