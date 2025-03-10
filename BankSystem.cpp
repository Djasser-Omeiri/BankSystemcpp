#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;
enum UMenu
{
    eListUsers = 1,
    eAddUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenu = 6
};
enum TransMenu
{
    eDeposit = 1,
    eWithdraw = 2,
    ebalances = 3,
    eMenu = 4
};
enum Menu
{
    eShowClients = 1,
    eAddClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTranscations = 6,
    eUserMenu = 7,
    eLoginPage = 8
};
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
    bool permissions[7] = {false};
    bool MarkForDelete = false;
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
string ConvertsClientToLine(sClient &C, string delim = "||")
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
void PrintClientCard(sClient &Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}
void WriteClientToFile(sClient C)
{
    ofstream file;
    file.open("clients.txt", ios::app);
    if (!file.is_open())
        cout << "Error: Unable to open file" << endl;
    else
    {
        file << ConvertsClientToLine(C) << endl;
        file.close();
    }
}
void TWOcreateaclient(vector<sClient> &c)
{
    bool condition = false;
    do
    {
        WriteClientToFile(AddClient(c));
        c = LoadfiletoClientsV();
        cout << "Do you want to add another client? (1/0): ";
        cin >> condition;
    } while (condition);
}
vector<sClient> MarkForDeleteClient(vector<sClient> &c, string &AccountNumber)
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
        cout << "Client not found" << endl;

    return c;
}
void ThreeDeleteClient(vector<sClient> &c)
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
        cout << "Client not found" << endl;
    else
    {
        cout << "\nAre you sure you want to delete this client? (1/0): ";
        cin >> condition;
        if (condition)
        {
            c = MarkForDeleteClient(c, AccountNumber);
            write_V_ClientsToFile(c);
            cout << "Client deleted successfully" << endl;
        }
    }
}
void FourUpdateClient(vector<sClient> &c)
{
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
        write_V_ClientsToFile(c);
        cout << "Client updated successfully" << endl;
    }
    else
        cout << "Client not found" << endl;
}
void FiveFindClient(vector<sClient> &c)
{
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
        cout << "Client not found" << endl;
}
bool findclient(vector<sClient> &c, string &AccountNumber)
{
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
                cout << "\nYour New Balance is: " << s.AccountBalance << endl;
                break;
            }
        }
        write_V_ClientsToFile(c);
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
                    cout << "\nYour New Balance is: " << s.AccountBalance;
                }

                else
                    cout << "Insufficient funds" << endl;
                break;
            }
        }
        write_V_ClientsToFile(c);
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

// Function to display the transaction menu and handle transactions

