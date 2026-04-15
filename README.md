🏦 Bank Management System
📌 Overview

A simple yet powerful Bank Management System built using C++.
This project simulates real-world banking operations including client management and financial transactions, with persistent data storage using file handling.

💡 Designed to demonstrate strong understanding of programming fundamentals and clean code structure.
This project is a simple Bank Management System built using C++ as a console application.
It allows users to manage bank clients and perform basic banking operations such as adding clients, updating their information, deleting accounts, and handling financial transactions.

.

🎯 Key Features

👤 Client Management

Add new clients with validation (unique account number)

View all clients in a formatted table

Update existing client details

Delete clients safely (with confirmation)


Search for clients بسهولة وسرعة

💰 Transactions System

Deposit money into accounts

Withdraw money with balance validation

Display total balances across all clients

🧠 Concepts & Skills Demonstrated

✅ Object-like design using struct

✅ Clean architecture using modular functions

✅ File handling (Read / Write / Update)

✅ Data parsing using custom delimiter #//#

✅ Input validation & user interaction

✅ Enum-based menu navigation

✅ Working with dynamic data using vector

✅ Pass by reference for performance optimization

⚙️ How It Works

Data is stored in:

NewClients.txt

Each record is formatted as:

AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance

Flow:

Load data from file → vector

Perform operations

Save updates back to file


🖥️ Screens Preview (Console)

🔹 Main Menu

[1] Show Client List

[2] Add New Client

[3] Delete Client

[4] Update Client Info

[5] Find Client

[6] Transactions

[7] Exit

🔹 Transactions Menu

[1] Deposit

[2] Withdraw

[3] Total Balances

[4] Main Menu

🚀 Getting Started

1️⃣ Clone the Repository
git clone https://github.com/your-username/bank-system.git

2️⃣ Run the Project

Open using Visual Studio / CodeBlocks / any C++ compiler

Compile & Run

📂 Project Structure

📁 Bank-System
 ┣ 📄 main.cpp

 ┣ 📄 NewClients.txt
 ┗ 📄 README.md

⚠️ Limitations

Console-based (no GUI)

No authentication system

Data stored in plain text (not encrypted)

🔮 Future Improvements

🔐 Add login system (Admin/User roles)

🔒 Encrypt sensitive data (Pin Code)

🗄️ Replace file system with database (SQL)

🖥️ Build GUI version

📜 Add transaction history






