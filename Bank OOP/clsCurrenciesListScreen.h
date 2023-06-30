#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include <iomanip>

using namespace std;
class clsCurrenciesListScreen : protected clsScreen
{
private:
    static void _PrintCurrencyRecord(clsCurrency Currency) {
        cout << setw(8) << left << "" << "| " << left << setw(30) << Currency.Countery();
        cout << "| " << left << setw(10) << Currency.CurrencyCode();
        cout << "| " << left << setw(42) << Currency.CurrencyName();
        cout << "| " << left << setw(25) << Currency.Rate();
       
    }
public:

    static void ShowCurrenciesListScreen() {
        vector <clsCurrency> vCurrencies = clsCurrency::GetCurrencyList();
        string Title = "\t Currencies List";
        string SubTitle = "\t  (" + to_string(vCurrencies.size()) + ") Currency.";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(10) << "Code";
        cout << "| " << left << setw(42) << "Name";
        cout << "| " << left << setw(25) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vCurrencies.size() == 0)
            cout << "\t\t\tNo Currencies Available In the Screen!";
        else
            for (clsCurrency Currency : vCurrencies) {
                _PrintCurrencyRecord(Currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

