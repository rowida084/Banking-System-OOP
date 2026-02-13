#pragma once
#include <iostream>
#include"clsDate.h"
#include"Global.h"

using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\n\t\t\t\t\tUser: " << currentUser.getUserName() << endl;
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate());
        cout << "\n\n";
    }

    static bool checkAccessRight(clsUser::enPermissions permission)
    {
        if (!currentUser.accessPermission(permission)) {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }

    }
    

};

