#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsCurrency.h"
#include"clsInputValidate.h"
class clsUpdateCurrencyScreen : protected clsScreen
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

	static float _readCurrencyRate()
	{
		float rate = 0;
		cout << "\nEnter New Rate? ";
		 rate = clsInputValidate::ReadFloatNumber();
		return rate;
	}

public :
static	void showUpdateCurrencyScreen()
	{
		_DrawScreenHeader("Update Currency Screen ");
		cout << "Please Enter Currency Code? " << endl;
		string currencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::isCurrencyExist(currencyCode)) {
			cout << "\n Currency is not found ,Choose another one: ";
			currencyCode = clsInputValidate::ReadString();
		}

		clsCurrency currency = clsCurrency::findByCode(currencyCode);
		_PrintCurrency(currency);

		char answer = 'n';
		cout << "\n Are you sure you want to update the rate of this currency? y/n? ";
		cin >> answer;

		if (answer == 'Y' || answer == 'y') {

			cout << "\n\n Update Currency Rate: ";
			cout << "\n-----------------------\n";
			
			currency.updateRate(_readCurrencyRate());
			cout << "\n Currency Rate Updated Successfully :-)" << endl;
			_PrintCurrency(currency);
		}
	}
};

