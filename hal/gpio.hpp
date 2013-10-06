#pragma once



namespace gpio {


	class PinOut
	{
	public:
		PinOut() {}

		virtual void high() = 0;
		virtual void low() = 0;
	};

}


