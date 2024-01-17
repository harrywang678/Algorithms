/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Harry Wang and Jimmy Zhang
 * Date        : 10/11/2023
 * Description : Water Jug Puzzle using BFS.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// Initialize the variables
int A, B, C, goalA, goalB, goalC;

// Struct to represent the state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State* parent;

    State(int _a, int _b, int _c, string _directions)
        : a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    // Default constructor
    State() {
        a = -1;
        b = -1;
        c = -1;
        directions = "";
        parent = nullptr;
    }

    // String representation of the state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

vector<State> BFS(int currA, int currB, int currC) {
    // Queue to keep order
    queue<State> Queue;
    // Keep track of what we've already seen
    State** seen = new State*[A + 1];
    // Make each row in seen have B+1 columns
    for (int i = 0; i < A + 1; i++) {
        seen[i] = new State[B + 1];
    }

    // Create the initial state
    State current(0, 0, currC, "Initial state.");

    Queue.push(current);

    while (!Queue.empty()) {
        // Get the first object in the queue and pop it
        currA = Queue.front().a;
        currB = Queue.front().b;
        currC = Queue.front().c;
        string curDir = Queue.front().directions;
        State* curPar = Queue.front().parent;

        current = Queue.front();
        Queue.pop();

        // Found the solution
        if (currA == goalA && currB == goalB) {
            break;
        }

        // Check if the current state has been seen
        if (seen[currA][currB].c != -1) {
            continue;
        }

        // Mark the current state as having been visited
        seen[currA][currB].a = currA;
        seen[currA][currB].b = currB;
        seen[currA][currB].c = currC;
        seen[currA][currB].directions = curDir;
        seen[currA][currB].parent = curPar;

        // Pour from C to A
        if (currA < A && currC != 0) {
            int nextA = currA + currC;
            // If it overflows, just fill to max
            if (nextA > A) {
                nextA = A;
            }
            // Pour enough to fill destination jug and keep leftover
            int nextC = currC - (nextA - currA);
            // Conversion from int to string
            stringstream ss;
            ss << nextA - currA;
            // Check for plural or singular
            string dir = (nextA - currA == 1) ? "Pour " + ss.str() + " gallon from C to A." : "Pour " + ss.str() + " gallons from C to A.";
            State nextState(nextA, currB, nextC, dir);
            // Set parent to keep track
            nextState.parent = &seen[currA][currB];
            // Add to queue
            Queue.push(nextState);
        }

        // Pour from B to A
        if (currA < A && currB != 0) {
            int nextA = currA + currB;
            if (nextA > A) {
                nextA = A;
            }
            int nextB = currB - (nextA - currA);
            stringstream ss;
            ss << nextA - currA;
            string dir = (nextA - currA == 1) ? "Pour " + ss.str() + " gallon from B to A." : "Pour " + ss.str() + " gallons from B to A.";
            State nextState(nextA, nextB, currC, dir);
            nextState.parent = &seen[currA][currB];
            Queue.push(nextState);
        }

        // Pour from C to B
        if (currB < B && currC != 0) {
            int nextB = currB + currC;
            if (nextB > B) {
                nextB = B;
            }
            int nextC = currC - (nextB - currB);
            stringstream ss;
            ss << nextB - currB;
            string dir = (nextB - currB == 1) ? "Pour " + ss.str() + " gallon from C to B." : "Pour " + ss.str() + " gallons from C to B.";
            State nextState(currA, nextB, nextC, dir);
            nextState.parent = &seen[currA][currB];
            Queue.push(nextState);
        }

        // Pour from A to B
        if (currB < B && currA != 0) {
            int nextB = currB + currA;
            if (nextB > B) {
                nextB = B;
            }
            int nextA = currA - (nextB - currB);
            stringstream ss;
            ss << nextB - currB;
            string dir = (nextB - currB == 1) ? "Pour " + ss.str() + " gallon from A to B." : "Pour " + ss.str() + " gallons from A to B.";
            State nextState(nextA, nextB, currC, dir);
            nextState.parent = &seen[currA][currB];
            Queue.push(nextState);
        }

        // Pour from B to C
        if (currC < C && currB != 0) {
            int nextC = currC + currB;
            if (nextC > C) {
                nextC = C;
            }
            int nextB = currB - (nextC - currC);
            stringstream ss;
            ss << nextC - currC;
            string dir = (nextC - currC == 1) ? "Pour " + ss.str() + " gallon from B to C." : "Pour " + ss.str() + " gallons from B to C.";
            State nextState(currA, nextB, nextC, dir);
            nextState.parent = &seen[currA][currB];
            Queue.push(nextState);
        }

        // Pour from A to C
        if (currC < C && currA != 0) {
            int nextC = currC + currA;
            if (nextC > C) {
                nextC = C;
            }
            int nextA = currA - (nextC - currC);
            stringstream ss;
            ss << nextC - currC;
            string dir = (nextC - currC == 1) ? "Pour " + ss.str() + " gallon from A to C." : "Pour " + ss.str() + " gallons from A to C.";
            State nextState(nextA, currB, nextC, dir);
            nextState.parent = &seen[currA][currB];
            Queue.push(nextState);
        }
    }

    // Check if the solution is not reached
    if (goalA != current.a && goalB != current.b) {
        for (int i = 0; i < A + 1; i++) {
            delete[] seen[i];
        }
        delete[] seen;
        return vector<State>();
    }

    // Initialize a vector to store the path of states to get to the desired goal
    vector<State> answer;
    // Backtrack to insert all steps into the vector answer
    while (current.parent != nullptr) {
        answer.insert(answer.begin(), current);
        current = *current.parent;
    }
    // Inserts the initial state
    answer.insert(answer.begin(), current);

    // Delete allocated memory.
    for (int i = 0; i < A + 1; i++) {
        delete[] seen[i];
    }
    delete[] seen;

    return answer;
}

int main(int argc, char *const argv[]) {
    istringstream iss;
    int x;

    // Basic tests to see if inputs match the correct usage
    if (argc != 7) {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 0;
    }

    for (int i = 1; i < 4; i++) {
        iss.str(argv[i]);
        if (!(iss >> x) || x <= 0) {
            cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << char('A' + i - 1) << "." << endl;
            return 0;
        }
        iss.clear();
    }

    for (int i = 4; i < argc; i++) {
        iss.str(argv[i]);
        if (!(iss >> x) || x < 0) {
            cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << char('A' + i - 4) << "." << endl;
            return 0;
        }
        iss.clear();
    }

    // Store input into variables
    iss.str(argv[1]);
    iss >> A;
    iss.clear();
    iss.str(argv[2]);
    iss >> B;
    iss.clear();
    iss.str(argv[3]);
    iss >> C;
    iss.clear();
    iss.str(argv[4]);
    iss >> goalA;
    iss.clear();
    iss.str(argv[5]);
    iss >> goalB;
    iss.clear();
    iss.str(argv[6]);
    iss >> goalC;
    iss.clear();

    // Check if goal exceeds capacity
    if (A < goalA) {
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 0;
    }
    if (B < goalB) {
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 0;
    }
    if (C < goalC) {
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 0;
    }

    // Check if the capacity of C equals the sum of the goals.
    if (C != goalA + goalB + goalC) {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 0;
    }

    vector<State> route = BFS(0, 0, C);
    if (route.empty()) {
        cerr << "No solution." << endl;
        return 0;
    } else {
        for (State& step : route) {
            cout << step.directions << " " << step.to_string() << endl;
        }
    }
}