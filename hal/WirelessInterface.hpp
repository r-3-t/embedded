#pragma once


namespace wireless
{
	class Wireless
	{
	public:
		Wireless();
		virtual ~Wireless();

		virtual void			send(const unsigned char* data, unsigned int data_len) const = 0;

		virtual unsigned int	recv(unsigned char* data, unsigned int max_data_len) = 0;

		virtual unsigned int	num_bytes_available() const = 0;
	};

}
