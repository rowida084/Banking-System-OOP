#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsClient.h"
#include <iomanip>

class clsListClientScreen :protected clsScreen
{

private:
    static void _PrintUserRecordLine(clsClient client)
    {

        cout << setw(8) << left << "" << "| " << setw(12) << left << client.getAccountNumber();
        cout << "| " << setw(25) << left << client.getFullName();
        cout << "| " << setw(12) << left << client.getPhone();
        cout << "| " << setw(20) << left << client.getEmail();
        cout << "| " << setw(10) << left << client.getPinCode();
        cout << "| " << setw(12) << left << client.getBalance();

    }

public:

    static void ShowClientsList()
    {
        vector <clsClient> vClients = clsClient::getClientList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        if (!checkAccessRight(clsUser::enPermissions::enListClients))
        {
            return;
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "Acount Number";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pincode";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsClient client : vClients)
            {

                _PrintUserRecordLine(client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

