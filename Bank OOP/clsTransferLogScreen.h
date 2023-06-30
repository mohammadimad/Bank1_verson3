#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h";
class clsTransferLogScreen : protected clsScreen
{
private:
    static void PrintTransferRegisterRecordLine(clsBankClient::stTransferRegisterRecord TransferRegisterRecord)
    {
        cout << setw(6) << left << "" << "| " << setw(25) << left << TransferRegisterRecord.DateTime;
        cout << "| " << setw(6) << left << TransferRegisterRecord.AccountNumber;
        cout << "| " << setw(6) << left << TransferRegisterRecord.AccountNumber2;
        cout << "| " << setw(10) << left << TransferRegisterRecord.Amount;
        cout << "| " << setw(10) << left << TransferRegisterRecord.Number1;
        cout << "| " << setw(10) << left << TransferRegisterRecord.Number2;
        cout << "| " << setw(10) << left << TransferRegisterRecord.User;
    }
public:
    static void ShowTranferRegisterScreen() {
        vector <clsBankClient::stTransferRegisterRecord> vTransferRegisterRecord = clsBankClient::GetTransferRegisterList();
        _DrawScreenHeader("\tTransfer Log");
        cout << setw(6) << left << "" << "\n\t_______________________________________________________";
        cout << "___________________________________________________\n" << endl;

        cout << setw(6) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(6) << "s.Acct";
        cout << "| " << left << setw(6) << "d.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(10) << "d.User";
        cout << setw(6) << left << "" << "\n\t_______________________________________________________";
        cout << "___________________________________________________\n" << endl;

        if (vTransferRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Transfer Available In the System!";
        else

            for (clsBankClient::stTransferRegisterRecord Record : vTransferRegisterRecord)
            {

                PrintTransferRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(6) << left << "" << "\n\t_______________________________________________________";
        cout << "___________________________________________________\n" << endl;
    }
};

