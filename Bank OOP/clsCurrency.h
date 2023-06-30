#pragma once
#include <iostream>
#include "clsString.h"
#include <fstream>
#include <string>
using namespace std;
class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1};
	enMode _Mode;
	string _Country;
	string _CurrenecyCode;
	string _CurrencyName;
	bool _MarkedForDeleted = false;
	float _Rate;
	static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#") {
		vector <string> vCurrencyData;
		vCurrencyData = clsString::Split(Line, Seperator);
		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1],
			vCurrencyData[2], stod(vCurrencyData[3]));
	}
	static vector <clsCurrency> _LoadCurrenciesDataFromFile() {
		vector < clsCurrency > vCurrency;
		fstream Myfile;
		Myfile.open("Currencies.txt", ios::in);
		string Line;
		if (Myfile.is_open()) {
			while (getline(Myfile, Line)) {
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
				vCurrency.push_back(Currency);
			}
			Myfile.close();
		}
		return vCurrency;
	}
	string _ConverCurrenecyObjectToLine(clsCurrency Currenecey, string Seperator = "#//#") {
		string CurrenceyRecord = "";
		CurrenceyRecord += Currenecey.Countery() + Seperator;
		CurrenceyRecord += Currenecey.CurrencyCode() + Seperator;
		CurrenceyRecord += Currenecey.CurrencyName() + Seperator;
		CurrenceyRecord += to_string(Currenecey.Rate()) + Seperator;
		return CurrenceyRecord;
	}
	void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrency) {
		fstream MyFile;
		string DateLine;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsCurrency& C : vCurrency) {
				if (C.MarkedForDeleted() == false) {
					DateLine = _ConverCurrenecyObjectToLine(C);
					MyFile << DateLine << endl;
				}
			}
		}
		MyFile.close();
	}
	void _Update() {
		vector <clsCurrency> _vCurrency;
		_vCurrency = _LoadCurrenciesDataFromFile();
		for (clsCurrency& C : _vCurrency) {
			if (C.CurrencyCode() == CurrencyCode()) {
				C = *this;
				break;
			}
		}
		_SaveCurrenciesDataToFile(_vCurrency);
	}
	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}
public:
	bool IsEmpty() {
		return (_Mode == EmptyMode);
	}
	clsCurrency(enMode Mode,string Country, string CurrencyCode,
		string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrenecyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string Countery() {
		return _Country;
	}
	string CurrencyName() {
		return _CurrencyName;
	}
	string CurrencyCode() {
		return _CurrenecyCode;
	}
	float Rate() {
		return _Rate;
	}
	bool MarkedForDeleted() {
		return _MarkedForDeleted;
	}
	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}
	static clsCurrency FindByCode(string CurrencyCode) {
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsCurrency Currenecy = _ConvertLinetoCurrencyObject(Line);
				if (Currenecy.CurrencyCode() == CurrencyCode) {
					MyFile.close();
					return Currenecy;
				}

			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}
	static clsCurrency FindByCountry(string Country) {
		
		Country = clsString::UpperAllString(Country);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsCurrency Currenecy = _ConvertLinetoCurrencyObject(Line);
				if (clsString::UpperAllString(Currenecy.Countery()) == Country) {
					MyFile.close();
					return Currenecy;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}
	static vector <clsCurrency> GetCurrencyList() {
		return _LoadCurrenciesDataFromFile();
	}
	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrency C1 = FindByCode(CurrencyCode);
		return (!C1.IsEmpty());
	}
	float ConvertToUSD(float Amount) {
		return (float)(Amount / Rate());
	}
	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.CurrencyCode() == "USD")
			return AmountInUSD;
		
		return float(Currency2.Rate() * ConvertToUSD(Amount));
	}
};

