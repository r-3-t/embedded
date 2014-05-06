#pragma once

#include <hw_types.h>
#include <uart.h>
#include <UartInterface.hpp>
#include <stdint.h>

namespace tix
{
namespace uart
{

	inline static uint32_t conf_2_baudrate(::uart::Configuration::Baudrate_t baudrate)
	{
		switch (baudrate)
		{
			case ::uart::Configuration::_9600	:	return 9600; 	break;
			case ::uart::Configuration::_19200	:	return 19200;	break;
			case ::uart::Configuration::_38400	:	return 38400;	break;
			case ::uart::Configuration::_57600	:	return 57600;	break;
			case ::uart::Configuration::_115200 :	return 115200;	break;
		}

		return (uint32_t)-1;
	}

	inline static uint16_t	conf_2_WordLength(::uart::Configuration::WordLength_t word_length)
	{
		switch (word_length)
		{
			case ::uart::Configuration::_8b:	return UART_CONFIG_WLEN_8;
			case ::uart::Configuration::_9b:	return -1; //TODO: trig error
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_StopBits(::uart::Configuration::StopBit_t StopBits)
	{
		switch (StopBits)
		{
			case ::uart::Configuration::_1:	return UART_CONFIG_STOP_ONE;
			case ::uart::Configuration::_0_5:	return -1; //TODO: trig error
			case ::uart::Configuration::_2:	return UART_CONFIG_STOP_TWO;
			case ::uart::Configuration::_1_5:	return -1; //TODO: trig error
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_Parity(::uart::Configuration::Parity_t Parity)
	{
		switch (Parity)
		{
			case ::uart::Configuration::no:	return UART_CONFIG_PAR_NONE;
			case ::uart::Configuration::even:	return UART_CONFIG_PAR_EVEN;
			case ::uart::Configuration::odd:	return UART_CONFIG_PAR_ODD;
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_Mode(::uart::Configuration::Mode_t Mode)
	{
		switch (Mode)
		{
			case ::uart::Configuration::Rx:	return -1; //TODO: trig error
			case ::uart::Configuration::Tx:	return -1; //TODO: trig error
			case ::uart::Configuration::Rx_Tx:	return -1; //TODO: trig error
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_HardwareFlowControl(::uart::Configuration::HardwareFlowControl_t HardwareFlowControl)
	{
		switch (HardwareFlowControl)
		{
			case ::uart::Configuration::None:		return UART_FLOWCONTROL_NONE;
			case ::uart::Configuration::Rts:		return UART_FLOWCONTROL_RX;
			case ::uart::Configuration::Cts:		return UART_FLOWCONTROL_TX;
			case ::uart::Configuration::Rts_Cts:	return UART_FLOWCONTROL_RX | UART_FLOWCONTROL_TX;
		}

		return (uint16_t)-1;
	}

}
}
