#include "Statistics.h"

Statistics::Statistics(string username) : m_username{ username }
{
	/**
	* Input: std::string username
	* This is the parameterized constructor of the class Statistics
	*/
}

set<string> Statistics::uniqueWords()
{
	/**
	* Input: void
	* Output: std::set<std::string> representing the unique words the player used while playing
	*/
	ifstream player;
	player.open("./players/" + m_username + ".csv");
	set<string>* uniqueWords = new set<string>;
	vector<string> rows;
	while (player) 
	{
		//We read the rows from our .csv file
		string row;
		getline(player, row, '\n');
		rows.push_back(row);
	}
	player.close();

	vector<string> usedWords;
	for (auto row : rows)
	{
		stringstream ss;
		ss << row;
		string time, start, end, hints, words;
		getline(ss, time, ',');  //We drop these values
		getline(ss, start, ','); //We drop these values
		getline(ss, end, ',');   //We drop these values
		getline(ss, hints, ',');   //We drop these values
		getline(ss, words, ',');
		usedWords.push_back(words);
	}

	for (auto wordString : usedWords)
	{
		
		stringstream ss;
		ss << wordString;
		while (ss)
		{
			string word;
			getline(ss, word, ' ');
			uniqueWords->insert(word);
		}
		
	}
	return *uniqueWords;
}

double Statistics::efficiency()
{
	/**
	* Input: -
	* Output: double representing the efficiency of the player
	* The efficiency is calculated as fallows: for each game, the player scores 100% efficiency if it tried the same number of words as the optimal number
	*										   each hint costs the player 10% of efficiency
	*										   the standard mean of the efficiencies of each game is returned
	*/
	ifstream player;
	player.open("./players/" + m_username + ".csv");
	vector<string> rows;
	while (player)
	{
		//We read the rows from our .csv file
		string row;
		getline(player, row, '\n');
		rows.push_back(row);
	}
	player.close();

	vector<tuple<int, int, int>> playerData;
	for (auto row : rows)
	{
		stringstream ss;
		ss << row;
		string time, start, end, hints, words, moves, optimum;
		int intHints, intMoves, intOptimum;
		getline(ss, time, ',');  //We drop these values
		getline(ss, start, ','); //We drop these values
		getline(ss, end, ',');   //We drop these values
		getline(ss, hints, ',');
		stringstream toint;
		toint << hints;
		toint >> intHints;
		getline(ss, words, ',');  //We drop these values
		getline(ss, moves, ',');
		toint << moves;
		toint >> intMoves;
		getline(ss, optimum, ',');
		toint << optimum;
		toint >> intOptimum;
		playerData.push_back(make_tuple(intHints, intMoves, intOptimum));
	}

	vector<double> gamesEfficiency;
	double sumEff = 0;
	for (auto info : playerData)
	{
		double eff = 0;
		eff -= (double)get<0>(info) * 0.10; //each hint decreases 0.05 % from the efficiency of the player
		eff += (double)get<2>(info) * 100 / (double)get<1>(info);
		gamesEfficiency.push_back(eff);
		sumEff += eff;
	}

	return sumEff / (double)gamesEfficiency.size();
}
