
#include <hal/clock.hpp>
#include <hal/uart.hpp>
#include <hal/spi.hpp>
#include <frontend_arduino.hpp>
using namespace ::arduino::gpio;
using namespace ::arduino::clock;
using namespace ::arduino::spi;
#include <RF24.h>

HardwareSPI SPI;

#include <stdio.h>
#include <stdlib.h>

#define UNUSED(expr) do { (void)(expr); } while (0)

#define CURRENT_UART  1

void callback (const types::buffer& buffer, uart::Uart& uart)
{
  uart.send(buffer);
  uart.send("\r\n");
}

//------------------------------------------------------------------------------

extern "C"
{
void write_stdout (const unsigned char* ptr, unsigned int len)
{
  uart::get_instance(CURRENT_UART).send(ptr, len);
}
}

const uint8_t num_channels = 128;
uint8_t values[num_channels];

int main ()
{

	uart::init_instance<uart::PolicyNotifyOnChar<'\r'>>(CURRENT_UART, callback);

	RF24 radio(1,2);

	radio.begin();

	radio.printDetails();


	radio.setAutoAck(false);

	// Get into standby mode
	radio.startListening();
	radio.stopListening();

	// Print out header, high then low digit
	int i = 0;
	while ( i < num_channels )
	{
		printf("%x",i>>4);
		++i;
	}

	printf("\n\r");
	i = 0;

	while ( i < num_channels )
	{
		printf("%x",i&0xf);
		++i;
	}
	printf("\n\r");


	//
	// Loop
	//

	const int num_reps = 100;

	while (1)
	{
		// Clear measurement values
		memset(values,0,sizeof(values));

		// Scan all channels num_reps times
		int rep_counter = num_reps;
		while (rep_counter--)
		{
			int i = num_channels;
			while (i--)
			{
				// Select this channel
				radio.setChannel(i);

				// Listen for a little
				radio.startListening();
				delayMicroseconds(128);
				radio.stopListening();

				// Did we get a carrier?
				if ( radio.testCarrier() )
				++values[i];
			}
		}

		// Print out channel measurements, clamped to a single hex digit
		int i = 0;
		while ( i < num_channels )
		{
			printf("%x",min(0xf,values[i]&0xf));
			++i;
		}
		printf("\n\r");
	}

	while (1);

	return 0;
}

