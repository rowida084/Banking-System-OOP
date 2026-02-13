#pragma once
#include<iostream>
#include<string>
#include "clsString.h"
#include "clsPerson.h"
#include"clsDate.h"
#include<vector>
#include<fstream>
using namespace std;

class clsClient : public clsPerson
{

private:

	enum enMode{emptyMode =0,updateMode=1,addNewMode=2};

	enMode _mode;
	string _accountNumber;
	string _pinCode;
	float _balance;
	bool _markedForDeleted = false;

	static clsClient _convertLineToObject(string line, string separatore = "#//#") {

		vector<string > vClientData;
		vClientData = clsString::Split(line, separatore);
		return clsClient(vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stod(vClientData[6]), enMode::updateMode);
	}

	static string _convertClientObjectToLine(clsClient client, string separator = "#//#") {

		string dataLine = "";
		dataLine += client.getFirstName() + separator;
		dataLine += client.getLastName() + separator;
		dataLine += client.getEmail() + separator;
		dataLine += client.getPhone() + separator;
		dataLine += client.getAccountNumber() + separator;
		dataLine += client.getPinCode() + separator;
		dataLine += to_string(client.getBalance()) + separator;
		return dataLine;
	}

	static clsClient _getEmptyClientObjet() {
		return clsClient("", "", "", "", "", "", 0, enMode::emptyMode);
	}

	static vector <clsClient> _loadClientsDataFromFile() {
		vector<clsClient> vClients;

		fstream myFile;
		myFile.open("Clients.txt", ios::in);//read mode
		if (myFile.is_open()) {
			string line;

			while (getline(myFile, line)) {
				clsClient client = _convertLineToObject(line);
				vClients.push_back(client);
			}
			myFile.close();
			}
		return vClients;
	}

	static void _saveClientDataToFile(vector<clsClient>vClients) {

		fstream myFile;
		myFile.open("Clients.txt", ios::out);//overwrite mood
		string dataLine;

		if (myFile.is_open()) {

			for (clsClient& c : vClients) {
				if (c.getMarkedForDeleted() == false) {
					dataLine = clsClient::_convertClientObjectToLine(c);
					myFile << dataLine << endl;
				}
			}

			myFile.close();
		}
	}

	void _addDataLineToFile(string dataLine) {

		fstream myFile;
		myFile.open("Clients.txt", ios::out | ios::app);

		if (myFile.is_open()) {
			myFile << dataLine << endl;
		}

		myFile.close();
	}

	void _update() {

		vector<clsClient>vClients = _loadClientsDataFromFile();

		for (clsClient& c : vClients) {

			if (c.getAccountNumber() == getAccountNumber()) {
				c = *this ;
				break;
			}
		}
		_saveClientDataToFile(vClients);
	}

	void _addNew() {
		_addDataLineToFile(_convertClientObjectToLine(*this));
	}

	 string _prepareTranserLogRecord(string userName, clsClient destinationClient, double amount,string separator = "#//#")
	{
		string record = "";
		record += clsDate::getSystemDateString() + separator;
		record += getAccountNumber() + separator;
		record += destinationClient.getAccountNumber() + separator;
		record += to_string(amount) + separator;
		record += to_string(getBalance()) + separator;
		record += to_string(destinationClient.getBalance()) + separator;
		record += userName;
		return record;
	}

	 public:
		 struct stTransferLog 
		 {
			 string date;
			 string userName;
			 double amount = 0;
			 string sourceAccount;
			 string destinationAccount;
			 double sourceBalance;
			 double destinationBalance;
		 };

