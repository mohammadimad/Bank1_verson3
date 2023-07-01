#pragma once
#include <iostream>
#include "clsDate.h";
using namespace std;
class clsInputValidate
{
public:
	
	static bool IsNumberBetween(short Number, short from, short to) {
		
		return (Number >= from && Number <= to) ? true : false;
	}
	static bool IsNumberBetween(int Number, int from, int to) {
		
		return (Number >= from && Number <= to) ? true : false;
	}
	static bool IsNumberBetween(double Number, double from, double to) {
		
		return (Number >= from && Number <= to) ? true : false;
	}
	static string ReadString() {
		string S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}
	static bool IsNumberBetween(float Number, float from, float to) {
		
		return (Number >= from && Number <= to) ? true : false;
	}
	static bool IsDateBetween(clsDate Date,clsDate Date2, clsDate Date3) {
		if (clsDate::CompareDates(Date2, Date3) == clsDate::enDateCompare::Before) {
			if (clsDate::CompareDates(Date, Date2) == clsDate::enDateCompare::Before ||
				clsDate::CompareDates(Date, Date3) == clsDate::enDateCompare::After) {
				return false;
			}
			else
				return true;
		}
		else{
			clsDate::SwapDates(Date2, Date3);
			if (clsDate::CompareDates(Date, Date2) == clsDate::enDateCompare::Before ||
				clsDate::CompareDates(Date, Date3) == clsDate::enDateCompare::After) {
				return false;
			}
			else
				return true;
		}
	}
	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again") {
		int Number;   
		cout << "Please enter a number?" << endl;   
		while (!(cin >> Number)) {
			// user didn't input a number
			cin.clear();   
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			cout << ErrorMessage << endl;
			cin >> Number;   
		} 
			return Number; 
	}
	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		short Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	static double ReadDoubleNumber(string ErrorMessage = "Invalid Number, Enter again") {
		double Number;
		//cout << "Please enter a number?" << endl;
		while (!(cin >> Number)) {
			// user didn't input a number
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Number;
		}
		return Number;
	}
	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again") {
		float Number;
		//cout << "Please enter a number?" << endl;
		while (!(cin >> Number)) {
			// user didn't input a number
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Number;
		}
		return Number;
	}
	static short ReadShortNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadShortNumber();
		}
		return Number;
	}
	static int ReadIntNumberBetween(int from, int to,string ErrorMessage = "Invalid Number, Enter again") {
		int Number;
		do {
			Number = ReadIntNumber();
			if (!IsNumberBetween(Number, from, to))
				cout << ErrorMessage;
		} while (!IsNumberBetween(Number,from,to));
		return Number;
	}
	static double ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		float Number = ReadFloatNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadFloatNumber();
		}
		return Number;
	}
	static int ReadDoubleNumberBetween(double from, double to, string ErrorMessage = "Invalid Number, Enter again") {
		double Number;
		do {
			Number = ReadIntNumber();
			if (!IsNumberBetween(Number, from, to))
				cout << ErrorMessage;
		} while (!IsNumberBetween(Number, from, to));
		return Number;
	}
	static bool IsValideDate(clsDate Date) {
		clsDate::ValidDate(Date);
	}
};

