#include "UserManagement.h"
#include <iostream>


void signUp(vector<User>& users) {
    User newUser;
    cout << "\n=== Sign Up ===\n";

    // Username and Password
    cout << "Enter username: ";
    cin >> newUser.username;

    for (const auto& user : users) {
        if (user.username == newUser.username) {
            cout << "Username already exists. Try a different one.\n";
            return;
        }
    }

    cout << "Enter password: ";
    cin >> newUser.password;

    // Age, Gender, Height, Weight
    cout << "Enter age: ";
    cin >> newUser.age;

    cout << "Enter gender (Male/Female/Other): ";
    cin >> newUser.gender;

    cout << "Enter height (in cm): ";
    cin >> newUser.height;

    cout << "Enter weight (in kg): ";
    cin >> newUser.weight;

    // Activity Level
    cout << "Select your activity level:\n";
    cout << "1. Seated work\n";
    cout << "2. Mild activity\n";
    cout << "3. Average activity\n";
    cout << "4. Active\n";
    cout << "5. Very active\n";
    cout << "Enter your choice: ";
    int activityChoice;
    cin >> activityChoice;

    switch (activityChoice) {
    case 1:
        newUser.activityLevel = "Seated work";
        break;
    case 2:
        newUser.activityLevel = "Mild activity";
        break;
    case 3:
        newUser.activityLevel = "Average activity";
        break;
    case 4:
        newUser.activityLevel = "Active";
        break;
    case 5:
        newUser.activityLevel = "Very active";
        break;
    default:
        cout << "Invalid choice. Defaulting to 'Seated work'.\n";
        newUser.activityLevel = "Seated work";
    }

    // Goal
    cout << "Select your goal:\n";
    cout << "1. Lose weight\n";
    cout << "2. Keep weight\n";
    cout << "3. Gain weight\n";
    cout << "Enter your choice: ";
    int goalChoice;
    cin >> goalChoice;

    switch (goalChoice) {
    case 1:
        newUser.goal = "Lose weight";
        break;
    case 2:
        newUser.goal = "Keep weight";
        break;
    case 3:
        newUser.goal = "Gain weight";
        break;
    default:
        cout << "Invalid choice. Defaulting to 'Keep weight'.\n";
        newUser.goal = "Keep weight";
    }

    // Account Type
    cout << "Select account type:\n";
    cout << "1. Standard\n";
    cout << "2. Premium\n";
    cout << "Enter your choice: ";
    int accountChoice;
    cin >> accountChoice;

    switch (accountChoice) {
    case 1:
        newUser.accountType = "Standard";
        break;
    case 2:
        newUser.accountType = "Premium";
        break;
    default:
        cout << "Invalid choice. Defaulting to 'Standard'.\n";
        newUser.accountType = "Standard";
    }

    // Save the user
    users.push_back(newUser);
    cout << "Sign up successful! You can now log in.\n";
}

void logIn(const vector<User>& users) {
    string username, password;
    cout << "\n=== Log In ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Find the user
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            cout << "Welcome, " << username << "!\n";
            return;
        }
    }

    cout << "Invalid username or password. Please try again.\n";
}

void closeApp() {
    cout << "Closing the application. Goodbye!\n";
}
