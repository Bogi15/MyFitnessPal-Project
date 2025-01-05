#pragma once
#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <vector>
#include <string>

using namespace std;

struct Meal {
    string name;
    int calories;
};

struct Workout {
    string name;
    int calories;
};

struct DailyLog {
    string date;
    vector<Meal> meals;
    vector<Workout> workouts;
    int totalCaloriesConsumed = 0;
    int totalCalorisBurned = 0;
};

struct User {
    string username;
    string password;
    int age;
    string gender;
    double height; // in cm
    double weight; // in kg
    double BMR;
    string activityLevel;
    string goal;
    string accountType;
    int calorieDifferenceFromMaintenance = 0;
    int dailyCalorieGoal;
    vector<DailyLog> logs;
};


void signUp(vector<User>& users);
void logIn(const vector<User>& users);
void closeApp();
void addMeal(User& user);
void addWorkout(User& user);
void viewDailyLog(const User& user);
void updateUserInfo(User& user);
int calculateCalorieGoal(const User& user);

#endif 
