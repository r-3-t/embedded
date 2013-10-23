#include <pinout.hpp>

#include <iostream>


int main (int argc, char** argv)
{
	const std::vector<pinout::Pin_Description>& pins = pinout::PinDescription();

	std::cout << "Pins : " << std::endl;
	for (auto pin : pins)
	{
		std::cout <<	"gpio: "		<< "\t" << pin.gpio		 	<< "\t" <<
						"gpio_id: "		<< "\t" << pin.id			<< "\t" <<
						"bus: "			<< "\t" << pin.bus		 	<< "\t" <<
						"bus_id: "		<< "\t" << pin.bus_id		<< "\t" <<
						"function: "	<< "\t" << pin.function	 	<< "\t" <<
						"gpio: "		<< "\t" << pin.gpio			<< std::endl;
	}

	std::cout << "USART 1 : " << std::endl;
	auto iter = std::find_if (pins.begin(), pins.end(), [] (const pinout::Pin_Description& pin) -> bool {
		return (pin.bus == pinout::USART) && (pin.bus_id == 1);
	});
	while (iter != pins.end())
	{
		std::cout <<	"gpio: "		<< "\t" << (*iter).gpio		<< "\t" << 
						"gpio_id: "		<< "\t" << (*iter).id		<< "\t" << 
						"bus: "			<< "\t" << (*iter).bus		<< "\t" << 
						"bus_id: "		<< "\t" << (*iter).bus_id	<< "\t" << 
						"function: "	<< "\t" << (*iter).function	<< "\t" << 
						"gpio: "		<< "\t" << (*iter).gpio		<< std::endl;

		iter++;
	}

}

