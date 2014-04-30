/******************************************************************************\
		INCLUDES
\******************************************************************************/
#include <hal/Clock.hpp>
#include <hal/Uart.hpp>
#include <hal/I2c.hpp>

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

/******************************************************************************\
		GLOBALS
\******************************************************************************/
::uart::ConcreteUart UartCommand(CURRENT_UART, &uart_callback);

::i2c::ConcreteI2c I2cMaster(I2C_MASTER, &master_receive_callback);
::i2c::ConcreteI2c I2cSlave(I2C_SLAVE, &slave_receive_callback, i2c::Configuration::_Slave());

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
	UartCommand.send("Master (from slave) : ");
	UartCommand.send(&c, sizeof(c));
	UartCommand.send("\r\n");
}

void slave_receive_callback (const uint8_t c)
{
	I2cSlave.send(c);
}

//------------------------------------------------------------------------------

extern "C"
{
void write_stdout (const unsigned char* ptr, unsigned int len)
{
	UartCommand.send(ptr, len);
}
}
//------------------------------------------------------------------------------

int main(void)
{
	unsigned char Idx = 0;

	printf("Set I2C slave address.\r\n");
	I2cSlave.setSlaveAddress(I2C_SLAVE_ADDRESS);

	printf("Begin I2C loop.\r\n");
	while(1)
	{
		printf("Loop...\r\n");
		I2cMaster.setSlaveAddress(I2C_SLAVE_ADDRESS, ::i2c::MasterWriteToSlave);
		I2cMaster.send(Idx);
		clock::msleep(500);
		Idx++;
	}
}

//------------------------------------------------------------------------------


