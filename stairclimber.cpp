/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Harry Wang
 * Date        : 10/4/2023
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    if (num_stairs <= 0){
        return {{}};
    }
    
    vector < vector <int> > ways;

    for (int i = 1; i < 4; i++){
        if (num_stairs >= i){
            vector < vector< int > > result = get_ways(num_stairs -i);
            for (size_t j = 0; j < result.size(); j++){
                result[j].insert(result[j].begin(), i);
                ways.push_back(result[j]);
            }
    }
    }
    return ways;        

}


int num_digits(int num){
    int x = 1; 
    while (num >= 10){ 
        num = num/10;
        x += 1;
    }
    return x;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int x = 1;
    int y = ways.size();
    int z = num_digits(y);

    for (size_t i = 0; i < ways.size(); i++){
        cout << right << setw(z) << x << ". [";
        x++;
        for (size_t j = 0; j < ways[i].size(); j++){
            if (j < ways[i].size() - 1)
                cout << ways[i][j] << ", ";
            else{
                cout << ways[i][j];
            }
        }
        cout << "]" << endl;
    }
}




int main(int argc, char * const argv[]) {

    int n;
    istringstream iss;
    

    if (argc == 1){
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 0;
    }
    else if (argc > 2){
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 0;
    }
    iss.str(argv[1]);

    if (! (iss >> n)){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 0;
    }

    if(n <= 0) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 0;
    }

    if (n == 1){
        int y = get_ways(n).size();
        vector < vector <int> > x = get_ways(n);
        cout << y << " way to climb 1 stair." << endl;
        display_ways(x);
        return 0;
    }
    
    else {
        vector < vector <int> > x = get_ways(n);
        int y = get_ways(n).size();
        cout << y << " ways to climb " << n << " stairs." << endl;
        display_ways(x);
        return 0;
        
    }
}
