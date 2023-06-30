#pragma once
#include <iostream>
#include "clsDate.h";
#include "clsString.h";
#include "clsPerson.h";
#include "clsUtil.h";
#include <vector>
#include <string>
#include <fstream>
#include "Global.h"
using namespace std;
class clsBankClient: public clsPerson
{
private:
	enum enMode {EmptyMode = 0, UpdateMode = 1,AddMode = 2};
	enMode _Mode;
	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {
		vector <string> vClientsData;
		vClientsData = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, vClientsData[0], vClientsData[1], vClientsData[2], vClientsData[3],
			vClientsData[4], vClientsData[5], stod(vClientsData[6]));
	}
	  void _SaveClientDateToFile(vector <clsBankClient> vClient) {
		fstream MyFile;
		string DateLine;
		MyFile.open("Clients.txt",ios::out);
		if (MyFile.is_open()) {
			for (clsBankClient& C : vClient) {
				if (C.MarkedForDeleted() == false) {
					DateLine = _ConverClientObjectToLine(C);
					MyFile << DateLine << endl;
				}
			}
		}
		MyFile.close();
	}
	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "","", 0);
	}
	void _Update() {
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDateFromFile();
		for (clsBankClient& C : _vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
				}
			}
		_SaveClientDateToFile(_vClients);
		}
	string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);
		return stClientRecord;
	}
	static vector <clsBankClient> _LoadClientsDateFromFile() {
		vector <clsBankClient> vClients;
			fstream Myfile;
		Myfile.open("Clients.txt", ios::in);
		string Line;
		if (Myfile.is_open()) {
			while (getline(Myfile, Line)) {
			   clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClients.push_back(Client);
			}
			Myfile.close();
		}
		return vClients;
	}
	void _AddDataLineToFile(string DataLine) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out| ios::app);
		if (MyFile.is_open()) {
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
	void _AddNew() {
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDeleted = false;
	string _PrepareTransferInRecord(float Amount, clsBankClient DestinationClient, string UserName,string Seperator = "#//#") {
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += (UserName);
		return TransferLogRecord;
	}
	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName) {
		fstream MyFile;
		string DateLine = _PrepareTransferInRecord(Amount, DestinationClient,UserName);
		MyFile.open("TransferRegister.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << DateLine << endl;
			MyFile.close();
		}
	}
	struct stTransferRegisterRecord;
	static stTransferRegisterRecord _ConvertTransferRegisterLineToRecord(string Line, string Seperator = "#//#") {

		stTransferRegisterRecord TransferRegisterRecord;
		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		TransferRegisterRecord.DateTime = LoginRegisterDataLine[0];
		TransferRegisterRecord.AccountNumber = LoginRegisterDataLine[1];
		TransferRegisterRecord.AccountNumber2 = LoginRegisterDataLine[2];
		TransferRegisterRecord.Amount = stod(LoginRegisterDataLine[3]);
		TransferRegisterRecord.Number1 = stod(LoginRegisterDataLine[4]);
		TransferRegisterRecord.Number2 = stod(LoginRegisterDataLine[5]);
		TransferRegisterRecord.User = LoginRegisterDataLine[6];
		return TransferRegisterRecord;
	}
public:
	struct stTransferRegisterRecord {
		string DateTime;
		string AccountNumber;
		string AccountNumber2;
		float Amount;
		float Number1;
		float Number2;
		string User;
	};
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, 
		string Phone,string AccountNumber,
	string PinCode, float AccountBalance): clsPerson(FirstName,LastName,Email,Phone) 
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}
	string AccountNumber() {
		return _AccountNumber;
	}
	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	string GetPinCode() {
		return _PinCode;
	}
	bool MarkedForDeleted() {
		return _MarkedForDeleted;
	}
	_declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;
	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance() {
		return _AccountBalance;
	}
	_declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;
	
	static clsBankClient Find(string AccoountNumber) {
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
                                  
		if (MyFile.is_open()) {
			string Line;
			
			while (getline(MyFile,Line)) {
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccoountNumber) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccoountNumber,string PinCode) {
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccoountNumber && Client.PinCode == PinCode) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client1 = Find(AccountNumber);
		return (!Client1.IsEmpty());
	}
	static enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1,
		svFailAccpuntNumberExists = 2};
	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddMode, "", "", "", "", AccountNumber, "", 0);
	}
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
			if (clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResults::svFailAccpuntNumberExists;
			}
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		
	}
	}
	 bool Delete(string AccountNumber) {
		 vector <clsBankClient>vClients;
		 vClients = _LoadClientsDateFromFile();
		 for (clsBankClient& C : vClients) {
			 if (C.AccountNumber() == AccountNumber) {
				 C._MarkedForDeleted = true;
				 break;
			 }
		 }
		 _SaveClientDateToFile(vClients);
		 *this = GetAddNewClientObject(AccountNumber);
		 return true;
	 }
	 static vector <clsBankClient> GetClientList() {
		 return _LoadClientsDateFromFile();
	 }
	 static double TotalBalance() {
		 vector <clsBankClient>vClients = GetClientList();
		 double totalbalances = 0;
		 for (clsBankClient C : vClients) {
			 totalbalances += C.AccountBalance;
		 }
		 return totalbalances;
	 }
	 void Deopsit(double Amount) {
		 _AccountBalance += Amount;
		 Save();
	 }
	 bool WithDraw(double Amount) {
		 if (Amount > _AccountBalance)
			 return false;
		 else {
			 _AccountBalance -= Amount;
			 Save();
			 
		 }
	 }
	 bool Transfer(float Amount, clsBankClient& DestinationClient) {
		 if (Amount > AccountBalance)
			 return false;
		 else {
			 WithDraw(Amount);
			 DestinationClient.Deopsit(Amount);
			 _RegisterTransferLog(Amount, DestinationClient, CurrentUser.UserName());
			 return true;
		 }
	 }
	 static vector <stTransferRegisterRecord> GetTransferRegisterList() {
		 vector <stTransferRegisterRecord> vTransferRegisterRecord;
		 fstream Myfile;
		 Myfile.open("TransferRegister.txt", ios::in);

		 if (Myfile.is_open()) {
			 string Line;
			 stTransferRegisterRecord TransferRegisterRecord;
			 while (getline(Myfile, Line)) {
				 TransferRegisterRecord = _ConvertTransferRegisterLineToRecord(Line);
				 vTransferRegisterRecord.push_back(TransferRegisterRecord);
			 }
			 Myfile.close();
		 }
		 return vTransferRegisterRecord;
	 }
};

