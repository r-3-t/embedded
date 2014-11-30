#include <usart_conf.hpp>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <hw_types.h>
#include <hw_memmap.h>
#include <SpiInterface.hpp>
#include <ssi.h>
#include <interrupt.h>
#include <hw_ints.h>


#define TIXX_SPI_MAX_COUNT								3

namespace tix
{

	namespace spi
	{

		static ::tix::spi::Spi*				gpSpis[TIXX_SPI_MAX_COUNT];

		#define SPI_IRQ_CALLBACK(SpiX)	void SPI##SpiX##_IRQHandler()																\
											{																								\
												unsigned long status;																		\
												status = SSIIntStatus(gpSpis[SpiX]->SSI_Base, false);								\
												if ((status & SSI_RXFF) == SSI_RXFF)													\
												{																							\
													gpSpis[SpiX]->_callback(gpSpis[SpiX]->recv());							\
												}																							\
												if ((status & SSI_RXTO) == SSI_RXTO)													\
												{																							\
													gpSpis[SpiX]->_callback(gpSpis[SpiX]->recv());							\
												}																							\
												status = SSIIntStatus(gpSpis[SpiX]->SSI_Base, true);								\
												SSIIntClear(gpSpis[SpiX]->SSI_Base, status);										\
											}

		extern "C"
		{

				SPI_IRQ_CALLBACK(0)
				SPI_IRQ_CALLBACK(1)
				SPI_IRQ_CALLBACK(2)

		}

		Spi::Spi(unsigned int id, ::spi::SpiInterface::spi_callback_T callback, ::spi::Configuration config)
		{
			_id = id;
			_callback = callback;
			_config = config;

			gpSpis[id - 1] = this;
			
			this->Configure();
		}

