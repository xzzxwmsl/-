#pragma once
#include"pch.h"
#include<vector>
using namespace std;
class SCAN
{
public:
	SCAN();
	~SCAN();
	void getLocation();
	vector<string> getText();
private:
	string Location;
	string pro;
	vector<string> V;
};

