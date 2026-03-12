#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsClient.h"
#include"clsInputValidate.h"
#include"clsFindUserScreen.h"
#include"clsListUsersScreen.h"
#include"clsAddNewUserScreen.h"
#include"clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
class clsManageUsersScreen : protected clsScreen
{
private :
	enum enManageUserOption
	{
		enListUsers = 1, enAddNewUser = 2, enDeleteUser = 3,
		enUpdateUser = 4, enFindUser = 5, enMainMenu = 6
	};

	static short _readManageUserOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short choose = clsInputValidate::ReadShortNumberBetween(1, 6);
		return choose;
	}

	static void _showListUsersScreen()
	{
		clsListUsersScreen::showUsersList();
	}

	static void _showAddNewUserScreen()
	{
		clsAddNewUserScreen::showAddNewUser();
	}

	static void _showDeleteUserScreen()
	{
		clsDeleteUserScreen::showDeleteUser();
	}

	static void _showUpdateUserScreen()
	{
		clsUpdateUserScreen::showUpdateUser();
	}

	static void _showFindUserScreen()
	{
		clsFindUserScreen::showFindUserScreen();
	}

	static void _gobackMainMenuScreen()
	{

	}

	static void _gobackManageUsersScreen()
	{
		cout << setw(37) << left << "" << "\n\tPress any to go back manage user menu..." << endl;
		system("pause>0");
		showManagerUserScreen();
	}

    static void _manageUserPerformance(enManageUserOption manageUserOption)
	{
		switch (manageUserOption)
		{
		case enManageUserOption::enListUsers:
		{
			system("cls");
			_showListUsersScreen();
			_gobackManageUsersScreen();
			break;
		}

		case enManageUserOption::enAddNewUser:
		{
			system("cls");
			_showAddNewUserScreen();
			_gobackManageUsersScreen();
			break;
		}

		case enManageUserOption::enDeleteUser:
		{
			system("cls");
			_showDeleteUserScreen();
			_gobackManageUsersScreen();
			break;
		}

		case enManageUserOption::enUpdateUser:
		{
			system("cls");
			_showUpdateUserScreen();
			_gobackManageUsersScreen();
			break;
		}

		case enManageUserOption::enFindUser:
		{
			system("cls");
			_showFindUserScreen();
			_gobackManageUsersScreen();
			break;
		}

		case enManageUserOption::enMainMenu:
		{

		}
		}
	}

public:
    static	void showManagerUserScreen()
	{
		system("cls");
	_DrawScreenHeader("\t Manage Users Screen");

	if (!checkAccessRight(clsUser::enPermissions::enManage))
	{
		return;
	}

	cout << setw(37) << left << "" << "===========================================\n";
	cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
	cout << setw(37) << left << "" << "===========================================\n";
	cout << setw(37) << left << "" << "\t[1] List Users.\n";
	cout << setw(37) << left << "" << "\t[2] Add New User.\n";
	cout << setw(37) << left << "" << "\t[3] Delete User.\n";
	cout << setw(37) << left << "" << "\t[4] Update User.\n";
	cout << setw(37) << left << "" << "\t[5] Find User.\n";
	cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
	cout << setw(37) << left << "" << "===========================================\n";

	_manageUserPerformance((enManageUserOption)_readManageUserOption());
	}
};

