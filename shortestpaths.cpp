/*******************************************************************************
 * Name        : shortestpath.cpp
 * Author      : Jimmy Zhang & Harry Wang
 * Version     : 1.0
 * Date        : 12/3/2023
 * Description : Implementation of Floyd's algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

int len(long val) {
    if (val == 0) {
        return 1;
    }
    long temp = val;
    int length = 0;
    while (temp > 0) {
        temp = temp/10;
        length++;
    }
    return length;
}

/**
 * Floyd algorithm + intermediate vertices
 * Uses Floyd's algorithm to update lengths matrix (stores shortest lengths of a pair) and updates intermediate matrix with chars when needed.
*/
void floyd(const vector<vector<long>>& original, vector<vector<long>>& lengths, vector<vector<long>>& intermediate) {
    int n = original.size(); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            lengths.at(i).at(j) = original.at(i).at(j);
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (lengths.at(i).at(j) > lengths.at(k).at(j) + lengths.at(i).at(k)) {
                    lengths.at(i).at(j) = lengths.at(k).at(j) + lengths.at(i).at(k);
                    intermediate.at(i).at(j) = k;
                }  
            }
        }
    }
}

/**
* Displays the matrix on the screen formatted as a table.
*/  
void display_table(vector<vector<long>> matrix, const string &label,
                    const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    int num_vertices = matrix.size();
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = matrix.at(i).at(j);
            if (cell < UINT_MAX && cell > max_val) {
                max_val = matrix.at(i).at(j);
            }
        }
    }
    int max_cell_width = use_letters ? len(max_val) :
        len(max(static_cast<long>(num_vertices), max_val));
    cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix.at(i).at(j) == UINT_MAX) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix.at(i).at(j) + 'A');
            } else {
                cout << matrix.at(i).at(j);
            }
        }
        cout << endl;
    }
    cout << endl;
}

void printTable(vector<vector<long>> distance, vector<vector<long>> intermediate) {
    int vertices = distance.size();
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                cout << char(i + 'A') << " -> " << char(j + 'A') << ", distance: 0, path: " << char(i + 'A') << endl;
            } else if (distance.at(i).at(j) == UINT_MAX) {
                cout << char(i + 'A') << " -> " << char(j + 'A') << ", distance: infinity, path: none" << endl;
            } else {
                vector<long> path;
                path.push_back(i);
                path.push_back(j);
                bool done = false;
                while (!done) {
                    for (size_t k = 0; k < path.size() - 1; k++) {
                        long inter = intermediate.at(path.at(k)).at(path.at(k + 1));    // Take the value from intermediate matrix to know which point we need to go through
                        if (inter < vertices) {     // Check if this point is valid (within the allowed range of letters)
                            path.insert(path.begin() + 1 + k, inter);   // Insert into path, after the kth element, in front of j (end of path)
                            k--;    // If there is a intermediate, have to check if there's another intermediate for that intermediate.
                        } else {
                            done = true;
                        }
                    }
                }
                cout << char(i + 'A') << " -> " << char(j + 'A') << ", distance: " << distance.at(i).at(j) << ", path: ";
                for (size_t idx = 0; idx < path.size(); idx++) {
                    cout << char(path.at(idx) + 'A');
                    if (idx < path.size() - 1) {
                        cout << " -> ";
                    }
                }
                cout << endl;
            }
        }
    }
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<vector<long>> original;
    int vertices = 0;
    try {
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        int line_num = 0;
        while (getline(input_file, line)) {
            istringstream iss;
            iss.str(line);
            // Check if first line is a valid integer
            if (line_num == 0) {
                if (!(iss>>vertices) || vertices < 1 || vertices > 26) {
                    cerr << "Error: Invalid number of vertices '" <<  line << "' on line 1." << endl;
                    return 1;
                }
                original = vector<vector<long>>(vertices, vector<long>(vertices, UINT_MAX));
                line_num++;
            } else {
                // Check if each line has 3 values
                string str;
                vector<string> currLine;
                while (getline(iss, str, ' ')) {
                    currLine.push_back(str);
                }
                if (currLine.size() != 3) {
                    cerr << "Error: Invalid edge data '" << line << "' on line " << line_num + 1 << "." << endl;
                    return 1;
                }
                // Check first value
                if (currLine.at(0).size() != 1 || currLine.at(0).at(0) < 'A' || currLine.at(0).at(0) > 'A' + vertices - 1) {
                    cerr << "Error: Starting vertex '" << currLine.at(0) << "' on line " << line_num + 1 << " is not among valid values A-" << char('A' + vertices - 1) << "." << endl;
                    return 1;
                }
                // Check second value
                if (currLine.at(1).size() != 1 || currLine.at(1).at(0) < 'A' || currLine.at(1).at(0) > 'A' + vertices - 1) {
                    cerr << "Error: Ending vertex '" << currLine.at(1) << "' on line " << line_num + 1 << " is not among valid values A-" << char('A' + vertices - 1) << "." << endl;
                    return 1;
                }
                // Check third value
                iss.clear();
                iss.str(currLine.at(2));
                int weight;
                if (!(iss>>weight) || weight < 1) {
                    cerr << "Error: Invalid edge weight '" << currLine.at(2) << "' on line " << line_num + 1 << "." << endl;
                    return 1;
                }
                int vertexFrom = currLine.at(0).at(0) - 65;
                int vertexTo = currLine.at(1).at(0) - 65;
                original.at(vertexFrom).at(vertexTo) = stoi(currLine.at(2));
                line_num++;
            }
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    for (int i = 0; i < vertices; i++) {
        original.at(i).at(i) = 0;
    }

    vector<vector<long>> weights = vector<vector<long>>(vertices, vector<long>(vertices, UINT_MAX));
    vector<vector<long>> intermediates = vector<vector<long>>(vertices, vector<long>(vertices, UINT_MAX));
    floyd(original, weights, intermediates);
    display_table(original, "Distance matrix:");
    display_table(weights, "Path lengths:");
    display_table(intermediates, "Intermediate vertices:", true);                    
    printTable(weights, intermediates);
}