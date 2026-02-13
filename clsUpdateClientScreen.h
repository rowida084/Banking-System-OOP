#pragma once
#include<iostream>
#include"clsClient.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
class clsUpdateClientScreen: protected clsScreen
{
private:
static	void _readClientInfo(clsClient& client) 
	{
		cout << "Enter FirstName : ";
		client.setFirstName(clsInputValidate::ReadString());
		cout << "Enter LastName: ";
		client.setLastName(clsInputValidate::ReadString());
		cout << "Enter Email   : ";
		client.setEmail(clsInputValidate::ReadString());
		cout << "Enter Phone   : ";
		client.setPhone(clsInputValidate::ReadString());
		cout << "Enter Balance : ";
		client.setBalance(clsInputValidate::ReadFloatNumber());
	}

static void _printClient(clsClient client) 
{
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
static	void showUpdateClient() 
{

	_DrawScreenHeader("Update Client Screen");

	if (!checkAccessRight(clsUser::enPermissions::enUpdateClient))
	{
		return;
	}

		string accountNumber = "";
		cout << "\nPlease Enter AccountNumber?" << endl;
		accountNumber = clsInputValidate::ReadString();

		while (!clsClient::isClientExist(accountNumber)) {
			cout << "\n accountNumber is not exist,choose another one ?" << endl;
			accountNumber = clsInputValidate::ReadString();
		}

		clsClient client = clsClient::find(accountNumber);
		clsUpdateClientScreen::_printClient(client);

		cout << "\nUpdate Client info :" << endl;
		cout << "----------------------" << endl;
		_readClientInfo(client);

		clsClient::enSaveResult saveResult;
		saveResult = client.save();
		switch (saveResult) {

		case clsClient::enSaveResult::svFaildEmptyObject: {
			cout << "\nError account was not saved becouse it's empty" << endl;
			break;
		}

		case clsClient::enSaveResult::svSucceeded: {
			cout << "\nAccount apdated successfuly :-)" << endl;
			clsUpdateClientScreen::_printClient(client);
			break;
		}

		}

	}

};

