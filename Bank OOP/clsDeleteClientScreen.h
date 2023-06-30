#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
#include <iomanip>
using namespace std;
class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client) {
        cout << "\nClient Card:";
        cout << "\n______________________";
        cout << "\nFirst Name     : " << Client.FirstName;
        cout << "\nLast Name      : " << Client.LastName;
        cout << "\nFull Name      : " << Client.FullName();
        cout << "\nEmail          : " << Client.Email;
        cout << "\nPhone          : " << Client.Phone;
        cout << "\nAccount Number : " << Client.AccountNumber();
        cout << "\nPassword       : " << Client.GetPinCode();
        cout << "\nBalance        : " << Client.AccountBalance;
        cout << "\n____________________\n";
    }
public:
    static void ShowDeleteClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
            return;
        }
        _DrawScreenHeader("\tDelete User Screen");
        string UserName = "";
        cout << "\nPlease enter clinet account number? ";
        UserName = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(UserName)) {
            cout << "\nAccount Number is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(UserName);
         _PrintClient(Client);
        cout << "\nAre you sure you want to delete this client y/n? ";
        char answer = 'n';
        cin >> answer;
        answer = tolower(answer);
        if (answer == 'y') {
            if (Client.Delete(UserName)) {
                cout << "\nAccount Deleted Successfully :-)\n";
                  _PrintClient(Client);
            }
            else {
                cout << "\nError client was not deleted\n";
            }
        }
    }
};

