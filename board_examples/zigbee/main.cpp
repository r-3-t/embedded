/*

    ZIGBEE AT command :

    To enter command mode : +++ (module shoud send 'OK')

    - Read the current speed : ATBD<CR>
        0 means 1200
        1 means 2400
        2 means 4800
        3 means 9600
        4 means 19200
        5 means 38400
        6 means 57600
        7 means 115200
    - configure the speed : ATBD<number><CR>
        ex : ATBD4<CR> (module shoud send 'OK')

    - write configuration to memory : ATWR<CR> (module shoud send 'OK')
    - leave the command mode : ATCN<CR> (module shoud send 'OK')

    - read network identifier : ATID<CR> (module shoud send 'OK')
    - write network identifier : ATID<wxyz><CR>
        Parameter Range: 0 - 0xFFFF

    - read node identifier : ATMY<CR>
    - write node identifier : ATMY<wxyz><CR>
        Parameter Range: 0 - 0xFFFF
        The MY command is used to set and read the 16-bit source address of the RF module. 

    - read destination node identifier : ATDL<CR>
    - write destination node identifier : ATDL<wxyz><CR>
        Parameter Range: 0 - 0xFFFF
        The DL command is used to set and read the lower 32 bits of the RF module's 64-bit destination address. When com- bined with the DH (Destination Address High) parameter, it defines the destination address used for transmission.


    example (come from http://www.libelium.com/squidbee/?title=How_to_set_XBee_parameters) :
    In the gateway node XBee module
    +++
    Ok
    ATID<CR>
    3332
    (it's ok so I don't change it)
    ATBD<CR>
    3
    (this means 9600, so I change it to 19200)
    ATBD4<CR>
    OK
    ATMY0<CR>
    OK
    ATDL1<CR>
    OK
    ATWR<CR>
    (to write the configuration to memory)
    OK
    ATCN<CR>


    In the SquidBee XBee module
    +++
    Ok
    ATID<CR>
    3332
    (it's ok so I don't change it)
    ATBD<CR>
    3
    (this means 9600, so I change it to 19200)
    ATBD4<CR>
    OK
    ATMY1<CR>
    OK
    ATDL0<CR>
    OK
    ATWR<CR>
    (to write the configuration to memory)
    OK
    ATCN<CR>


*/

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
    clock::msleep(1500);
    Idx++;
  }
}

//------------------------------------------------------------------------------



