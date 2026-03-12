#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"clsDate.h"
#include"clsUtil.h"
#include"clsString.h"
#include"clsPerson.h"

using namespace std;
class clsUser : public  clsPerson
{
private :

	enum enMode { enEmptyMode = 1, enUpdateMode = 2, enAddNewMode = 3 };

	string _userName;
	string _password;
	int _permissions;
	enMode _mode;
	bool _markedForDeleted = false;

	struct loginRegister;
	static clsUser _convertLineToObject(string line, string separatore = "#//#") {

		vector<string > vUsers;
		vUsers = clsString::Split(line, separatore);
		return clsUser(enMode::enUpdateMode,vUsers[0], vUsers[1], vUsers[2], vUsers[3],
			vUsers[4], clsUtil::decryptText( vUsers[5]), stoi(vUsers[6]));
	}

	 string _prepareLoginRecord(string separator="#//#")
	{
		string dataRecord = "";
		dataRecord += clsDate::getSystemDateString()+separator;
		dataRecord += getUserName() +separator;
		dataRecord += clsUtil::encryptText(getPassword())+separator;
		dataRecord += to_string(getPermissions());
		return dataRecord;
	}

	static string _convertClientObjectToLine(clsUser user, string separator = "#//#") {

		string dataLine = "";
		dataLine += user.getFirstName() + separator;
		dataLine += user.getLastName() + separator;
		dataLine += user.getEmail() + separator;
		dataLine += user.getPhone() + separator;
		dataLine += user.getUserName() + separator;
		dataLine +=clsUtil::encryptText( user.getPassword()) + separator;
		dataLine += to_string(user.getPermissions()) + separator;
		return dataLine;
	}

	static clsUser _getEmptyUserObjet() {
		return clsUser(enMode::enEmptyMode,"", "", "", "", "", "", 0);
	}

	static vector <clsUser> _loadClientsDataFromFile() {
		vector<clsUser> vUsers;

		fstream myFile;
		myFile.open("Users.txt", ios::in);//read mode
		if (myFile.is_open()) {
			string line;

			while (getline(myFile, line)) {
				clsUser user = _convertLineToObject(line);
				vUsers.push_back(user);
			}
			myFile.close();
		}
		return vUsers;
	}

	static void _saveClientDataToFile(vector<clsUser>vUsers) {

		fstream myFile;
		myFile.open("Users.txt", ios::out);//overwrite mood
		string dataLine;

		if (myFile.is_open()) {

			for (clsUser& u : vUsers) {
				if (u.getMarkedForDeleted() == false) {
					dataLine = clsUser::_convertClientObjectToLine(u);
					myFile << dataLine << endl;
				}
			}

			myFile.close();
		}
	}

	void _addDataLineToFile(string dataLine) {

		fstream myFile;
		myFile.open("Users.txt", ios::out | ios::app);

		if (myFile.is_open()) {
			myFile << dataLine << endl;
		}

		myFile.close();
	}

	void _update() {

		vector<clsUser>vUsers = _loadClientsDataFromFile();

		for (clsUser& u : vUsers) {

			if (u.getUserName() == getUserName()) {
				u = *this;
				break;
			}
		}
		_saveClientDataToFile(vUsers);
	}

	void _addNew() {
		_addDataLineToFile(_convertClientObjectToLine(*this));
	}

	public:
		struct loginRegister
		{
			string date;
			string userName;
			string password;
			int permissions = 0;
		};

		private:
	static loginRegister _convertLoginRegisterLineToRecord(string line)
	{
		loginRegister loginRegisterLine;
		vector<string > vLoginRegister = clsString::Split(line,"#//#");

		loginRegisterLine.date = vLoginRegister[0];
		loginRegisterLine.userName = vLoginRegister[1];
		loginRegisterLine.password = clsUtil::decryptText(vLoginRegister[2]);
		loginRegisterLine.permissions = stoi(vLoginRegister[3]);

		return loginRegisterLine;
	}

public :

	enum enPermissions
	{
		enAll=-1,enListClients = 1, enAddNewClient = 2, enDeleteClient = 4, enUpdateClient = 8,
		enFindClient = 16, enTransaction = 32, enManage = 64, enLoginRegister = 128
	};

	

