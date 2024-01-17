#include <iostream>
#include <sstream>
using namespace std;


int max(int n, int m) {
    if (n > m){
        return n;
    } else {
        return m;
    }
}

int main(int argc, char* argv[]) {
    int n, m;
    istringstream iss; // string to integer

    if (argc != 3) {
        cerr << "Ussage: " << argv[0] << "<int> <int>" << endl;
        return 1;
    }

    iss.str(argv[1]);
    if(! (iss >> n)){ // Checks if the translation from string to integer works or not ...
        cerr << "Err : first command line arg must be int" << endl; // If the translation fails
        return 1;
    }

    iss.clear(); // clear in between because it will keep track of all the things it went through
    
    iss.str(argv[2]);
    if(! (iss >> m)) {
        cerr << "Err : first command line arg must be int" << endl;
        return 1;
    }

    cout << "n is: " << n << endl;
    cout << "m is: " << m << endl;
    cout << "max (" << n << ", " << m << ") is: " << max(n,m) << endl;
    return 0;



}

