/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Harry Wang
 * Version     : 1.0
 * Date        : 10.31.2023
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high); 

long merge(int array[],int scratch[],int low,int mid,int high){ 

    //Set counter, i1 is iterating the left sub-array, i2 is iterating through the left sub-array.
    long count = 0; 
    long i1 = low;
    long i2 = mid + 1;
    long i = low;

    // If the element in the left sub-array is smaller than the right sub-array, copy the left sub-array element into scratch and vice versa.
    while ((i1 <= mid) && (i2 <= high)){
        if(array[i1] <= array[i2]){
            scratch[i++] = array[i1++];
        }
        else{
            scratch[i++] = array[i2++];
            count = count + (mid + 1 - i1); // The difference between mid + 1 and i1 will be the inversion count.   
        }
    }
    
    // In case there are still more elements in the left sub-array.
    for (int y = i1; y <= mid; y++){
        scratch[i++] = array[y];
    }
    // In case there are still more elements in the right sub-array.
    for (int y = i2; y <= high; y++){
        scratch[i++] = array[y];
    }
    // Copies all the element from scratch back to array.
    for (int j = low; j <= high; j++){
        array[j] = scratch[j];
    }

    //return the count
    return count;
    
}

/**
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long counter = 0;
    for (int i = 0; i < length - 1; i++){
        for (int j = i+1; j < length; j++){
            if (array[i] > array[j]){
                counter++;
            }
        }
    }
    return counter;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int* scratch = new int[length]; // Create a scratch array
    long x = mergesort(array,scratch,0,length - 1);
    delete[] scratch; // delete the scratch array
    return x;
}



static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long count = 0; // initialize counter
    if (low < high){ //when low is less than high...
        int mid = low + (high - low)/2; // mid will be the last element of the first array
        count += mergesort(array,scratch,low,mid);
        count += mergesort(array,scratch,mid + 1, high);
        count += merge(array,scratch,low,mid,high);
    }
    return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    if (argc > 2){ //if there are more than 1 argument...
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 0;
    }

    istringstream convert;
    string name = "";

    if (argc == 2){ // if there are 1 argument...
        convert.str(argv[1]);
        convert >> name;
        if (name != "slow"){ // if the argument is not slow...
        cerr << "Error: Unrecognized option '" << name << "'." << endl;
            return 0;
    }
    }
    
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {  
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }


    if (values.size() == 0){ // if there are no input...
        cerr << "Error: Sequence of integers not received." << endl;
        return 0;
    }

    // TODO: produce output
    if (name == "slow"){ // if argument is "slow"... 
        long x = count_inversions_slow(&values[0],values.size());
        cout << "Number of inversions (slow): " << x << endl;
        return 0;
    }

    else{ // if the argument is "fast"...
        long x = count_inversions_fast(&values[0],values.size());
        cout << "Number of inversions (fast): " << x << endl;
        return 0;
    }


    return 0;
}
