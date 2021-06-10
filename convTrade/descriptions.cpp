#include "declarations.h"

void callInterface(int mode) // ������� ��� ������ ���������� �� ���������.
{
	switch (mode) // ����������� ����������
	{
	case 0:
		cout << " Greetings you in the \"Convtrade\" application!\n "; // ����� ��� ����� � ����������
		break;
	case 1000:
		cout << " Before start working, you need to authorize in system.\n"; // ���������, ���� ������������ �� �����������
		break;
	case 10000:
		cout << " Have you an account or you need to registrate yourself?\n \"1\" - authorize in my own account\n" // ��������� ������, ����
			<< " \"2\" - registrate a new account\n \"3\" - continue without authorization (the minigame will not be available)\n Your input: ___\b\b"; // ������������ �� ����������� � ���������� ����� ����������� ��� �����������
		break;
	case 100010:
		cout << " Enter login: _____\b\b\b\b\b"; // ������ �� �����
		break;
	case 100011:
		cout << " Enter username: _____\b\b\b\b\b";
		break;
	case 10002:
		cout << " Enter password: _____\b\b\b\b\b"; // ������ �� ������
		break;
	case 10003:
		cout << " Enter password again: _____\b\b\b\b\b"; // (��� �����������) ������ �� ��������� ���� ������ ��� �������� ������������ �����
		break;
	case 1001:
		cout << " Login completed successfully!\n "; // ���������� �� ������ ��������� ����� � �������
		break;
	case 1002:
		cout << " Registration completed successfully!\n "; // ���������� �� ������ �������� �����������
		break;
	case 200:
		cout << " Here is the main menu. Select a further action option\n and enter a number next to the option.\n"
			<< " \"1\" - move in currencies converter.\n \"2\" - move in minigame (need to authorize)\n \"3\" - open an account data (need to authorize)\n \"4\" - authorizate in system\n"
			<< " \"5\" - shut down the program\n Your input: _____\b\b\b\b\b";
		break;
	case 201:
		cout << " Here is the main menu. Select a further action option\n and enter a number next to the option.\n "
			<< " \"1\" - move in currencies converter.\n \"2\" - move in minigame\n \"3\" - open an account data\n \"4\" - exit the account\n"
			<< " \"5\" - shut down the program\n Your input: _____\b\b\b\b\b";
		break;
	case 300:
		cout << "\n opening the converter . . .\n";
		break;
	case 400:
		cout << "\n opening the minigame . . .\n";
		break;
	case 500:
		cout << "\n opening the account data . . .\n";
		break;
	case 5000:
		cout << " To change the account data, you need first enter the field of data,\n which will be changed,"
			<< " then, enter the data,\n which will be changed, and then, enter the data,\n which will changing.\n"
			<< " To cansel the operation, enter \"cansel\"\n Enter the field of data, which is will be redacted: _____\b\b\b\b\b";
		break;
	case 5001:
		cout << " Enter the content, which is will be changed: _____\b\b\b\b\b";
		break;
	case 5002:
		cout << " Enter the content, which is will change data: _____\b\b\b\b\b";
		break;
	case 5003:
		cout << " Redacting is completed.\n";
		break;
	case 5004:
		cout << " The operation was cancelled. \n";
		break;
	case 600:
		cout << "\n shutting down . . .\n";
		break;
	case -100:
		cout << " Error 100: incorrectly selected answer option. Try again\n";
		break;
	case -101:
		cout << " Error 101: some data are inputed incorrectly. Try again\n"; // ������ � ����� 101: ���� ����� ��� ������ 
		break; // ��� ����������� ������� �������
	case -102:
		cout << " Error 102: entered passwords are not coincidered. Try again.\n"; // ������ � ����� 102:  ���� ������, ��������� ��� �����������, �� ���������
		break;
	case -103:
		cout << " Error 103: Account with this username is already registrated.\n"; // ������ � ����� 103: ���� ����� ������������ ��� ���������������
		break;
	case -104:
		cout << " Error 104: To get access to this option, you need to authorize in system.\n";
	}
}

bool startFunc(json& objref)
{
	bool result = 0;
	callInterface(10000);
	result = entryFork(objref);
	return result;
}

bool entryFork(json& objref)
{
	int input;
	bool funcAns = 0;
	do
	{
		cin >> input;
		cin.get();
		switch (input)
		{
		case 1:
			funcAns = authorization(objref);
			break;
		case 2:
			funcAns = registration(objref);
			break;
		case 3:
			return 0;
		default:
			callInterface(-100);
			cout << " Your input: ___\b\b";
		}
	} while (input != 1 && input != 2 && input != 3);
	return funcAns;
}

