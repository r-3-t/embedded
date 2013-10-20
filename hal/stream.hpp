#pragma once


class stream
{
public:
	stream();
	~stream();

	void push_back(unsigned char c);

	void clear();

	unsigned int size() const;

	unsigned char operator[](unsigned int) const;

private:
	struct stream_internal;
	stream_internal* _internal;
};