	 private:
		static stTransferLog _convertTransferLineToRecord(string dataLine)
	 {
			 stTransferLog transferLog;
		 vector<string> vData = clsString::Split(dataLine, "#//#");
		 transferLog.date = vData[0];
		 transferLog.sourceAccount = vData[1];
		 transferLog.destinationAccount = vData[2];
		 transferLog.amount = stod(vData[3]);
		 transferLog.sourceBalance = stod(vData[4]);
		 transferLog.destinationBalance = stod(vData[5]);
		 transferLog.userName = vData[6];

		 return transferLog; 
	 }

public:

	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFailesAcountNumberExist = 2 };

	enSaveResult save() {
		switch (_mode) {
		case enMode::emptyMode: {

			return enSaveResult::svFaildEmptyObject;

		}

		case enMode::updateMode: {

			_update();
			return enSaveResult::svSucceeded;
			break;
		}
		case enMode::addNewMode: {

			if (clsClient::isClientExist(_accountNumber)) {
				return enSaveResult::svFailesAcountNumberExist;
			}

			else {
				_addNew();
				_mode = enMode::addNewMode;
				return enSaveResult::svSucceeded;
				break;
			}
		}
		}
	}

	clsClient(string firstName, string lastName, string email, string phone,
		string accountNumber, string pinCode, float balance,enMode mode) :
		clsPerson(firstName, lastName, email, phone) {

		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_balance = balance;
		_mode = mode;
	}

	bool isEmpty() {
		return (_mode == enMode::emptyMode);
}

	void setaccountNumber(string accountNumber) {
		_accountNumber = accountNumber;
	}

	string getAccountNumber() {
		return _accountNumber;
	}

	void setPinCode(string pinCode) {
		_pinCode = pinCode;
	}

	string getPinCode() {
		return _pinCode;
	}

	void setBalance(float balance) {
		_balance = balance;
	}

	float getBalance() {
		return _balance;
	}

	bool getMarkedForDeleted() {
		return _markedForDeleted;
	}


	static clsClient find(string accountNumber) {

		fstream myFile;
		myFile.open("Clients.txt", ios::in);
		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				clsClient client = _convertLineToObject(line);

				if (client.getAccountNumber() == accountNumber) {
					myFile.close();
					return client;
				}
				
			}
			myFile.close();
			}
		return _getEmptyClientObjet();
	}

	static clsClient find(string accountNum, string PinCode) {
		
		fstream myFile;
		myFile.open("Clients.txt", ios::in);
		string line;
		if (myFile.is_open()) {
			while (getline(myFile, line)) {
				clsClient client = _convertLineToObject(line);

				if (client.getAccountNumber() == accountNum && client.getPinCode() == PinCode) {
					myFile.close();
					return client;
				}
			}
			myFile.close();
		}
		return _getEmptyClientObjet();
	}

	static bool isClientExist(string accountNumber) {

		clsClient client = clsClient:: find(accountNumber);
		return (!client.isEmpty());
	}

	static clsClient getAddNewClient(string accountNumber) {

		return clsClient("", "", "", "", accountNumber, "", '0.0f', enMode::addNewMode);

	}

	bool  Delete() 
	{
		vector<clsClient>_vClients = clsClient::_loadClientsDataFromFile();

		for (clsClient& c : _vClients)
		{
			if (c.getAccountNumber() == _accountNumber) 
			{
				c._markedForDeleted = true;
				break;
			}
		}

		clsClient::_saveClientDataToFile(_vClients);

		*this = _getEmptyClientObjet();

		return true;
	}

	static  vector<clsClient> getClientList() {
		return _loadClientsDataFromFile();
	}

	static double getTotalBalances()
	{
		vector<clsClient>_vClients = getClientList();

		double totalBalances = 0;
		for (clsClient& c : _vClients)
		{
			totalBalances += c.getBalance();
		}

		return totalBalances;
	}

	 void deposit(double amount) {
		_balance += amount;
		save();
	}

	 bool withdraw(double amount) {
		 if (amount > _balance) {
			 return false;
		 }
		 else
		 {
			 _balance -= amount;
			 save();
		 }
	 }

	 void registerTransferLog(string userName, clsClient destinationClient, double amount)
	 {
		 string dataLine = _prepareTranserLogRecord(userName, destinationClient, amount);
		 fstream myFile;
		 myFile.open("TransferLog.txt", ios::out | ios::app);
		 if (myFile.is_open()) 
		 {
			 myFile << dataLine << endl;
			 myFile.close();
		 }
	 }

	 bool transfer(double amount, clsClient& destinationClient,string userName)
	 {
		 if (amount > getBalance()) {
			 return false;
		 }
		 withdraw(amount);
		 destinationClient.deposit(amount);
		 registerTransferLog(userName, destinationClient, amount);
			 return true;
	 }

	static  vector<stTransferLog> getTransferLog()
	 {
		 vector<stTransferLog> vTranferLogData;
		 fstream myFile;
		 myFile.open("TransferLog.txt", ios::in);
		 if (myFile.is_open())
		 {
			 string line;
			 stTransferLog transferLog;
			 while (getline(myFile, line))
			 {
				 transferLog = _convertTransferLineToRecord(line);
				 vTranferLogData.push_back(transferLog);
			 }
			 myFile.close();
		 }
		 return vTranferLogData;
	 }

};

