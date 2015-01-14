#pragma once

#include <types.hpp>
#include <cstddef>

namespace arduino
{
	namespace print
	{

		typedef enum
		{
			DEC,
			HEX,
			OCT,
			BIN
		} ArduinoFormat_T;

		class Print
		{
		public:

			Print();

			virtual void begin(int Speed) {};
			virtual void write(const char c) {};
			virtual int write(const char* pc) { return 0; };
			virtual size_t write(const unsigned char* pc, unsigned int size) { return 0; };
			virtual int available() {return 0; };
			virtual int read() { return 0; };

			int print(const char* pString);
			void print(const char c);
			void print(const ::types::uint32 v);
			void print(const ::types::uint16 v);
			void print(const ::types::byte b);
			void print(const ::types::int32 v);
			void print(const ::types::int16 v);
			void print(const float f);
			void print(const int c, ArduinoFormat_T format);
			void print(double d, int size);
			void println(const ::types::byte b);
			void println(const char c, ArduinoFormat_T format);
			void println(const char* pString);
			void println();

		private:

		}; //class Print


	} //namespace print

} //namespace arduino
