#pragma once


namespace stm32fx
{

namespace spi
{

	namespace sp = ::spi;
	inline static uint16_t conf_2_direction(sp::Configuration::Direction_t direction)
	{
		switch (direction)
		{
			case sp::Configuration::_2Lines_FullDuplex	:	return SPI_Direction_2Lines_FullDuplex; break;
			case sp::Configuration::_2Lines_RxOnly	:		return SPI_Direction_2Lines_RxOnly;		break;
			case sp::Configuration::_1Line_Rx	:			return SPI_Direction_1Line_Rx;			break;
			case sp::Configuration::_1Line_Tx	:			return SPI_Direction_1Line_Tx;			break;
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_mode(sp::Configuration::Mode_t mode)
	{
		switch (mode)
		{
			case sp::Configuration::Master:		return SPI_Mode_Master;
			case sp::Configuration::Slave:		return SPI_Mode_Slave;
		}

		return (uint16_t)-1;
	}

	// inline uint16_t	conf_2_DataSize(spi::Configuration::DataSize_t DataSize)
	// {
	// 	switch (DataSize)
	// 	{
	// 		case spi::Configuration::_8b:	return SPI_DataSize_8b;
	// 		case spi::Configuration::_16b:	return SPI_DataSize_16b;
	// 	}

	// 	return (uint16_t)-1;
	// }

	inline static uint16_t	conf_2_ClockPolarity(sp::Configuration::ClockPolarity_t clockPolarity)
	{
		switch (clockPolarity)
		{
			case sp::Configuration::Low:	return SPI_CPOL_Low;
			case sp::Configuration::High:	return SPI_CPOL_High;
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_ClockPhase(sp::Configuration::ClockPhase_t clockPhase)
	{
		switch (clockPhase)
		{
			case sp::Configuration::_1_Edge:	return SPI_CPHA_1Edge;
			case sp::Configuration::_2_Edge:	return SPI_CPHA_2Edge;
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_SlaveSelectManagement(sp::Configuration::SlaveSelectManagement_t slaveSelectManagement)
	{
		switch (slaveSelectManagement)
		{
			case sp::Configuration::Soft:		return SPI_NSS_Soft;
			case sp::Configuration::Hard:		return SPI_NSS_Hard;
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_BaudRatePrescaler(sp::Configuration::BaudRatePrescaler_t baudRatePrescaler)
	{
		switch (baudRatePrescaler)
		{
			case sp::Configuration::_2:			return SPI_BaudRatePrescaler_2;
			case sp::Configuration::_4:			return SPI_BaudRatePrescaler_4;
			case sp::Configuration::_8:			return SPI_BaudRatePrescaler_8;
			case sp::Configuration::_16:		return SPI_BaudRatePrescaler_16;
			case sp::Configuration::_32:		return SPI_BaudRatePrescaler_32;
			case sp::Configuration::_64:		return SPI_BaudRatePrescaler_64;
			case sp::Configuration::_128:		return SPI_BaudRatePrescaler_128;
			case sp::Configuration::_256:		return SPI_BaudRatePrescaler_256;
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_FirstBitTransmission(sp::Configuration::FirstBitTransmission_t firstBitTransmission)
	{
		switch (firstBitTransmission)
		{
			case sp::Configuration::MSB:		return SPI_FirstBit_MSB;
			case sp::Configuration::LSB:		return SPI_FirstBit_LSB;
		}

		return (uint16_t)-1;
	}
} // end namespace spi

} // end namespace stm32fx

