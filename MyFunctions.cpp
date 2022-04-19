#include "MyFunctions.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

bool accounts() {
  ifstream students;
  students.open("Names.txt");

  string c = "";
  getline(students, c);
  if (c.length() > 0) {
    students.close();
    return true;
  }
  return false;
}

void getInformation() {
  bool foundAccount= false;
  
  string firstName = "";
  string lastName = "";
  string answerHolder;
  string guidanceCounselor;
  string lines;
  string contact;
  string eContact;
  
  int grade;
  int year;
  int numberOfClasses;
  int numberOfAssignments;
  int accountLine = 0;
  
  double avg;
  double sum;

  vector<double> credits;
  vector<string> classes;
  vector<string> copyFile = {};
  vector<double> GPAs = {};

  cout << "\nEnter student's first name (case sensitive!): ";
  getline(cin, firstName);

  cout << "\nEnter student's last name (case sensitive!): ";
  getline(cin, lastName);

  do {
    cout << "\nWhat grade is " << firstName << " in (Enter a number 1-12)? ";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (digit(answerHolder)) {
      if (stoi(answerHolder) > 12 || stoi(answerHolder) < 1) {
      cout << "\nInvalid grade.";
      answerHolder = "a";
      }
    }
  } while(!digit(answerHolder));
  grade = stoi(answerHolder);

  do {
    cout << "\nWhat year was " << firstName << " enrolled? ";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (digit(answerHolder)) {
      if (stoi(answerHolder) > 2022 || stoi(answerHolder) < 1990) {
      cout << "\nInvalid year of enrollment.";
      answerHolder = "a";
      }
    }
  } while(!digit(answerHolder));
  year = stoi(answerHolder);

  
  do {
    cout << "\nHow many classes does " << firstName << " take (Minimum 5, maximum 10)? ";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (digit(answerHolder)) {
      if (stoi(answerHolder) > 10 || stoi(answerHolder) < 2) {
      cout << "\nInvalid amount of classes.";
      answerHolder = "a";
      }
    }
  } while(!digit(answerHolder));
  numberOfClasses = stoi(answerHolder);

  classes.resize(numberOfClasses);  

  for (int i = 0; i < classes.size(); i++) {
    cout << "\nEnter " << firstName << "'s class #" << i + 1 << ": ";
    getline(cin, answerHolder);
    
    if (answerHolder == "" || answerHolder == " ") {
      i--;
    } else {
      classes[i] = answerHolder;
      classes[i].append(".");
      credits.push_back(getCredits());
      classes[i].append(to_string(credits[credits.size()-1]));
      classes[i].append("|");

      // START OF ASSIGNMENTS

      do {
        cout << "\nEnter the number of assignments for this class: ";
        getline(cin, answerHolder);
        if (answerHolder.length() == 0) {
            answerHolder = "a";
        }
        if (digit(answerHolder)) {
          if (stoi(answerHolder) < 0) {
          cout << "\nInvalid amount of assignments.";
          answerHolder = "a";
          }
        }
      } while(!digit(answerHolder));
      numberOfAssignments = stoi(answerHolder);

      for (int j = 0; j < numberOfAssignments; j++) {
        if (numberOfAssignments == 0) {
          break;
        }
        cout << "\nEnter assignment #" << j + 1 << ": ";
        getline(cin, answerHolder);
        if (answerHolder.length() == 0) {
          cout << "\nNo assignment entered.";
            j--;
        } else {
          classes[i].append(answerHolder);
          classes[i].append(",");
          classes[i].append(to_string(getGrade()) + "|");
        }
      }

      // END OF ASSIGNMENTS
    }
  }

  for (int i = 0; i < classes.size(); i++) {
    GPAs.push_back(getAvg(classes, i, credits[i]));
  }

  for (int i = 0; i < GPAs.size(); i++) {
    sum+= GPAs[i];
  }
  avg = (sum / GPAs.size());
  
  cout << "\nPlease enter " << firstName << "'s guidance councelor: ";
  getline(cin, guidanceCounselor);

  do {
    cout << "\nPlease enter a contact number for the parent or guardian of " << firstName << " (Including country code, max 12 digits, do not include spaces or hyphens): ";
    getline(cin, answerHolder);
    if (answerHolder.length() > 12) {
      answerHolder = "a";
    }
    if (answerHolder.length() < 10) {
      answerHolder = "a";
    }
  } while(!digit(answerHolder));
  contact = answerHolder;

  do {
    cout << "\nPlease enter an emergency contact number for " << firstName << " (Including country code, max 12 digits, do not include spaces or hyphens): ";
    getline(cin, answerHolder);
    if (answerHolder.length() > 12) {
      answerHolder = "a";
    }
    if (answerHolder.length() < 10) {
      answerHolder = "a";
    }
  } while(!digit(answerHolder));
  eContact = answerHolder;

  // Write to file
  string thisfilename = firstName + lastName + ".txt";
  
  std::ofstream ofs;
  ofs.open(thisfilename, std::ofstream::out | std::ofstream::trunc);
  ofs.close();
  
  fstream student;
  student.open (thisfilename);
  student << "Name: " << firstName << " " << lastName << endl;
  student << "Grade: " << grade << endl;
  student << "Year: " << year << endl;
  student << "Classes (Class.credits): " << endl;
  for(int i = 0; i < classes.size(); i++) {
    student << "\t" << classes[i].substr(0, classes[i].find("|")) << endl;
    vector<string> grades{};
    string delimiter = "|";

    student << "\t\tAssignments (Class,grade):\n";
      
    size_t pos;
    while ((pos = classes[i].find("|")) != string::npos) {
      grades.push_back(classes[i].substr(0, pos));
      classes[i].erase(0, pos + delimiter.length());
    }

    for (int j = 1; j < grades.size(); j++) {
      student << "\t\t" << grades[j] << endl;
    }
  }
  student << "\nGPA: " << setprecision(2) << avg << endl;
  student << "Guidance Councelor: " << guidanceCounselor << endl;
  student << "Contact Number: " << contact << endl;
  student << "Emergency Contact: " << eContact << endl;
  student.close();

  ifstream copier("Names.txt");
    if (copier.is_open()) {
      while (getline(copier, lines)) {
        copyFile.push_back(lines);
      }
      copier.close();
  }
  
  for (int i = 0; i < copyFile.size(); i++) {
  string fl = firstName + " " + lastName;
    if (copyFile[i] == fl) {
      foundAccount = true;
      break;
    } else {
      foundAccount = false;
    }
  }

  if (!foundAccount) {
    student.open("Names.txt", ios::app);
    student << endl << firstName << " " << lastName;
    student.close();
  }
}

