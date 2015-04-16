/******************************************************************************\
		INCLUDES
\******************************************************************************/
#include <ClockInterface.hpp>
#include <EdgeTimeInterface.hpp>

#include <stdint.h>
#include <stdio.h>

/******************************************************************************\
		DEFINES
\******************************************************************************/
#define PWM_PORT								2
#define PWM_PIN									0

#define EDGE_TIME_PORT							2
#define EDGE_TIME_PIN							7


void edge_time_callback();


/******************************************************************************\
		GLOBALS
\******************************************************************************/
//initialize pwm with frequency of 100hz, duty can change from 0 to 100
::pwm::ConcretePwm pwm0(PWM_PORT, PWM_PIN, 50/*Hz*/, 20000 /* From 0 to 100 */);

::edge_time::ConcreteEdgeTime edgetime(EDGE_TIME_PORT, EDGE_TIME_PIN, &edge_time_callback);

uint32_t _time;
uint32_t elapsed_time;



/******************************************************************************\
		PROTOTYPES
\******************************************************************************/
void uart_callback (const uint8_t c);
::uart::ConcreteUart UartCommand(DEFAULT_UART, &uart_callback);

/******************************************************************************\
		FUNCTIONS
\******************************************************************************/

void uart_callback (const uint8_t c)
{
	UartCommand.send(&c, sizeof(c));
	UartCommand.send("\r\n");
}

//------------------------------------------------------------------------------

extern "C"
{
void write_stdout (const unsigned char* ptr, unsigned int len)
{
	UartCommand.send(ptr, len);
}
}

void edge_time_callback()
{

	elapsed_time = ::clock::ticksToUs(edgetime.get_last_record());

	return;
}

int main(void)
{
	pwm0.setDuty(1250); // 0%
	pwm0.enable();

	edgetime.enable();

	while (1)
	{
	    clock::msleep(435);
	    printf("EdgeTime : %d\r\n", elapsed_time);
	}
}

//------------------------------------------------------------------------------


