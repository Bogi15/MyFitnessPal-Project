#include "UserManagement.h"
#include <iostream>
#include <fstream>

using namespace std;


void userMenu(User& user) {
    int choice;
    do {
        cout << "\n=== User Menu ===\n";
        cout << "1. Add Meal\n";
        cout << "2. Add Workout\n";
        cout << "3. View Daily Log\n";
        cout << "4. Update User Info\n";
        cout << "5. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: 
            addMeal(user); break;
        case 2: 
            //addWorkout(user); break;
        case 3: 
            viewDailyLog(user); break;
        case 4: 
            //updateUserInfo(user); break;
        case 5: 
            cout << "Logging out...\n"; break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}


int calculateCalorieGoal(const User& user) {
    return user.BMR + user.calorieDifferenceFromMaintenance;
}

double calculatingBMR(const User& user) {
    if (user.gender == "M") {
        return 88.362 + (13.397 * user.weight) + (4.799 * user.height) - (5.677 * user.age);
    }
    if (user.gender == "F") {
        return 447.593 + (9.247 * user.weight) + (3.098 * user.height) - (4.330 * user.age);
    }
}
    
void calculatingBMRWithActivityLevels(User& user) {
    if (user.activityLevel == "Seated work") user.BMR = user.BMR * 1.2;
    if (user.activityLevel == "Mild activity") user.BMR = user.BMR * 1.375;
    if (user.activityLevel == "Average activity") user.BMR = user.BMR * 1.55;
    if (user.activityLevel == "Active") user.BMR = user.BMR * 1.725;
    if (user.activityLevel == "Very active") user.BMR = user.BMR * 1.9;
}

void createUserFile(const User& newUser) {
    string filename = "users\\" + newUser.username + ".txt";
    ofstream userFile(filename);
    if (userFile.is_open()) {
        userFile << newUser.username << endl;
        userFile << newUser.password << endl;
        userFile << newUser.age << endl;
        userFile << newUser.gender << endl;
        userFile << newUser.height << " cm" << endl;
        userFile << newUser.weight << " kg" << endl;
        userFile << newUser.activityLevel << endl;
        userFile << newUser.goal << endl;
        userFile << newUser.calorieDifferenceFromMaintenance << " kcal" << endl;
        userFile << newUser.accountType << endl;
        userFile << newUser.BMR << endl;
        userFile << newUser.dailyCalorieGoal << endl;
        
        userFile.close();
        //dali da go izpisva - mislq che e izlishno
        // cout << "User data saved in " << filename << endl;
    }
    else {
        cout << "Unable to create file!" << endl;
    }
}


bool readUsernameAndPassword(const string& filename, string& username, string& password) {
    ifstream userFile(filename);
    if (!userFile.is_open()) {
        return false;
    }

    userFile >> username;
    userFile >> password;

    userFile.close();
    return true;
}


bool readFullUserFromFile(const string& filename, User& user) {
    ifstream userFile(filename);
    if (!userFile.is_open()) {
        return false;
    }

    getline(userFile, user.username);
    getline(userFile, user.password);
    userFile >> user.age;
    userFile.ignore(); 
    getline(userFile, user.gender);
    userFile >> user.height;
    userFile >> user.weight;
    userFile.ignore(); 
    getline(userFile, user.activityLevel);
    getline(userFile, user.goal);
    userFile >> user.calorieDifferenceFromMaintenance;
    userFile.ignore(); 
    getline(userFile, user.accountType);
    userFile >> user.BMR;
    userFile >> user.dailyCalorieGoal;

    userFile.close();
    return true;
}



void signUp(vector<User>& users) {
    User newUser;
    cout << "\n=== Sign Up ===\n";

    
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


    cout << "Enter age: ";
    while (!(cin >> newUser.age) || newUser.age <= 0) {
        cout << "Invalid input. Enter a valid age: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter gender (M/F): ";
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
    while (!(cin >> activityChoice) || activityChoice < 1 || activityChoice > 5) {
        cout << "Invalid choice. Select a number between 1 and 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (activityChoice) {
    case 1: newUser.activityLevel = "Seated work"; break;
    case 2: newUser.activityLevel = "Mild activity"; break;
    case 3: newUser.activityLevel = "Average activity"; break;
    case 4: newUser.activityLevel = "Active"; break;
    case 5: newUser.activityLevel = "Very active"; break;
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
        cout << "Select your weekly goal:\n";
        cout << "1. 0.25 kg per week\n";
        cout << "2. 0.50 kg per week\n";
        cout << "3. 0.75 kg per week\n";
        cout << "4. 1.00 kg per week\n";
        cout << "Enter your choice: ";
        int amountPerWeekChoiceLose;
        cin >> amountPerWeekChoiceLose;
        switch (amountPerWeekChoiceLose) {
        case 1: newUser.calorieDifferenceFromMaintenance = -275; break;
        case 2: newUser.calorieDifferenceFromMaintenance = -550; break;
        case 3: newUser.calorieDifferenceFromMaintenance = -825; break;
        case 4: newUser.calorieDifferenceFromMaintenance = -1100; break;
        default: 
            cout << "Invalid choice. Defaulting to 0.25 kg per week.\n";
            newUser.calorieDifferenceFromMaintenance = 275;
        }
        break;
    case 2: newUser.goal = "Keep weight"; break;
    case 3:
        newUser.goal = "Gain weight";

        cout << "Select your weekly goal:\n";
        cout << "1. 0.25 kg per week\n";
        cout << "2. 0.50 kg per week\n";
        cout << "3. 0.75 kg per week\n";
        cout << "4. 1.00 kg per week\n";
        cout << "Enter your choice: ";
        int amountPerWeekChoiceGain;
        cin >> amountPerWeekChoiceGain;
        switch (amountPerWeekChoiceGain) {
        case 1: newUser.calorieDifferenceFromMaintenance = 275; break;
        case 2: newUser.calorieDifferenceFromMaintenance = 550; break;
        case 3: newUser.calorieDifferenceFromMaintenance = 825; break;
        case 4: newUser.calorieDifferenceFromMaintenance = 1100; break;
        default:
            cout << "Invalid choice. Defaulting to 0.25 kg per week.\n";
            newUser.calorieDifferenceFromMaintenance = 275;
        }
        break;
    default:
        cout << "Invalid choice. Defaulting to 'Keep weight'.\n";
        newUser.goal = "Keep weight";
    }

    
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

    newUser.BMR = calculatingBMR(newUser);
    newUser.dailyCalorieGoal = calculateCalorieGoal(newUser);

    
    users.push_back(newUser);   
    cout << "Sign up successful! You can now log in.\n";

    createUserFile(newUser);
}

void logIn(const vector<User>& users) {
    string enteredUsername, enteredPassword;
    cout << "\n=== Log In ===\n";
    cout << "Enter username: ";
    cin >> enteredUsername;
    cout << "Enter password: ";
    cin >> enteredPassword;

    string filename = "users\\" + enteredUsername + ".txt";
    string storedUsername, storedPassword;

    // namirane na choveka - ?
    if (readUsernameAndPassword(filename, storedUsername, storedPassword)) {
        if (enteredPassword == storedPassword) {
            User user;
            if (readFullUserFromFile(filename, user)) {
                cout << "Login successful! Welcome, " << user.username << ".\n";
            }
            else {
                cout << "Failed to load user data. Please try again.\n";
            }
        }
        else {
            cout << "Invalid password. Try again.\n";
        }
    }
    else {
        cout << "User does not exist. Try again.\n";
    }
}

void closeApp() {
    cout << "Closing the application. Goodbye!\n";
}
