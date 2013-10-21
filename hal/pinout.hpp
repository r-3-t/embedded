#pragma once



namespace pinout {

	typedef enum {USART, UART, SPI, I2C} Bus_Type;

	typedef enum {Mosi, Miso, Clk, Rx, Tx, Cts, Rts}Pin_Function;

	typedef unsigned int Pin_id;

	typedef unsigned int Gpio_id;

	typedef unsigned int Bus_id;




	struct Pin_Description
	{
		Gpio_id			gpio;
		Pin_id			id;

		Bus_Type		bus;
		Bus_id			bus_id;

		Pin_Function	function;
	};

	unsigned int NumPin();
	const Pin_Description* PinDescription();

}
