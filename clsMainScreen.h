#pragma once
#include<iostream>
#include<iomanip>
#include"Global.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsListClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsManageUsersScreen.h"
#include"clsAddNewClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsLoginRegisterScreen.h"
#include "clsTransactionMenuScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private :
    enum enMainMenuOption {
        enListClient = 1, enAddNewClient = 2, enDeleteClient = 3, enUpdateClient = 4,
        enFindClient = 5, enShowTransactionMenu = 6, enManageUser = 7, enLoginReister = 8, enExist = 9
    };

    static short _readMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
        short choose = clsInputValidate::ReadShortNumberBetween(1, 9);
        return choose;

    }

	static  void _goBackMainMenu() 
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back the main menu \n";
		system("pause>0");
		showMainMenu(); 
	}

    static void _showListClientScreen() 
    {
        clsListClientScreen::ShowClientsList();
    }

    static void _showAddNewClientScreren()
    {
        clsAddNewClientScreen::showAddNewClient();
    }

    static void _showDeleteClientScreen() 
    {
        clsDeleteClientScreen::showDeleteClient();
    }

    static void _showUpdateClientScreen()
    {
        clsUpdateClientScreen::showUpdateClient();
    }

    static void _showFindClientScreen()
    {
        clsFindClientScreen::showFindClientScreen();
    }

    static void _showTransactionMenuScreen()
    {
       clsTransactionMenuScreen::showTransactionmenuScreen();
    }

    static void _showManageUserScreen()
    {
        clsManageUsersScreen::showManagerUserScreen();
    }

    static void _showLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _logout()
    {
        currentUser = clsUser::find("", "");
    }

    static void _mainMenuPerformance(enMainMenuOption mainMenuOption) 
    {
        switch (mainMenuOption)
        {

        case enMainMenuOption::enListClient: 
        {
            system("cls"); 
            _showListClientScreen();
           _goBackMainMenu();
           break;
        }

        case enMainMenuOption::enAddNewClient:
        {
            system("cls");
            _showAddNewClientScreren();
            _goBackMainMenu();
            break;
        }

        case enMainMenuOption::enDeleteClient: 
        {
            system("cls");
            _showDeleteClientScreen();
            _goBackMainMenu();
            break;
        }

        case enMainMenuOption::enUpdateClient:
        {
            system("cls");
            _showUpdateClientScreen();
            _goBackMainMenu();
            break;
        }

        case enMainMenuOption::enFindClient:
        {
            system("cls");
            _showFindClientScreen();
            _goBackMainMenu();
            break;
        }

        case enMainMenuOption::enShowTransactionMenu:
        {
            system("cls");
            _showTransactionMenuScreen();
            _goBackMainMenu();
            break;
        }

        case enMainMenuOption::enManageUser:
        {
            system("cls");
            _showManageUserScreen();
            _goBackMainMenu();
            break;
        }

        case enMainMenuOption::enLoginReister: {
            system("cls");
            _showLoginRegisterScreen();
            _goBackMainMenu();
            break;
        }

        case enMainMenuOption::enExist:
        {
            system("cls");
            _logout();
           
            break;
        }

        }

    }

public :
    static void showMainMenu()
    {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Logout .\n";

        cout << setw(37) << left << "" << "===========================================\n";

        _mainMenuPerformance((enMainMenuOption)_readMainMenuOption());

    }

};

