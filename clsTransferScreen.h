#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsClient.h"
#include"clsInputValidate.h"
class clsTransferScreen : protected clsScreen
{
private:
	static void _printClient(clsClient client)
	{
		cout << "Client Card      " << endl;
		cout << "----------------------------------------" << endl;
		cout << "First Name     : " << client.getFirstName() << endl;
		cout << "Last Name      : " << client.getLastName() << endl;
		cout << "Balance        : " << client.getBalance() << endl;
		cout << "----------------------------------------" << endl;

	}

	static string  _readAccountNumber()
	{
		string accountNumber;
		accountNumber = clsInputValidate::ReadString();
		while (!clsClient::isClientExist(accountNumber))
		{
			cout << "\n Account number is not exist, choose another one: ";
			accountNumber = clsInputValidate::ReadString();
		}
		return accountNumber;
	}

	static float ReadAmount(clsClient SourceClient)
	{
		float Amount;

		cout << "\nEnter Transfer Amount? ";

		Amount = clsInputValidate::ReadFloatNumber();

		while (Amount > SourceClient.getBalance())
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}
	
public:
	static void showTransferScreen()
	{
		_DrawScreenHeader("Transfer Screen");
		cout << "\nPlease Enter Account Number To Transfer From: ";
		clsClient sourceClient = clsClient::find(_readAccountNumber());
		_printClient(sourceClient);
	
		cout << "\nPlease Enter Account Number To Transfer To: ";
		clsClient distinationClient = clsClient::find(_readAccountNumber());
		_printClient(distinationClient);


		float amount = ReadAmount(sourceClient);
			
		char answer = 'n';
		cout << "\nAre you sure you want do this operation? y/n? ";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			if (sourceClient.transfer(amount, distinationClient,currentUser.getUserName()))
				cout << "\nTransfer Done Successfully" << endl;
			else
				cout << "\nTransfer failed" << endl;
		}
		_printClient(sourceClient);
		_printClient(distinationClient);

		}
};

