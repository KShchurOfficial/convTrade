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
	string pass;
	double wallet;
};

void fillStruct(getAccount& target, json& victim);
void callInterface(int mode);
bool authorization(json&);

#endif // !declarations