#include "DFA.h"

// Check if string b is a suffix of string a
bool checkSuffix(string b, string a) {
	int lenA = a.length();
	int lenB = b.length();
	if (lenB == 0)
		return true;
	if (lenA < lenB)
		return false;
	int d = lenA - lenB;
	for (int i = lenB - 1; i >= 0; i--)
		if (b[i] != a[i + d])
			return false;
	return true;
}

// Build DFA
void buildDFA(string P, vector<vector<int>>& dfa) {
	int m = P.length();
	string Pa, Pk;
	int k;
	dfa.resize(m + 1);
	for (int i = 0; i <= m; i++)
		dfa[i].resize(95);

	for (int q = 0; q <= m; q++) {
		for (char i = 0x20; i <= 0x7e; i++) {
			k = min(m + 1, q + 2);
			do {
				k--;
				Pk = P.substr(0, k);
				Pa = P.substr(0, q) + i;
			} while (!checkSuffix(Pk, Pa) && k);
			dfa[q][i - 0x20] = k;
		}
	}
}

// DFA search algorithm
vector<int> DFA_Search(string P, string T) {
	vector<vector<int>> dfa;
	buildDFA(P, dfa);

	vector<int> res;
	res.resize(0);
	int q = 0;
	int n = T.length();
	int m = P.length();
	for (int i = 0; i < n; i++) {
		if (T[i] < 0x20 || T[i] > 0x7e)
			q = 0;
		else {
			q = dfa[q][T[i] - 0x20];
			if (q == m)
				res.push_back(i + 1);
		}
	}
	return res;
}

// Read input from a file
void readInput(string& input, char* fileName) {
	fstream fin;
	input = "";
	fin.open(fileName, fstream::in);
	string x;
	while (getline(fin, x))
		input += x;
	fin.close();
}

// Find Computer Name
void findComputerName(string& input, string& preComputerName, string& newListing, vector<string>& ComputerName) {
	vector<int> predictPos = DFA_Search(preComputerName, input);
	int j;
	int newListingLen = newListing.length();
	string computerName;
	for (int i = 0; i < predictPos.size(); i++) {
		computerName = "";
		j = predictPos[i];
		while (input[j++] != '>');
		while (input[j] != '<')
			computerName += input[j++];
		
		//New Listing
		if (computerName == "") {
			j += newListingLen;
			while (input[j] == '\t' || input[j] == ' ') j++;
			while (input[j] != '<')
				computerName += input[j++];
		}
		ComputerName.push_back(computerName);
	}
}

// Find Computer Price
void findComputerPrice(string& input, string& preComputerPrice, string& prRange, vector<string>& ComputerPrice) {
	vector<int> predictPos = DFA_Search(preComputerPrice, input);
	int j;
	int prRangeLen = prRange.length();
	string computerPrice;
	for (int i = 0; i < predictPos.size(); i++) {
		computerPrice = "";
		j = predictPos[i] + 1;
		if (input[j] != ' ' && input[j] != '\t')
			j--;
		else
			while (input[j] == ' ' || input[j] == '\t') ++j;
		while (input[j] != ' ')
			computerPrice += input[j++];
		if (computerPrice == "<span") {
			computerPrice = "";
			j += prRangeLen;
			while (input[j] != ' ')
				computerPrice += input[j++];
		}
		ComputerPrice.push_back(computerPrice);
	}
}

int main() {
	char fileName[] = "ebay.html";
	string input;
	readInput(input, fileName);
	string preComputerName = "<h3 class=\"lvtitle\"><a href=";
	string preComputerPrice = "<span  class=\"bold\">";
	string newListing = "<span class=\"newly\">New listing</span>";
	string prRange = " class=\"prRange\">";

	vector<string> ComputerName;
	vector<string> ComputerPrice;
	findComputerName(input, preComputerName, newListing, ComputerName);
	findComputerPrice(input, preComputerPrice, prRange, ComputerPrice);

	freopen("Laptop.txt", "w", stdout);
	for (int i = 0; i < ComputerName.size(); ++i) {
		cout << setw(100) << left << ComputerName[i];
		cout << ComputerPrice[i] << " VND";
		cout << endl << endl;
	}

	fclose(stdout);

	return 0;
}