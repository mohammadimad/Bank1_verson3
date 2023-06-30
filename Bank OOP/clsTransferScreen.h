#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h";
class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client) {
        cout << "\nClient Card:";
        cout << "\n______________________";
        cout << "\nFull Name      : " << Client.FullName();
        cout << "\nAccount Number : " << Client.AccountNumber();
        cout << "\nBalance        : " << Client.AccountBalance;
        cout << "\n____________________\n";
    }
    static float _ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadFloatNumber();

        while (Amount > SourceClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDoubleNumber();
        }
        return Amount;
    }
    static string _ReadAccountNumber()
    {
        string AccountNumber;
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }
public:
    static void ShowTransferScreen() {
        _DrawScreenHeader("\tTransfer Screen");
        cout << "\nPlease enter account number to transfer from: ";
        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
        _PrintClient(SourceClient);
        cout << "\nPlease enter account number to transfer to: ";
        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
        _PrintClient(DestinationClient);
        float Amount = _ReadAmount(SourceClient);
        cout << "\nAre you sure you want to perform this transaction y/n? ";
        char answer = 'n';
        cin >> answer;
        answer = tolower(answer);
        if (answer == 'y') {
            if(SourceClient.Transfer(Amount, DestinationClient))   
                cout << "\nTransfer done seccessfully\n";
            else
                cout << "\nTransfer Faild \n";
        }
        else
            cout << "\nOperation was cancelled\n";
        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
    }
};

