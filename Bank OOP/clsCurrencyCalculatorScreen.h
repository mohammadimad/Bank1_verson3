#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsString.h"
#include "clsInputValidate.h"
using namespace std;
class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
   
    static void _PrintCurrencyCard(clsCurrency Currency, string Title ) {
        cout << Title;
        cout << "\n______________________";
        cout << "\nCountry       : " << Currency.Countery();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$)      : " << Currency.Rate();
        cout << "\n____________________\n";
    }
  
   static float _ReadAmount()
   {
       cout << "\nEnter Amount to Exchange: ";
       float Amount = 0;

       Amount = clsInputValidate::ReadFloatNumber();
       return Amount;
   }
   static clsCurrency _GetCurrency(string Message)
   {

       string CurrencyCode;
       cout << Message << endl;

       CurrencyCode = clsInputValidate::ReadString();

       while (!clsCurrency::IsCurrencyExist(CurrencyCode))
       {
           cout << "\nCurrency is not found, choose another one: ";
           CurrencyCode = clsInputValidate::ReadString();
       }

       clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
       return Currency;

   }
   static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
   {

       _PrintCurrencyCard(Currency1, "Convert From:");

       float AmountInUSD = Currency1.ConvertToUSD(Amount);

       cout << Amount << " " << Currency1.CurrencyCode()
           << " = " << AmountInUSD << " USD\n";

       if (Currency2.CurrencyCode() == "USD")
       {
           return;
       }

       cout << "\nConverting from USD to:\n";

       _PrintCurrencyCard(Currency2, "To:");

       float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

       cout << Amount << " " << Currency1.CurrencyCode()
           << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();

   }

public:
    static void ShowCurrencyCalculatorScreen() {
        char Continue = 'y';
        do {
            system("cls");
            _DrawScreenHeader("\tShow Currency Calculator Screen");
            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;
        } while (Continue == 'y');
        
    }
};

