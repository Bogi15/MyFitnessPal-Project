#include <iostream>
#include <vector>
#include "UserManagement.h"

using namespace std;

//void userMenu(User& user) {
//    int choice;
//    do {
//        cout << "\n=== User Menu ===\n";
//        cout << "1. Add Meal\n";
//        cout << "2. Add Workout\n";
//        cout << "3. View Daily Log\n";
//        cout << "4. Update User Info\n";
//        cout << "5. Log Out\n";
//        cout << "Enter your choice: ";
//        cin >> choice;
//        switch (choice) {
//        case 1: 
//            addMeal(user); break;
//        case 2: 
//            addWorkout(user); break;
//        case 3: 
//            viewDailyLog(user); break;
//        case 4: 
//            updateUserInfo(user); break;
//        case 5: 
//            cout << "Logging out...\n"; break;
//        default:
//            cout << "Invalid choice. Please try again.\n";
//        }
//    } while (choice != 5);
//}


void displayUserMenu() {
    cout << "\n=== User Menu ===\n";
    cout << "1. Add Meal with Calories\n";
    cout << "2. Add Workout with Calories Burned\n";
    cout << "3. View Daily Calorie Intake\n";
    cout << "4. View Previous Days\n";
    cout << "5. Edit Meal or Workout for Today\n";
    cout << "6. Delete Data for a Day\n";
    cout << "7. Update Calorie Goal (Gain/Lose Weight)\n";
    cout << "8. Logout\n";
    cout << "Enter your choice: ";
}


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
