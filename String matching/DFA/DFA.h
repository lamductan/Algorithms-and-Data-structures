#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

bool checkSuffix(string, string);
void buildDFA(string, vector<vector<int>>&);
vector<int> DFA_Search(string, string);

void readInput(string&, char*);
void findComputerName(string&, string&, string&, vector<string>&);
void findComputerPrice(string&, string&, string&, vector<string>&);