#pragma once
#include<iostream>
#include<iomanip>
#include"clsUtil.h"
#include"clsClient.h"
#include"clsScreen.h"
class clsTotalBalancesScreen : protected clsScreen
{
private:
static void _printClientRecordBalanceLine(clsClient Client)
	{

		cout << "| " << setw(15) << left << Client.getAccountNumber();
		cout << "| " << setw(40) << left << Client.getFullName();
		cout << "| " << setw(12) << left << Client.getBalance();

	}

public:
static void showTotalBalances() 
{
	_DrawScreenHeader("Total Balances");

	

		vector <clsClient> vClients = clsClient::getClientList();

		cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		double TotalBalances = clsClient::getTotalBalances();

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else

			for (clsClient Client : vClients)
			{
				_printClientRecordBalanceLine(Client);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
		cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";

	}
};

