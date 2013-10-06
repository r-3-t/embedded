#pragma once

#include <types.hpp>


namespace uart {

	class Uart
	{
	public:
		Uart(void (*callback)(const std::string&, uart::Uart&)) : _callback(callback){};
		virtual void send(const types::buffer& buf) 		= 0;
		virtual void send(const unsigned char* buf, unsigned int length) 		= 0;
		virtual void accumulator(types::byte b)				= 0;

	protected:
		void (*_callback)(const std::string&, uart::Uart&);
	};

	//--------------------------------------------------------------------------
	template<char c>
	struct PolicyNotifyOnChar
	{
		enum {value = c};
		bool need_to_notify(const types::buffer&, char b)
		{
			if (b == value)
				return true;
			else
				return false;
		}
	};

	template <unsigned int Number>
	struct PolicyNotifyOnSize
	{
		enum {value = Number};
		bool need_to_notify(const types::buffer& buf, char)
		{
			if (buf.size() == value)
				return true;
			else
				return false;
		}
	};

	//--------------------------------------------------------------------------
	struct Configuration
	{
		typedef enum {_9600, _19200, _38400, _57600, _115200} Baudrate_t;
		Baudrate_t	baudRate;            /*!< This member configures the USART communication baud rate.
												The baud rate is computed using the following formula:
												- IntegerDivider = ((PCLKx) / (8 * (OVR8+1) * (USART_InitStruct->USART_BaudRate)))
												- FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 8 * (OVR8+1)) + 0.5 
												Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */

		typedef enum {_8b, _9b} WordLength_t;
		WordLength_t 	WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
												This parameter can be a value of @ref USART_Word_Length */

		typedef enum {_1, _0_5, _2, _1_5} StopBit_t;
		StopBit_t StopBits;            /*!< Specifies the number of stop bits transmitted.
												This parameter can be a value of @ref USART_Stop_Bits */

		typedef enum {no, even, odd} Parity_t;
		Parity_t Parity;              /*!< Specifies the parity mode.
											This parameter can be a value of @ref USART_Parity
											@note When parity is enabled, the computed parity is inserted
											at the MSB position of the transmitted data (9th bit when
											the word length is set to 9 data bits; 8th bit when the
											word length is set to 8 data bits). */

		typedef enum {Rx, Tx, Rx_Tx} Mode_t;
		Mode_t Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
											This parameter can be a value of @ref USART_Mode */

		typedef enum {None, Rts, Cts, Rts_Cts} HardwareFlowControl_t;
		HardwareFlowControl_t HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
										or disabled.
										This parameter can be a value of @ref USART_Hardware_Flow_Control */

		static Configuration _9600_8_N_1()
		{
			return {_9600, _8b, _1, no, Rx_Tx, None};
		}
	};

	//--------------------------------------------------------------------------
	template <typename Policy = PolicyNotifyOnChar<'\n'>>
	class UartWithPolicy : public Uart, public Policy
	{
	public:
		void accumulator(types::byte b);
	protected:
		UartWithPolicy(void (*callback)(const std::string&, uart::Uart&)) : Uart(callback) {}

	private:
		//std::function<void (const buffer&)> _callback;
		types::buffer	buf;

	};


	/** return the number of available uart on the target system
		@return the number of available uart on the target system
	*/
	unsigned int	num_instance();

	template <class T>
	void init_instance(unsigned int id, void (*callback)(const std::string&, uart::Uart&), Configuration config = Configuration::_9600_8_N_1());

	Uart& get_instance(unsigned int id);

	//--------------------------------------------------------------------------
	template <typename Policy>
	void UartWithPolicy< Policy >::accumulator(types::byte b)
	{
		buf.push_back(b);
		if (Policy::need_to_notify(buf, b))
		{
			_callback(buf, *this);
			buf.clear();
		}
	}


} /* namesapce uart */
