#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsMainScreen.h"
#include"Global.h"
class clsLoginScreen : protected clsScreen
{
private :
	static bool _login()
	{
		bool loginFailed = false;
		string userName, password;
		 short loginFailedCount = 0;
		do
		{
			
			if (loginFailed) {
				loginFailedCount++;
				cout << "\nInvalid username/password\n\n";
				cout << "\nYou have " << (3 - loginFailedCount) << " trail(s) to login\n\n";
			}

			if (loginFailedCount == 3)
			{
				cout << "\nyour locked after 3 failed trails \n\n";
				return false;
			}
			cout << "\nEnter user name?";
				cin >> userName;
				cout << "Enter password?";
				cin >> password;

				currentUser = clsUser::find(userName, password);
				loginFailed = currentUser.isEmpty();
		} while (loginFailed);
		currentUser.registerLogin();
		clsMainScreen::showMainMenu();
		return true;
	}

public:
	static bool showLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\tLogin Screen");
	return 	_login();
	}

};