	clsUser(enMode mode, string firstName, string lastName,
	string email, string phone, string userName, string password,int permissions ):
		clsPerson ( firstName,  lastName,  phone,  email)
	{
		_mode = mode;
		_userName = userName;
		_password = password;
		_permissions = permissions;
	}



	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFailesUserNameExist = 2 };

	enSaveResult save() {
		switch (_mode) {
		case enMode::enEmptyMode: {

			return enSaveResult::svFaildEmptyObject;

		}

		case enMode::enUpdateMode: {

			_update();
			return enSaveResult::svSucceeded;
			break;
		}
		case enMode::enAddNewMode: {

			if (clsUser::isUserExist(_userName)) {
				return enSaveResult::svFailesUserNameExist;
			}

			else {
				_addNew();
				_mode = enMode::enAddNewMode;
				return enSaveResult::svSucceeded;
				break;
			}
		}
		}
	}

	string getUserName()
	{
	return _userName;
    }

	void setUserName(string userName)
	{
		_userName = userName;
	}

	string getPassword()
	{
		return _password;
	}

	void setPassword(string password)
	{
		_password = password;
	}

	int getPermissions()
	{
		return _permissions;
	}

	void setPermissions(int permissions)
	{
		_permissions = permissions;
	}

	bool getMarkedForDeleted()
	{
		return _markedForDeleted;
	}

	string getFullName() {
		return getFirstName() +" "+ getLastName();
	}

	bool isEmpty() {
		return (_mode == enMode::enEmptyMode);
	}

	static clsUser find(string userName) {

		fstream myFile;
		myFile.open("Users.txt", ios::in);
		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				clsUser user = _convertLineToObject(line);

				if (user.getUserName() == userName) {
					myFile.close();
					return user;
				}

			}
			myFile.close();
		}
		return _getEmptyUserObjet();
	}

	static clsUser find(string userName, string password) {

		fstream myFile;
		myFile.open("Users.txt", ios::in);
		string line;
		if (myFile.is_open()) {
			while (getline(myFile, line)) {
				clsUser user = _convertLineToObject(line);

				if (user.getUserName() == userName && user.getPassword() == password) {
					myFile.close();
					return user;
				}
			}
			myFile.close();
		}
		return _getEmptyUserObjet();
	}

	static bool isUserExist(string userName) 
	{
		clsUser user = clsUser::find(userName);
		return (!user.isEmpty());
	}

	static clsUser getAddNewUser(string userName) {

		return clsUser(enMode::enAddNewMode,"", "", "", "", userName, "", 0 );

	}

	bool  Delete()
	{
		vector<clsUser>_vUsers = clsUser::_loadClientsDataFromFile();

		for (clsUser& u : _vUsers)
		{
			if (u.getUserName() == _userName)
			{
				u._markedForDeleted = true;
				break;
			}
		}

		clsUser::_saveClientDataToFile(_vUsers);

		*this = _getEmptyUserObjet();

		return true;
	}

	static  vector<clsUser> getUsersList() {
		return _loadClientsDataFromFile();
	}

	void registerLogin()
	{
		string dataRecord = _prepareLoginRecord();
		fstream myFile;
		myFile.open("LoginRegister.txt", ios::out | ios::app);
		if (myFile.is_open())
		{
			myFile << dataRecord << endl;
			myFile.close();
			}
	 }

	static vector<loginRegister> getLoginRegisterList()
	{
		vector<loginRegister>vLoginRegisterData;

		fstream myFile;
		myFile.open("LoginRegister.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			loginRegister loginRegisterLine;
			while (getline(myFile, line)) 
			{
				loginRegisterLine = _convertLoginRegisterLineToRecord(line);
				vLoginRegisterData.push_back(loginRegisterLine);
			}
			myFile.close();
		}
		return vLoginRegisterData;
	}
	
	bool accessPermission(enPermissions permission)
	{
		if (permission == enPermissions::enAll)
		{
			return true;
		}
		if ((permission & this->_permissions) == permission) {
			return true;
		}
		return  false;
	}
};

