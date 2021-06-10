#include "declarations.h"

void callInterface(int mode) // функция для вывода оповещений от программы.
{
	switch (mode) // регулировка оповещения
	{
	case 0:
		cout << " Greetings you in the \"Convtrade\" application!\n "; // вывод при входе в приложение
		break;
	case 1000:
		cout << " Before start working, you need to authorize in system.\n"; // выводится, если пользователь не авторизован
		break;
	case 10000:
		cout << " Have you an account or you need to registrate yourself?\n \"1\" - authorize in my own account\n" // выводится следом, если
			<< " \"2\" - registrate a new account\n \"3\" - continue without authorization (the minigame will not be available)\n Your input: ___\b\b"; // пользователь не авторизован и предлагает выбор регистрации или авторизации
		break;
	case 100010:
		cout << " Enter login: _____\b\b\b\b\b"; // запрос на логин
		break;
	case 100011:
		cout << " Enter username: _____\b\b\b\b\b";
		break;
	case 10002:
		cout << " Enter password: _____\b\b\b\b\b"; // запрос на пароль
		break;
	case 10003:
		cout << " Enter password again: _____\b\b\b\b\b"; // (при регистрации) запрос на повторный ввод пароля для проверки правильности ввода
		break;
	case 1001:
		cout << " Login completed successfully!\n "; // оповещение на случай успешного входа в систему
		break;
	case 1002:
		cout << " Registration completed successfully!\n "; // оповещение на случай успешной регистрации
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
		cout << " Error 101: some data are inputed incorrectly. Try again\n"; // ошибка с кодом 101: если логин или пароль 
		break; // при авторизации введены неверно
	case -102:
		cout << " Error 102: entered passwords are not coincidered. Try again.\n"; // ошибка с кодом 102:  если пароли, введенные при регистрации, не совпадают
		break;
	case -103:
		cout << " Error 103: Account with this username is already registrated.\n"; // ошибка с кодом 103: если такой пользователь уже зарегистрирован
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

bool registration(json& jsonData) // описание функции регистрации пользователя
{
	string getLogin, getName, getPass = " ", checkPass = "  "; // обьявляются три строки: для логина и двух вводов пароля
	while (true) // далее следует бесконечный цикл
	{
		callInterface(100010); // вывод запроса на ввод логина
		getline(cin, getLogin); // ввод логина
		callInterface(100011);
		getline(cin, getName);
		callInterface(10002); // вывод запроса на ввод пароля
		getline(cin, getPass); // ввод пароля
		callInterface(10003); // вывод запроса на второй ввод пароля
		getline(cin, checkPass); // ввод пароля

		if (checkPass != getPass) // если введенные пароли не совпадают
		{
			callInterface(-102); // вывод оповещения об ошибке
		}
		else // если пароли введены правильно
		{
			if (checkAvail(getName)) // происходит проверка результата вызова функции checkAvail,
			{	// которая проверяет на совпадение существующие и регистрируемое имя пользователя.
				// если проверка прошла успешно
				string bornWay = "..//accounts/" + to_string(countAccs() + 1) + ".json", bornContent;  // создаются еще две строки
				// bornWay - путь к новому файлу с данными для входа (высчитывается количество аккаунтов, и новому присваивается крайний номер).
				// bornContent - буферная строка, получающая json-данные и используемая для записи данных в новый файл.

				jsonData["name"] = getName; // заполняется объект json
				jsonData["login"] = getLogin; 
				jsonData["pass"] = getPass;
				jsonData["experience"] = 0;
				jsonData["wallet"] = 10;
				jsonData["wTS"] = "";

				bornContent = jsonData.dump(); // происходит "сериализация" json-данных - преобразование их в формат string с возможностью дальнейшего восстановления из формата.

				ofstream bornUser; // создается объект ofstream для подключения и записи в новый файл,
				bornUser.open(bornWay.c_str()); // открывается новый файл по новому адресу,
				bornUser << bornContent; // записываются сериализованные json-данные
				bornUser.close(); // и файл закрывается.

				callInterface(1002); // выводится оповещение об успешном завершении регистрации.
				return 1; // возвращается значение true, обозначающее, что пользователь теперь авторизован
			}
		}
	}
}

int countAccs() // описание функции, считающей зарегистрированное количество учетных записей
{
	string wayBase = "..//accounts/", fileExtension = ".json", fullWay; // объявляются три строки
	// wayBase - основание адреса
	// fileExtension - расширение файла
	// fullWay - полный путь
	int fileNum = 1; // номер открываемого файла
	ifstream followLink; // объект followLink, с помощью которого будут открываться файлы по передаваемой обновляемой ссылке 
	fullWay = wayBase + to_string(fileNum) + fileExtension; // собирается полный путь (fileNum преобразуется из int в string)
	followLink.open(fullWay.c_str()); // открывается файл по собранному пути (fullWay переводится в символьный массив)
	while (followLink.is_open()) // пока открываются файлы по изменяемому пути 
	{
		followLink.close(); // закрыть открывшийся файл
		fileNum++; // увеличить номер файла
		fullWay = wayBase + to_string(fileNum) + fileExtension; // собрать новый путь к файлу
		followLink.open(fullWay.c_str()); // и открыть следующий файл
	}
	return (fileNum - 1);// возвращается количество существующих файлов
}

bool authorization(json& jsonData) // описание функции авторизации пользователя в системе
{
	int accsQuan = 0; // создается переменная для хранения количества зарегистрированных пользователей
	accsQuan = countAccs(); // задается значение (принимается возврат функции countAccs())

	string getName, getLogin, getPass; // создаются три строки для принятия имени, логина и пароля соответственно
	callInterface(100010); // вызов запроса на ввод логина
	getline(cin, getLogin); // ввод логина
	callInterface(100011);
	getline(cin, getName);
	callInterface(10002); // вызов запроса на ввод пароля
	getline(cin, getPass); // ввод пароля
	string wayBase = "..//accounts/", fileExtension = ".json", fullWay; // объявляются три строки
	// wayBase - основание адреса
	// fileExtension - расширение файла
	// fullWay - полный путь
	int fileNum = 1; // номер открываемого файла
	bool wrongInput = false; // индикатор неправильного ввода логина или пароля
	ifstream followLink; // объект ifstream для чтения файла
	string reader, fullContent; // две строки для чтения и записи информации из файла
	while (true)
	{
		if (wrongInput) // если 
		{
			wrongInput = false;
			callInterface(100010);
			getline(cin, getLogin);
			callInterface(100011);
			getline(cin, getName);
			callInterface(10002);
			getline(cin, getPass); 
		}
		fullWay = wayBase + to_string(fileNum) + fileExtension; // из компонентов собирается полный путь (fileNum преобразовывается из int в string)
		followLink.open(fullWay.c_str()); // по собранному полному пути открывается файл
		if (followLink.is_open()) // если файл удалось открыть
		{
			while (!followLink.eof()) // и пока не конец файла
			{
				getline(followLink, reader); // построчно считать файл
				fullContent += reader; // и записать в спец. буфер
			}
			jsonData = json::parse(fullContent); // после достижения конца файла произвести "десериализацию" - восстановление данных в формат json
		}
		fullContent = ""; // очистить буфер записи данных из файла
		followLink.close(); // закрыть файл
		if (jsonData["name"] == getName && jsonData["login"] == getLogin && jsonData["pass"] == getPass) // проверка на совпадение введеных и записанных в файл логина и пароля
		{
			callInterface(1001); // вывод оповещения об успешном завершении авторизации
			break; // завершение цикла
		}
		else // если имя, логин и пароль не совпадают 
		{
			fileNum++; // перейти к следующему файлу
			if (fileNum > accsQuan) // если порядковый номер файла больше чем количество зарегистрированных пользователей
			{
				callInterface(-101); // вывести оповещение об ошибке
				wrongInput = true; // изменить показание индикатора неправильного ввода логина или пароля
				fileNum = 1; // изменить номер файла на 1 (перейти в начало)
			}
		}
	}
	return 1; // вернуть true в результате успешной регистрации, т.к. пользователь теперь авторизован
}

bool checkAvail(string username) // описание функции проверки на зарегистрированный аккаунт
{
	int accsQuan = 0; // создается переменная для хранения количества зарегистрированных аккаунтов
	accsQuan = countAccs(); // инициализация переменной возвращаемым значением функции countAccs()
	string wayBase = "..//accounts/", fileExtension = ".json", fullWay; // объявляются три строки
	// wayBase - основание адреса
	// fileExtension - расширение файла
	// fullWay - полный путь
	int fileNum = 1; // номер открываемого файла
	ifstream followLink; // объект ifstream для чтения файла
	string reader, fullContent; // две строки для чтения и записи информации из файла
	json jsonData; // json-буфер для получения данных аккаунта
	while (true)
	{
		fullWay = wayBase + to_string(fileNum) + fileExtension; // из компонентов собирается полный путь
		followLink.open(fullWay.c_str()); // по собранному пути открывается файл
		if (followLink.is_open()) // если файл открылся
		{
			while (!followLink.eof()) // пока не достигнут конец файла
			{
				getline(followLink, reader); // построчно считать файл
				fullContent += reader; //  и записать строку в буфер
			}
			jsonData = json::parse(fullContent); // после полного прочтения произвести "десериализацию" данных
		}
		fullContent = ""; // очистить буфер записи инофрмации
		followLink.close(); // закрыть файл
		if (jsonData["name"] == username) // если логин из файла совпадает с введенным именем
		{
			callInterface(-103); // вывести оповещение об ошибке 
			return 0; // вернуть false
		}
		else
		{
			followLink.close(); // закрыть файл
			fileNum++; // увеличить номер файла (переключиться на следующий файл)
			if (fileNum > accsQuan) // если номер файла больше кол-ва зарегистрированных пользователей (достигнут и проверен последний файл)
			{
				return 1; // вернуть true, т.к. логин уникальный и совпадений не найдено
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
	// подмена контента
	// сборка структуры
	return;
}