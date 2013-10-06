/* 
* Spi2: 
* Miso - pb14 
* Mosi - pb15 
* Sck - pb13 
* Nss - pb12 
* 
* Spi1: 
* Nss - pa4 
* Sck - pa5 
* Mosi - pa7 
* Miso - pa6 
* 
*/ 

#include <stm32f4xx_gpio.h> 
#include <stm32f4xx_rcc.h> 
#include <stm32f4xx_spi.h> 

#include <stm32f4_discovery.h> 

#include <hal/clock.hpp>
#include <hal/uart.hpp>
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

//------------------------------------------------------------------------------

extern "C"
{
  void write_stdout (const unsigned char* ptr, unsigned int len)
  {
    uart::get_instance(CURRENT_UART).send(ptr, len);
  }
}


void spi1_init ()
{ 
    RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE); // clock port 
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_SPI1, ENABLE); // SPI1 clock 
    GPIO_InitTypeDef gpio;
    GPIO_StructInit (& gpio);
    gpio.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init (GPIOA, & gpio);
    GPIO_PinAFConfig (GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig (GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
    GPIO_PinAFConfig (GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
    SPI_I2S_DeInit (SPI1);
    SPI_InitTypeDef spi1;
    SPI_StructInit (& spi1);
    spi1.SPI_Mode = SPI_Mode_Master;
    spi1.SPI_DataSize = SPI_DataSize_16b;
    spi1.SPI_NSS = SPI_NSS_Soft;
    SPI_Init (SPI1, & spi1);
    SPI_Cmd (SPI1, ENABLE);
}

void spi2_init ()
{ 
    RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI2, ENABLE);
    GPIO_InitTypeDef gpio;
    GPIO_StructInit (& gpio);
    gpio.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init (GPIOB, & gpio);
    GPIO_PinAFConfig (GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
    GPIO_PinAFConfig (GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
    GPIO_PinAFConfig (GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
    SPI_I2S_DeInit (SPI2);
    SPI_InitTypeDef spi2;
    SPI_StructInit (& spi2);
    spi2.SPI_Mode = SPI_Mode_Slave;
    spi2.SPI_DataSize = SPI_DataSize_16b;
    spi2.SPI_NSS = SPI_NSS_Soft;
    SPI_Init (SPI2, & spi2);
    SPI_Cmd (SPI2, ENABLE); 
} 

uint16_t SPI1_Buffer_Tx [32] = {0x0102, 0x0304,
0x0506, 0x0708, 0x090A, 0x0B0C,
0x0D0E, 0x0F10, 0x1112, 0x1314, 0x1516, 0x1718,
0x191A, 0x1B1C, 0x1D1E, 0x1F20, 0x2122, 0x2324,
0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C,
0x3D3E, 0x3F40};

uint16_t spi1_send (uint16_t data)
{
  SPI_I2S_SendData (SPI1, data);
  while (SPI_I2S_GetFlagStatus (SPI1, SPI_I2S_FLAG_TXE) == RESET); // wait until transmit complete
  while( (SPI1->SR & SPI_I2S_FLAG_RXNE) == RESET); // wait until receive complete
  while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
  return SPI1->DR; // return received data from SPI data register
}

uint16_t spi1_receve ()
{
  return spi1_send(0xFF); // return received data from SPI data register
}

void spi2_send (uint16_t data)
{
  SPI_I2S_SendData (SPI2, data);
  while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_TXE) == RESET);
  //while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_TXE) == RESET); // wait until transmit complete 
}

uint16_t spi2_receve ()
{
  while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_RXNE) == RESET); // wait until receive complete
  uint16_t received = SPI_I2S_ReceiveData (SPI2);
  return received;
}

uint16_t I2S2_Buffer_Rx  [32];
uint16_t RxIdx = 0;

uint16_t I2S2_Buffer_Rx1  [32];
uint16_t RxIdx1 = 0;

int change_mode = 0;

