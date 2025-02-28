#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
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
typedef struct sUser
{
    string Username;
    string password;
    short permission;
} sUser;
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
sClient ConvertlinetoRecord(string DataLine, string delim = "||")
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
string ConvertRecordToLine(sClient C, string delim = "||")
{
    string DataLine = C.AccountNumber + delim + C.PinCode + delim + C.Name + delim + C.Phone + delim + to_string(C.AccountBalance);
    return DataLine;
}
vector<sClient> LoadfiletoVector()
{
    vector<sClient> c;
    ifstream file;
    file.open("clients.txt");
    string DataLine;
    if (file.is_open())
    {
        while (getline(file, DataLine))
        {
            c.push_back(ConvertlinetoRecord(DataLine));
        }
        file.close();
    }
    else
    {
        cout << "Error: Unable to open file" << endl;
    }
    return c;
}
void writeClientsToFile(vector<sClient> &c)
{
    ofstream file;
    file.open("clients.txt");
    if (file.is_open())
    {
        for (sClient &client : c)
        {
            if (!client.MarkForDelete)
            {
                file << ConvertRecordToLine(client) << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "Error: Unable to open file" << endl;
    }
}
void ONEshowClientsList(vector<sClient> &c)
{
    cout << setw(40) << right << "Clients List (" << c.size() << " clients)" << endl;
    cout << "==================================================================================" << endl;
    cout << left << setw(20) << "|| Account Number"
         << left << setw(20) << "|| Name"
         << left << setw(20) << "|| Phone"
         << left << setw(20) << "|| Account Balance" << endl;
    cout << "==================================================================================" << endl;
    for (sClient &client : c)
    {
        if (!client.MarkForDelete)
        {
            cout << left << setw(20) << "|| " + client.AccountNumber
                 << left << setw(20) << "|| " + client.Name
                 << left << setw(20) << "|| " + client.Phone
                 << left << setw(20) << "|| " + to_string(client.AccountBalance) << endl;
        }
    }
    cout << "==================================================================================" << endl;
}
sClient AddClient(vector<sClient> &c)
{
    sClient client;
    bool found;
    do
    {
        found = false;
        cout << "Enter Account Number: ";
        getline(cin >> ws, client.AccountNumber);
        for (sClient &clientv : c)
        {
            if (clientv.AccountNumber == client.AccountNumber)
            {
                cout << "Account Number already exists" << endl;
                found = true;
            }
        }
    } while (found);
    cout << "Enter Pin Code: ";
    getline(cin, client.PinCode);
    cout << "Enter Name: ";
    getline(cin, client.Name);
    cout << "Enter Phone: ";
    getline(cin, client.Phone);
    cout << "Enter the Account Balance: ";
    cin >> client.AccountBalance;
    return client;
}
void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}
void WriteTofile(sClient C)
{
    ofstream file;
    file.open("clients.txt", ios::app);
    if (file.is_open())
    {
        file << ConvertRecordToLine(C) << endl;
        file.close();
    }
    else
    {
        cout << "Error: Unable to open file" << endl;
    }
}
void TWOcreateaclient(vector<sClient> &c)
{
    bool condition = false;
    do
    {
        WriteTofile(AddClient(c));
        c = LoadfiletoVector();
        cout << "Do you want to add another client? (1/0): ";
        cin >> condition;
    } while (condition);
}
vector<sClient> MarkForDeleteClient(vector<sClient> &c, string AccountNumber)
{
    bool found = false;
    for (sClient &client : c)
    {
        if (client.AccountNumber == AccountNumber)
        {
            client.MarkForDelete = true;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Client not found" << endl;
    }
    return c;
}
void deleteclient(vector<sClient> &c)
{
    bool condition, found = false;
    string AccountNumber;
    cout << "Enter the Account Number of the client you want to delete: ";
    cin >> AccountNumber;
    for (sClient &s : c)
    {
        if (AccountNumber == s.AccountNumber)
        {
            PrintClientCard(s);
            found = true;
        }
    }
    if (!found)
    {
        cout << "Client not found" << endl;
    }
    else
    {
        cout << "\nAre you sure you want to delete this client? (1/0): ";
        cin >> condition;
        if (condition)
        {
            c = MarkForDeleteClient(c, AccountNumber);
            writeClientsToFile(c);
            cout << "Client deleted successfully" << endl;
        }
    }
}
void ThreeDeleteClient(vector<sClient> &c)
{
    c = LoadfiletoVector();
    deleteclient(c);
}
void FourUpdateClient(vector<sClient> &c)
{
    c = LoadfiletoVector();
    bool found = false;
    string AccountNumber;
    cout << "Enter the Account Number of the client you want to update: ";
    cin >> AccountNumber;
    for (sClient &s : c)
    {
        if (AccountNumber == s.AccountNumber)
        {
            PrintClientCard(s);
            found = true;
            break;
        }
    }
    if (found)
    {
        for (sClient &s : c)
        {
            if (AccountNumber == s.AccountNumber)
            {
                cout << "\nEnter the new Pin Code: ";
                getline(cin >> ws, s.PinCode);
                cout << "Enter the new Name: ";
                getline(cin, s.Name);
                cout << "Enter the new Phone: ";
                getline(cin, s.Phone);
                cout << "Enter the new Account Balance: ";
                cin >> s.AccountBalance;
                break;
            }
        }
        writeClientsToFile(c);
        cout << "Client updated successfully" << endl;
    }
    else
    {
        cout << "Client not found" << endl;
    }
}
void FiveFindClient(vector<sClient> &c)
{
    c = LoadfiletoVector();
    bool found = false;
    string AccountNumber;
    cout << "Enter the Account Number of the client you want to find: ";
    cin >> AccountNumber;
    for (sClient &s : c)
    {
        if (AccountNumber == s.AccountNumber)
        {
            PrintClientCard(s);
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Client not found" << endl;
    }
}
bool findclient(vector<sClient> &c, string &AccountNumber)
{
    c = LoadfiletoVector();
    cout << "Enter the Account Number of the client you want to find: ";
    cin >> AccountNumber;
    for (sClient &s : c)
    {
        if (AccountNumber == s.AccountNumber)
        {
            PrintClientCard(s);
            return true;
        }
    }
    cout << "Client not found" << endl;
    return false;
}

void Deposit(vector<sClient> &c)
{
    string AccountNumber;
    double amount;
    if (findclient(c, AccountNumber))
    {
        cout << "\nEnter the amount you want to deposit: ";
        cin >> amount;
        for (sClient &s : c)
        {
            if (AccountNumber == s.AccountNumber)
            {
                s.AccountBalance += amount;
                break;
            }
        }
        writeClientsToFile(c);
    }
}
void Withdraw(vector<sClient> &c)
{
    string AccountNumber;
    double amount;
    if (findclient(c, AccountNumber))
    {
        cout << "\nEnter the amount you want to withdraw: ";
        cin >> amount;
        for (sClient &s : c)
        {
            if (AccountNumber == s.AccountNumber)
            {
                if (s.AccountBalance >= amount)
                {
                    s.AccountBalance -= amount;
                }
                else
                {
                    cout << "Insufficient funds" << endl;
                }
                break;
            }
        }
        writeClientsToFile(c);
    }
}
void ShowAllBalances(vector<sClient> &c)
{
    cout << setw(50) << "Total Balances" << endl;
    cout << "==================================================================================" << endl;
    cout << left << setw(15) << "||AccountNumber" 
         << left << setw(20) << "||Name" 
         << left << setw(15) << "||AccountBalance" << endl;
    cout << "==================================================================================" << endl;
    for (sClient &client : c)
    {
        cout << left << setw(15) << "||" + client.AccountNumber 
             << left << setw(20) << "||" + client.Name 
             << left << setw(15) << "||" + to_string(client.AccountBalance) << endl;
    }
}
void TransactionMenu(vector<sClient> &c)
{
    while (true)
    {
        c = LoadfiletoVector();
        system("cls");
        cout << "\n===== Transaction Menu =====\n";
        cout << "1) Deposit\n";
        cout << "2) Withdraw\n";
        cout << "3) Total Balances\n";
        cout << "4) Back to Main Menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Deposit selected.\n";
            cout << "==================================================================================" << endl;
            Deposit(c);
            backtomainmenu();
            break;
        case 2:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Withdraw selected.\n";
            cout << "==================================================================================" << endl;
            Withdraw(c);
            backtomainmenu();
            break;
        case 3:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Total Balances selected.\n";
            cout << "==================================================================================" << endl;
            ShowAllBalances(c);
            backtomainmenu();
            break;
        case 4:
            system("cls");
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
void menu()
{
    vector<sClient> v;
    while (true)
    {
        v = LoadfiletoVector();
        system("cls");
        cout << "\n===== Client Management System =====\n";
        cout << "1) Show Clients\n";
        cout << "2) Add Client\n";
        cout << "3) Delete Client\n";
        cout << "4) Update Client\n";
        cout << "5) Find Client\n";
        cout << "6) Transaction Menu\n";
        cout << "7) Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Show Clients selected.\n";
            cout << "==================================================================================" << endl;
            ONEshowClientsList(v);
            backtomainmenu();
            break;
        case 2:
            system("cls");

            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Add Client selected.\n";
            cout << "==================================================================================" << endl;
            TWOcreateaclient(v);
            backtomainmenu();
            break;
        case 3:
            system("cls");

            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Delete Client selected.\n";
            cout << "==================================================================================" << endl;
            ThreeDeleteClient(v);
            backtomainmenu();
            break;
        case 4:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Update Client selected.\n";
            cout << "==================================================================================" << endl;
            FourUpdateClient(v);
            backtomainmenu();
            break;
        case 5:
            system("cls");

            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Find Client selected.\n";
            cout << "==================================================================================" << endl;
            FiveFindClient(v);
            backtomainmenu();
            break;
        case 6:
            system("cls");
            TransactionMenu(v);
            break;
        case 7:
            cout << "Exiting program...\n";
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
int main()
{
    menu();
    return 0;
}