bool registration(json& jsonData) // �������� ������� ����������� ������������
{
	string getLogin, getName, getPass = " ", checkPass = "  "; // ����������� ��� ������: ��� ������ � ���� ������ ������
	while (true) // ����� ������� ����������� ����
	{
		callInterface(100010); // ����� ������� �� ���� ������
		getline(cin, getLogin); // ���� ������
		callInterface(100011);
		getline(cin, getName);
		callInterface(10002); // ����� ������� �� ���� ������
		getline(cin, getPass); // ���� ������
		callInterface(10003); // ����� ������� �� ������ ���� ������
		getline(cin, checkPass); // ���� ������

		if (checkPass != getPass) // ���� ��������� ������ �� ���������
		{
			callInterface(-102); // ����� ���������� �� ������
		}
		else // ���� ������ ������� ���������
		{
			if (checkAvail(getName)) // ���������� �������� ���������� ������ ������� checkAvail,
			{	// ������� ��������� �� ���������� ������������ � �������������� ��� ������������.
				// ���� �������� ������ �������
				string bornWay = "..//accounts/" + to_string(countAccs() + 1) + ".json", bornContent;  // ��������� ��� ��� ������
				// bornWay - ���� � ������ ����� � ������� ��� ����� (������������� ���������� ���������, � ������ ������������� ������� �����).
				// bornContent - �������� ������, ���������� json-������ � ������������ ��� ������ ������ � ����� ����.

				jsonData["name"] = getName; // ����������� ������ json
				jsonData["login"] = getLogin; 
				jsonData["pass"] = getPass;
				jsonData["experience"] = 0;
				jsonData["wallet"] = 10;
				jsonData["wTS"] = "";

				bornContent = jsonData.dump(); // ���������� "������������" json-������ - �������������� �� � ������ string � ������������ ����������� �������������� �� �������.

				ofstream bornUser; // ��������� ������ ofstream ��� ����������� � ������ � ����� ����,
				bornUser.open(bornWay.c_str()); // ����������� ����� ���� �� ������ ������,
				bornUser << bornContent; // ������������ ��������������� json-������
				bornUser.close(); // � ���� �����������.

				callInterface(1002); // ��������� ���������� �� �������� ���������� �����������.
				return 1; // ������������ �������� true, ������������, ��� ������������ ������ �����������
			}
		}
	}
}

int countAccs() // �������� �������, ��������� ������������������ ���������� ������� �������
{
	string wayBase = "..//accounts/", fileExtension = ".json", fullWay; // ����������� ��� ������
	// wayBase - ��������� ������
	// fileExtension - ���������� �����
	// fullWay - ������ ����
	int fileNum = 1; // ����� ������������ �����
	ifstream followLink; // ������ followLink, � ������� �������� ����� ����������� ����� �� ������������ ����������� ������ 
	fullWay = wayBase + to_string(fileNum) + fileExtension; // ���������� ������ ���� (fileNum ������������� �� int � string)
	followLink.open(fullWay.c_str()); // ����������� ���� �� ���������� ���� (fullWay ����������� � ���������� ������)
	while (followLink.is_open()) // ���� ����������� ����� �� ����������� ���� 
	{
		followLink.close(); // ������� ����������� ����
		fileNum++; // ��������� ����� �����
		fullWay = wayBase + to_string(fileNum) + fileExtension; // ������� ����� ���� � �����
		followLink.open(fullWay.c_str()); // � ������� ��������� ����
	}
	return (fileNum - 1);// ������������ ���������� ������������ ������
}

bool authorization(json& jsonData) // �������� ������� ����������� ������������ � �������
{
	int accsQuan = 0; // ��������� ���������� ��� �������� ���������� ������������������ �������������
	accsQuan = countAccs(); // �������� �������� (����������� ������� ������� countAccs())

	string getName, getLogin, getPass; // ��������� ��� ������ ��� �������� �����, ������ � ������ ��������������
	callInterface(100010); // ����� ������� �� ���� ������
	getline(cin, getLogin); // ���� ������
	callInterface(100011);
	getline(cin, getName);
	callInterface(10002); // ����� ������� �� ���� ������
	getline(cin, getPass); // ���� ������
	string wayBase = "..//accounts/", fileExtension = ".json", fullWay; // ����������� ��� ������
	// wayBase - ��������� ������
	// fileExtension - ���������� �����
	// fullWay - ������ ����
	int fileNum = 1; // ����� ������������ �����
	bool wrongInput = false; // ��������� ������������� ����� ������ ��� ������
	ifstream followLink; // ������ ifstream ��� ������ �����
	string reader, fullContent; // ��� ������ ��� ������ � ������ ���������� �� �����
	while (true)
	{
		if (wrongInput) // ���� 
		{
			wrongInput = false;
			callInterface(100010);
			getline(cin, getLogin);
			callInterface(100011);
			getline(cin, getName);
			callInterface(10002);
			getline(cin, getPass); 
		}
		fullWay = wayBase + to_string(fileNum) + fileExtension; // �� ����������� ���������� ������ ���� (fileNum ����������������� �� int � string)
		followLink.open(fullWay.c_str()); // �� ���������� ������� ���� ����������� ����
		if (followLink.is_open()) // ���� ���� ������� �������
		{
			while (!followLink.eof()) // � ���� �� ����� �����
			{
				getline(followLink, reader); // ��������� ������� ����
				fullContent += reader; // � �������� � ����. �����
			}
			jsonData = json::parse(fullContent); // ����� ���������� ����� ����� ���������� "��������������" - �������������� ������ � ������ json
		}
		fullContent = ""; // �������� ����� ������ ������ �� �����
		followLink.close(); // ������� ����
		if (jsonData["name"] == getName && jsonData["login"] == getLogin && jsonData["pass"] == getPass) // �������� �� ���������� �������� � ���������� � ���� ������ � ������
		{
			callInterface(1001); // ����� ���������� �� �������� ���������� �����������
			break; // ���������� �����
		}
		else // ���� ���, ����� � ������ �� ��������� 
		{
			fileNum++; // ������� � ���������� �����
			if (fileNum > accsQuan) // ���� ���������� ����� ����� ������ ��� ���������� ������������������ �������������
			{
				callInterface(-101); // ������� ���������� �� ������
				wrongInput = true; // �������� ��������� ���������� ������������� ����� ������ ��� ������
				fileNum = 1; // �������� ����� ����� �� 1 (������� � ������)
			}
		}
	}
	return 1; // ������� true � ���������� �������� �����������, �.�. ������������ ������ �����������
}

