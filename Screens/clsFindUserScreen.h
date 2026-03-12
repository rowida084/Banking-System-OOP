#pragma once
#include<iostream>
#include"clsUser.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
class clsFindUserScreen : protected clsScreen
{
private:
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

public:
	static void showFindUserScreen() {
		_DrawScreenHeader("Find User Screen");
		string userName = "";
		cout << "Please Enter User Name : ";
		userName = clsInputValidate::ReadString();

		while (!clsUser::isUserExist(userName)) {
			cout << "User name is not found , Choose another one: ";
			userName = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::find(userName);

		if (!user.isEmpty())
		{
			cout << "\nUser found :-)\n";
		}
		else
		{
			cout << "\nUser was not found :-(\n";
		}
		_printUser(user);
	}
};

