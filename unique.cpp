/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Harry Wang
 * Date        : 9/28/2023
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) { 
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for (unsigned int i = 0; i < s.length(); i++ ){ 
        if (!islower(s[i])){ // islower() will return false if its not a lower case letter, it will even return false for characters like ! and numbers
            return false; // if it detects  anything thats not a lower case character, it will return false.
        }
    }
    return true;
    }



bool all_unique_letters(const string &s) {  
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.
 
    unsigned int x = 0; 
    for (unsigned int i = 0; i < s.length(); i++){ 
        if (0 == (1 & (x >> (s[i] - 'a')))){ // if the corresponding bit is 0, make it 1
            x = (1 << (s[i] - 'a')) | x;
        }
        else { // if the corresponding bit is 1, return false.
            return false;
        }
    }
    return true;
}

int main(int argc, char* const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.


    if (argc == 1){ // if there is no argument
        cout << "Usage: ./unique <string>" << endl;
        return 0;
    }

    if (argc > 2){ // there is more than one argument
        cout << "Usage: ./unique <string>" << endl;
        return 0;
    }

    if (is_all_lowercase(argv[1]) == false){ // the string contains a "non-lowercase"
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 0;
    }

    if (all_unique_letters(argv[1]) == true){ // All letters are unique
        cout << "All letters are unique." << endl;
        return 0;

    }
 
    else { // there are duplicates letter found
        cout << "Duplicate letters found." << endl;
        return 0;
    }
    }

