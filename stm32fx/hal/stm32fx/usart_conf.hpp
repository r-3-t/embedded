#pragma once



namespace stm32fx
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
			case uc::Configuration::_8b:	return USART_WordLength_8b;
			case uc::Configuration::_9b:	return USART_WordLength_9b;
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_StopBits(uc::Configuration::StopBit_t StopBits)
	{
		switch (StopBits)
		{
			case uc::Configuration::_1:	return USART_StopBits_1;
			case uc::Configuration::_0_5:	return USART_StopBits_0_5;
			case uc::Configuration::_2:	return USART_StopBits_2;
			case uc::Configuration::_1_5:	return USART_StopBits_1_5;
		}

		return (uint16_t)-1;
	}
	
	inline static uint16_t	conf_2_Parity(uc::Configuration::Parity_t Parity)
	{
		switch (Parity)
		{
			case uc::Configuration::no:	return USART_Parity_No;
			case uc::Configuration::even:	return USART_Parity_Even;
			case uc::Configuration::odd:	return USART_Parity_Odd;
		}

		return (uint16_t)-1;	
	}
	
	inline static uint16_t	conf_2_Mode(uc::Configuration::Mode_t Mode)
	{
		switch (Mode)
		{
			case uc::Configuration::Rx:	return USART_Mode_Rx;
			case uc::Configuration::Tx:	return USART_Mode_Tx;
			case uc::Configuration::Rx_Tx:	return (USART_Mode_Rx | USART_Mode_Tx);
		}

		return (uint16_t)-1;		
	}
	
	inline static uint16_t	conf_2_HardwareFlowControl(uc::Configuration::HardwareFlowControl_t HardwareFlowControl)
	{
		switch (HardwareFlowControl)
		{
			case uc::Configuration::None:		return USART_HardwareFlowControl_None;
			case uc::Configuration::Rts:		return USART_HardwareFlowControl_RTS;
			case uc::Configuration::Cts:		return USART_HardwareFlowControl_CTS;
			case uc::Configuration::Rts_Cts:	return USART_HardwareFlowControl_RTS_CTS;
		}	

		return (uint16_t)-1;	
	}
	
}
}
