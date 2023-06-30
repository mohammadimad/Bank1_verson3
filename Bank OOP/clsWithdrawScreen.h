#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsMainScreen.h";
using namespace std;

class clsWithdrawScreen : protected clsScreen
{
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
    static string _ReadAccountNumber() {
        string AccountNumber = "";
        cout << "\nPlease enter clinet account number? ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }
public:
    static void ShowWithdrawScreen() {
        _DrawScreenHeader("\tWithdraw Screen");
        string AccountNumber = "";
        AccountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        double Amount = 0;
        cout << "Please enter withdraw amount? ";
        Amount = clsInputValidate::ReadDoubleNumber();
        cout << "\nAre you sure you want to perform this transaction y/n? ";
        char answer = 'n';
        cin >> answer;
        answer = tolower(answer);
        if (answer == 'y') {
            if (Client.WithDraw(Amount)) {
                cout << "\nAmount Withdraw Successfully.\n";
                cout << "\nNew Balance is: " << Client.AccountBalance;
            }
            else {
                cout << "\nCannot Withdraw, Insuffecient Balance.\n";
                cout << "\nAmount to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client.AccountBalance;
            }
        }
        else
            cout << "\nOperation was cancelled\n";
    }
};

