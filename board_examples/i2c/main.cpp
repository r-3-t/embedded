/******************************************************************************\
		INCLUDES
\******************************************************************************/
#include <ClockInterface.hpp>
#include <UartInterface.hpp>
#include <I2cInterface.hpp>

#include <stdio.h>

/******************************************************************************\
		DEFINES
\******************************************************************************/
#define CURRENT_UART  											1
#define I2C_MASTER												1
#define I2C_SLAVE												2
#define I2C_SLAVE_ADDRESS										0x42

/******************************************************************************\
		PROTOTYPES
\******************************************************************************/
void uart_callback (const uint8_t c);
void master_receive_callback (const uint8_t c);
void slave_receive_callback (const uint8_t c);
void on_master_request_callback();

/******************************************************************************\
		GLOBALS
\******************************************************************************/
::uart::ConcreteUart UartCommand(CURRENT_UART, &uart_callback);

::i2c::ConcreteI2c I2cMaster(I2C_MASTER, &master_receive_callback);
::i2c::ConcreteI2c I2cSlave(I2C_SLAVE, &slave_receive_callback, i2c::Configuration::_Slave(), &on_master_request_callback);

/******************************************************************************\
		FUNCTIONS
\******************************************************************************/
void uart_callback (const uint8_t c)
{
	UartCommand.send(&c, sizeof(c));
	UartCommand.send("\r\n");
}

void master_receive_callback (const uint8_t c)
{
	UartCommand.send("Master - received from slave : ");
	UartCommand.send(&c, sizeof(c));
	UartCommand.send("\r\n");
}


unsigned char slave_c;
void slave_receive_callback (const uint8_t c)
{
	UartCommand.send("Slave - received : ");
	UartCommand.send(&c, sizeof(c));
	UartCommand.send("\r\n");
	slave_c = c;
}

void on_master_request_callback()
{
	UartCommand.send("Slave - master request, sending back : ");
	UartCommand.send(&slave_c, sizeof(slave_c));
	UartCommand.send("\r\n");
	I2cSlave.send(slave_c);

}

//------------------------------------------------------------------------------

extern "C"
{
void write_stdout (const unsigned char* ptr, unsigned int len)
{
	UartCommand.send(ptr, len);
}

void write_stderr (const unsigned char* ptr, unsigned int len)
{
	UartCommand.send(ptr, len);
}
}
//------------------------------------------------------------------------------

int main(void)
{
	unsigned char Idx = 'a';
	types::buffer buf;


	printf("Set I2C slave address.\r\n");
	I2cSlave.setSlaveAddress(I2C_SLAVE_ADDRESS);


	printf("Begin I2C loop.\r\n");
	while(1)
	{
		printf("===========================================\r\n");
		buf.push_back(Idx);

		//send to slave
		I2cMaster.setSlaveAddress(I2C_SLAVE_ADDRESS, ::i2c::MasterWriteToSlave);
		I2cMaster.send(buf);

		//receive from slave
		I2cMaster.setSlaveAddress(I2C_SLAVE_ADDRESS, ::i2c::MasterReadFromSlave);
		//send back last char thrice
		I2cMaster.request(3);

		//next
		clock::msleep(1000);
		Idx++;
	}
}

//------------------------------------------------------------------------------


