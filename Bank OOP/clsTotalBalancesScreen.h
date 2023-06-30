#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsMainScreen.h";
using namespace std;
class clsTotalBalancesScreen : protected clsScreen
{
private:
    static void PrintClientRecordBalanceLine(clsBankClient Client) {
        cout << setw(25) << left << "" << "| " << left << setw(15) << Client.AccountNumber();
        cout << "| " << left << setw(40) << Client.FullName();
        cout << "| " << left << setw(12) << Client.AccountBalance;
    }
public :
    static void ShowTotalBalances() {
        vector <clsBankClient> vClients = clsBankClient::GetClientList();
        double TotalBalance = clsBankClient::TotalBalance();
        string Title = "\tBalances List Screen";
        string SubTitle = "\t  (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vClients.size() == 0)
            cout << "\t\t\tNo Clinets Available In the Screen!";
        else
            for (clsBankClient Client : vClients) {
                PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;
        cout << setw(8) << left << "" << "\t\t\t\t\t\t\t    Total Balance = " << TotalBalance << endl;
        cout << setw(8) << left << "" << "\t\t\t\t\t    ( " << clsUtil::NumberToText(TotalBalance) << " )\n";
    }
};

