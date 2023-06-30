#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include "clsDate.h"
#include "clsUtil.h"
#include <fstream>
class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddMode = 2 };
	
	enMode _Mode;
	string _UserName;
	string _Password;
	string _EncryptedPassword;
	bool _MarkedForDeleted = false;
	int _Permissions;

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#") {
		stLoginRegisterRecord LoginRegisterRecord;
		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = (LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permissions = stod(LoginRegisterDataLine[3]);
		return LoginRegisterRecord;
	}
	
    string _PrepareLongInRecord(string Seperator = "#//#") {
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName() + Seperator;
		LoginRecord += (Password) + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}
	static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#") {
		vector <string> vUserData;
		vUserData = clsString::Split(Line, Seperator);
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], (vUserData[5]), stod(vUserData[6]));
	}
	string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#") {
		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName() + Seperator;
		UserRecord += (User.Password)+ Seperator;
		UserRecord += to_string(User.Permissions);
		return UserRecord;
	}
	static vector <clsUser> _LoadUsersDataFromFile() {
		vector <clsUser> vUsers;
		fstream Myfile;
		Myfile.open("Users.txt", ios::in);
		string Line;
		if (Myfile.is_open()) {
			while (getline(Myfile, Line)) {
				clsUser User = _ConvertLinetoUserObject(Line);
				vUsers.push_back(User);
			}
			Myfile.close();
		}
		return vUsers;
	}
	void _SaveUsersDataToFile(vector <clsUser> vUser) {
		fstream MyFile;
		string DateLine;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsUser& U : vUser) {
				if (U.MarkedForDeleted() == false) {
					DateLine = _ConverUserObjectToLine(U);
					MyFile << DateLine << endl;
				}
			}
		}
		MyFile.close();
	}
	void _Update() {
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();
		for (clsUser& U : _vUsers) {
			if (U.UserName() == UserName()) {
				U = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
	}
	void _AddNew() {
		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}
	void _AddDataLineToFile(string DataLine) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static string EnctyptedPassword(string Password)
	{
		return clsUtil::EncryptText(Password);
	}
public:
	
	 enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32,
		pManageUsers = 64, pShowLogInRegister = 128
	};
	 struct stLoginRegisterRecord {
		 string DateTime;
		 string UserName;
		 string Password;
		 int Permissions;
	 };
	clsUser(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string UserName,
		string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}
	string UserName() {
		return _UserName;
	}
	void SetPassword(string Password) {
		_Password = Password;
	}
	string GetPassword() {
		return _Password;
	}
	bool MarkedForDeleted() {
		return _MarkedForDeleted;
	}
	_declspec(property(get = GetPassword, put = SetPassword))string Password;
	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	int GetPermissions() {
		return _Permissions;
	}
	_declspec(property(get = GetPermissions, put = SetPermissions))int Permissions;
	static clsUser Find(string UserName) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName() == UserName) {
					MyFile.close();
					return User;
				}
				
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}
	static clsUser Find(string UserName, string Password) {	
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName() == UserName && User.Password == Password) {
					MyFile.close();
					return User;
				}	
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}
	static enum enSaveResults {
		svFaildEmptyObject = 0, svSucceeded = 1,
		svFailUserNameExists = 2
	};
	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			if (IsEmpty())
				return enSaveResults::svFaildEmptyObject;
		case enMode::UpdateMode:

			_Update();
			return enSaveResults::svSucceeded;
			break;

		case enMode::AddMode:
			if (clsUser::IsUserExist(_UserName)) {
				return enSaveResults::svFailUserNameExists;
			}
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;

		}
	}
	static bool IsUserExist(string UserName) {
		clsUser User1 = Find(UserName);
		return (!User1.IsEmpty());
	}
	bool Delete(string UserName) {
			vector <clsUser>vUsers;
			vUsers = _LoadUsersDataFromFile();
			for (clsUser& U : vUsers) {
				if (U.UserName() == UserName) {
					U._MarkedForDeleted = true;
					break;
				}
			}
			_SaveUsersDataToFile(vUsers);
			*this = GetAddNewUserObject(UserName);
			return true;
		}
	static clsUser GetAddNewUserObject(string UserName) {
		return clsUser(enMode::AddMode, "", "", "", "", UserName, "", 0);
	}
	static vector <clsUser> GetUserList() {
		return _LoadUsersDataFromFile();
	}
	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}
	static vector <stLoginRegisterRecord> GetLoginRegisterList() {
		vector <stLoginRegisterRecord> vLoginRegisterRecord;
		fstream Myfile;
		Myfile.open("LoginRegister.txt", ios::in);
		
		if (Myfile.is_open()) {
			string Line;
			stLoginRegisterRecord LoginRegisterRecord;
			while (getline(Myfile, Line)) {
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}
			Myfile.close();
		}
		return vLoginRegisterRecord;
	 }	
	void RegisterLogIn() {
		fstream MyFile;
		string DateLine = _PrepareLongInRecord();
		MyFile.open("LoginRegister.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << DateLine << endl;
			MyFile.close();
		}

	}
};

