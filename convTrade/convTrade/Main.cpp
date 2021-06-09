#include "declarations.h"

int main()
{
	bool isOnline = false;
	callInterface(0);
	callInterface(1000);
	json userAccData;
	isOnline = authorization(userAccData);
	if (isOnline)
	{
		//
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