// IntroCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CurrencyManager.h"
#include "RomanNumeral.h"

int main()
{
   std::string romanNotation1;
   std::string romanNotation2;
   std::cout << "Give me two roman numerals:" << std::endl;
   std::cin >> romanNotation1 >> romanNotation2;
   RomanNumeral romanNumeral1, romanNumeral2, romanNumeralResult;
   romanNumeral1.setValue(romanNotation1);
   romanNumeral2.setValue(romanNotation2);
   int result = romanNumeral1.getValue() + romanNumeral2.getValue();
   romanNumeralResult.setValue(result);
   std::cout << romanNumeral1.getNotation() << " + " << romanNumeral2.getNotation()
      << " = " << romanNumeralResult.getNotation();
   
   return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
