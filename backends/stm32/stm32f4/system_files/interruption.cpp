#include <hal/uart.hpp>
#include <stm32f4xx_usart.h>


namespace stm32f4
{



namespace uart
{

	#define USART_IRQ_CALLBACK(UsartX)	void USART##UsartX##_IRQn()										\
										{																\
										    ::uart::get_instance(UsartX).accumulator(USART##UsartX ->DR);		\
										}

	#define UART_IRQ_CALLBACK(UartX)	void UART##UartX##_IRQn()										\
										{																\
										    ::uart::get_instance(UartX).accumulator(UART##UartX ->DR);		\
										}


	USART_IRQ_CALLBACK(1)
	USART_IRQ_CALLBACK(2)
	USART_IRQ_CALLBACK(3)
	UART_IRQ_CALLBACK(4)
	UART_IRQ_CALLBACK(5)
	USART_IRQ_CALLBACK(6)


}





}
