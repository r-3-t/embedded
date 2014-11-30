#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>
#include <Pinout.hpp>



namespace pinout
{

	Pinout::Pinout(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{

		_Gpio_id = GPIOId;

		_Pin_id = PINId;

		gpio::configure_gpio_pin(_Gpio_id, _Pin_id);
	}

	void Pinout::configure_input()
	{
		gpio::configure_input_pin(_Gpio_id, _Pin_id);
	}

	void Pinout::high()
	{
		::gpio::set_pin(_Gpio_id, _Pin_id);
	}

	void Pinout::low()
	{
		::gpio::reset_pin(_Gpio_id, _Pin_id);
	}

	bool Pinout::is_pin_high()
	{
		return ::gpio::is_pin_high(_Gpio_id, _Pin_id);
	}

} //namespace pinout