namespace stm32f4
{

  namespace spi
  {

//extern "C" {
void SPI2_IRQ_Handler()
{
  printf ("spi2 - IRQ handler \r\n");

  if (change_mode == 0)
  {
      /* Check the interrupt source */
    if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) == SET)
    {
        /* Store the I2S2 received data in the relative data table */
        I2S2_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI2);
        if (RxIdx == 32)
        {
          printf ("please stop\r\n");
          RxIdx = 0;
        }
    }
  }
  else
  {
      if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) == SET)
    {

        /* Store the I2S2 received data in the relative data table */
        while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_RXNE) == RESET); // wait until receive complete

        SPI_I2S_SendData (SPI2, I2S2_Buffer_Rx[RxIdx++] + 1);
        SPI_I2S_ReceiveData (SPI2);

        //printf ("plop\r\n");
        //while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_TXE) == RESET);

    }
  }
}

}
}

void SPI1_IRQHandler()
{
  printf ("spi1 - IRQ handler \r\n");
    /* Check the interrupt source */
  if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) == SET)
  {
      /* Store the I2S2 received data in the relative data table */
      I2S2_Buffer_Rx1[RxIdx1++] = SPI_I2S_ReceiveData(SPI1);
      if (RxIdx1 == 32)
      {
        printf ("please stop\r\n");
        RxIdx1 = 0;
      }
  }
}



int main ()
{
  STM_EVAL_LEDInit (LED3);
  STM_EVAL_LEDInit (LED4);
  STM_EVAL_LEDInit (LED5);
  STM_EVAL_LEDInit (LED6);
  spi1_init ();
  spi2_init ();
  STM_EVAL_LEDOn (LED5);
  uint16_t data [32];
  STM_EVAL_LEDOn (LED3);

  uart::init_instance<uart::PolicyNotifyOnChar<'\r'>>(CURRENT_UART, callback);


  SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
  //SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);

  NVIC_InitTypeDef    NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)
  NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART2 interrupts
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     // this sets the subpriority inside the group
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      // the USART2 interrupts are globally enabled
  NVIC_Init(&NVIC_InitStructure);              // the properties are passed to the NVIC_Init function which takes care of the low level stuff


  //NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
  //NVIC_Init(&NVIC_InitStructure);              // the properties are passe

  for (int i = 0; i < 30000000; i++) {}
  int i = 0;
  for (; i <32; i++)
  {
    printf ("spi1 - send \r\n");
    spi1_send (SPI1_Buffer_Tx [i]);

  }

  STM_EVAL_LEDOn (LED4);
  /* Check the transmission */
  for (i = 0; i <32; i++)
  {
    if (SPI1_Buffer_Tx[i] != SPI1_Buffer_Tx [i])
    {
      STM_EVAL_LEDOff (LED4);
      printf ("ai 1 at %d | in : %04X, out : %04X\r\n", i, I2S2_Buffer_Rx[i], SPI1_Buffer_Tx [i]);
    }
  }

  printf ("---------- END SEND\r\n");
  change_mode = 1;
  RxIdx = 0;

  // send the wanted command
  spi1_send ( 0xAAAA );
  for (i=0; i <32; i++)
  {
    printf ("spi2 - send \r\n");
    I2S2_Buffer_Rx1[i] = spi1_receve ( );
  }

  /* Check the transmission */
  for (i = 0; i <32; i++)
  {
    if ((I2S2_Buffer_Rx[i] + 1) != (I2S2_Buffer_Rx1 [i]))
    {
      STM_EVAL_LEDOff (LED4);
      printf ("ai 2 at %d | in : %04X, out : %04X\r\n", i, I2S2_Buffer_Rx[i] + 1, I2S2_Buffer_Rx1 [i]);
    }
  }

  while (1) {
  STM_EVAL_LEDToggle (LED6);
  for (int i = 0; i < 3000000; i++) {}
  }
  return 0; 
}

