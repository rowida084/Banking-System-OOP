#pragma once
#include<iostream>
#include"clsUser.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
class clsDeleteUserScreen :protected clsScreen
{
private:
	static void _printUser(clsUser user) {

		cout << "Client Card      " << endl;
		cout << "----------------------------------------" << endl;
		cout << "First Name     : " << user.getFirstName() << endl;
		cout << "Last Name      : " << user.getLastName() << endl;
		cout << "Email          : " << user.getEmail() << endl;
		cout << "Phone          : " << user.getPhone() << endl;
		cout << "Account Number : " << user.getUserName() << endl;
		cout << "Password       : " << user.getPassword() << endl;
		cout << "Balance        : " << user.getPermissions() << endl;
		cout << "----------------------------------------" << endl;

	}

public:
	static	void showDeleteUser() {
		_DrawScreenHeader("Delete User Screen");
		string userName = "";
		cout << "Please Enter User Name: ";
		userName = clsInputValidate::ReadString();

		while (!clsUser::isUserExist(userName)) {
			cout << "User name is not found , Choose another one: ";
			userName = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::find(userName);
		clsDeleteUserScreen::_printUser(user);

		char answer = 'n';
		cout << "Are you sure you want delete this user y/n ? ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {

			if (user.Delete()) {
				cout << "user deleted successfully :-)" << endl;
				clsDeleteUserScreen::_printUser(user);
			}

			else {
				cout << "Error user was not deleted" << endl;
			}

		}

	}

};

