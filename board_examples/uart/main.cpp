
#include <hal/clock.hpp>
#include <hal/uart.hpp>

#include <stdio.h>

#define UNUSED(expr) do { (void)(expr); } while (0)

#define CURRENT_UART  1

//------------------------------------------------------------------------------

void callback (const std::string& buffer, uart::Uart& uart)
{
  uart.send(buffer.c_str());
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
//------------------------------------------------------------------------------

int main(void)
{
  uart::init_instance<uart::PolicyNotifyOnChar<'\r'>>(CURRENT_UART, callback);

  unsigned char Idx = 0;
  while(1)
  {
    printf ("Index : %d\r\n", Idx);
    clock::usleep(500);
    Idx++;
  }
}

//------------------------------------------------------------------------------


