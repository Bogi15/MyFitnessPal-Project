#include "UserManagement.h"
#include <iostream>
#include <fstream>

using namespace std;

string getCurrentDate() {
    
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", ltm);
    return string(date);

}

string generateDailyFilename(const string& username) {
    return "users/" + username + "_" + getCurrentDate() + ".txt";
}

void saveDailyData(const User& user) {
    string filename = "users/" + user.username + "_daily_" + getCurrentDate() + ".txt";
    ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << user.dailyCalorieGoal << endl;
        outFile << user.caloriesEaten << endl;
        if (user.accountType == "Premium") {
            outFile << user.proteinsEaten << endl;
            outFile << user.fatsEaten << endl;
            outFile << user.carbsEaten << endl;
        }
        outFile.close();
    }
}

void loadDailyData(User& user) {
    string filename = "users/" + user.username + "_daily_" + getCurrentDate() + ".txt";
    ifstream inFile(filename);

    if (inFile.is_open()) {
        inFile >> user.dailyCalorieGoal;
        inFile >> user.caloriesEaten;
        if (user.accountType == "Premium") {
            inFile >> user.proteinsEaten;
            inFile >> user.fatsEaten;
            inFile >> user.carbsEaten;
        }
        inFile.close();
    }
    else {
        cout << "Unable to open file to load daily data!" << endl;
    }
}


void dateLog(User& user, const string& date) {
    cout << "\n=== Daily Log for " << date << " ===\n";

    int totalCaloriesEaten = 0;
    int totalCaloriesBurned = 0;
    int totalCarbs = 0;
    int totalProtein = 0;
    int totalFats = 0;

    string mealsFilename = "users/" + user.username + "_meals_" + date + ".txt";
    ifstream mealsFile(mealsFilename);
    string line;

    if (mealsFile.is_open()) {
        cout << "\nMeals Consumed:\n";
        while (true) {
            string line;
            int id, calories, protein = 0, fats = 0, carbs = 0;
            string name;
              
            if(!getline(mealsFile, line))  break;
              
            id = convertIdToNumber(line);
            getline(mealsFile, name);
            mealsFile >> calories;

            if (user.accountType == "Premium") {
                mealsFile >> protein;
                mealsFile >> fats;
                mealsFile >> carbs;
            }
            mealsFile.ignore(numeric_limits<streamsize>::max(), '\n');

            totalCaloriesEaten += calories;
            totalCarbs += carbs;
            totalProtein += protein;
            totalFats += fats;

            cout << id << ". " << name << " - " << calories << " kcal";
            if (user.accountType == "Premium") {
                cout << ", " << protein << "g protein, " << fats << "g fats, " << carbs << "g carbs";
            }
            cout << "\n";
        }
        mealsFile.close();
    }
    else {
        cout << "No meals data found for " << date << endl << endl;
    }

    string workoutsFilename = "users/" + user.username + "_workouts_" + date + ".txt";
    ifstream workoutsFile(workoutsFilename);

    if (workoutsFile.is_open()) {
        cout << "\nWorkouts Performed:\n";
        while (true) {
            string line;
            int id, caloriesBurned;
            string name;


            if (!getline(workoutsFile, line)) break;

            id = convertIdToNumber(line);
            getline(workoutsFile, name);
            workoutsFile >> caloriesBurned;
            workoutsFile.ignore(numeric_limits<streamsize>::max(), '\n');

            totalCaloriesBurned += caloriesBurned;
            cout << id << ". " << name << " - " << caloriesBurned << " kcal burned\n";
        }
        workoutsFile.close();
    }
    else {
        cout << "No workouts data found for " << date << endl;
    }

    
    cout << "\nSummary:\n";
    cout << "Total Calories Consumed: " << totalCaloriesEaten << " kcal\n";
    cout << "Total Calories Burned: " << totalCaloriesBurned << " kcal\n";
    cout << "Net Calories: " << (totalCaloriesEaten - totalCaloriesBurned) << " kcal\n";
    if (user.accountType == "Premium") {
        cout << "Total Carbs Consumed: " << totalCarbs << " grams\n";
        cout << "Total Protein Consumed: " << totalProtein << " grams\n";
        cout << "Total Fats Consumed: " << totalFats << " grams\n";
    }
    cout << endl;
}

