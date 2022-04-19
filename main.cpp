#include "MyFunctions.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
  bool runAgain = false;
  string answer = "n";
  int ab = 0;
  
  string name1 = "Classes";
  
  do {
      worksheet1(name1);
      cout << "Press y/Y to return to main menu. Any other character to quit: ";
      getline(cin, answer);
      if (answer == "y" || answer == "Y") {
          runAgain = true;
      }
      else {
          runAgain = false;
      }
  } while (runAgain);
}
