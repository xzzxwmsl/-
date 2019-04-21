// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#ifndef PCH_H
#define PCH_H
#include<iostream>
#include<string>
#include<map>
using namespace std;
// TODO: 添加要在此处预编译的标头
extern int line;
static const int MAXNUM = 1 << 10;
typedef enum
{
	START, INNUM, INLETTER, DONE, INEQ, INLE, INGE, INNE, INLBUFFER, INCOMMENT, INRBUFFER
}State;

typedef enum {
	IF, ELSE, INT, RETURN, VOID, WHILE, PLUS, MINUS, MUL, DIV, LT, LE, GT, GE, ASSIGN, EQ,
	NEQ, COMMA, SEMI, LPAREN, RPAREN, LBUFFER, RBUFFER, LBRACKET, RBRACKET, LBRACE, RBRACE,
	ID, NUM, ENDFILE, ERROR
}TokenType;

static const string Author = "xzz";

static struct {
	TokenType tok;
	string tokName;
}reversedWords[6] = {
	{IF,"if"},{ELSE,"else"},{VOID,"void"},{RETURN,"return"},{INT,"int"},{WHILE,"while"}
};


static struct TokenSet{  //保存每个token的类型与名字
	std::string tokenType;
	std::string tokenName;
	int line; // token出现在程序的第几行
}token;
#endif //PCH_H