		void Spi::Configure()
		{

			//GPIO configuration for SSI use
			unsigned long ClkPinConfig;
			unsigned long FssPinConfig;
			unsigned long RxPinConfig;
			unsigned long TxPinConfig;

			//clocks associated to UARTs
			unsigned long SSIPeripheral;
			unsigned long GPIOPeripheral;

			// the gpio used
			unsigned long 		GPIO_Port;
			unsigned char		GPIO_Pin_FSS;			// the selected pin
			unsigned char		GPIO_Pin_SCK;			// the selected pin
			unsigned char		GPIO_Pin_MISO;			// the selected pin
			unsigned char		GPIO_Pin_MOSI;			// the selected pin

			switch (_id)
			{
				case 1:
					//SSI base
					SSI_Base					= SSI0_BASE;

					//Peripheral clocks
					SSIPeripheral				= SYSCTL_PERIPH_SSI0;
					GPIOPeripheral				= SYSCTL_PERIPH_GPIOA;

					//Configure GPIO for SSI
					ClkPinConfig				= GPIO_PA2_SSI0CLK;
					FssPinConfig				= GPIO_PA3_SSI0FSS;
					RxPinConfig					= GPIO_PA4_SSI0RX;
					TxPinConfig					= GPIO_PA5_SSI0TX;

					//GPIO for SSI pins
					GPIO_Port					= GPIO_PORTA_BASE;
					GPIO_Pin_FSS				= GPIO_PIN_3;
					GPIO_Pin_SCK				= GPIO_PIN_2;
					GPIO_Pin_MISO				= GPIO_PIN_4;
					GPIO_Pin_MOSI				= GPIO_PIN_5;

					SSIIntRegister(SSI_Base, SPI0_IRQHandler);

					break;

				case 2:
					//SSI base
					SSI_Base					= SSI1_BASE;

					//Peripheral clocks
					SSIPeripheral				= SYSCTL_PERIPH_SSI1;
					GPIOPeripheral				= SYSCTL_PERIPH_GPIOD;

					//Configure GPIO for SSI
					ClkPinConfig				= GPIO_PD0_SSI1CLK;
					FssPinConfig				= GPIO_PD1_SSI1FSS;
					RxPinConfig					= GPIO_PD2_SSI1RX;
					TxPinConfig					= GPIO_PD3_SSI1TX;

					//GPIO for SSI pins
					GPIO_Port					= GPIO_PORTD_BASE;
					GPIO_Pin_FSS				= GPIO_PIN_1;
					GPIO_Pin_SCK				= GPIO_PIN_0;
					GPIO_Pin_MISO				= GPIO_PIN_2;
					GPIO_Pin_MOSI				= GPIO_PIN_3;

					SSIIntRegister(SSI_Base, SPI1_IRQHandler);

				case 3:
					//SSI base
					SSI_Base					= SSI2_BASE;

					//Peripheral clocks
					SSIPeripheral				= SYSCTL_PERIPH_SSI2;
					GPIOPeripheral				= SYSCTL_PERIPH_GPIOB;

					//Configure GPIO for SSI
					ClkPinConfig				= GPIO_PB4_SSI2CLK;
					FssPinConfig				= GPIO_PB5_SSI2FSS;
					RxPinConfig					= GPIO_PB6_SSI2RX;
					TxPinConfig					= GPIO_PB7_SSI2TX;

					//GPIO for SSI pins
					GPIO_Port					= GPIO_PORTB_BASE;
					GPIO_Pin_FSS				= GPIO_PIN_5;
					GPIO_Pin_SCK				= GPIO_PIN_4;
					GPIO_Pin_MISO				= GPIO_PIN_6;
					GPIO_Pin_MOSI				= GPIO_PIN_7;

					SSIIntRegister(SSI_Base, SPI2_IRQHandler);

					break;


				default:
					fprintf(stderr, "Unimplemented spi %i !\n", _id);
					abort();
					break;
			}


			//
			// Enable the peripherals
			//
			SysCtlPeripheralEnable(GPIOPeripheral);
			SysCtlPeripheralEnable(SSIPeripheral);


			//
			// Set GPIO for SSI pins.
			//
			GPIOPinConfigure(ClkPinConfig);
			GPIOPinConfigure(FssPinConfig);
			GPIOPinConfigure(RxPinConfig);
			GPIOPinConfigure(TxPinConfig);

			GPIOPinTypeSSI(GPIO_Port, GPIO_Pin_FSS | GPIO_Pin_SCK | GPIO_Pin_MISO | GPIO_Pin_MOSI);

			//master
			SSIConfigSetExpClk(SSI_Base, SysCtlClockGet(), (conf_2_ClockPolarity(_config.clockPolarity) << 1) | conf_2_ClockPhase(_config.clockPhase),
					conf_2_mode(_config.mode), _config.DataRate, 8);

			//
			// Enable interrupt on RX event
			//
			SSIIntEnable(SSI_Base, SSI_RXFF | SSI_RXTO);


			//enable SSI
			SSIEnable(SSI_Base);

			_configured = true;
		}

		uint8_t Spi::send(uint8_t data)
		{
			unsigned long   result;
			unsigned long	data_8;

			//SSIDataPut is blocking
			data_8 = data & 0xFF;
			SSIDataPut(SSI_Base, data_8);

			SSIDataGet(SSI_Base, &result);

			//wait end of transmission
			while (SSIBusy(SSI_Base) == true);

			return result & 0xFF;
		}

		uint8_t Spi::recv()
		{
			unsigned long   result;

			SSIDataGet(SSI_Base, &result);

			return result & 0xFF;
		}

		void Spi::send(types::fifo& send_fifo)
		{
			unsigned char c;

			while (cbuff_dequeue(&send_fifo, &c, sizeof(c)) > 0)
			{
				send(c & 0xFF);
			}

		}

		void Spi::send(const unsigned char* buf, unsigned int length)
		{
			for (unsigned int i = 0; i < length; i++)
			{
				send(buf[i] & 0xFF);
			}
		}


	} /* namespace spi  */

} /* namespace tix  */

