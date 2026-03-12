#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsClient.h"
class clsTransferLogScreen : protected clsScreen
    {

    private:

        static void PrintTransferLogRecordLine(clsClient::stTransferLog TransferLogRecord)
        {

            cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.date;
            cout << "| " << setw(8) << left << TransferLogRecord.sourceAccount;
            cout << "| " << setw(8) << left << TransferLogRecord.destinationAccount;
            cout << "| " << setw(8) << left << TransferLogRecord.amount;
            cout << "| " << setw(10) << left << TransferLogRecord.sourceBalance;
            cout << "| " << setw(10) << left << TransferLogRecord.destinationBalance;
            cout << "| " << setw(8) << left << TransferLogRecord.userName;


        }

    public:

        static void ShowTransferLogScreen()
        {
            vector <clsClient::stTransferLog> vTransferLogRecord = clsClient::getTransferLog();

            string Title = "\tTransfer Log List Screen";
            string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

            _DrawScreenHeader(Title, SubTitle);

            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
            cout << "| " << left << setw(8) << "s.Acct";
            cout << "| " << left << setw(8) << "d.Acct";
            cout << "| " << left << setw(8) << "Amount";
            cout << "| " << left << setw(10) << "s.Balance";
            cout << "| " << left << setw(10) << "d.Balance";
            cout << "| " << left << setw(8) << "User";

            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            if (vTransferLogRecord.size() == 0)
                cout << "\t\t\t\tNo Transfers Available In the System!";
            else

                for (clsClient::stTransferLog Record : vTransferLogRecord)
                {

                    PrintTransferLogRecordLine(Record);
                    cout << endl;
                }

            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

        }

    };