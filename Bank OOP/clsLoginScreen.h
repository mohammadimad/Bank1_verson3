#pragma once
//#include <iostream>
//#include "clsUser.h";
////#include "clsScreen.h";
//#include "clsMainScreen.h";
//#include "clsLoginScreen.h";
//#include "Global.h";


#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsmainScreen.h"
#include "Global.h"

using namespace std;
class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		short x = 3;
		bool LoginFaild = false;
		string Username, Password;
		do
		{
			if (LoginFaild)
			{
				
				cout << "\nInvlaid Username/Password!\n";
				cout << "You have " << --x << " Trials to login.\n\n";
			}
			if (x == 0) {
				cout << "\nYou are Locked after 3 faild trails\n";
				return false;
			}
			cout << "Enter Username? ";
			cin >> Username;
			cout << "Enter Password? ";
			cin >> Password;
			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();
			
		} while (LoginFaild);
		if (!CurrentUser.IsEmpty()) {
			CurrentUser.RegisterLogIn();
			clsmainScreen::ShowMainMenue();
		}
		else {
			clsmainScreen::ShowMainMenue();
		}
		return true;
	}
	
public:
	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}
};

