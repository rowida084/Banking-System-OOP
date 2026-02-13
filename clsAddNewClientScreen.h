#pragma once
#include <iostream>
#include"clsUser.h"
#include"clsScreen.h"
#include"clsClient.h"
#include"clsInputValidate.h"
class clsAddNewClientScreen : protected clsScreen
{
private:
static	void _readClientInfo(clsClient& client) {

		cout << "Enter FirstName : ";
		client.setFirstName(clsInputValidate::ReadString());
		cout << "Enter LastName: ";
		client.setLastName(clsInputValidate::ReadString());
		cout << "Enter Email   : ";
		client.setEmail(clsInputValidate::ReadString());
		cout << "Enter Phone   : ";
		client.setPhone(clsInputValidate::ReadString());
		cout << "Enter PinCode : ";
		client.setPinCode(clsInputValidate::ReadString());
		cout << "Enter Balance : ";
		client.setBalance(clsInputValidate::ReadFloatNumber());
	}

static void _printClient (clsClient client) {

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
	static void showAddNewClient() {

		_DrawScreenHeader("Add New Client Screen ");

		if (!checkAccessRight(clsUser::enPermissions::enAddNewClient))
		{
			return;
		}

		cout << "\n Please Enter Account Number: ";
		string accountNumber = clsInputValidate::ReadString();

		while (clsClient::isClientExist(accountNumber)) {
			cout << "Acount Number is already used,choose another one: " << endl;
			accountNumber = clsInputValidate::ReadString();
		}

		clsClient newClient = clsClient::getAddNewClient(accountNumber);
		_readClientInfo(newClient);

		clsClient::enSaveResult saveResult;
		saveResult = newClient.save();

		switch (saveResult) {

		case clsClient::enSaveResult::svFaildEmptyObject: {
			cout << "\nError account was not save because it's empty." << endl;
			break;
		}
		case clsClient::enSaveResult::svSucceeded: {
			cout << "\nAccount Added successfuly:-)\n" << endl;
			_printClient(newClient);
			break;
		}

		case clsClient::enSaveResult::svFailesAcountNumberExist: {
			cout << "\nError account was not save because it's already used." << endl;
			break;
		}
		}

	}
};



