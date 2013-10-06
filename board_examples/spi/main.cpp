
#include <hal/clock.hpp>
#include <hal/uart.hpp>
#include <hal/spi.hpp>
#include <misc.h>
#include <stdio.h>

#define UNUSED(expr) do { (void)(expr); } while (0)

#define CURRENT_UART  4

//------------------------------------------------------------------------------

void callback (const std::string& buffer, uart::Uart& uart)
{
  uart.send(buffer.c_str());
  uart.send("\r\n");
}

void spi_callback(spi::Spi& spi)
{
  printf ("recv ... \r\n");
  uint8_t c = spi.recv();
  printf ("spi2 recv : %02X\r\n", c);
}

//------------------------------------------------------------------------------

extern "C"
{
void write_stdout (const unsigned char* ptr, unsigned int len)
{
  uart::get_instance(CURRENT_UART).send(ptr, len);
}
}

int main ()
{

  uart::init_instance<uart::PolicyNotifyOnChar<'\r'>>(CURRENT_UART, callback);

  using namespace spi;
  spi::init_instance(1,     { Configuration::_2Lines_FullDuplex, 
                              Configuration::Master,
                              Configuration::Low,
                              Configuration::_1_Edge,
                              Configuration::Soft,
                              Configuration::_2,
                              Configuration::MSB,
                              7
                            });

  spi::init_instance(2,     { Configuration::_2Lines_FullDuplex, 
                              Configuration::Slave,
                              Configuration::Low,
                              Configuration::_1_Edge,
                              Configuration::Soft,
                              Configuration::_2,
                              Configuration::MSB,
                              7
                            });




  spi::Spi& spi1 = get_instance(1);
  spi::Spi& spi2 = get_instance(2);
  spi2.register_callback(spi_callback);

  for (unsigned int i = 0; i < 0xFF; i++)
  {
    printf ("send ... %02X\r\n", i);
    spi1.send (i);
  }

  while (1);

  return 0; 
}

