#include "StringStream.h"
#include <stdexcept>
#include <stdio.h>
using namespace std;
void StringStream::rewind(size_t w)
{
	if (pos >=w) {
		pos -= w;
	}
	else {
		char buf [1024];
		_snprintf(buf, sizeof(buf), "Can't String::rewind() %d bytes", w);
		throw std::exception(buf);
	}
}
