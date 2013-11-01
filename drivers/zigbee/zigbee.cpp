#include "zigbee.hpp"
#include "clock.hpp"
#include <sstream>
#include <string.h>

namespace wireless
{

	//__________________________________________________________________________

	Zigbee::Zigbee(const unsigned int uart_id /*= 1*/) : _uart(*(uart::Uart*)nullptr)
	{
		using namespace std::placeholders;
		uart::init_instance<uart::PolicyNotifyOnSize<1>>(uart_id, std::bind(&Zigbee::_uart_callback, this, _1, _2));
		_uart = uart::get_instance(uart_id);
	}

	//__________________________________________________________________________

	void Zigbee::set_speed(Speed speed)
	{
		std::ostringstream oss;
		oss << "ATBD" << speed << '\r';
		send_and_check_command(oss.str().c_str());
	}

	//__________________________________________________________________________

	void Zigbee::set_network_id (NetworkId networkId)
	{
		std::ostringstream oss;
		oss << "ATID" << std::hex << networkId << '\r';
		send_and_check_command(oss.str().c_str());
	}

	//__________________________________________________________________________

	void Zigbee::set_node_id (NodeId nodeId)
	{
		std::ostringstream oss;
		oss << "ATMY" << std::hex << nodeId << '\r';
		send_and_check_command(oss.str().c_str());
	}

	//__________________________________________________________________________

	void Zigbee::set_destination_node_id (NodeId nodeId)
	{
		std::ostringstream oss;
		oss << "ATDL" << std::hex << nodeId << '\r';
		send_and_check_command(oss.str().c_str());
	}

	//__________________________________________________________________________

	void Zigbee::send_and_check_command(const char* command)
	{
		enter_command_mode();
		_uart.send(command);
		check_command();
		leave_command_mode();
	}

	//__________________________________________________________________________

	void			Zigbee::send(const unsigned char* data, unsigned int data_len) const
	{
		_uart.send(data, data_len);
	}

	//__________________________________________________________________________

	unsigned int	Zigbee::recv(unsigned char* data, unsigned int max_data_len)
	{
		unsigned int num_bytes = 0;
		unsigned char* buf_recv = _recv_buffer.data();
		unsigned int buf_recv_size = _recv_buffer.size();

		while ((num_bytes < buf_recv_size) && (num_bytes < max_data_len))
		{
			data[num_bytes] = buf_recv[num_bytes];
			num_bytes++;
		}

		// remove read data from the recv_buf
		if (num_bytes > 0)
			_recv_buffer.erase(_recv_buffer.begin(), _recv_buffer.begin() + num_bytes);

		return num_bytes;
	}

	//__________________________________________________________________________

	unsigned int Zigbee::num_bytes_available() const
	{
		return _recv_buffer.size();
	}

	//__________________________________________________________________________

	bool Zigbee::check_command()
	{
		clock::msleep(20);
		if (_recv_buffer.size() != 2)
			return false;

		unsigned char* data = _recv_buffer.data();
		bool bOk = false;
		if (memcmp(data, "OK", 2) == 0)
			bOk = true;
		_recv_buffer.clear();
		return bOk;
	}

	//__________________________________________________________________________

	bool Zigbee::enter_command_mode()
	{
		_recv_buffer.clear();
		_uart.send("+++\r");
		return check_command();
	}

	//__________________________________________________________________________
		
	bool Zigbee::leave_command_mode()
	{
		_uart.send("ATCN\r");
		return check_command();
	}

	//__________________________________________________________________________

	void Zigbee::_uart_callback(const types::buffer& buf, uart::Uart&)
	{
		_recv_buffer.insert(_recv_buffer.end(), buf.begin(), buf.end());
	}

	//__________________________________________________________________________
}
