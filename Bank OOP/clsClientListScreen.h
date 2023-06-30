#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
#include <iomanip>
using namespace std;

class clsClientListScreen: protected clsScreen
{
private:
    static void _PrintClientRecord(clsBankClient Client) {
        cout << setw(8) << left << ""  <<"| " << left << setw(15) << Client.AccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(25) << Client.Email;
        cout << "| " << left << setw(10) << Client.PinCode;
        cout << "| " << left << setw(12) << Client.AccountBalance;
    }
public :
  
    static void ShowClientsList() {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients)) {
            return;
        }
        vector <clsBankClient> vClients = clsBankClient::GetClientList();
        string Title = "\t   Clients List";
        string SubTitle = "\t  (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title,SubTitle);
        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vClients.size() == 0)
            cout << "\t\t\tNo Clinets Available In the Screen!";
        else
            for (clsBankClient Client : vClients) {
                _PrintClientRecord(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

