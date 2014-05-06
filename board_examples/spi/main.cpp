/******************************************************************************\
		INCLUDES
\******************************************************************************/
#include <UartInterface.hpp>
#include <SpiInterface.hpp>
#include <stdio.h>

/******************************************************************************\
		PROTOYPES
\******************************************************************************/
void uart_callback (uint8_t c);
void spi_slave_callback(uint8_t c);

/******************************************************************************\
		GLOBALES
\******************************************************************************/
::spi::ConcreteSpi			Spi1(1, 0,::spi::Configuration::_default_master());
::spi::ConcreteSpi			Spi2(2, spi_slave_callback,::spi::Configuration::_default_slave());

::uart::ConcreteUart 		UartCommand(1, &uart_callback);

/******************************************************************************\
		DEFINES
\******************************************************************************/

/******************************************************************************\
		FUNCTIONS
\******************************************************************************/

void uart_callback (uint8_t c)
{
  printf("Send to SPI : %02X\r\n", c);
  
}

void spi_slave_callback(uint8_t c)
{
  printf ("spi slave recv : %02X\r\n", c);
}

extern "C"
{
void write_stdout (const unsigned char* ptr, unsigned int len)
{
  UartCommand.send(ptr, len);
}
}

int main ()
{

  for (unsigned int i = 0; i < 0xFF; i++)
  {
    printf ("send ... %02X\r\n", i);
    Spi1.send (i);
  }

  while (1);

  return 0; 
}

