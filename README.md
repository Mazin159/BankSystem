🏦 Bank Management System (C++ Console Application)
📌 Overview

This project is a simple Bank Management System built using C++ as a console application.
It allows users to manage bank clients and perform basic banking operations such as adding clients, updating their information, deleting accounts, and handling financial transactions.

The system uses file handling to store data persistently, making it practical and closer to real-world applications.

🚀 Features
👤 Client Management
Add new clients
View all clients
Update client information
Delete clients
Search for a client by account number
💰 Transactions
Deposit money
Withdraw money (with validation)
View total balances of all clients
📊 Data Handling
Persistent storage using text files
Load and save client data dynamically
🛠️ Technologies & Concepts Used
💻 Programming Language
C++
📚 Core Concepts Applied
Structs → to represent client data (sClient)
Enums → for menu navigation (enMainMenue, enTransactions)
Vectors → to store and manage clients dynamically
Functions → modular and reusable code
File Handling (fstream) → reading/writing data
String Manipulation → splitting and formatting records
Data Validation → ensuring correct user input
Pass by Reference → for performance and data modification
Separation of Concerns → dividing logic into clear functions
🧠 How It Works
Client data is stored in a file:
NewClients.txt
Each client is saved in this format:
AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
The program:
Loads data from file into a vector
Performs operations (add/update/delete)
Saves data back to the file
🖥️ System Screens
Main Menu
[1] Show Client List
[2] Add New Client
[3] Delete Client
[4] Update Client Info
[5] Find Client
[6] Transactions
[7] Exit
Transactions Menu
[1] Deposit
[2] Withdraw
[3] Total Balances
[4] Main Menu
⚙️ How to Run
Clone the repository:
git clone https://github.com/your-username/bank-system.git
Open the project using any C++ compiler (Visual Studio / CodeBlocks / etc.)
Run the program
📂 Project Structure
📁 Bank-System
 ┣ 📄 main.cpp
 ┣ 📄 NewClients.txt
 ┗ 📄 README.md
⚠️ Notes
The system runs in console mode only
Data is stored locally (no database used)
Account numbers must be unique
Withdrawals are validated against balance
