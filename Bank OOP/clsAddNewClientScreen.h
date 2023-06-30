#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
#include <iomanip>
using namespace std;
class clsAddNewClientScreen: protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client) {
        cout << "\nEnter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();
        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();
        cout << "\nEnter Pin Code: ";
        Client.PinCode = clsInputValidate::ReadString();
        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }
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
    static void ShowAddNewClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
            return;
        }
        _DrawScreenHeader("\t Add New Client Screen");
        string AccountNumber = "";
        cout << "\nPlease enter clinet account number? ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount Number is already used,choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResults;
        SaveResults = NewClient.Save();
        switch (SaveResults) {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        case clsBankClient::enSaveResults::svFailAccpuntNumberExists:
            cout << "\nAccount Number is already used";
        }

    }
};

