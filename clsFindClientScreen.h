#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsClient.h"
#include"clsInputValidate.h"
class clsFindClientScreen : protected clsScreen
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

public :
	static void showFindClientScreen()
	{
		_DrawScreenHeader("Find Client Screen");

		if (!checkAccessRight(clsUser::enPermissions::enFindClient))
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

		if (!client.isEmpty())
		{
			cout << "\nClient found :-)\n";
		}
		else
		{
			cout << "\nClient was not found :-(\n";
		}
		_printClient(client);
	}
};

