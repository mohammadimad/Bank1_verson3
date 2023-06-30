#pragma once
#include <iostream>
#include "clsUser.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
#include <iomanip>
using namespace std;
class clsUpdateUserScreen : clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User) {
        cout << "\nEnter First Name: ";
        User.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter Last Name: ";
        User.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();
        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();
        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();
        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }
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
    static int _ReadPermissionsToSet() {
        int Permissions = 0;
        char Answer = 'n';
        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }
        cout << "\nDo you want to give access to : \n ";
        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pListClients;
        }
        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }
        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }
        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }
        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }
        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }
        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }
        cout << "\nShow Login Register y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pShowLogInRegister;
        }
        return Permissions;
    }
public:
    static void ShowUpdateUserScreen() {
        _DrawScreenHeader("\tUpdate User Screen");
        string UserName = "";
        cout << "\nPlease enter user name? ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nUser Name is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);
        cout << "\nAre you sure you want to update this user y/n? ";
        char Answer = 'n';
        cin >> Answer;
        Answer = tolower(Answer);
        if (Answer == 'y') {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";
            _ReadUserInfo(User);
            clsUser::enSaveResults SaveResult;

            SaveResult = User.Save();

            switch (SaveResult)
            {
            case  clsUser::enSaveResults::svSucceeded:
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(User);
                break;
            case clsUser::enSaveResults::svFaildEmptyObject:

                cout << "\nError user was not saved because it's Empty";
                break;
            }

        }
    }
};

