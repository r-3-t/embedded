#include <stream.hpp>


#include <vector>

struct stream::stream_internal
{
	std::vector<unsigned char> value;
};

stream::stream() : _internal(new stream::stream_internal)
{

}


stream::~stream()
{
	delete _internal;
}

void stream::push_back(unsigned char c)
{
	_internal->value.push_back(c);
}

void stream::clear()
{
	_internal->value.clear();
}

unsigned int stream::size() const
{
	return _internal->value.size();
}

unsigned char stream::operator[](unsigned int Idx) const
{
	return _internal->value[Idx];
}
	