void TransactionMenu(vector<sClient> &c)
{
    while (true)
    {
        c = LoadfiletoClientsV();
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
        case TransMenu::eDeposit:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Deposit selected.\n";
            cout << "==================================================================================" << endl;
            Deposit(c);
            backtomainmenu();
            break;
        case TransMenu::eWithdraw:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Withdraw selected.\n";
            cout << "==================================================================================" << endl;
            Withdraw(c);
            backtomainmenu();
            break;
        case TransMenu::ebalances:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(20) << "Total Balances selected.\n";
            cout << "==================================================================================" << endl;
            ShowAllBalances(c);
            backtomainmenu();
            break;
        case TransMenu::eMenu:
            system("cls");
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

// Function to calculate user permissions

// Function to calculate user permissions
void CountPermissionF(sUser &user)
{
    bool arr[7], per;
    user.permission = 0;
    cout << "Do you want to give full access? (1/0)\n";
    cin >> per;
    if (per)
    {
        user.permission = -1;
    }
    else
    {
        cout << "Do you want to give access to: \n";
        cout << "Show Clients list? (1/0) ";
        cin >> arr[0];
        cout << "Add New Clients? (1/0) ";
        cin >> arr[1];
        cout << "Delete Clients? (1/0) ";
        cin >> arr[2];
        cout << "Update Clients? (1/0) ";
        cin >> arr[3];
        cout << "Find Clients? (1/0) ";
        cin >> arr[4];
        cout << "Transactions? (1/0) ";
        cin >> arr[5];
        cout << "Manage Users? (1/0)";
        cin >> arr[6];
    }
    for (short i = 0; i < 7; i++)
    {
        if (arr[i])
        {
            user.permission += pow(2, i);
        }
    }
}

// Function to check user permissions

// Function to check user permissions
bool Permission(sUser user, short numberofoption)
{
    bool valid = false;
    if (user.permission == -1)
        return valid = true;
    for (short i = 6; i >= 0; i--)
    {
        if (user.permission >= pow(2, i))
        {
            user.permission -= pow(2, i);
            if (i + 1 == numberofoption)
                return valid = true;
        }
        if (user.permission == 0)
            break;
    }
    return valid;
}
sUser ConvertLineTosUser(string &DataLine, string delim = "||")
{
    sUser U;
    vector<string> vString = SplitString(DataLine, delim);
    U.Username = vString[0];
    U.password = vString[1];
    U.permission = stoi(vString[2]);
    return U;
}
string ConvertsUserToLine(sUser &U, string delim = "||")
{
    string DataLine = U.Username + delim + U.password + delim + to_string(U.permission);
    return DataLine;
}

// Function to load users from a file into a vector

// Function to load users from a file into a vector
vector<sUser> LoadfiletoUsersV()
{
    vector<sUser> u;
    ifstream file;
    file.open("users.txt");
    string DataLine;
    if (!file.is_open())
        cout << "Error: Unable to open file" << endl;
    else
    {
        while (getline(file, DataLine))
        {
            u.push_back(ConvertLineTosUser(DataLine));
        }
        file.close();
    }
    return u;
}

// Function to write users from a vector to a file

// Function to write users from a vector to a file
void write_V_UsersToFile(vector<sUser> &u)
{
    ofstream file;
    file.open("users.txt");
    if (!file.is_open())
        cout << "Error: Unable to open file" << endl;
    else
    {
        for (sUser &user : u)
        {
            if (!user.MarkForDelete)
            {
                file << ConvertsUserToLine(user) << endl;
            }
        }
        file.close();
    }
}
void ShowUsersList(vector<sUser> &u)
{
    cout << setw(40) << right << "Users List (" << u.size() << " users)" << endl;
    cout << "==================================================================================" << endl;
    cout << left << setw(20) << "|| Username"
         << left << setw(20) << "|| Password"
         << left << setw(20) << "|| Permission" << endl;
    cout << "==================================================================================" << endl;
    for (sUser &user : u)
    {
        if (!user.MarkForDelete)
        {
            cout << left << setw(20) << "|| " + user.Username
                 << left << setw(20) << "|| " + user.password
                 << left << setw(20) << "|| " + to_string(user.permission) << endl;
        }
    }
    cout << "==================================================================================" << endl;
}
sUser AddUser(vector<sUser> &u)
{
    sUser user;
    bool found;
    do
    {
        found = false;
        cout << "Enter Username: ";
        getline(cin >> ws, user.Username);
        for (sUser &userv : u)
        {
            if (userv.Username == user.Username)
            {
                cout << "Username already exists" << endl;
                found = true;
            }
        }
    } while (found);
    cout << "Enter Password: ";
    getline(cin, user.password);
    CountPermissionF(user);
    return user;
}
void PrintUserCard(sUser &user)
{
    cout << "\nThe following are the user details:\n";
    cout << "\nUsername: " << user.Username;
    cout << "\nPassword : " << user.password;
    cout << "\nPermission Number : " << user.permission;
}
void WriteUserToFile(sUser U)
{
    ofstream file;
    file.open("users.txt", ios::app);
    if (!file.is_open())
        cout << "Error: Unable to open file" << endl;
    else
    {
        file << ConvertsUserToLine(U) << endl;
        file.close();
    }
}
void CreateaUsers(vector<sUser> &u)
{
    bool condition = false;
    do
    {
        WriteUserToFile(AddUser(u));
        u = LoadfiletoUsersV();
        cout << "Do you want to add another user? (1/0): ";
        cin >> condition;
    } while (condition);
}
vector<sUser> MarkForDeleteUser(vector<sUser> &u, string &Username)
{
    bool found = false;
    for (sUser &user : u)
    {
        if (user.Username == Username)
        {
            user.MarkForDelete = true;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Client not found" << endl;

    return u;
}
void Deleteuser(vector<sUser> &u, sUser &user)
{
    u = LoadfiletoUsersV();
    bool condition, found = false;
    string Username;
    sUser TheUserWeWantToDelete;
    cout << "Enter the Username of the user you want to delete: ";
    cin >> Username;
    for (sUser &s : u)
    {
        if (Username == s.Username)
        {
            PrintUserCard(s);
            found = true;
            TheUserWeWantToDelete = s;
        }
    }
    if (!found)
        cout << "Client not found" << endl;

    else
    {
        if (user.permission != -1 && TheUserWeWantToDelete.permission == -1)
            cout << "\nYou do not have permission to delete this user\n";
        else
        {
            cout << "\nAre you sure you want to delete this user? (1/0): ";
            cin >> condition;
            if (condition)
            {
                u = MarkForDeleteUser(u, Username);
                write_V_UsersToFile(u);
                cout << "User deleted successfully" << endl;
            }
        }
    }
}
void UpdateUser(vector<sUser> &u)
{
    u = LoadfiletoUsersV();
    bool found = false;
    string Username;
    cout << "Enter the Username of the user you want to update: ";
    cin >> Username;
    for (sUser &s : u)
    {
        if (Username == s.Username)
        {
            PrintUserCard(s);
            found = true;
            break;
        }
    }
    if (found)
    {
        for (sUser &s : u)
        {
            if (Username == s.Username)
            {
                cout << "\nEnter the new Username: ";
                getline(cin >> ws, s.Username);
                cout << "Enter the new Password: ";
                getline(cin, s.password);
                CountPermissionF(s);
                break;
            }
        }
        write_V_UsersToFile(u);
        cout << "User updated successfully" << endl;
    }
    else
        cout << "User not found" << endl;
}
void FindUser(vector<sUser> &u)
{
    u = LoadfiletoUsersV();
    bool found = false;
    string Username;
    cout << "Enter the Username of the user you want to find: ";
    cin >> Username;
    for (sUser &s : u)
    {
        if (Username == s.Username)
        {
            PrintUserCard(s);
            found = true;
            break;
        }
    }
    if (!found)
        cout << "User not found" << endl;
}

void ManageMenuUser(vector<sUser> &u, sUser &user)
{
    while (true)
    {
        u = LoadfiletoUsersV();
        system("cls");

        cout << "\n===== Manage Users Menu Screen =====\n";
        cout << "1) List Users\n";
        cout << "2) Add New User\n";
        cout << "3) Delete User\n";
        cout << "4) Update User\n";
        cout << "5) Find User\n";
        cout << "6) Main Menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        switch (choice)
        {
        case UMenu::eListUsers:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "List users selected.\n";
            cout << "==================================================================================" << endl;
            ShowUsersList(u);
            backtomainmenu();
            break;
        case UMenu::eAddUser:
            system("cls");

            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Add User selected.\n";
            cout << "==================================================================================" << endl;
            CreateaUsers(u);
            backtomainmenu();
            break;
        case UMenu::eDeleteUser:
            system("cls");

            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Delete User selected.\n";
            cout << "==================================================================================" << endl;
            Deleteuser(u, user);
            backtomainmenu();
            break;
        case UMenu::eUpdateUser:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Update User selected.\n";
            cout << "==================================================================================" << endl;
            UpdateUser(u);
            backtomainmenu();
            break;
        case UMenu::eFindUser:
            system("cls");

            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Find User selected.\n";
            cout << "==================================================================================" << endl;
            FindUser(u);
            backtomainmenu();
            break;
        case UMenu::eMainMenu:
            backtomainmenu();
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
void NoPermissionText()
{
    cout << "==========================================================\n";
    cout << "You have no access to this option,please contact the admin\n";
    cout << "==========================================================\n";
}

// Function to display the main menu and handle client management

// Function to display the main menu and handle client management
void menu(vector<sUser> &u, sUser &user)
{
    vector<sClient> v;
    while (true)
    {
        v = LoadfiletoClientsV();
        u = LoadfiletoUsersV();
        system("cls");

        cout << "\n===== Client Management System =====\n";
        cout << "1) Show Clients\n";
        cout << "2) Add Client\n";
        cout << "3) Delete Client\n";
        cout << "4) Update Client\n";
        cout << "5) Find Client\n";
        cout << "6) Transaction Menu\n";
        cout << "7) Manage Users Menu\n";
        cout << "8) Login Page\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case Menu::eShowClients:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Show Clients selected.\n";
            cout << "==================================================================================" << endl;
            if (Permission(user, 1))
                ONEshowClientsList(v);
            else
                NoPermissionText();

            backtomainmenu();
            break;
        case Menu::eAddClient:
            system("cls");

            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Add Client selected.\n";
            cout << "==================================================================================" << endl;
            if (Permission(user, 2))
                TWOcreateaclient(v);
            else
                NoPermissionText();

            backtomainmenu();
            break;
        case Menu::eDeleteClient:
            system("cls");

            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Delete Client selected.\n";
            cout << "==================================================================================" << endl;
            if (Permission(user, 3))
                ThreeDeleteClient(v);
            else
                NoPermissionText();
            backtomainmenu();
            break;
        case Menu::eUpdateClient:
            system("cls");
            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Update Client selected.\n";
            cout << "==================================================================================" << endl;
            if (Permission(user, 4))
                FourUpdateClient(v);
            else
                NoPermissionText();

            backtomainmenu();
            break;
        case Menu::eFindClient:
            system("cls");

            cout << "==================================================================================" << endl;
            cout << setw(50) << right << "Find Client selected.\n";
            cout << "==================================================================================" << endl;
            if (Permission(user, 5))
                FiveFindClient(v);
            else
                NoPermissionText();
            backtomainmenu();
            break;
        case Menu::eTranscations:
            system("cls");
            if (Permission(user, 6))
                TransactionMenu(v);
            else
                NoPermissionText();
            backtomainmenu();
            break;
        case Menu::eUserMenu:
            system("cls");
            if (Permission(user, 7))
                ManageMenuUser(u, user);
            else
                NoPermissionText();
            backtomainmenu();
            break;
        case Menu::eLoginPage:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

// Function to display the login screen and handle user login
// Function to display the login screen and handle user login
void loginScreen()
{
    vector<sUser> u;
    bool found = false;
    u = LoadfiletoUsersV();
    sUser user;
    while (true)
    {
        system("cls");
        cout << "==================================================================================" << endl;
        cout << setw(50) << right << "Login Page\n";
        cout << "==================================================================================" << endl;
        cout << "Username: ";
        cin >> user.Username;
        cout << "Password: ";
        cin >> user.password;
        for (sUser &s : u)
        {
            if (user.Username == s.Username && user.password == s.password)
            {
                menu(u, s);
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "User not found\n";
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