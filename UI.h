#pragma once
#include <iostream>
#include <string>
#include "Graph.h"
#include <fstream>
#include "appFunctions.h"
#include <sstream>
#include <algorithm>
#include <random>
#include "Statistics.h"

using namespace std;

class UI
{
public:
	void printMenu();
	void chooseOption();
	bool showStats();
	void automatic();
	string getName();
	int selectDifficulty();
	string getStart(int numChars);
	string getRandomFromDict(string src);
	tuple<vector<string>, int, int> getWord(Graph<string>& g, string start, string target);
	void interactive();
	void showHint(Graph<string>& g,string word, string target);
	string askForHint();
	void colourDifferentLetter(string word1, string word2);
	

	Graph<string>& generateGraphByCharNum(int num);
};

