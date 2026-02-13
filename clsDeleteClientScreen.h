#pragma once
#include<iostream>
#include"clsClient.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
class clsDeleteClientScreen: protected clsScreen
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

public:
static	void showDeleteClient() 
{
	_DrawScreenHeader("Delete Client Screen");

	if (!checkAccessRight(clsUser::enPermissions::enDeleteClient))
	{
		return;
	}
		string accountNumber = "";
		cout << "Please Enter Account Number: ";
		accountNumber = clsInputValidate::ReadString();

		while (!clsClient::isClientExist(accountNumber)) {
			cout << "Account number is not found , Choose another one: ";
			accountNumber = clsInputValidate::ReadString();
		}

		clsClient client = clsClient::find(accountNumber);
		clsDeleteClientScreen::_printClient(client);

		char answer = 'n';
		cout << "Are you sure you want delete this client y/n ? ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {

			if (client.Delete()) {
				cout << "Client deleted successfully :-)" << endl;
				clsDeleteClientScreen::_printClient(client);
			}

			else {
				cout << "Error client was not deleted" << endl;
			}

		}

	}

};