bool checkAvail(string username) // �������� ������� �������� �� ������������������ �������
{
	int accsQuan = 0; // ��������� ���������� ��� �������� ���������� ������������������ ���������
	accsQuan = countAccs(); // ������������� ���������� ������������ ��������� ������� countAccs()
	string wayBase = "..//accounts/", fileExtension = ".json", fullWay; // ����������� ��� ������
	// wayBase - ��������� ������
	// fileExtension - ���������� �����
	// fullWay - ������ ����
	int fileNum = 1; // ����� ������������ �����
	ifstream followLink; // ������ ifstream ��� ������ �����
	string reader, fullContent; // ��� ������ ��� ������ � ������ ���������� �� �����
	json jsonData; // json-����� ��� ��������� ������ ��������
	while (true)
	{
		fullWay = wayBase + to_string(fileNum) + fileExtension; // �� ����������� ���������� ������ ����
		followLink.open(fullWay.c_str()); // �� ���������� ���� ����������� ����
		if (followLink.is_open()) // ���� ���� ��������
		{
			while (!followLink.eof()) // ���� �� ��������� ����� �����
			{
				getline(followLink, reader); // ��������� ������� ����
				fullContent += reader; //  � �������� ������ � �����
			}
			jsonData = json::parse(fullContent); // ����� ������� ��������� ���������� "��������������" ������
		}
		fullContent = ""; // �������� ����� ������ ����������
		followLink.close(); // ������� ����
		if (jsonData["name"] == username) // ���� ����� �� ����� ��������� � ��������� ������
		{
			callInterface(-103); // ������� ���������� �� ������ 
			return 0; // ������� false
		}
		else
		{
			followLink.close(); // ������� ����
			fileNum++; // ��������� ����� ����� (������������� �� ��������� ����)
			if (fileNum > accsQuan) // ���� ����� ����� ������ ���-�� ������������������ ������������� (��������� � �������� ��������� ����)
			{
				return 1; // ������� true, �.�. ����� ���������� � ���������� �� �������
			}
		}
	}
}

void fillStruct(getAccount& target, json& victim)
{
	target.name = victim["name"].get<string>();
	target.login = victim["login"].get<string>();
	target.pass = victim["pass"].get<string>();
	target.experience = victim["experience"].get<int>();
	target.wallet = victim["wallet"].get<double>();
	target.wTStorage = victim["wTS"].get<string>();
}

void showAccData(getAccount& content, json& objref)
{
	int chooseMode = -1;
	while (true)
	{
		cout << " Here is an user account data: \n 1. username: " << content.name << ";\n"
			<< " 2. wallet: " << content.wallet << " BetTokens;\n 3. users experience: "
			<< content.experience << " EXP;\n Enter \"1\" to redact name? login or password\n Enter \"0\" to return in the main menu\n"
			<< " Your input: _\b";
		cin >> chooseMode;
		cin.get();
		if (chooseMode == 1)
		{
			system("cls");
			redactAcc(content, objref);
		}
		else if (chooseMode == 0)
		{
			return;
		}
		else
		{
			callInterface(-100);
			cout << "\n Your input: _\b";
		}
	}
}

void redactAcc(getAccount& content, json& objref)
{
	string changingCont, changedCont, changedField, cancelComm = "cancel";
	callInterface(5000);
	getline(cin, changedField);
	if (changedField == cancelComm)
	{
		callInterface(5004);
		system("cls");
		return;
	}
	callInterface(5001);
	getline(cin, changedCont);
	if (changedCont == cancelComm)
	{
		callInterface(5004);
		system("cls");
		return;
	}
	callInterface(5002);
	getline(cin, changingCont);
	if (changingCont == cancelComm)
	{
		callInterface(5004);
		system("cls");
		return;
	}
	// ������� ��������
	// ������ ���������
	return;
}