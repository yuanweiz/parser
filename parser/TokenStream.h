#ifndef __TOKEN_STREAM_H
#define __TOKEN_STREAM_H
#include <vector>
#include "StringStream.h"
#include <assert.h>
enum class TokenType :int 
{ L_BRAC = 128, R_BRAC, NUM, COMMA ,END};
struct Token {
	TokenType type;
	union {
		double value;
	}data;
};
class TokenStream {
public:
	using size_t = std::vector<Token>::size_type;
	TokenStream(StringStream * s) :pos_(0),ss_(*s)
	{
		//currently not lazy stream
		//one pass
		while (ss_.peek()) {
			Token token;
			char c = ss_.take();
			if (c == '[') {
				token.type = TokenType::L_BRAC;
			}
			else if (c == ']') {
				token.type = TokenType::R_BRAC;
			}
			else if (c == ',') {
				token.type = TokenType::COMMA;
			}
			else {
				int i = c-'0';
				while (true) {
					char next = ss_.peek();
					if (next >= '0' && next <= '9') {
						i = i * 10 + (next - '0');
						ss_.take();
					}
					else break;
				}
				token.type = TokenType::NUM;
				token.data.value = i;
			}
			tokens_.push_back(token);
		}
	}
	bool readable() {
		assert(pos_ <= tokens_.size());
		return pos_ < tokens_.size();
	}
	void eat(TokenType type) {
		if (peek().type == type)
			advance();
		else {
			throw std::exception("TokenStream::eat(): wrong type");
		}
	}
	Token& peek() {
		return tokens_[pos_];
	}
	void advance() {
		pos_++;
	}

private:
	size_t pos_;
	
	std::vector<Token> tokens_;
	StringStream & ss_;
};
#endif// __TOKEN_STREAM_H