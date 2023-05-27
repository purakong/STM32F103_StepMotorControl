
#include "../../../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xb.h"
#include "../../../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"
#include "../../../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_ll_usart.h"
#include "../../Inc/uart/uart.h"
#include "sys/_stdint.h"
#include "../../Inc/stepMotor/stepMotor.h"


uint8_t vUart_RecievedChar;
uint16_t vUart_RecievedData;

void USART1_RX_IT_Set(uint8_t flag)
{
	if(flag == 1)
	{
		*((volatile unsigned char *) 0x4001380C) |= UART_RXIT;
	}
	else if(flag == 0)
	{
		USART1->CR1 &= ~(UART_RXIT);
	}
}

void UART1_Write(uint8_t ch)
{
	//Make sure the Transmit data register is empty
	while(!(USART1->SR & SR_TXE)){}

	//Write to transmit data register
	USART1->DR = (ch & 0xFFU);

}


void UART_Write(USART_TypeDef *USARTx, uint8_t ch)
{
	//Make sure the Transmit data register is empty
	while(!(USART1->SR & SR_TXE)){}

	//Write to transmit data register
	USART1->DR = (ch & 0xFFU);

}

uint8_t UART3_Read(void)
{
	//Make sure the Receive data register is not empty
	while(!(USART3->SR & SR_RXE)){}

	/*Read Data*/
	return (uint8_t)USART3->DR;
}

void UART_printString(USART_TypeDef *USARTx, char *str)
{
	//'\0' 문자를 만날 때 까지 반복
	for(int i=0; str[i]; i++)
	{
		LL_USART_TransmitData8(USARTx,str[i]);
		HAL_Delay(1);
	}
}

void UART_printUnsigned8bitNumber(USART_TypeDef *USARTx, uint8_t data)
{
	//8bit는 255가 최대값이므로, 널문자를 포함한 4Byte 선언
	char numString[4] = "0";
	int i, index = 0;
	if(data>0)
	{
		for(i = 0; data !=0; i++)
		{
			numString[i] = data % 10 + '0';
			data = data/10;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for(i = index; i>=0; i--)
	{
		UART_Write(USARTx,numString[i]);
//		HAL_Delay(1);
	}
}

void UART_printUnsigned16bitNumber(USART_TypeDef *USARTx, uint16_t data)
{
	char numString[6] = "0";
	int i, index = 0;
	if(data>0)
	{
		for(i = 0; data !=0; i++)
		{
			numString[i] = data % 10 + '0';
			data = data/10;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for(i = index; i>=0; i--)
	{
		LL_USART_TransmitData8(USARTx,numString[i]);
		HAL_Delay(1);
	}
}

void UART_printSigned16bitNumber(USART_TypeDef *USARTx, int16_t data)
{
	char numString[7] = "0";
	int i, index = 0;
	unsigned short u_data;
	if(data>0)
	{
		for(i = 0; data !=0; i++)
		{
			numString[i] = data % 10 + '0';
			data = data/10;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	else if(data<0)
	{
		u_data = -data;
		for(i = 0; u_data !=0; i++)
		{
			numString[i] = u_data % 10 + '0';
			u_data = u_data/10;
		}
		numString[i] = '-';
		numString[++i] = '\0';
		index = i - 1;
	}

	for(i = index; i>=0; i--)
	{
		LL_USART_TransmitData8(USARTx,numString[i]);
		HAL_Delay(1);
	}
}

void UART_printUnsigned32bitNumber(USART_TypeDef *USARTx, uint32_t data)
{
	char numString[11] = "0";
	int i, index = 0;
	if(data>0)
	{
		for(i = 0; data !=0; i++)
		{
			numString[i] = data % 10 + '0';
			data = data/10;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for(i = index; i>=0; i--)
	{
		LL_USART_TransmitData8(USARTx,numString[i]);
		HAL_Delay(1);

	}
}

//실수형 변수 출력
//data 출력값, len: 소수점 이하 자릿수
void UART_printDouble(USART_TypeDef *USARTx, double data, int len)
{
	char numString[20] = "0";
	int i = 0;
	int j = 0;
	int index = 0;
	long long_data = (long)data;
	long decimal_data = (long)((data - (double)long_data)*pow(10.0,(double)len));
	unsigned long u_long_data;
	if(data > 0)
	{
		for(j = 0; j <len; j++)
		{
			numString[i] = decimal_data % 10 + '0';
			decimal_data = decimal_data/10;
			i++;
		}

		// 46의 아스키코드값은 '.'이다.
		numString[i] = 46;
		i++;

		for(i; long_data !=0; i++)
		{
			numString[i] = long_data % 10 + '0';
			long_data = long_data/10;
		}

		numString[i] = '\0';
		index = i - 1;
	}

	else if(data < 0)
	{
		decimal_data = -decimal_data;
		for(j = 0; j <len; j++)
		{
			numString[i] = decimal_data % 10 + '0';
			decimal_data = decimal_data/10;
			i++;
		}

		// 46의 아스키코드값은 '.'이다.
		numString[i] = 46;
		i++;

		u_long_data = -long_data;
		for(i; u_long_data !=0; i++)
		{
			numString[i] = u_long_data % 10 + '0';
			u_long_data = u_long_data/10;
		}
		numString[i] = '-';
		numString[++i] = '\0';
		index = i - 1;
	}

	for(i = index; i>=0; i--)
	{
		LL_USART_TransmitData8(USARTx, numString[i]);
		HAL_Delay(1);
	}

}

void USART_Rx_CallBack(USART_TypeDef *USARTx)
{
	vUart_RecievedChar = LL_USART_ReceiveData8(USARTx);

	if(vUart_RecievedChar == '/')
	{
		UART_Write(USARTx,0xA);
		stepMotor_Set_Angle(vUart_RecievedData);
		vUart_RecievedData = 0;
		vUart_RecievedChar = 0;
		StepMotor_SetStartFlag(1);
	}
	else
	{
		UART_Write(USARTx,vUart_RecievedChar);
		vUart_RecievedData *= 10;
		vUart_RecievedData += (vUart_RecievedChar - '0');
	}
}


void UART_Enable_RX_IT(void)
{
	LL_USART_EnableIT_RXNE(USART1);

	for(uint8_t i = 0; i<100; i++)
	{
		if(LL_USART_IsEnabledIT_RXNE(USART1) == UART_SUCCESS)
		{
			UART_printString(USART1,"USART1 RX is enabled");
			break;
		}
		else
		{
			LL_USART_EnableIT_RXNE(USART1);
		}
	}

	if(LL_USART_IsEnabledIT_RXNE(USART1) == UART_FAIL)
	{
		UART_printString(USART1,"USART1 RX isn't working");
	}
}
