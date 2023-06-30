#pragma once
#include <iostream>
#include "clsUser.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
#include <iomanip>
using namespace std;
class clsFindUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User) {
        cout << "\nUser Card:";
        cout << "\n______________________";
        cout << "\nFirst Name     : " << User.FirstName;
        cout << "\nLast Name      : " << User.LastName;
        cout << "\nFull Name      : " << User.FullName();
        cout << "\nEmail          : " << User.Email;
        cout << "\nPhone          : " << User.Phone;
        cout << "\nAccount Number : " << User.UserName();
        cout << "\nPassword       : " << User.GetPassword();
        cout << "\nPermissions    : " << User.Permissions;
        cout << "\n____________________\n";
    }
public:
    static void ShowFindUserScreen() {
        _DrawScreenHeader("\tFind User Screen");
        string UserName = "";
        cout << "\nPlease enter user name? ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nUser Name is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        if (!User.IsEmpty())
            cout << "\nUser Found : -)\n";

        else
            cout << "\nUser is not Found : -(\n";

        _PrintUser(User);
    }
};

