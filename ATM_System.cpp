#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

// Structure to hold client information
typedef struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
} sClient;

// Enum to represent ATM menu options
enum AtmMenu
{
    Quick_Withdraw = 1,
    Normal_Withdraw = 2,
    Deposit = 3,
    Balance = 4,
    Logout = 5
};

// Function to prompt user to go back to the main menu
void backtomainmenu()
{
    cout << endl;
    cout << "Press any key to go back to main menu";
    cin.ignore();
    cin.get();
}

// Function to split a string by a delimiter
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

// Function to convert a line of data to a sClient structure
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

// Function to convert a sClient structure to a line of data
string ConvertsClientToLine(sClient C, string delim = "||")
{
    string DataLine = C.AccountNumber + delim + C.PinCode + delim + C.Name + delim + C.Phone + delim + to_string(C.AccountBalance);
    return DataLine;
}

// Function to load clients from a file into a vector
vector<sClient> LoadfiletoClientsV()
{
    vector<sClient> c;
    ifstream file;
    file.open("clients.txt");
    string DataLine;
    if (!file.is_open())
        cout << "Error: Unable to open file" << endl;
    else
    {
        while (getline(file, DataLine))
        {
            c.push_back(ConvertLineTosClient(DataLine));
        }
        file.close();
    }
    return c;
}

// Function to write clients from a vector to a file
void write_V_ClientsToFile(vector<sClient> &c)
{
    ofstream file;
    file.open("clients.txt");
    if (!file.is_open())
        cout << "Error: Unable to open file" << endl;

    else
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
}

// Function to deposit an amount into a client's account
void DepositAmount(sClient &client)
{
    double amount;
    char var;
    cout << "\nEnter the amount you want to deposit: ";
    cin >> amount;
    cout << "Are you sure you want perform this transaction?(y/n) ";
    cin >> var;
    if (var == 'y' || var == 'Y')
    {
        client.AccountBalance += amount;
        cout << "Done successfully, New balance is: " << client.AccountBalance;
    }
    else cout << "Transaction is cancelled";
    
}

// Function to withdraw an amount from a client's account
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
            cout << "Done successfully, New balance is: " << client.AccountBalance;
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

// Function to withdraw a specific amount from a client's account
void WithdrawAmount(sClient &client, double amount)
{
    if (client.AccountBalance >= amount)
    {
        client.AccountBalance -= amount;
        cout << "Done successfully, New balance is: " << client.AccountBalance;
    }
    else
    {
        cout << "The Amount exceeds your balance, take another choice." << endl;
        cout << "Press anykey to continue...";
        cin.ignore();
        cin.get();
    }
}

// Function to display the quick withdraw menu and handle quick withdraw transactions
void QuickWithdrawMenu(sClient &client)
{
    while (true)
    {
        system("cls");
        cout << "\n===== QUICK WITHDRAW MENU =====\n";
        cout << "1)20\t";
        cout << "2)50\n";
        cout << "3)100\t";
        cout << "4)200\n";
        cout << "5)400\t";
        cout << "6)600\n";
        cout << "7)800\t";
        cout << "8)1000\n";
        cout << "9) Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        double amounts[] = {20, 50, 100, 200, 400, 600, 800, 1000};

        if (choice >= 1 && choice <= 8)
        {
            WithdrawAmount(client, amounts[choice - 1]);
            backtomainmenu();
            return;
        }
        else if (choice == 9)
        {
            backtomainmenu();
            return;
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

// Function to show the balance of a client's account
void ShowBalance(const sClient &client)
{
    system("cls");
    cout << "==================================================================================" << endl;
    cout << setw(20) << "Balance Information\n";
    cout << "==================================================================================" << endl;
    cout << "Account Balance: " << fixed << setprecision(2) << client.AccountBalance << endl;
    backtomainmenu();
}

// Function to display the transaction menu and handle transactions
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
            QuickWithdrawMenu(client);
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
            DepositAmount(client);
            backtomainmenu();
            break;
        case AtmMenu::Balance:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Balance Selected.\n";
            cout << "==================================================================================" << endl;
            ShowBalance(client);
            break;
        case AtmMenu::Logout:
            backtomainmenu();
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

// Function to display the login screen and handle user login
void loginScreen()
{
    vector<sClient> clients;
    clients = LoadfiletoClientsV();
    sClient Client;
    bool found;
    while (true)
    {
        found = false;
        system("cls");
        cout << "==================================================================================" << endl;
        cout << setw(50) << right << "Login Page\n";
        cout << "==================================================================================" << endl;
        cout << "AccountNumber: ";
        cin >> Client.AccountNumber;
        cout << "PinCode: ";
        cin >> Client.PinCode;
        for (sClient &client : clients)
        {
            if (Client.AccountNumber == client.AccountNumber && Client.PinCode == client.PinCode)
            {
                found = true;
                TransactionMenu(client);
                write_V_ClientsToFile(clients);
                break;
            }
        }
        if (found == false)
        {
            cout << "Client not found or the password is wrong" << endl;
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
        }
    }
}

int main()
{
    loginScreen();
    return 0;
}
