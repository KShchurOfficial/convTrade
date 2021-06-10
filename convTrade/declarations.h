#ifndef declarations
#define declarations
#define CURL_STATICLIB

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <curl\curl.h>
#include <nlohmann/json.hpp>


using namespace std;
using namespace nlohmann;

struct getAccount
{
	string name;
	string login;
	string pass;
	double wallet;
	int experience;
	string wTStorage; // way to storage
};

bool startFunc(json& objref);
void callInterface(int mode);
bool entryFork(json& objref);
bool authorization(json& objref);
bool checkAvail(string login); // checking for availability
bool registration(json& objref);
int countAccs();
void fillStruct(getAccount& target, json& victim);

void showAccData(getAccount& content, json& objref);
void redactAcc(getAccount& content, json& objref);

void converterMain(json& userInfo);

#endif // !declarations