#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <iostream>
#include "UI.h"
#include "Graph.h"
#include "appFunctions.h"
#include "Statistics.h"
#include "test.h"

using namespace std;

int main(){
	UI ui;
	ui.chooseOption();

	testAll();
	return 0;
}