#include "Print.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


namespace arduino
{
	namespace print
	{

		Print::Print()
		{
			return;
		}

		int Print::print(const char* pString)
		{
			this->write(pString);
		}

		void Print::print(const char c)
		{
			this->write(c);
		}


		void Print::print(const int c, ArduinoFormat_T format)
		{
			char Buffer[32];
			memset(Buffer, 0, sizeof(Buffer));

			if (format == DEC)
			{
				sprintf(Buffer, "%i", c);
			}
			else if (format == HEX)
			{
				sprintf(Buffer, "%x", c);
			}
			else
			{
				sprintf(Buffer, "%x", c);
			}
			this->print(Buffer);

		}

		void Print::print(double d, int size)
		{
			char Buffer[16];
			memset(Buffer, 0, sizeof(Buffer));

			sprintf(Buffer, "%05f", d);

			this->print(Buffer);

		}

		void Print::println(const char c, ArduinoFormat_T format)
		{
			this->print(c, format);
			this->println();
		}

		void Print::println(const char* pString)
		{
			this->print(pString);
			this->println();
		}

		void Print::println()
		{
			this->print("\r\n");
		}

	} //namespace print

} //namespace arduino
