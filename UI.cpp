#include "UI.h"

void UI::printMenu()
{
	/**
	* Input: -
	* Output: void
	* Displays the menu to the user
	*/
	cout << "What would you like to do?" << endl;
	cout << "\ta. Play automatic" << endl;
	cout << "\ti. Play interactive" << endl;
	cout << "\td. Diplsay statistics" << endl;
	cout << "\te. Exit the program" << endl;
}

void UI::chooseOption()
{
	/**
	* Input: -
	* Output: void
	* Reads the option from the user
	*/

	do {
		printMenu();
		char option;
		cin >> option;
		switch (option) {
		default:
			cout << "Please choose a valid option" << endl;
			break;
		case 'a':
			automatic();
			break;
		case 'i':
			interactive();
			break;
		case 'd':
			showStats();
			break;
		case 'e':
			exit(0);
		}

	} while (true);
}

bool UI::showStats()
{
	/**
	* Input: -
	* Output: - true if the player exists
	*		  - false otherwise
	* Shows the statistics of a player to the user. Displays a message if the player does not exist in the "database"
	*/
	string username;
	cout << "Enter the username: ";
	cin >> username;
	if (fileExists("./players/" + username + ".csv") == false)
	{
		cout << "The player does not exist!" << endl;
		return false;
	}
	Statistics player(username);
	set<string> words = player.uniqueWords();
	cout << username << "'s efficiency: " << player.efficiency() << endl;
	cout << "Here are all the unique words the player used: ";
	for (auto word : words)
	{
		cout << word << " ";
	}
	cout << endl;
	return true;
}

void UI::automatic()
{
	/**
	* Input: -
	* Output: void
	* This method allows the user to play in automatic words. It first asks for the number of letters of the word, then for the starting ad ending word.
	*/
	string start, target;
	int length;
	cout << "Enter the length of the words: ";
	cin >> length;
	cout << endl << "Enter the word you'd like to start with: ";
	cin >> start;
	cout << endl << "Enter the word you'd like to get to: ";
	cin >> target;
	cout << endl;
	Graph<string> g = generateGraphByCharNum(length);
	string strNum = to_string(length);
	string src = "./words/wordsLength" + strNum + ".txt";
	addWordLinks(g, src);
	g.displayShortestPath(start, target);
}

string UI::getName()
{
	/**
	* Input: -
	* Output: void
	* Asks the user for its name. (Naively) every name is allowed as it's cansidered a username
	*/
	string name;
	cout << "What is your name? \n\tname: ";
	cin >> name;
	cout << endl;
	return name;
}

int UI::selectDifficulty()
{
	/**
	* Input: -
	* Output: void
	* Asks the user for the length of the words (which is considered to be the difficulty of the game)
	*/
	int nums;
	cout << "Select dificulty (as in the number of characters for the words, up to 31 characters): ";
	cin >> nums;
	cout << endl;
	int i = 0;
	while ((nums < 0) || (nums > 31)) 
	{
		cout << "Please enter a number in the range 0-31: ";
		cin >> nums;
	}
	return nums;
}

string UI::getStart(int numChars)
{
	/**
	* Input: int numChars represents the number of characters of a word
	* Output: std::string representing the starting word
	* Forces the user to enter a word with the specified number of characters
	*/
	string start;
	cout << "Enter the word you'd like to start with: ";
	cin >> start;
	while (start.length() != numChars)
	{
		cout << "Please enter a word with the specified number of characters!" << endl;
		cin >> start;
	}
	return start;
}

string UI::getRandomFromDict(string src)
{
	/**
	* Input: std::string src - represents the source of a file we open
	* Output: std::string representing a word randomly selected from the dictionary
	*/
	random_device rd; //get a random number from hardware
	mt19937 gen(rd()); // we seed the generator
	vector<string> words = vectorFromFile(src);
	uniform_int_distribution<> distr(0, words.size()-1);
	string target = words[distr(gen)];
	return target;
}

