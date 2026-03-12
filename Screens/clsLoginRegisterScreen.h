#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include"clsScreen.h"
class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void PrintLoginRegisterRecordLine(clsUser::loginRegister LoginRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.date;
        cout << "| " << setw(20) << left << LoginRegisterRecord.userName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.permissions;
    }

public:
    static void ShowLoginRegisterScreen()
    {

        vector <clsUser::loginRegister> vLoginRegisterRecord = clsUser::getLoginRegisterList();

        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);
        if (!checkAccessRight(clsUser::enPermissions::enLoginRegister))
        {
            return;
        }

        if (!checkAccessRight(clsUser::enPermissions::enListClients))
        {
            return;
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsUser::loginRegister &Record : vLoginRegisterRecord)
            {

                PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};

