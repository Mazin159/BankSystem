#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
const string ClientsFileName = "NewClients.txt";

struct sClient {
	string AccountNumber;
	string Name;
	string PinCode;
	string PhoneNumber;
	double Balance;
	bool MarkToDelete = false;
};
void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.PhoneNumber;
	cout << "\nAccount Balance: " << Client.Balance;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}
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

sClient ConvertStringToClientRecord(string S1, string Delim = "#//#") {
	vector<string> vRecord;
	sClient Client;
	vRecord = SplitString(S1, Delim);

	Client.AccountNumber = vRecord[0];
	Client.PinCode = vRecord[1];
	Client.Name = vRecord[2];
	Client.PhoneNumber = vRecord[3];
	Client.Balance = stod(vRecord[4]);


	return Client;
}
vector<sClient> LoadClientsDataFromFile(string FileName) {
	fstream MyFile;
	vector<sClient> vClients;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		string Line;

		while (getline(MyFile, Line)) {

			if (Line != "") {

				vClients.push_back(ConvertStringToClientRecord(Line));

			}
		}
		MyFile.close();

	}
	return vClients;

}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client)
{
	
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

void AddDataLineToFile(string stDataLine, string FileName) {
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}

}

sClient ReadClient() {
	
	sClient Client;
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	bool IsExiste = false;

	// Usage of std::ws will extract allthe whitespace character
	do
	{
		IsExiste = false;
		cout << "Enter Account Number? ";
      getline(cin >> ws, Client.AccountNumber);

	  if (FindClientByAccountNumber(Client.AccountNumber, vClients,Client)) {
		  IsExiste = true;
		  cout << "This Account Number is already Existes! Please enter another account number:\n";
		 
	  }
	  

	} while (IsExiste);
	
	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.PhoneNumber);
	cout << "Enter AccountBalance? ";
	cin >> Client.Balance;
	return Client;
}

void AddClientToFile() {
	sClient Client = ReadClient();
	AddDataLineToFile(ConvertClientRecordToString(Client), ClientsFileName);

}

void AddClientsToFile() {
	char AddMore = 'Y';
	do
	{
		system("cls");
		cout << "Adding New Client:\n\n";
		AddClientToFile();
		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber,
	vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkToDelete = true;
			return true;
		}
	}
	return false;
}
void SaveClientsDataToFile(vector<sClient> vClients,string FileName) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkToDelete == false)
			{
				//we only write records that are not marked for delete.
					DataLine = ConvertClientRecordToString(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
}

bool DeleteClientByAccoutNumber(string AccountNumber, vector<sClient>& vClients) {
	
	sClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		char Ans;
		cout << "\nAre you sure you want to delete this Client? (y/n)  :";
		cin >> Ans;
		if (Ans == 'Y' || Ans == 'y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(vClients, ClientsFileName);
			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}

	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}

	return false;
}

void PrintClientRecord(sClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber
		<< "| " << setw(10) << Client.PinCode
		<< "| " << setw(25) << Client.Name
		<< "| " << setw(15) << Client.PhoneNumber
		<< "| " << setw(12) << fixed << setprecision(2) << Client.Balance
		<< "|\n";
}
void PrintAllClientsData(vector<sClient> vClients)
{
	cout << "\n\t\t\tClient List (" << vClients.size() << ") Client(s)\n";

	cout << "----------------------------------------------------------------------------------------\n";

	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << setw(10) << "Pin Code"
		<< "| " << setw(25) << "Client Name"
		<< "| " << setw(15) << "Phone"
		<< "| " << setw(12) << "Balance"
		<< "|\n";

	cout << "----------------------------------------------------------------------------------------\n";

	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
	}

	cout << "----------------------------------------------------------------------------------------\n";
}
sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.PhoneNumber);
	cout << "Enter AccountBalance? ";
	cin >> Client.Balance;
	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector
	<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,
		Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n? ";
			cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(vClients,ClientsFileName);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}



int main()
{
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	PrintAllClientsData(vClients);
	system("pause>0");
	return 0;
		
}

