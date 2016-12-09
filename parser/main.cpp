#include "StringStream.h"
#include "TokenStream.h"

//[1,2,3,5,7,9,10]

//list := [] | [ items]
//items := item itemtail
//itemtail = (, item)*
//item := list | NUM
struct List {
	bool isNum;
	double num;
	std::vector<List> list;
};
struct helper {
	helper(const char * msg) {
		for (int i = 0;i < indent;++i) {
			putchar(' ');
		}
		puts(msg);
		indent=indent+2;
	}
	~helper() {
		indent -= 2;
	}
	static int indent;
};
int helper::indent = 0;

void parseNum(TokenStream & , List& );
void parseList(TokenStream & , List& );
void parseItem(TokenStream & , List& );
void parseItems(TokenStream & , List& );
void parseItemTail(TokenStream & , List& );
void parseNum(TokenStream & ts, List& list) {
	helper h("parseNum");
	list.isNum = true;
	list.num = ts.peek().data.value;
	ts.eat(TokenType::NUM);
}

void parseItem(TokenStream &ts, List&list) {
	helper h("parseItem");
	auto type = ts.peek().type;
	if ( type == TokenType::L_BRAC) {
		parseList(ts, list);
	}
	else if (type == TokenType::NUM){
		parseNum(ts, list);
	}
	else {
		throw std::exception("");
	}
}
void parseItemTail(TokenStream & ts, List&list) {
	helper h("parseItemTail");
	assert(list.isNum == false);
	assert(ts.readable());
	while (ts.peek().type != TokenType::R_BRAC) {
		ts.eat(TokenType::COMMA);
		List item;
		parseItem(ts, item);
		list.list.push_back(item);
	}
}

void parseItems(TokenStream& ts, List& list) {
	helper h("parseItems");
	List head;
	parseItem(ts,head);
	list.list.push_back(head);
	parseItemTail(ts, list);
}
void parseList(TokenStream& ts,List & list) {
	helper h("parseList");
	list.isNum = false;
	if (!ts.readable())
		return;
	ts.eat(TokenType::L_BRAC);
	if (ts.peek().type != TokenType::R_BRAC)
		parseItems(ts, list);
	ts.eat(TokenType::R_BRAC);
}
int main() {
	//simplest parser
	StringStream ss("[ 1, 2  ,3,[4,5],[[9]]]");
	TokenStream ts(&ss);
	List list;
	//starts from List#
	parseList(ts,list);

	return 0;
}