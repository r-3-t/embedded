#pragma once

#include <types.hpp>


namespace i2c {

	typedef enum
	{
		MasterWriteToSlave = 0,
		MasterReadFromSlave
	} MasterOperation_T;

	class I2cInterface
	{
	public:
		typedef void (*i2c_receive_callback)(const uint8_t c);
		typedef void (*i2c_on_master_request_callback)();

		I2cInterface() {}

		virtual void send(const char car)													= 0;
		virtual void send(const types::buffer& buf)											= 0;
		virtual void setSlaveAddress(const uint8_t slave_address)							= 0;
		virtual void request(const int BytesCount)											= 0;

		i2c_receive_callback _receive_callback;
		i2c_on_master_request_callback _on_master_request_callback;

	};

	//--------------------------------------------------------------------------
	struct Configuration
	{
//		typedef enum {_9600, _19200, _38400, _57600, _115200} Baudrate_t;
//		Baudrate_t	baudRate;            /*!< This member configures the USART communication baud rate.
//												The baud rate is computed using the following formula:
//												- IntegerDivider = ((PCLKx) / (8 * (OVR8+1) * (USART_InitStruct->USART_BaudRate)))
//												- FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 8 * (OVR8+1)) + 0.5
//												Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */
//
//		typedef enum {_8b, _9b} WordLength_t;
//		WordLength_t 	WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
//												This parameter can be a value of @ref USART_Word_Length */
//
//		typedef enum {_1, _0_5, _2, _1_5} StopBit_t;
//		StopBit_t StopBits;            /*!< Specifies the number of stop bits transmitted.
//												This parameter can be a value of @ref USART_Stop_Bits */
//
//		typedef enum {no, even, odd} Parity_t;
//		Parity_t Parity;              /*!< Specifies the parity mode.
//											This parameter can be a value of @ref USART_Parity
//											@note When parity is enabled, the computed parity is inserted
//											at the MSB position of the transmitted data (9th bit when
//											the word length is set to 9 data bits; 8th bit when the
//											word length is set to 8 data bits). */
//
//		typedef enum {Rx, Tx, Rx_Tx} Mode_t;
//		Mode_t Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
//											This parameter can be a value of @ref USART_Mode */
//
//		typedef enum {None, Rts, Cts, Rts_Cts} HardwareFlowControl_t;
//		HardwareFlowControl_t HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
//										or disabled.
//										This parameter can be a value of @ref USART_Hardware_Flow_Control */

		typedef enum {Master, Slave} Mode_t;
		Mode_t Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
											This parameter can be a value of @ref USART_Mode */

		static Configuration _Master()
		{
			return {Master};
		}

		static Configuration _Slave()
		{
			return {Slave};
		}
	};



} /* namesapce i2c */
