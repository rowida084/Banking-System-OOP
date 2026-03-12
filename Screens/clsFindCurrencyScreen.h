#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsCurrency.h"
#include"clsInputValidate.h"
class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.getCountry();
		cout << "\nCode       : " << Currency.getCode();
		cout << "\nName       : " << Currency.getName();
		cout << "\nRate(1$) = : " << Currency.getRate();

		cout << "\n_____________________________\n";

	}

	static void _showResult(clsCurrency currency)
	{
		if (!currency.isEmpty())
		{
			cout << "Currency Found :-)" << endl;
			_PrintCurrency(currency);
		}
		else
			cout << "Currency Not Found!" << endl;
	}


public:
	static void showFindCurrencyScreen()
	{
		_DrawScreenHeader("Find Currency Screen ");
		short answer = 1;
		cout << "\n Find By: [1] Code or [2] Country? ";
		cin >> answer;
		string find;
		clsCurrency currency = clsCurrency::findByCode(" ");
		if (answer == 1)
		{
			string currencyCode;
			cout << "\nPlease enter currencycode? ";
			currencyCode = clsInputValidate::ReadString();
			currency = clsCurrency::findByCode(currencyCode);
			_showResult(currency);
		}
		else if (answer == 2)
		{
			string country;
			cout << "\n Please enter country ?";
			country = clsInputValidate::ReadString();
			currency = clsCurrency::findByCountry(country);
			_showResult(currency);
		}

	}
};