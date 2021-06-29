#pragma once
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <tuple>

using namespace std;

class Statistics
{
public:
	Statistics(string username);

	set<string> uniqueWords();

	double efficiency();

private:
	string m_username;
};
