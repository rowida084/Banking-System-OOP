#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsDepositScreen.h"
#include"clsTransferScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTransferLogScreen.h"
#include"clsTotalBalancesScreen.h"

using namespace std;

class clsTransactionMenuScreen : protected clsScreen
{
private:
	enum enTransactionMenuOption
	{
		enDeposit = 1, enwithdraw = 2, enshowTotalBalance = 3, enTransfer=4,
		enShowTransferLog=5,enshowMainMenu = 6
	};

	static short _readTransactionMenuOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}

	static void _goBackTransactionScreen()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back the Transaction menu \n";
		system("pause>0");
		showTransactionmenuScreen();
	}

	static void _showDepositScreen()
	{
		clsDepositScreen::showDepositScreen();
	}

	static void _showWithdrawScreen()
	{
		clsWithdrawScreen::showEithdrawScreen();
	}

	static void _showTatalBalanceScreen()
	{
		clsTotalBalancesScreen::showTotalBalances();
	}

	static void _showTransferScreen()
	{
		clsTransferScreen::showTransferScreen();
	}

	static void _showTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _transactionMenuPerformance(enTransactionMenuOption transactionMenuOption)
	{
		switch (transactionMenuOption)
		{
		case enTransactionMenuOption::enDeposit:
		{
			system("cls");
			_showDepositScreen();
			_goBackTransactionScreen();
			break;
		}

		case enTransactionMenuOption::enwithdraw:
		{
			system("cls");
			_showWithdrawScreen();
			_goBackTransactionScreen();
			break;
		}

		case enTransactionMenuOption::enshowTotalBalance:
		{
			system("cls");
			_showTatalBalanceScreen();
			_goBackTransactionScreen();
			break;
		}

		case enTransactionMenuOption::enTransfer:
		{
			system("cls");
			_showTransferScreen();
			_goBackTransactionScreen();
			break;
		}

		case enTransactionMenuOption::enShowTransferLog:
		{
			system("cls");
			_showTransferLogScreen();
			_goBackTransactionScreen();
			break;
		}

		case enTransactionMenuOption::enshowMainMenu:
		{
		}
		}
	}


public:
	static void showTransactionmenuScreen() {
		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		if (!checkAccessRight(clsUser::enPermissions::enTransaction))
		{
			return;
		}

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu .\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_transactionMenuPerformance((enTransactionMenuOption)_readTransactionMenuOption());
	}

};

