#include <iostream>
#include <vector>
#include "UserManagement.h"

using namespace std;

int main() {
    vector<User> users;
    int choice;

    do {
        cout << "\n=== Welcome to MyFitnessPal ===\n";
        cout << "1. Log In\n";
        cout << "2. Sign Up\n";
        cout << "3. Close Application\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            logIn(users);
            break;
        case 2:
            signUp(users);
            break;
        case 3:
            closeApp();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
