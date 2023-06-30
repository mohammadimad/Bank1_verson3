#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsUpdateCurrencyScreen : public clsScreen
{
private:
    static float _ReadRate() {
        
        cout << "\nEnter New Rate: ";
        float NewRate = 0;
        NewRate = clsInputValidate::ReadFloatNumber();
        return NewRate;
    }
    static void _PrintCurrency(clsCurrency Currency) {
        cout << "\nCurrency Card:";
        cout << "\n______________________";
        cout << "\nCountry       : " << Currency.Countery();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$)      : " << Currency.Rate();
        cout << "\n____________________\n";
    }
    static clsCurrency _ReadCurrencyInfo(clsCurrency& Currency) {
        float NewRate = 1;
        cout << "\nEnter New Rate: ";
        cin >> NewRate;
        Currency.UpdateRate(NewRate);
        //Currency.UpdateRare() = clsInputValidate::ReadString();
       
    }
public :
    static void ShowUpdateCurrencyRateScreen() {
        _DrawScreenHeader("\tUpdate Currency Screen");
        string CurrencyCode = "";
        cout << "\nPlease enter Currency code? ";
        CurrencyCode = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrency(Currency);
        cout << "\nAre you sure you want to update this user y/n? ";
        char Answer = 'n';
        cin >> Answer;
        Answer = tolower(Answer);
        if (Answer == 'y') {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";
            Currency.UpdateRate(_ReadRate());
            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(Currency);
        }
    }
};

