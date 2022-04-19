#include "MyFunctions.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

void worksheet1(string namedItem) {

    string answerHolder = ""; //Makes error trapping ints easier
    string name = ""; //Name of user

    bool accountExists = accounts(); //Checks if the account exists

    int answerChoice; //Answer to the menu prompts
    int boolToInt; //Manually sets value to 0 (true) or 1 (false) based on boolean

    cout << "✧ Student Information System ✧\n\nWhat would you like to do? Enter the number corresponding to your choice\n";

      accountExists = accounts();
    if(accountExists) {

      do {
        cout << "1) View student information\n2) Register a new student or edit an existing one\n3) Quit\n";
        getline(cin, answerHolder);
      } while (!digit(answerHolder) || stoi(answerHolder)> 3 || stoi(answerHolder) < 1);
      boolToInt = 0;
      answerChoice = stoi(answerHolder);

    } else {
      
      do {
        cout << "1) Register a new student\n2) Quit\n";
        getline(cin, answerHolder);
      } while (!digit(answerHolder) || stoi(answerHolder)> 3 || stoi(answerHolder) < 1);
      boolToInt = 1;
      answerChoice = stoi(answerHolder);

    }

    switch(boolToInt) {
      case 0: 
        if (answerChoice == 1) {
          viewInformation(); break;
        } else if (answerChoice == 2) {
          getInformation(); break;
        } else if (answerChoice == 3) {
          cout << "Thanks for coming!";
          exit(0);
        }
      case 1: 
        if (answerChoice == 1) {
          getInformation(); break;
        } else if (answerChoice == 2) {
          cout << "Thanks for coming!";
          exit(0);
        }
    }
}
