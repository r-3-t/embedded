#pragma once

#include <wireless.hpp>
#include <uart.hpp>
#include <types.hpp>

namespace wireless
{
	class Zigbee
	{
	public:
		typedef enum {_1200 = 0, _2400, _4800, _9600, _19200, _38400, _57600, _115200} Speed;

		typedef unsigned short NetworkId;

		typedef unsigned short NodeId;

		Zigbee(const unsigned int uart_id = 1);

		void set_speed(Speed speed);

		void set_network_id (NetworkId networkId);

		void set_node_id (NodeId nodeId);

		void set_destination_node_id (NodeId nodeId);

		virtual void			send(const unsigned char* data, unsigned int data_len) const ;

		virtual unsigned int	recv(unsigned char* data, unsigned int max_data_len);

		virtual unsigned int	num_bytes_available() const;

	private:
		bool enter_command_mode();
		bool leave_command_mode();
		bool check_command();

		void send_and_check_command(const char* command);

		void	_uart_callback(const types::buffer&, uart::Uart&);

		uart::Uart&		_uart;
		types::buffer	_recv_buffer;
	};
}

