#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsFindCurrencyScreen : protected clsScreen
{
private:
    static void _PrintCurrency(clsCurrency Currency) {
        cout << "\nCurrency Card:";
        cout << "\n______________________";
        cout << "\nCountry       : " << Currency.Countery();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$)      : " << Currency.Rate();
        cout << "\n____________________\n";
    }
    static short _ReadChoice()
    {
        cout <<  "Find By: [1] Code or [2] Country ? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 2, "Enter Number between 1 to 2? ");
        return Choice;
    }
    static void _ShowResults(clsCurrency Currency) {
        if (!Currency.IsEmpty())
            cout << "\nCurrency Found : -)\n";

        else
            cout << "\nCurrency is not Found : -(\n";

        _PrintCurrency(Currency);
    }
public:
    static void ShowFindCurrencyScreen() {
        _DrawScreenHeader("\tFind Currency Screen");
        int choise = _ReadChoice();
        
        
        if (choise == 1) {
            string CurrencyCode;
            cout << "\nPlease enter currencycode: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else {
            string Country;
            cout << "\nPlease enter country name: ";
            cin >> Country;
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
        }
        
    }
};

