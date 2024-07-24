# ATM-Machine-using-OOP

**INTRODUCTION:**
    This project simulates an ATM machine, enabling users to perform essential banking transactions such as checking balances, making withdrawals, and validating PINs. It demonstrates key object-oriented programming principles in C++.

**CODE EXPLANATION:**

**BANK ACCOUNT CLASS:**
  Manages individual bank accounts with the following functionalities:

  - **Balance Inquiry**: Allows users to check the current balance.
  - **Withdrawal**: Handles withdrawal requests and updates the account balance accordingly.
  - **Account Information**: Manages account numbers and provides account details for display.

**ATM CLASS:**
  Handles the core operations of the ATM, including:

- **Card Insertion**: Simulates the process of card insertion by the user.
- **PIN Validation**: Checks the entered PIN against stored data to authenticate users.
- **Transaction Handling**: Facilitates actions such as balance inquiry and withdrawals.
- **Logging**: Records transaction details in a log file for audit purposes.

**Helper Functions**
  Includes several utility functions:

  - **clear()**: Clears the terminal screen to enhance user experience.
  - **logTransaction()**: Logs transaction details with a timestamp to track activities.

**ERROR HANDLING:**
  Robust error handling mechanisms are implemented to manage:

  - **Invalid Withdrawal Amounts**: Prevents transactions with invalid amounts.
  - **Insufficient Funds**: Ensures that users have sufficient funds before allowing withdrawals.
  - **Incorrect PIN Entries**: Handles incorrect PIN entries, prompts for re-entry, and limits retry attempts.

**LOGGING**
  Transactions are recorded in a log file (transaction.log) with details such as:

  - **Transaction Type**: Type of transaction performed.
  - **Time of Transaction**: Timestamp of when the transaction occurred.

**USER INTERACTION:**
  Users interact with the ATM simulation through a command-line interface with the following steps:

  - **Card Insertion**: Users simulate card insertion.
  - **PIN Entry**: Users must enter a correct PIN to proceed with transactions.
  - **Transaction Choices**: After PIN validation, users can choose to check their balance, withdraw funds, or exit the program.

**FEATURES**

- **Bank Account Management**: Provides functionalities for managing balances and account information.
- **Secure Transactions**: Ensures secure access through PIN validation.
- **Cross-Platform Compatibility**: Designed to run on both Windows and Unix-like systems.
- **Transaction Logging**: Keeps a comprehensive log of all transactions for auditing and tracking purposes.

**USAGE**

- **Compile the Program:** Ensure you have a C++ compiler installed. Compile the source files to create the executable.
- **Launch the Application:** Execute the compiled executable to start the program.
- **Authenticate:** Enter the ATM PIN to access the main menu. The default PIN is 7654.
- **Choose a Transaction:** Select the desired transaction option from the menu (e.g., check balance, withdraw funds).
- **Follow Instructions:** Complete the transaction by following the on-screen prompts.
- **Exit:** Safely exit the application by choosing the exit option from the menu.
