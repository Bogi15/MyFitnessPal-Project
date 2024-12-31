#pragma once
#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <vector>
#include <string>

using namespace std;


struct User {
    string username;
    string password;
    int age;
    string gender;
    double height; // in cm
    double weight; // in kg
    string activityLevel;
    string goal;
    string accountType;
};


void signUp(vector<User>& users);
void logIn(const vector<User>& users);
void closeApp();

#endif 
