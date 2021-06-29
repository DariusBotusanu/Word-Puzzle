#pragma once
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "Graph.h"
#include <random>
#include <sstream>
#include <windows.h>
#include <chrono>


using namespace std;

bool differsByOffset(string word1, string word2, int offset);

vector<string> computeWildcards(string word);

map<string, vector<string>> getWordMap(string src);

void addWordLinks(Graph<string>& g, string src);

vector<string> vectorFromFile(string src);

void partitionDict(std::string src);

void setColor(int value);

string getTime();

string dropLastChar(string word);

void storeInfo(string username, string dateTime, string start, string end, int hints, vector<string> usedWords, int moves, int optimalMoves);

bool fileExists(const string& name);



