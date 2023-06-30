#pragma once
#include <iostream>
#include "clsUser.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
#include "Global.h";
#include <iomanip>
using namespace std;
class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User){
        cout << "\nClient Card:";
        cout << "\n______________________";
        cout << "\nFirst Name     : " << User.FirstName;
        cout << "\nLast Name      : " << User.LastName;
        cout << "\nFull Name      : " << User.FullName();
        cout << "\nEmail          : " << User.Email;
        cout << "\nPhone          : " << User.Phone;
        cout << "\nUser Name      : " << User.UserName();
        cout << "\nPassword       : " << User.Password;
        cout << "\nPermissions    : " << User.Permissions;
        cout << "\n____________________\n";
    }
public:
    static void ShowDeleteUserScreen() {
        _DrawScreenHeader("\tDelete User Screen");
        string UserName = "";
        cout << "\nPlease enter user name? ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nUser Name is already used,choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);
        cout << "\nAre you sure you want to delete this user y/n? ";
        char answer = 'n';
        cin >> answer;
        answer = tolower(answer);
        if (answer == 'y') {
            if (User.Delete(UserName)) {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User);
            }
            else {
                cout << "\nError user was not deleted\n";
            }
        }
    }
};

