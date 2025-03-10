# Bank System in C++

This project is a console-based banking system developed in C++ that simulates various banking operations, including account management, permission-based user roles, and ATM interactions.

## Features

### BankSystem.cpp
- **Create User**: Allows the admin to create users with different levels of permissions.
  - **Admin**: Full control over the system.
  - **Users**: Bank employees with specific permissions assigned by the admin.
- **Create Client**: Clients can open accounts with basic banking services.
- **Menu Options**:

#### Main Menu:
  - Show Clients
  - Add Client
  - Delete Client
  - Update Client Information
  - Find Client
  - Transactions Menu
  - User Menu
  - Login Page

#### User Menu:
  - List Users
  - Add User
  - Delete User
  - Update User
  - Find User
  - Return to Main Menu

#### Transactions Menu:
  - Deposit
  - Withdraw
  - Check Balances
  - Return to Main Menu

- **Permission Validation**: When a user selects a menu option, the system checks if they have the necessary permissions to access that feature. If they do, access is granted; otherwise, a message will prompt them to contact the admin.

### ATM_System.cpp
- **PIN Verification**: Secure PIN-based user authentication.
- **Transaction Handling**: Process ATM-based deposits, withdrawals, and balance checks.

## Usage

1. **Clone the Repository**
```bash
git clone https://github.com/Djasser-Omeiri/BankSystemcpp.git
cd BankSystemcpp
```

2. **Compile the Code**
```bash
g++ BankSystem.cpp -o BankSystem
g++ ATM_System.cpp -o ATMSystem
```

3. **Run the Executables**
```bash
./BankSystem
./ATMSystem
```

## Project Structure
```
BankSystemcpp/
├── BankSystem.cpp    # Main banking operations
├── ATM_System.cpp    # ATM-related functionality
└── .vscode/          # VSCode configuration (optional)
```

## Dependencies
- C++ Compiler (e.g., g++)
- Compatible with major OS (Linux, Windows, macOS)

## Contributions
Feel free to submit issues or pull requests to enhance the system.

## License
This project is licensed under the MIT License.

