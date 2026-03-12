#pragma once
#include<iostream>
#include"clsClient.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
{
private:
	static void _printClient(clsClient client) {

		cout << "Client Card      " << endl;
		cout << "----------------------------------------" << endl;
		cout << "First Name     : " << client.getFirstName() << endl;
		cout << "Last Name      : " << client.getLastName() << endl;
		cout << "Email          : " << client.getEmail() << endl;
		cout << "Phone          : " << client.getPhone() << endl;
		cout << "Account Number : " << client.getAccountNumber() << endl;
		cout << "Password       : " << client.getPinCode() << endl;
		cout << "Balance        : " << client.getBalance() << endl;
		cout << "----------------------------------------" << endl;

	}

	static string  _readAccountNumber() {
		string accountNumber = "";
		cout << "Please Enter AccountNumber? " << endl;
		cin >> accountNumber;
		return accountNumber;
	}

public:
	static void showEithdrawScreen()
	{
		_DrawScreenHeader("Withdraw Screen ");

		string accountNumber = _readAccountNumber();

		while (!clsClient::isClientExist(accountNumber)) {
			cout << "\n Client with account number[" << accountNumber << "]does not exist,Please enter another" << endl;
			accountNumber = _readAccountNumber();
		}

		clsClient client = clsClient::find(accountNumber);
		_printClient(client);

		double amount = 0;
		cout << "\nEnter withdraw amount?" << endl;
		amount = clsInputValidate::ReadDblNumber();

		while (client.getBalance() < amount)
		{
			cout << "\nCannot withdraw, insuffecient balance." << endl;
			cout << "\nAmount to withdraw is " << amount;
			cout << "\nYour balance is " << client.getBalance();
			cout << "\nEnter  another withdraw amount?" << endl;
			amount = clsInputValidate::ReadDblNumber();

		}

		cout << "\nAre you sure you want to perform this transaction y/n?" << endl;
		char answer = 'n';
		cin >> answer;

		if (answer == 'Y' || answer == 'y')
		{
			client.withdraw(amount);
			cout << "\nAmount withdrawed successfully." << endl;
			cout << "\nNew Balance is " << client.getBalance();
		}
		else
		{
			cout << "Operatio was cancelled." << endl;
		}
	}

};

