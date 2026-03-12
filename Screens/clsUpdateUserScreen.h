#pragma once
#include<iostream>
#include"clsUser.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
class clsUpdateUserScreen : protected clsScreen
{
private:
	static void _readUserInfo(clsUser& user)
	{
		cout << "Enter FirstName : ";
		user.setFirstName(clsInputValidate::ReadString());
		cout << "Enter LastName: ";
		user.setLastName(clsInputValidate::ReadString());
		cout << "Enter Email   : ";
		user.setEmail(clsInputValidate::ReadString());
		cout << "Enter Phone   : ";
		user.setPhone(clsInputValidate::ReadString());
		cout << "Enter Password : ";
		user.setPassword(clsInputValidate::ReadString());
		cout << "Enter permissions : ";
		user.setPermissions(_readPermissionsToSet());
	}

	static void _printUser(clsUser user) {

		cout << "User Card      " << endl;
		cout << "----------------------------------------" << endl;
		cout << "First Name     : " << user.getFirstName() << endl;
		cout << "Last Name      : " << user.getLastName() << endl;
		cout << "Email          : " << user.getEmail() << endl;
		cout << "Phone          : " << user.getPhone() << endl;
		cout << "User Name      : " << user.getUserName() << endl;
		cout << "Password       : " << user.getPassword() << endl;
		cout << "Permissions    : " << user.getPermissions() << endl;
		cout << "----------------------------------------" << endl;

	}

	static int _readPermissionsToSet()
	{
		int permissions = 0;
		char answer = 'n';

		cout << "\nDo you want to give full access? y/n?";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to :\n";
		cout << "\nShow client list? y/n?";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::enListClients;
		}

		cout << "\nAdd new client? y/n?";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::enAddNewClient;
		}

		cout << "\nDelete client? y/n?";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::enDeleteClient;
		}

		cout << "\nUpdate client? y/n?";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::enUpdateClient;
		}

		cout << "\nFind client? y/n?";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::enFindClient;
		}

		cout << "\nTransactions? y/n?";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::enTransaction;
		}

		cout << "\nManage Users? y/n?";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			permissions += clsUser::enPermissions::enManage;
		}

		return permissions;
	}

public:
	static	void showUpdateUser() {

		_DrawScreenHeader("Update User Screen");
		string userName = "";
		cout << "\nPlease Enter UserName?" << endl;
		userName = clsInputValidate::ReadString();

		while (!clsUser::isUserExist(userName)) {
			cout << "\n username is not exist,choose another one ?" << endl;
			userName = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::find(userName);
		clsUpdateUserScreen::_printUser(user);

		cout << "\nUpdate User info :" << endl;
		cout << "----------------------" << endl;
		_readUserInfo(user);

		clsUser::enSaveResult saveResult;
		saveResult = user.save();
		switch (saveResult) {

		case clsUser::enSaveResult::svFaildEmptyObject: {
			cout << "\nError account was not saved becouse it's empty" << endl;
			break;
		}

		case clsUser::enSaveResult::svSucceeded: {
			cout << "\nAccount apdated successfuly :-)" << endl;
			clsUpdateUserScreen::_printUser(user);
			break;
		}

		}

	}
};

