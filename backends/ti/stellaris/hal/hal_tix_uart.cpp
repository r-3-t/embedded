#include <usart_conf.hpp>
#include <string.h>
#include <hw_types.h>
#include <hw_memmap.h>
#include <UartInterface.hpp>

#include <gpio.h>
#include <uart.h>

#define TIXX_UART_MAX_COUNT								3

namespace tix
{

	namespace uart
	{

		static ::tix::uart::Uart*				gpUarts[TIXX_UART_MAX_COUNT];

		#define USART_IRQ_CALLBACK(UsartX)	void USART##UsartX##_IRQHandler()																\
											{																								\
												unsigned long status;																		\
												status = UARTIntStatus(gpUarts[UsartX]->UART_Base, false);								\
												if ((status & UART_INT_RX) == UART_INT_RX)													\
												{																							\
													gpUarts[UsartX]->_callback(gpUarts[UsartX]->receive());							\
												}																							\
												status = UARTIntStatus(gpUarts[UsartX]->UART_Base, true);								\
												UARTIntClear(gpUarts[UsartX]->UART_Base, status);										\
											}

		extern "C"
		{

			USART_IRQ_CALLBACK(0)
			USART_IRQ_CALLBACK(1)
			USART_IRQ_CALLBACK(2)

		}

		Uart::Uart(unsigned int id, ::uart::UartInterface::uart_callback_T callback, ::uart::Configuration config)
		{
			_id = id;
			_callback = callback;
			_config = config;
			_configured = false;

			gpUarts[id - 1] = this;
		}

		void Uart::Configure()
		{

			//GPIO configuration for UART use
			unsigned long RxPinConfig;
			unsigned long TxPinConfig;

			//clocks associated to UARTs
			unsigned long UartPeripheral;
			unsigned long GPIOPeripheral;

			// the gpio used
			unsigned long GPIO_Port;
			unsigned char GPIO_Pin_TX;			// the selected pin
			unsigned char GPIO_Pin_RX;			// the selected pin

			switch (_id)
			{
			case 1:
				UART_Base = UART0_BASE;
				UartPeripheral = SYSCTL_PERIPH_UART0;
				GPIOPeripheral = SYSCTL_PERIPH_GPIOA;
				RxPinConfig = GPIO_PA0_U0RX;
				TxPinConfig = GPIO_PA1_U0TX;
				GPIO_Port = GPIO_PORTA_BASE;
				GPIO_Pin_RX = GPIO_PIN_0;
				GPIO_Pin_TX = GPIO_PIN_1;
				UARTIntRegister(UART_Base, USART0_IRQHandler);
				break;
			case 2:
				UART_Base = UART1_BASE;
				UartPeripheral = SYSCTL_PERIPH_UART1;
				GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
				RxPinConfig = GPIO_PB0_U1RX;
				TxPinConfig = GPIO_PB1_U1TX;
				GPIO_Port = GPIO_PORTB_BASE;
				GPIO_Pin_RX = GPIO_PIN_0;
				GPIO_Pin_TX = GPIO_PIN_1;
				UARTIntRegister(UART_Base, USART1_IRQHandler);
				break;
			case 3:
				UART_Base = UART2_BASE;
				UartPeripheral = SYSCTL_PERIPH_UART2;
				GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
				RxPinConfig = GPIO_PD6_U2RX;
				TxPinConfig = GPIO_PD7_U2TX;
				GPIO_Port = GPIO_PORTB_BASE;
				GPIO_Pin_RX = GPIO_PIN_6;
				GPIO_Pin_TX = GPIO_PIN_7;
				UARTIntRegister(UART_Base, USART2_IRQHandler);
				break;
			default:
				return;
				break;
			} //end switch


			//
			// Enable the peripherals
			//
			SysCtlPeripheralEnable(UartPeripheral);
			SysCtlPeripheralEnable(GPIOPeripheral);


			//
			// Set GPIO for UART pins.
			//
			GPIOPinConfigure(RxPinConfig);
			GPIOPinConfigure(TxPinConfig);
			GPIOPinTypeUART(GPIO_Port, GPIO_Pin_RX | GPIO_Pin_TX);

			//
			// Configure the UART
			//
			UARTConfigSetExpClk(UART_Base, SysCtlClockGet(),
								conf_2_baudrate(_config.baudRate),
								(conf_2_Parity(_config.Parity)
								| conf_2_StopBits(_config.StopBits)
								| conf_2_WordLength(_config.WordLength)));


			//
			// Configure Hardware control flow
			//
			UARTFlowControlSet(UART_Base, conf_2_HardwareFlowControl(_config.HardwareFlowControl));

			//
			// Enable interrupt on RX event
			//
			UARTIntEnable(UART_Base, UART_INT_RX);

			//
			// Disable FIFOs, one interrupt to user per car
			//
			UARTFIFODisable(UART_Base);


			_configured = true;
		}

		void Uart::send(const char* const str)
		{
			send((const unsigned char*) str, (unsigned int)strlen(str));
		}


		void Uart::send(const types::buffer& buf)
		{
			if (_configured == false)
			{
				this->Configure();
			}
			for (auto c : buf)
			{
				UARTCharPut(UART_Base, c & 0xFF);
			}

		}

		void Uart::send(const unsigned char* buf, unsigned int length)
		{
			if (_configured == false)
			{
				this->Configure();
			}
			for (unsigned int i = 0; i < length; i++)
			{
				UARTCharPut(UART_Base, buf[i] & 0xFF);
			}
		}

		unsigned char Uart::receive()
		{
			return (unsigned char) (UARTCharGetNonBlocking(UART_Base) & 0xFF);
		}


	} /* namespace uart  */

} /* namespace tix  */

