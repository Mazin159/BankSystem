#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct sClient {
	string AccountNumber;
	string Name;
	string PinCode;
	string PhoneNumber;
	double Balance;
	bool MarkToDelete = false;
};


string ConvertClientRecordToString(sClient Client,string Delim = "#//#") {
	string Record;
	string sBalance = to_string(Client.Balance);
	
	Record = Client.AccountNumber + Delim + Client.PinCode + Delim
		+ Client.Name + Delim + Client.PhoneNumber + Delim + sBalance;

		return Record;
}

vector<string> SplitString(string S1, string Delim="#//#") {
	string Word;
	vector<string> vString;
	int pos = 0;
	while ((pos = S1.find(Delim)) != std::string::npos) {

		Word = S1.substr(0,pos);

		if (Word != "") {
		vString.push_back(Word);

		}
		S1.erase(0, pos + Delim.length());
	}

	if (S1 != "") {
		vString.push_back(S1);
	}

	return vString;
}


int main()
{
	
	
	
}

