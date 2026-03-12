#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"clsString.h"
using namespace std;
class clsCurrency
{
private :
	enum enMode { enEmpty = 0, enUpdate = 1 };
	enMode _mode;

		string _country;
		string _code;
		string _name;
		float _rate;

		static clsCurrency _convertLineToCurrencyObject(string line, string sepatator = "#//#")
		{
			vector<string> vData;
			vData = clsString::Split(line, sepatator);
			return clsCurrency(enMode::enUpdate, vData[0], vData[1], vData[2], stod(vData[3]));
		}

		static string _convertCurrencyObjectToLine(clsCurrency currency, string separator = "#//#")
		{
			string line = "";
			line += currency.getCountry() + separator;
			line += currency.getCode() + separator;
			line += currency.getName() + separator;
			line += to_string(currency.getRate());

			return line;
		}

		static vector<clsCurrency> _loadDataFromFile()
		{
			vector<clsCurrency> vCurrencies;
			fstream myFile;
			myFile.open("Currencies.txt", ios::in);
			if (myFile.is_open()) {
				string line;
				while (getline(myFile, line))
				{
					clsCurrency currency = _convertLineToCurrencyObject(line);
					vCurrencies.push_back(currency);
				}
				myFile.close();
				}
			return vCurrencies;
		}

		static clsCurrency _getEmptyCurrencyObject()
		{
			return clsCurrency(enMode::enEmpty, "", "", "", 0);
		}

		static void _saveDataToFile(vector<clsCurrency> vCurrencies)
		{
			fstream myFile;
			myFile.open("Currencies.txt", ios::out);
			if (myFile.is_open())
			{
				for (clsCurrency& c : vCurrencies)
				{
					string line = _convertCurrencyObjectToLine(c);
					myFile << line << endl;
				}
				myFile.close();
			}
		}

public:
	clsCurrency(enMode mode,string country, string code, string name,float rate)
	{
		_mode = mode;
		_country = country;
		_code = code;
		_name = name;
		_rate = rate;
}

	string getCountry()
	{
		return _country;
	}

	string getCode()
	{
		return _code;
	}

	string getName()
	{
		return _name;
	}

	void updateRate(float rate)
	{
		_rate = rate;
		update();
	}

	 float getRate()
	{
		return _rate;
	}

	 static clsCurrency findByCode(string countryCode)
	 {
		 countryCode = clsString::UpperAllString(countryCode);
		 fstream myFile;
		 myFile.open("Currencies.txt", ios::in);
		 if (myFile.is_open())
		 {
			 string line;
			 while (getline(myFile, line))
			 {
				 clsCurrency currency = _convertLineToCurrencyObject(line);
				 if (clsString::UpperAllString(currency.getCode()) == countryCode) {
					 myFile.close();
					 return currency;
				 }

			 }
			 myFile.close();
		 }
		 return _getEmptyCurrencyObject();
	 }

	 static clsCurrency findByCountry(string country)
	 {
		 country = clsString::UpperAllString(country);
		 fstream myFile;
		 myFile.open("Currencies.txt", ios::in);
		 if (myFile.is_open()) {
			 string line;
			 while (getline(myFile, line))
			 {
				 clsCurrency currency = _convertLineToCurrencyObject(line);
				 if (clsString::UpperAllString( currency.getCountry()) == country)
				 {
					 myFile.close();
					 return currency;
				 }
			 }
			 myFile.close();
		 }
		 return _getEmptyCurrencyObject();
	 }

	 bool isEmpty()
	 {
		 return (_mode == enMode::enEmpty);
	 }

	static  bool isCurrencyExist(string currencyCode)
	 {
		 clsCurrency currency = findByCode(currencyCode);
		 return(!currency.isEmpty());
	 }

	 static  vector< clsCurrency> getCurrenciesList()
	 {
		 return _loadDataFromFile();
	 }

	 void update()
	 {
		 vector<clsCurrency> vCurrencies = _loadDataFromFile();
		 for (clsCurrency& c : vCurrencies)
		 {
			 if (c.getCode() == getCode())
			 {
				 c = *this;
				 break;
			 }
		 }
		 _saveDataToFile(vCurrencies);
	 }

	  float convertToUSD( float amount)
	 {
		  return (float) (amount / getRate());
	 }

	  float convertToOtherCurrency(float amount, clsCurrency currency)
	  {
		 float amountInUSD = convertToUSD(amount);
		  if (currency.getCode() == "USD")
		  {
			  return amountInUSD;
		  }
		  return (float)amountInUSD *currency.getRate() ;
	  }
};

