#pragma once

#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>


namespace pinout
{

	class Pinout : public ::pinout::PinoutInterface
	{
	public:
		Pinout(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);

		virtual void high();
		virtual void low();

	private:
		::pinout::Gpio_id				_Gpio_id;
		::pinout::Pin_id 				_Pin_id;
	};

	typedef ::pinout::Pinout					ConcretePinout;

} //namespace pinout