tuple<vector<string>, int, int> UI::getWord(Graph<string>& g, string start, string target)
{
	/**
	* Input: std::string src - represents the source of a file we open
	* Output: std::tuple<std::vector<std::string>, int, int> represents the words tried by the user, the number of hints taken and the number of steps it took the user to reach the end
	* This function is the backend of the interactive play. It forces the user to comply with the game rules until it reaches the target word.
	*/
	string current = start; //Represents the current word, initially it's the starting point
	int steps = 0; //Represents number of steps needed to get to the target
	int hints = 0; //Represents the number of tips used;
	vector<string> triedWords; //Represents the nubmer of words the user tried in order to get to the target
	while(current != target)
	{
		if (askForHint()[0] == 'y')
		{
			hints++;
			cout << "You should change the coloured letter: ";
			showHint(g, current, target);
			cout << endl;
		}
		vector<string> words = vectorFromFile("./words/wordsLength" + to_string(start.length()) + ".txt");
		string word;
		cout << "Enter the next word: ";
		cin >> word;
		triedWords.push_back(word);
		cout << endl;
		if (find(words.begin(), words.end(), word) == words.end()) 
		{
			cout << "The word does not exist!" << endl;
			steps++;
		}
		else if(!differsByOffset(current, word, 1))
		{
			cout << "You are allowed to change only 1 letter at once!" << endl;
		}
		else if (differsByOffset(current, word, 1))
		{
			current = word;
			steps++;
		}

	}
	return make_tuple(triedWords, steps, hints);
}

void UI::interactive()
{
	/**
	* Input: -
	* Output: void
	* This function is groups together all the functions used for the interactive mode of the game.
	*/
	string time = getTime();

	unordered_map<string, int> dist;
	unordered_map<string, string> pred;

	string name = getName();
	int numChars = selectDifficulty();
	string start = getStart(numChars);
	Graph<string> g = generateGraphByCharNum(numChars);
	string src = "./words/wordsLength" + to_string(numChars) + ".txt";
	string target = getRandomFromDict(src);

	g.bfs(start, target, dist, pred);

	vector<string> path;
	string crawl = target;
	path.push_back(crawl);
	while (pred[crawl] != "")
	{
		path.push_back(pred[crawl]);
		crawl = pred[crawl];
	}

	cout << "You should get to: " << target << endl;
	tuple<vector<string>, int, int> gameData = getWord(g, start, target);

	

	storeInfo(name, time, start, target, get<2>(gameData), get<0>(gameData), get<1>(gameData), path.size()-1); // we store the informations in a .csv file
}

void UI::showHint(Graph<string>& g, string word, string target)
{
	/**
	* Input: - Graph<string>& g, string word, string target
	*		 - std::string word represents the current word the user needs to change
	*		 - std::string target represents the word the user needs to get to
	* Output: void
	* Shows the user the letter he needs to change from the current word in order to reach the end. The letter will be coloured differently
	*/
	unordered_map<string, int> dist;
	unordered_map<string, string> pred;
	g.bfs(word, target, dist, pred);
	string crawl = target;
	vector<string> path;
	path.push_back(crawl);
	while (pred[crawl] != "")
	{
		path.push_back(pred[crawl]);
		crawl = pred[crawl];
	}
	colourDifferentLetter(word, path[path.size()-2]);
}

string UI::askForHint()
{
	/**
	* Input: -
	* Output: std::string representing the answer of the user
	* Asks the user if he needs a hint
	*/
	string answer;
	cout << "Need a hint? Just press 'y', otherwise press any other key: ";
	cin >> answer;
	return answer;
}

void UI::colourDifferentLetter(string word1, string word2)
{
	/**
	* Input: - std::string word1
	*		 - std::string word2
	* Output: void
	* Thsi function colours the different characters between word1 and word2
	*/
	for (size_t i = 0; i < word1.length(); ++i) 
	{
		if (word1[i] != word2[i])
		{
			setColor(11); //We change the colour of the letter
			cout << word1[i];
			setColor(7); //We make sure the other letters remain white
		}
		else {
			cout << word1[i];
		}
	}
}

Graph<string>& UI::generateGraphByCharNum(int num)
{
	/**
	* Input: int num represented the number of characters of the words that will be inserted into the graph
	* Output: Graph<string>& representing a reference to the Graph<std::string> made by words of length "num"
	* This function builds the graph for the words of length "num"
	*/
	Graph<string>* g = new Graph<string>;
	string src;
	string strNum = to_string(num);
	src = "./words/wordsLength" + strNum + ".txt";
	addWordLinks(*g, src);
	return *g;
}

