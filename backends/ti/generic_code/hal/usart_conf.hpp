#pragma once

#include <hw_types.h>
#include <uart.h>

namespace tix
{
namespace uart
{

	namespace uc = ::uart;
	inline static uint32_t conf_2_baudrate(::uart::Configuration::Baudrate_t baudrate)
	{
		switch (baudrate)
		{
			case uc::Configuration::_9600	:	return 9600; 	break;
			case uc::Configuration::_19200	:	return 19200;	break;
			case uc::Configuration::_38400	:	return 38400;	break;
			case uc::Configuration::_57600	:	return 57600;	break;
			case uc::Configuration::_115200 :	return 115200;	break;
		}

		return (uint32_t)-1;
	}

	inline static uint16_t	conf_2_WordLength(uc::Configuration::WordLength_t word_length)
	{
		switch (word_length)
		{
			case uc::Configuration::_8b:	return UART_CONFIG_WLEN_8;
			case uc::Configuration::_9b:	return -1; //TODO: trig error
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_StopBits(uc::Configuration::StopBit_t StopBits)
	{
		switch (StopBits)
		{
			case uc::Configuration::_1:	return UART_CONFIG_STOP_ONE;
			case uc::Configuration::_0_5:	return -1; //TODO: trig error
			case uc::Configuration::_2:	return UART_CONFIG_STOP_TWO;
			case uc::Configuration::_1_5:	return -1; //TODO: trig error
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_Parity(uc::Configuration::Parity_t Parity)
	{
		switch (Parity)
		{
			case uc::Configuration::no:	return UART_CONFIG_PAR_NONE;
			case uc::Configuration::even:	return UART_CONFIG_PAR_EVEN;
			case uc::Configuration::odd:	return UART_CONFIG_PAR_ODD;
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_Mode(uc::Configuration::Mode_t Mode)
	{
		switch (Mode)
		{
			case uc::Configuration::Rx:	return -1; //TODO: trig error
			case uc::Configuration::Tx:	return -1; //TODO: trig error
			case uc::Configuration::Rx_Tx:	return -1; //TODO: trig error
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_HardwareFlowControl(uc::Configuration::HardwareFlowControl_t HardwareFlowControl)
	{
		switch (HardwareFlowControl)
		{
			case uc::Configuration::None:		return UART_FLOWCONTROL_NONE;
			case uc::Configuration::Rts:		return UART_FLOWCONTROL_RX;
			case uc::Configuration::Cts:		return UART_FLOWCONTROL_TX;
			case uc::Configuration::Rts_Cts:	return UART_FLOWCONTROL_RX | UART_FLOWCONTROL_TX;
		}

		return (uint16_t)-1;
	}

}
}
