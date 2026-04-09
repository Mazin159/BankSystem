#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct sClient {
	string AccountNumber;
	string Name;
	string PinCode;
	string Number;
	double Salary;
	bool MarkToDelete = false;
};

vector<string> SplitString(string s1, string delim) {
	string Word;
	vector<string> vString;
	int pos = 0;
	while ((pos = s1.find(delim)) != std::string::npos) {

		Word = s1.substr(0,pos);

		if (Word != "") {
		vString.push_back(Word);

		}
		s1.erase(0, pos + delim.length());
	}

	if (s1 != "") {
		vString.push_back(s1);
	}

	return vString;
}


int main()
{
	
	
	
}