bool digit(string a) {
  for (int i = 0; i < a.length(); i++) {
    if (!isdigit(a[i]) && to_string(a[i]) != "46") {
      return false;
      break;
    }
  }
  return true;
}

int getCredits() {
  int returnthis;
  string answerHolder = "";

  do {
    cout << "\nEnter the number of credits for this class (1-4): ";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (digit(answerHolder)) {
      if (stoi(answerHolder) > 4 || stoi(answerHolder) < 1) {
      cout << "\nInvalid amount of credits.";
      answerHolder = "a";
      }
    }
  } while(!digit(answerHolder));
  returnthis = stoi(answerHolder);

  return returnthis;
}

int getGrade() {
  int returnthis;
  string answerHolder = "";

  do {
    cout << "\nEnter the grade received for this assignment: ";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (digit(answerHolder)) {
      if (stoi(answerHolder) > 105 || stoi(answerHolder) < 1) {
      cout << "\nInvalid grade.";
      answerHolder = "a";
      }
    }
  } while(!digit(answerHolder));
  returnthis = stoi(answerHolder);

  return returnthis;
}

double getAvg(vector<string> classes, int whichClass, int max) {
  double sum = 0;
  double returnthis = 0;
  int count = 0;

  max = 4 - max;
  string delimiter = "|";
  vector<string> grades{};

  size_t pos;
  while ((pos = classes[whichClass].find(delimiter)) != string::npos) {
      grades.push_back(classes[whichClass].substr(0, pos));
      classes[whichClass].erase(0, pos + delimiter.length());
  }
  
  for (int i = 1; i < grades.size(); i++) {
    sum += stod(grades[i].substr(grades[i].find(",")+1, grades[i].length()-1));
    count++;
  }
  int thinga = sum / count;

  if(thinga > 94) {
    if(4.00 - max <= 0) {return 0;} return 4.00 - max;
  } else if(thinga > 90) {
    if(3.67 - max <= 0) {return 0;} return 3.67 - max;
  } else if(thinga > 87) {
    if(3.33 - max <= 0) {return 0;} return 3.33 - max;
  } else if(thinga > 83) {
    if(3.00 - max <= 0) {return 0;} return 3.00 - max;
  } else if(thinga > 80) {
    if(2.67 - max <= 0) {return 0;} return 2.67 - max;
  } else if(thinga > 77) {
    if(2.33 - max <= 0) {return 0;} return 2.33 - max;
  } else if(thinga > 73) {
    if(2.00 - max <= 0) {return 0;} return 2.00 - max;
  } else if(thinga > 70) {
    if(1.33 - max <= 0) {return 0;} return 1.33 - max;
  } else if(thinga > 67) {
    if(1.00 - max <= 0) {return 0;} return 1.00 - max;
  } else {
    if(0.00 - max <= 0) {return 0;} return 0.00;
  }
}

void viewInformation() {
  bool runAgain = false;
  string answerHolder = "";
  string lines = "";
  int count = 0;
  int person = 0;
  
  do {
    count = 1;
    fstream file("Names.txt");
    if (file.is_open()) {
      while (getline(file, lines)) {
        cout << "[" << count << "] "<< lines << endl;
        count++;
      }
    file.close();
  }
    
    do {
      cout << "\nPlease enter the number corresponding with the student you would like to view using the list above: ";
      getline(cin, answerHolder);
      if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (digit(answerHolder)) {
      if (stoi(answerHolder) > count-1 || stoi(answerHolder) < 1) {
      cout << "\nInvalid selection.";
      answerHolder = "a";
      }
      }
    } while(!digit(answerHolder));

      person = stoi(answerHolder);
      count = 0;
      
    fstream file2("Names.txt");
    if (file2.is_open()) {
      while (getline(file2, lines)) {
        count++;
        if(count == person) {
          break;
        }
      }
    file2.close();
  }
    string blob = lines.append(".txt");
    blob.erase(blob.find(" "), 1);
    cout << blob;
      
    fstream file3(blob);
    if (file3.is_open()) {
      while (getline(file3, lines)) {
        cout << endl << lines;
      }
    file3.close();
  }

    do {
    cout << "\nWould you like to view another student? \n1) Yes\n2) No\n";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (digit(answerHolder)) {
      if (stoi(answerHolder) > 2 || stoi(answerHolder) < 1) {
      cout << "\nInvalid entry.";
      answerHolder = "a";
      }
    }
  } while(!digit(answerHolder));
  if(answerHolder == "1") {
    runAgain = true;
  } else {
    runAgain = false;
  }
    
  } while(runAgain);
}
