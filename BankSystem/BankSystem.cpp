#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
const string ClientsFileName = "NewClients.txt";
const string UsersFileName = "Users.txt";
enum enPermissions {
	pShowClients = 1,
	pAddClient = 2,
	pDeleteClient = 4,
	pUpdateClient = 8,
	pFindClient = 16,
	pTransactions = 32,
	pManageUsers = 64,
	pAll = -1
};
struct sUser {
	string Name;
	string Password;
	int Permissions;
	bool MarkForDelete = false;
};
enum class enMainMenue{ enShowClient = 1 , enAddClient , enDeleteClient , enUpdateClient ,enFindClient,enTransactions,enMangeUsers, enLogout};
enum enTransactions { enDeposit = 1, enWithdraw, enTotalBalances , enMainMenu };
void ShowMainMenue();
void ShowTransactionMenu();
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
	cout << "\nThe following are the client details:";
	cout << "\n|-----------------------------------------";
	cout << "\n|Account Number | " << Client.AccountNumber;
	cout << "\n|Pin Code       | " << Client.PinCode;
	cout << "\n|Name           | " << Client.Name;
	cout << "\n|Phone          | " << Client.PhoneNumber;
	cout << "\n|Account Balance| " << Client.Balance;
	cout << "\n|-----------------------------------------\n";


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
void PrintClientRecordForBalance(sClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber
	
		<< "| " << setw(35) << Client.Name
	
		<< "| " << setw(15) << fixed << setprecision(2) << Client.Balance
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
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
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

			SaveClientsDataToFile(vClients, ClientsFileName);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}

		// 👇 مهم جدًا
		return false;
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
bool FindClientAndPrintCard() {
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		return true;
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
	return false;
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients) {
	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y / n ? ";
		cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.Balance += Amount;
				SaveClientsDataToFile(vClients, ClientsFileName);
				cout << "\n\nDone Successfully. New balance is: "
					<< C.Balance;
				return true;
			}
		}
		return false;
	}
}
bool Deposit(string AccountNumber, vector<sClient>& vClients,double DepositAmount) {
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber) {
			C.Balance = C.Balance + DepositAmount;
			return true;
		}
	}
	return false;
}
double AccountTotalBalanceByAccountNumber(string AccountNumber, vector<sClient> vClients) {
	double TotalBalance = 0 ;
	for (sClient C : vClients) {
		if (AccountNumber == C.AccountNumber) {
			TotalBalance = C.Balance;
			return TotalBalance;
		}
	}
	return TotalBalance;
}
bool DepositByAccountNumber(string AccountNumber, vector<sClient> &vClients) {
	sClient Client;
	double DepositAmount;
	char Ans = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "\nPlease Enter Deposit amount : ";
		cin >> DepositAmount;
		cout << "\nAre you sure you want to perform this transaction? (y/n) ";
		cin >> Ans;

		if (Ans == 'y' || Ans == 'Y') {
			Deposit(AccountNumber, vClients, DepositAmount);
			
			SaveClientsDataToFile(vClients, ClientsFileName);
		    vClients = LoadClientsDataFromFile(ClientsFileName);
		    cout << "\nThe deposit process was successful.\n";
		    cout << "\nYour total account balance after deposit : " <<
			
			AccountTotalBalanceByAccountNumber(AccountNumber, vClients) << endl;

		}
		else {

			cout << "\nOperation cancelled.\n";
			return false;
			
		}
		
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}

	return true;

}
bool Withdraw(string AccountNumber, vector<sClient>& vClients, double WithdrawAmount)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			if (WithdrawAmount <= 0)
				return false;

			if (C.Balance < WithdrawAmount)
				return false;

			C.Balance = C.Balance - WithdrawAmount;
			/*Deposit(AccountNumber, vClients, -WithdrawAmount);*/
			return true;
		}
	}
	return false;
}
bool WithdrawByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
	sClient Client;
	double WithdrawAmount;
	double AccountBalance = AccountTotalBalanceByAccountNumber(AccountNumber, vClients);
	char Ans = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		bool ValidWithdraw;
		do
		{
			cout << "\nPlease Enter withdraw amount : ";

		   cin >> WithdrawAmount;

		   if (WithdrawAmount > Client.Balance) {
			   ValidWithdraw = false;
			   cout << "\nYou can withdraw up to : " << Client.Balance << endl;

		   }
		   else {
			   ValidWithdraw = true;
		   }


		} while (!ValidWithdraw);
		


		cout << "\nAre you sure you want to perform this transaction? (y/n) ";
		cin >> Ans;

		if (Ans == 'y' || Ans == 'Y') {

			Withdraw(AccountNumber, vClients, WithdrawAmount);
			SaveClientsDataToFile(vClients, ClientsFileName);
			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\nThe Withdraw process was successful.\n";
			cout << "\nYour total account balance after Withdraw : " << AccountTotalBalanceByAccountNumber(AccountNumber, vClients) << endl;

		}
		else {

			cout << "\nOperation cancelled.\n";
			return false;

		}

		return true;

	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}

	return true;
}
void PrintBalancesList(vector<sClient> vClients) {

	double TotalBalances = 0;
	
		cout << "\n\t\t\tBalances List (" << vClients.size() << ") Client(s)\n";

		cout << "----------------------------------------------------------------------------------------\n";

		cout << "| " << left << setw(15) << "Account Number"
		
			<< "| " << setw(35) << "Client Name"
		
			<< "| " << setw(15) << "Balance"
			<< "|\n";

		cout << "----------------------------------------------------------------------------------------\n";

		for (sClient Client : vClients)
		{
			PrintClientRecordForBalance(Client);
			TotalBalances += Client.Balance;
		}

		cout << "----------------------------------------------------------------------------------------\n";
		cout << "\t\t\t[Total Balances] = " << TotalBalances<<endl;
		cout << "----------------------------------------------------------------------------------------\n";

	
}
enMainMenue GetUserChoiceForMainMenu() {
	int Choice;
	do
	{
	cout << "Choose what do you want to do? [1 to 7]? ";
	cin >> Choice;

	} while (Choice < 1 || Choice > 7);

	return (enMainMenue)Choice;

}
enTransactions GetUserChoiceForTransactions() {

	int Choice;
	do
	{
		cout << "Choose what do you want to do? [1 to 4]? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 4);

	return (enTransactions)Choice;

}
// Extenission's :
string ConvertUserToString(sUser User, string Delmi = "#//#") {
	string s1;
	s1 = User.Name + Delmi + User.Password + Delmi + to_string(User.Permissions);
	return s1;
}
sUser ConvertStringToUser(string UserString, string Delmi = "#//#") {
	sUser User;
	vector <string> vString = SplitString(UserString, Delmi);
	
	User.Name = vString[0];
	User.Password = vString[1];
	User.Permissions = stoi(vString[2]);

	return User;
}

void ShowAllClientsScreen() {
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	PrintAllClientsData(vClients);
}
void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	string AccountNumber = ReadClientAccountNumber();

	DeleteClientByAccoutNumber(AccountNumber, vClients);
}
void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> vClients =
		LoadClientsDataFromFile(ClientsFileName);

	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowAddNewClientsScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddClientsToFile();
}
void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> vClients =
		LoadClientsDataFromFile(ClientsFileName);

	sClient Client;

	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}
void ShowDepositScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";
	string Account = ReadClientAccountNumber();
	vector<sClient> vClintes = LoadClientsDataFromFile(ClientsFileName);
	DepositByAccountNumber(Account, vClintes);
}
void ShowWithdrawScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";
	string Account = ReadClientAccountNumber();
	vector<sClient> vClintes = LoadClientsDataFromFile(ClientsFileName);
	WithdrawByAccountNumber(Account, vClintes);
}
void ShowPrintBalancesList() {
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	PrintBalancesList(vClients);
}
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
void GoBackToTransactions()
{
	cout << "\n\nPress any key to go back to Transactions...";
	system("pause>0");
	ShowTransactionMenu();
}
void PerformMenuOption( enMainMenue MainMenuChoice) {
	

	switch (MainMenuChoice)
	{
	case enMainMenue::enShowClient:
	{
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;
	}

	case enMainMenue::enAddClient:
	{
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;
	}

	case enMainMenue::enDeleteClient:
	{
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	}

	case enMainMenue::enUpdateClient:
	{
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	}

	case enMainMenue::enFindClient:
	{
		system("cls");
		ShowFindClientScreen();

		GoBackToMainMenue();
		break;
	}
	case enMainMenue::enTransactions:
	{
		system("cls");
		ShowTransactionMenu();

		break;

	}

	case enMainMenue::enLogout:
	{
		system("cls");
		ShowEndScreen();
		break;
	}
	}
		

	

};
void PerformTransactions(enTransactions Choice) {

	switch (Choice) {
	case  enTransactions::enDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToTransactions();
		break;

	}
	case enTransactions::enWithdraw:
	{
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactions();
		break;

	}
	case enTransactions::enTotalBalances :
	{
		system("cls");
		ShowPrintBalancesList();
		GoBackToTransactions();
		break;
	}
	case enTransactions::enMainMenu :
	{
		system("cls");
		ShowMainMenue();
		break;
	}
	default:
	{
		system("cls");
		GoBackToMainMenue();
		break;
	}

	}

}
void ShowTransactionMenu() {
	system("cls");

	cout << "====================================================\n";
	cout << "\t\tTransaction Menu Screen\n";
	cout << "====================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	
	cout << "====================================================\n";
	PerformTransactions(GetUserChoiceForTransactions());
}
void ShowMainMenue()
{
	system("cls");

	cout << "====================================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "====================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "====================================================\n";

	PerformMenuOption(GetUserChoiceForMainMenu());
}





int main()
{	
	//ShowMainMenue();

	sUser User;
	User.Name = "admin";
	User.Password = "1234";
	User.Permissions = -1;
	AddDataLineToFile(ConvertUserToString(User), UsersFileName);


		return 0;	
}

