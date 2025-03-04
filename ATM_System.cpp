#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;
typedef struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
} sClient;
enum AtmMenu
{
    Quick_Withdraw = 1,
    Normal_Withdraw = 2,
    Deposit = 3,
    Balance = 4,
    Logout = 5
};
void backtomainmenu()
{
    cout << endl;
    cout << "Press any key to go back to main menu";
    cin.ignore();
    cin.get();
}
vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}
sClient ConvertLineTosClient(string DataLine, string delim = "||")
{
    sClient C;
    vector<string> vString = SplitString(DataLine, delim);
    C.AccountNumber = vString[0];
    C.PinCode = vString[1];
    C.Name = vString[2];
    C.Phone = vString[3];
    C.AccountBalance = stod(vString[4]);
    return C;
}
string ConvertsClientToLine(sClient C, string delim = "||")
{
    string DataLine = C.AccountNumber + delim + C.PinCode + delim + C.Name + delim + C.Phone + delim + to_string(C.AccountBalance);
    return DataLine;
}
vector<sClient> LoadfiletoClientsV()
{
    vector<sClient> c;
    ifstream file;
    file.open("clients.txt");
    string DataLine;
    if (file.is_open())
    {
        while (getline(file, DataLine))
        {
            c.push_back(ConvertLineTosClient(DataLine));
        }
        file.close();
    }
    else
    {
        cout << "Error: Unable to open file" << endl;
    }
    return c;
}
void write_V_ClientsToFile(vector<sClient> &c)
{
    ofstream file;
    file.open("clients.txt");
    if (file.is_open())
    {
        for (sClient &client : c)
        {
            if (!client.MarkForDelete)
            {
                file << ConvertsClientToLine(client) << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "Error: Unable to open file" << endl;
    }
}

void Deposit(sClient &client)
{
    double amount;
    cout << "\nEnter the amount you want to deposit: ";
    cin >> amount;
    client.AccountBalance += amount;
}
void Withdraw(sClient &client)
{
    double amount;
    bool valid = false;
    do
    {
        do
        {
            cout << "\nEnter an amount multiple of 5's : ";
            cin >> amount;
        } while (static_cast<int>(amount) % 5 != 0);

        if (client.AccountBalance >= amount)
        {
            client.AccountBalance -= amount;
            valid = true;
        }
        else
        {
            cout << "The Amount exceeds your balance, take another choice." << endl;
            cout << "Press anykey to continue...";
            cin.ignore();
            cin.get();
        }
    } while (valid == false);
}
void WithdrawAmount(sClient &client, double amount)
{
    bool valid = false;
    if (client.AccountBalance >= amount)
    {
        client.AccountBalance -= amount;
        valid = true;
    }
    else
    {
        cout << "The Amount exceeds your balance, take another choice." << endl;
        cout << "Press anykey to continue...";
        cin.ignore();
        cin.get();
    }
}
void TransactionMenu(sClient &client)
{
    while (true)
    {
        system("cls");
        cout << "\n===== ATM MAIN MENU SCREEN =====\n";
        cout << "1) Quick Withdraw\n";
        cout << "2) Normal Withdraw\n";
        cout << "3) Deposit \n";
        cout << "4) Show Balance\n";
        cout << "5) Logout\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case AtmMenu::Quick_Withdraw:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Quick Withdraw Selected.\n";
            cout << "==================================================================================" << endl;
            Withdraw(clie);
            backtomainmenu();
            break;
        case AtmMenu::Normal_Withdraw:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Normal Withdraw Selected.\n";
            cout << "==================================================================================" << endl;
            Withdraw(client);
            backtomainmenu();
            break;
        case AtmMenu::Deposit:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Deposit Selected.\n";
            cout << "==================================================================================" << endl;
            backtomainmenu();
            break;
        case AtmMenu::Balance:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Balance Selected.\n";
            cout << "==================================================================================" << endl;
            break;
        case AtmMenu::Logout:
            system("cls");
            backtomainmenu();
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
void loginScreen()
{
    vector<sClient> clients;
    clients = LoadfiletoClientsV();
    sClient Client;
    while (true)
    {
        system("cls");
        cout << "==================================================================================" << endl;
        cout << setw(50) << right << "Login Page\n";
        cout << "==================================================================================" << endl;
        cout << "AccountNumber ";
        cin >> Client.AccountNumber;
        cout << "PinCode: ";
        cin >> Client.PinCode;
        for (sClient &client : clients)
        {
            if (Client.AccountNumber == client.AccountNumber && Client.PinCode == client.PinCode)
            {
                TransactionMenu(client);
                write_V_ClientsToFile(clients);
                break;
            }
        }
        cout << "Client not found or the password is wrong" << endl;
        cin.ignore();
        cin.get();
    }
}
