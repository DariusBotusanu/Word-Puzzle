#define _CRT_SECURE_NO_WARNINGS
#include "appFunctions.h"


bool differsByOffset(string word1, string word2, int offset) 
{
	/**
	* Input: std::string word1, std::string word2, int offset, where word1 and word2 are the words to compare, and offset is the allowed difference in characters
	* Output: - true if the words differ by "offset" nubmer of characters
	*		  - false otherwise
	*/
	//Offset represents number of different characters in the words, (we will consider that case it's 1 for the program)
	if (word1.length() == word2.length()) {
		for (unsigned int i = 0; i < word1.length(); ++i) 
		{
			if (word1[i] != word2[i]) {
				offset--;
			}
			if (offset < 0) {
				//If we foudn more than one mismatch, we return false
				return false;
			}
		}
		if (offset == 0) 
		{
			//This condition means that the words differ by "offset" characters
			return true;
		}
		else 
		{
			//This case can be met either when the words are the same,
			//or their number of different characters is smaller than offset
			return false;
		}
	}
	else 
	{
		//If the words do not have the same length, we return false
		return false;
	}
}//Complexity: O(N), where N is the length of the words (if they are equal)

vector<string> computeWildcards(string word) 
{
	/**
	* Input: std::strign word
	* Output: std::vector<string>
	* This function computed the wildcards of a word. For example, the wildcards of cat are: *at, c*t, ca*
	*/
	vector<string> keysVector;
	for (auto i = 0; i < word.length(); ++i) 
	{
		//We store the character that we replace with the wildcard "*"
		char aux = word[i];
		//We replace the respective character with "*"
		word[i] = '*';
		//We store the key in our vector of keys
		keysVector.push_back(word);
		//We restore the initial word
		word[i] = aux;
	}
	//We return the vector of keys
	return keysVector;
}

map<string, vector<string>> getWordMap(string src) 
{
	/**
	* Input: std::string src, represents the source from where we open our file
	* Output: std::map<string, vector<string>>, represents a map where the key is the wildcard of a word and the value is a vector with all the matching words
	*/
	map<string, vector<string>> adjacentWords; //represents a map where the key is a wildcard of word and the value is a vector of matching words
	ifstream dictionary;
	dictionary.open(src);//We open the file where we read the words from
	vector<string> values; //represents the values of a key
	while (dictionary) 
	{
		string wordInDict;
		dictionary >> wordInDict;
		vector<string> wildcards = computeWildcards(wordInDict);
		for (auto wildcard : wildcards) 
		{
			adjacentWords[wildcard].push_back(wordInDict);
		}
	}
	dictionary.close();//We close the file
	return adjacentWords;
}

void addWordLinks(Graph<string>& g, string src) 
{
	/**
	* Input: - Graph<std::string>& a reference to an instance of class Graph<std::string>
	*        - std::string src the source accessed by the getWordMap function
	* Output: void
	* This function adds the links between adjacent words of the graph. It modifies the graph
	*/
	map<string, vector<string>> adjacentWords = getWordMap(src);
	for (auto pair : adjacentWords) 
	{
		for (auto word : pair.second) 
		{
			g.addElem(word);
			g.modifyList(word).insert(g.modifyList(word).end(), pair.second.begin(), pair.second.end());
		}
	}
}

vector<string> vectorFromFile(string src)
{
	/**
	* Input: std::string src - represents the source from where we read a file
	* Output: std::vector<std::string> - represents a vector of words from a dictionary
	*/
	ifstream dictionary;
	dictionary.open(src);//We open the file where we read the words from
	vector<string> values; //represents the values of a key
	while (dictionary) 
	{
		string wordInDict;
		dictionary >> wordInDict;
		values.push_back(wordInDict);
	}
	dictionary.close();//We close the file
	return values;
}

void partitionDict(std::string src) 
{
	/**
	* Input: std::string src represents the source from where we read a file
	* Output: void
	* This function partitions a .txt file into files which contain words of the same length
	*/
	ifstream dictionary;
	dictionary.open(src);
	size_t i = 0;
	while (dictionary) {
		std::string word;
		dictionary >> word;
		std::string saveTo = "./words/wordsLength";
		saveTo += to_string(word.size());
		saveTo += ".txt";
		ofstream file;
		file.open(saveTo, std::ios_base::app);
		file << word << "\n";
		file.close();
	}
	dictionary.close();
}

void setColor(int value) 
{
	/**
	* Input: int value - represents the value of a color
	* Output: void
	* This function prints a character, or several, with a specific colour
	*   1: Blue
	*	2: Green
	*	3: Cyan
	*	4: Red
	*	5: Purple
	*	6: Yellow (Dark)
	*	7: Default white
	*	8: Gray/Grey
	*	9: Bright blue
	*	10: Brigth green
	*	11: Bright cyan
	*	12: Bright red
	*	13: Pink/Magenta
	*	14: Yellow
	*	15: Bright white
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

string getTime()
{
	/**
	* Input: void
	* Output: std::string which represents the time and date when the function was called
	*/
	auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	string timeString = ctime(&time);
	return timeString;
}

string dropLastChar(string word)
{
	/**
	* Input: std::string word - represents a word
	* Output: std::string which represents the input word, without the last character
	* This function was designed to deal with the string which represents the time (which intially has a \n at the end)
	*/
	string toReturn;
	for (size_t i = 0; i < word.length() - 1; ++i)
	{
		toReturn += word[i];
	}
	return toReturn;
}

void storeInfo(string username, string dateTime, string start, string end, int hints, vector<string> usedWords, int moves, int optimalMoves)
{
	/**
	* Input: - std::string username
	*		 - std::string dateTime
	*		 - std::string start
	*		 - std::string end
	*		 - int hints
	*		 - vector<std::string> usedWords
	*		 - int moves
	*		 - int optimalMoves
	* Output: void
	* This function stores the information from the input in a .csv file
	*/
	fstream user;
	user.open("./players/" + username + ".csv", std::ios_base::app);
	user << dropLastChar(dateTime) << ", ";
	user << start << ", ";
	user << end << ", ";
	user << to_string(hints) << ", ";
	for (auto word : usedWords)
	{
		user << word << " ";
	}
	user << ", ";
	user << to_string(moves) << ", ";
	user << to_string(optimalMoves);
	user << "\n";
	user.close();
}

bool fileExists(const string& name)
{
	/**
	* Input: const std::string& name - name represents the source of a file we a re looking for
	* Output: - true : if the file exists
	*		  - false : otherwise
	*/
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
