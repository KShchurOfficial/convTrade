#include "declarations.h"

getAccount thisUser{};

int main()
{
	bool isOnline = false;
	json userAccData;
	int dialog = 0;
	callInterface(0);
	callInterface(1000);
	isOnline = startFunc(userAccData);
	if (isOnline == true)
	{
		fillStruct(thisUser, userAccData);
	}
	Sleep(1500);
	system("cls");
	while (true)
	{
		if (isOnline)
		{
			callInterface(201);
			cin >> dialog;
			cin.get();
			switch (dialog)
			{
			case 1:
				callInterface(300);
				Sleep(750);
				system("cls");
				converterMain(userAccData);
				break;
			case 2:
				callInterface(400);
				Sleep(750);
				system("cls");
				cout << "*\nminigame\n*";
				break;
			case 3:
				callInterface(500);
				Sleep(750);
				system("cls");
				showAccData(thisUser, userAccData);
				break;
			case 4:
				thisUser = {};
				isOnline = false;
				cout << "\n you are logged out of your account.\n";
				Sleep(750);
				system("cls");
				break;
			case 5:
				system("cls");
				callInterface(600);
				Sleep(750);
				return 0;
			default:
				callInterface(-100);
			}
		}
		else
		{
			callInterface(200);
			cin >> dialog;
			cin.get();
			switch (dialog)
			{
			case 1:
				callInterface(300);
				Sleep(750);
				system("cls");
				converterMain(userAccData);
				break;
			case 2:
				callInterface(-104);
				break;
			case 3:
				callInterface(-104);
				break;
			case 4:
				system("cls");
				Sleep(250);
				isOnline = startFunc(userAccData);
				if (isOnline)
				{
					fillStruct(thisUser, userAccData);
				}
				break;
			case 5:
				system("cls");
				callInterface(600);
				Sleep(750);
				return 0;
			default:
				callInterface(-100);
			}
		}
		Sleep(750);
		system("cls");
	}
}

/*
	ifstream origin;
	string reader, fullContent;
	json jsonData;
	origin.open("..//accounts/God.json");
	if (origin.is_open())
	{
		while (!origin.eof())
		{
			getline(origin, reader);
			fullContent += reader;
		}
		jsonData = json::parse(fullContent);
	}
	fillStruct(godAcc, jsonData);
	cout << " Name: " << godAcc.name << endl
		<< " Pass: " << godAcc.pass << endl
		<< " Wallet: " << godAcc.wallet - 1 << endl;*/