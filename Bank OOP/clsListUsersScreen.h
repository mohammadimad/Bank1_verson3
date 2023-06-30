#pragma once
#include <iostream>
#include "clsUser.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
#include <iomanip>
using namespace std; 
class clsListUsersScreen : protected clsScreen
{
private:
    static void _PrintUserRecord(clsUser User) {
        cout << setw(8) << left << "" << "| " << left << setw(15) << User.UserName();
        cout << "| " << left << setw(20) << User.FullName();
        cout << "| " << left << setw(12) << User.Phone;
        cout << "| " << left << setw(25) << User.Email;
        cout << "| " << left << setw(10) << User.Password;
        cout << "| " << left << setw(12) << User.Permissions;
    }
public:

    static void ShowUsersList() {
        vector <clsUser> vUsers = clsUser::GetUserList();
        string Title = "\t User List";
        string SubTitle = "\t  (" + to_string(vUsers.size()) + ") User(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vUsers.size() == 0)
            cout << "\t\t\tNo Users Available In the Screen!";
        else
            for (clsUser User : vUsers) {
                _PrintUserRecord(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

