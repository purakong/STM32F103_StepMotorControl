#include "../../Inc/sys/systick.h"

void delayMs(uint32_t delay_ms)
{
	//Reload with number of clocks per millisecond
	USER_SysTick->LOAD	= SYSTICK_LOAD_MS_VAL;

	//Clear Systick Curren value register
	USER_SysTick->VAL = 0;

	//Enable Systick and select internal clk source
	USER_SysTick->CTRL = SYSTICK_EN | SYSTICK_CLK_SRC;

	for(uint32_t i = 0; i<delay_ms; i++)
	{
		//Wait until the COUNT FLAG is set
		//while문을 1ms마다 빠져나간다
		while((USER_SysTick->CTRL & SYSTICK_COUNT_FLAG) == 0){}
	}

	USER_SysTick->CTRL = 0;
}

void delayUs(uint32_t delay_us)
{
	//Reload with number of clocks per millisecond
	USER_SysTick->LOAD	= SYSTICK_LOAD_US_VAL;

	//Clear Systick Curren value register
	USER_SysTick->VAL = 0;

	//Enable Systick and select internal clk source
	USER_SysTick->CTRL = SYSTICK_EN | SYSTICK_CLK_SRC;

	for(uint32_t i = 0; i<delay_us; i++)
	{
		//Wait until the COUNT FLAG is set
		//while문을 1ms마다 빠져나간다
		while((USER_SysTick->CTRL & SYSTICK_COUNT_FLAG) == 0){}
	}

//	USER_SysTick->CTRL = 0;
	USER_SysTick->LOAD	= SYSTICK_LOAD_10MS_VAL;
}

void SysTimerSetting(void)
{
	//Reload with number of clocks per millisecond
	USER_SysTick->LOAD	= SYSTICK_LOAD_10MS_VAL;

	//Clear Systick Curren value register
	USER_SysTick->VAL = 0;

	//Enable Systick and select internal clk source
//	USER_SysTick->CTRL = SYSTICK_EN | SYSTICK_CLK_SRC | SYSTICK_INT;
	USER_SysTick->CTRL = SYSTICK_EN | SYSTICK_CLK_SRC;
}
