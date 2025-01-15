#include <iostream>
#include <vector>
#include "UserManagement.h"

using namespace std;

void mainMenu() {
    vector<User> users;
    int choice;

    do {
        cout << "\n=== Welcome to MyFitnessPal ===\n";
        cout << "1. Sign Up\n";
        cout << "2. Log In\n";
        cout << "3. Close Application\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            signUp(users);
            break;
        case 2:
            logIn(users);
            break;
        case 3:
            closeApp();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

int main() {
    mainMenu();
    return 0;
}
