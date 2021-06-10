/*#include "declarations.h"

using namespace std;
using namespace nlohmann;

static size_t tCCodeToString(void* contents, size_t size, size_t nmemb, void* userp);
// translate CURLcode to string

int main()
{
    string chooseCurr, gRBase = "https://min-api.cryptocompare.com/data/price?"; // base of get-request
    string fromCurr = "fsym=", toCurr = "&tsyms=";
    cout << " Choose the cryptocurrency (for example: BTC - bitcoin)\n Your choice: ___\b\b\b";
    getline(cin, chooseCurr);
    fromCurr += chooseCurr;
    cout << " Choose the currency (for example: USD - US dollar)\n Your choice: ___\b\b\b";
    getline(cin, chooseCurr);
    toCurr += chooseCurr;
    string getRequest = gRBase + fromCurr + toCurr;
    json jsonData;
    CURL* curl;
    CURLcode primAns;
    string sTSAns; // Translated to String Answer
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, getRequest.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, tCCodeToString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sTSAns);
    primAns = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    jsonData = json::parse(sTSAns);
    cout << " data in JSON-form: " << jsonData["USD"] << endl;
}

static size_t tCCodeToString(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}*/

