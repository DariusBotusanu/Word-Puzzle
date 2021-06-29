#include "test.h"

void testAppFunctions()
{
	assert(differsByOffset("cat", "cot", 1));
	assert(!differsByOffset("the following string lies", "the previous string tells the truth", 1));

	vector<string> catWildcards = computeWildcards("cat");
	assert(catWildcards[0] == "*at");
	assert(catWildcards[1] == "c*t");
	assert(catWildcards[2] == "ca*");

	vector<string> words = vectorFromFile("./words/wordsLength4.txt");

	fstream file;
	file.open("./words/wordsLength4.txt");
	int i = 0;
	while (file)
	{
		string temp;
		file >> temp;
		assert(words[i++] == temp);
	}
	file.close();

	string testDrop = dropLastChar("the last letter is ...n");
	string dot = ".";
	assert(testDrop[testDrop.length()-1] == dot[0]);

	assert(!fileExists("This file does not exist .txt"));
	assert(fileExists("./words/wordsLength4.txt"));
}

void testStatistics()
{
	Statistics st("test_player_stats");
	set<string> uniqueSet = st.uniqueWords();
	assert(uniqueSet.find("cat") != uniqueSet.end());
	assert(uniqueSet.find("cot") != uniqueSet.end());
	assert(uniqueSet.find("cow") != uniqueSet.end());
	assert(uniqueSet.find("dock") != uniqueSet.end());
	assert(uniqueSet.find("duck") != uniqueSet.end());
	assert(uniqueSet.find("luck") != uniqueSet.end());
	assert(uniqueSet.find("unexistentWord") == uniqueSet.end());

	//assert(equalDouble(st.efficiency(), 99.8333));
}

bool equalDouble(double x, double y)
{
	return abs(x - y) < std::numeric_limits<double>::epsilon();
}


void testAll()
{
	testAppFunctions();
	testStatistics();
}
