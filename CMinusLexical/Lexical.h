#pragma once
#include"pch.h"
#include<vector>
using namespace std;
class Lexical
{
public:
	friend class Output;
	Lexical(vector<string>);
	~Lexical();
	void showPro();
	string getPro();
	TokenSet getToken();
	string tokToName(TokenType, string);
	void doLexical();
	void showResult();
private:
	int len; // 程序字节数
	int toknum; // token数目
	int index; //当前读取位置
	vector<string> V;
	vector<TokenSet> TokSet; // 保存所有的token
	string proText; // 将程序一起保存在 proText 中
	int line; // 当前读取到程序的第n行
};

