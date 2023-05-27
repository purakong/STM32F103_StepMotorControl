#ifndef UART_UART_H_
#define UART_UART_H_

#include "../../../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xb.h"

#define SR_RXE			(1U<<5)
#define SR_TXE			(1U<<7)

#define UART_RXIT		(1U<<5)

#define UART_SUCCESS	(1U)
#define UART_FAIL		(0U)
extern void UART1_Write(uint8_t ch);
extern void USART_Rx_CallBack(USART_TypeDef *USARTx);
extern void USART1_RX_IT_Set(uint8_t flag);
extern void UART_Enable_RX_IT(void);

#endif /* UART_UART_H_ */
