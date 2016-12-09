#ifndef __STRING_STREAM_H
#define __STRING_STREAM_H
#include <string>
#include <functional>
#include <stdexcept>
class StringStream {
public:
	using size_t=std::size_t;
	void rewind(size_t);
	StringStream(const std::string &str) :pos(0),str_(str) {}

	//idempotent, but not immutable
	char peek() {
		eatSpace();
		if (pos == str_.size()) {
			return '\0';
		}
		else
			return str_[pos];
	}
	char take() {
		char next = peek();
		if (next)
			pos++;
		return next;
	}
	void eat(char c) {
		eatSpace();
		char next = take();
		if (c != next) {
			char buf[1024];
			snprintf(buf,sizeof(buf),
				"StringStream::eat(): expected %c but get %c",
				c, next);
			throw std::exception(buf);
		}
	}
private:
	void eatSpace() {
		while (pos != str_.size() && isspace(str_[pos])){
			pos++;
		}
	}
	bool isspace(char c) {
		return c == ' ' || c == '\t';
	}
	size_t pos;
	std::string str_;
};
#endif// __STRING_STREAM_H