void loadDateLog( User& user) {
    string date;
    cout << "Enter the date (YYYY-MM-DD) for the log you want to view: ";
    cin >> date;
    dateLog(user, date);
}


void displayDailyIntake(User& user) {
    cout << "\n=== Display Daily Intake ===\n";
    cout << "Daily Calorie Goal: " << user.caloriesEaten << "/" << user.dailyCalorieGoal << " kcal" << endl;
    if (user.accountType == "Premium") {
        cout << "Daily Carbs Goal: " << user.carbsEaten << "/" << user.carbsGoal << " grams" << endl;
        cout << "Daily Protein Goal: " << user.proteinsEaten << "/" << user.proteinsGoal << " grams" << endl;
        cout << "Daily Fats Goal: " << user.fatsEaten << "/" << user.fatsGoal << " grams" << endl;
    }
}


void calculatingMacronutrients(User& user){
    int dailyCaloriesGoal = user.dailyCalorieGoal;
    string goal = user.goal;
    if (goal == "Lose weight") {
        user.carbsGoal = (0.35 * dailyCaloriesGoal) / 4;
        user.proteinsGoal = (0.35 * dailyCaloriesGoal)/4;
        user.fatsGoal = (0.30 * dailyCaloriesGoal) / 9;
    }
    else if (goal == "Keep weight") {
        user.carbsGoal = (0.45 * dailyCaloriesGoal) / 4;
        user.proteinsGoal = (0.25 * dailyCaloriesGoal) / 4;
        user.fatsGoal = (0.30 * dailyCaloriesGoal) / 9;
    }
    else {
        user.carbsGoal = (0.35 * dailyCaloriesGoal) / 4;
        user.proteinsGoal = (0.40 * dailyCaloriesGoal) / 4;
        user.fatsGoal = (0.25 * dailyCaloriesGoal) / 9;
    }
}

void viewDailyLog( User& user) {
    string choice;
    do {
        if (user.accountType == "Premium") calculatingMacronutrients(user);
        displayDailyIntake(user);

        cout << "\nWrite back to go back to the User Menu: ";
        cin >> choice;
    } while (choice != "back");
}

void addMeal(User& user) {
    Meal meal;
    meal.id = user.meals.size() + 1;
    cout << "Enter meal name: ";
    cin.ignore();
    getline(cin, meal.name);

    cout << "Enter calories: ";
    cin >> meal.calories;
    user.caloriesEaten += meal.calories;

    if (user.accountType == "Premium") {
        cout << "Enter protein (g): ";
        cin >> meal.proteins;
        user.proteinsEaten += meal.proteins;

        cout << "Enter fats (g): ";
        cin >> meal.fats;
        user.fatsEaten += meal.fats;

        cout << "Enter carbs (g): ";
        cin >> meal.carbs;
        user.carbsEaten += meal.carbs;
    }

    user.meals.push_back(meal);
    cout << "Meal added successfully!\n";

    
    string filename = "users/" + user.username + "_meals_" + getCurrentDate() + ".txt";
    ofstream outFile(filename, ios::app); 
    if (outFile.is_open()) {
        outFile << meal.id << endl;
        outFile << meal.name << endl;
        outFile << meal.calories << endl;

        if (user.accountType == "Premium") {
            outFile << meal.proteins << endl;
            outFile << meal.fats << endl;
            outFile << meal.carbs << endl;
        }
        
        outFile.close();
    }
    else {
        cout << "Unable to open file to append meal data!" << endl;
    }
}

void addWorkout(User& user) {
    Workout workout;
    workout.id = user.workouts.size() + 1;  
    cout << "Enter workout name: ";
    cin.ignore();
    getline(cin, workout.name);

    cout << "Enter calories burned: ";
    cin >> workout.caloriesBurned;
    user.dailyCalorieGoal += workout.caloriesBurned;

    user.workouts.push_back(workout);
    cout << "Workout added successfully!\n";

    string filename = "users/" + user.username + "_workouts_" + getCurrentDate() + ".txt";
    ofstream outFile(filename, ios::app); 
    if (outFile.is_open()) {
        outFile << workout.id << endl;
        outFile << workout.name << endl;
        outFile << workout.caloriesBurned << endl;
        outFile.close();
    }
    else {
        cout << "Unable to open file to append workout data!" << endl;
    }
}

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
