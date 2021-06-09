#include "declarations.h"

const int accsQuan = 3;
void callInterface(int mode)
{
	switch (mode)
	{
	case 0:
		cout << " Greetings you in the \"Convtrade\" application!\n ";
		break;
	case 1000:
		cout << " Before start working, you need to authorize in system.\n";
		break;
	case 10001:
		cout << " Enter login: _____\b\b\b\b\b";
		break;
	case 10002:
		cout << " Enter password: _____\b\b\b\b\b";
		break;
	case 1001:
		cout << " Login completed successfully! ";
		break;
	case -101:
		cout << " Error 101: Login or password are inputed incorrectly. Try again\n";
		break;
	}
}

bool authorization(json& jsonData)
{
	string getLogin, getPass;
	callInterface(10001);
	getline(cin, getLogin);
	callInterface(10002);
	getline(cin, getPass);
	string wayBase = "..//accounts/", fileExtension = ".json", fullWay;
	int fileNum = 1;
	bool wrongInput = false;
	ifstream followLink;
	string reader, fullContent;
	while (true)
	{
		if (wrongInput)
		{
			wrongInput = false;
			callInterface(10001);
			getline(cin, getLogin);
			callInterface(10002);
			getline(cin, getPass);
		}
		fullWay = wayBase + to_string(fileNum) + fileExtension;
		followLink.open(fullWay.c_str());
		if (followLink.is_open())
		{
			while (!followLink.eof())
			{
				getline(followLink, reader);
				fullContent += reader;
			}
			jsonData = json::parse(fullContent);
		}
		fullContent = "";
		followLink.close();
		if (jsonData["login"] == getLogin && jsonData["pass"] == getPass)
		{
			callInterface(1001);
			break;
		}
		else
		{
			followLink.close();
			fileNum++;
			if (fileNum > accsQuan)
			{
				callInterface(-101);
				wrongInput = true;
				fileNum = 1;
			}
		}
	}
	return 1;
}

void fillStruct(getAccount& target, json& victim)
{
	target.name = victim["name"];
	target.pass = victim["pass"];
	target.wallet = victim["wallet"];
}