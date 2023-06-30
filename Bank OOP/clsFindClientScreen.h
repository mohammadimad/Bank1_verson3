#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
#include <iomanip>
using namespace std;
class clsFindClientScreen : protected clsScreen
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

public :
    static void ShowFindClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {
            return;
        }
        _DrawScreenHeader("\tFind Client Screen");
        string AccountNumber = "";
        cout << "\nPlease enter clinet account number? ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount Number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        if (!Client.IsEmpty()) 
            cout << "\nClient Found : -)\n";

        else
            cout << "\nClient is not Found : -(\n";
        
        _PrintClient(Client);
    }
};

