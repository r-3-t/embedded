#pragma once

#include <spi.hpp>
#include <hal/spi_conf.hpp>
#include <hw_memmap.h>
#include <gpio.h>
#include <ssi.h>

namespace tix {

namespace  spi {

	using namespace tix::spi;

	class tix_Spi : public ::spi::Spi
	{
	public:
		tix_Spi(unsigned int id, ::spi::Configuration config) :
							::spi::Spi(id)
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

			switch (id)
			{
				case 1:
					//SSI base
					_SSI_Base					= SSI0_BASE;

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

					break;

				case 2:
					//SSI base
					_SSI_Base					= SSI1_BASE;

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

					break;


				default:
					//SSI base
					_SSI_Base					= -1;

					//Peripheral clocks
					SSIPeripheral				= -1;
					GPIOPeripheral				= -1;

					//Configure GPIO for SSI
					ClkPinConfig				= -1;
					FssPinConfig				= -1;
					RxPinConfig					= -1;
					TxPinConfig					= -1;

					//GPIO for SSI pins
					GPIO_Port					= -1;
					GPIO_Pin_FSS				= -1;
					GPIO_Pin_SCK				= -1;
					GPIO_Pin_MISO				= -1;
					GPIO_Pin_MOSI				= -1;

					return;
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
			SSIConfigSetExpClk(_SSI_Base, SysCtlClockGet(), (conf_2_ClockPolarity(config.clockPolarity) << 1) | conf_2_ClockPhase(config.clockPhase),
					conf_2_mode(config.mode), config.DataRate, 8);




			//enable SSI
			SSIEnable(_SSI_Base);

		}

		virtual uint8_t send(uint8_t data)
		{
			unsigned long   result;
			unsigned long	data_8;

			//SSIDataPut is blocking
			data_8 = data & 0xFF;
			SSIDataPut(_SSI_Base, data_8);

			SSIDataGet(_SSI_Base, &result);

			//wait end of transmission
			while (SSIBusy(_SSI_Base) == true);

			return result & 0xFF;
		}

		virtual uint8_t recv()
		{
			unsigned long   result;
			
			SSIDataGet(_SSI_Base, &result);

			return result & 0xFF;
		}

		virtual void register_callback(void (*callback)(::spi::Spi&))
		{
			_callback = callback;


		}
		private:
			unsigned long	  		_SSI_Base;
	};


	static ::spi::Spi* gpSpi_1 = nullptr;
	static ::spi::Spi* gpSpi_2 = nullptr;

/*
 //TODO: implement callbacks and interrupts
	#define SPI_IRQ_CALLBACK(SpiX)	void SPI##SpiX##_IRQ_Handler()									\
									{																\
										if (SPI_I2S_GetITStatus(SPI##SpiX, SPI_I2S_IT_RXNE) == SET)	\
										{															\
											::spi::Spi* spi = gpSpi_##SpiX;							\
									    	spi->_callback(*spi);									\
										}															\
									}


	SPI_IRQ_CALLBACK(1)
	SPI_IRQ_CALLBACK(2)
*/
	static ::spi::Spi* gpSpi_NULL = nullptr;

	} /* namespace spi  */

} /* namespace tix  */

namespace spi
{

	unsigned int	num_instance()
	{
		return 2;
	}

	void init_instance(unsigned int id, Configuration config)
	{
		switch (id)
		{
			case 1: ::tix::spi::gpSpi_1 = new ::tix::spi::tix_Spi(1, config); break;
			case 2: ::tix::spi::gpSpi_2 = new ::tix::spi::tix_Spi(2, config); break;
		}
	}

	Spi& get_instance(unsigned int id)
	{
		switch (id)
		{
			case 1: return *::tix::spi::gpSpi_1;
			case 2: return *::tix::spi::gpSpi_2;
		}
		return *::tix::spi::gpSpi_NULL;
	}
}
