#include <bits/stdc++.h> 
//include most libraries

using namespace std;

const int SIZE = 3;
const int PUZZLE_SIZE = SIZE * SIZE;

// Struct to represent a state of the puzzle, does not include cost only heuristic
struct PuzzleState {
    int puzzle[PUZZLE_SIZE];
    int heuristic;
//for positioning in PQ , with less heuristic at top pisotion
    bool operator>(const PuzzleState& other) const {
        return heuristic > other.heuristic;
    }
};

// Function to calculate the heuristic  of added minimum distance of misplaced tiles from the goal state
int calculateHeuristic(const int* puzzle) {
    int h = 0;
    for (int i = 0; i < PUZZLE_SIZE; ++i) {
        if (puzzle[i] != i) {
            int row_diff = abs(i / SIZE - puzzle[i] / SIZE);
            int col_diff = abs(i % SIZE - puzzle[i] % SIZE);
            h += row_diff + col_diff;
        }
    }
    return h;
}

// Function to check if a state is the goal state
bool isGoalState(const int* puzzle) {
    for (int i = 0; i < PUZZLE_SIZE; ++i) {
        if (puzzle[i] != i) {
            return false;
        }
    }
    return true;
}

// Function to print the puzzle state
void printPuzzle(const int* puzzle) {
    for (int i = 0; i < PUZZLE_SIZE; ++i) {
        cout << puzzle[i] << ' ';
        if ((i + 1) % SIZE == 0) {
            cout << endl;
        }
    }
}

// Function to perform Greedy Best-First Search
void solvePuzzle(const int* initialState) {
    priority_queue<PuzzleState, vector<PuzzleState>, greater<PuzzleState>> pq;
    map<vector<int>, bool> visited;

    PuzzleState initial;
    for (int i = 0; i < PUZZLE_SIZE; ++i) {
        initial.puzzle[i] = initialState[i];
    }
    initial.heuristic = calculateHeuristic(initialState);

    pq.push(initial);

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();

        if (isGoalState(current.puzzle)) {
            cout << "Goal State Reached!" << endl;
            cout << "Goal state:" << endl;
            printPuzzle(current.puzzle);
            return;
        }

        visited[vector<int>(current.puzzle, current.puzzle + PUZZLE_SIZE)] = true;

    
        int blankIndex;
        for (blankIndex = 0; blankIndex < PUZZLE_SIZE; ++blankIndex) {
            if (current.puzzle[blankIndex] == 0) {
                break;
            }
        }


        const int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < 4; ++i) {
            int newBlankRow = blankIndex / SIZE + moves[i][0];
            int newBlankCol = blankIndex % SIZE + moves[i][1];

            if (newBlankRow >= 0 && newBlankRow < SIZE && newBlankCol >= 0 && newBlankCol < SIZE) {
                int newIndex = newBlankRow * SIZE + newBlankCol;

                PuzzleState nextState;
                copy(current.puzzle, current.puzzle + PUZZLE_SIZE, nextState.puzzle);
                swap(nextState.puzzle[blankIndex], nextState.puzzle[newIndex]);
                nextState.heuristic = calculateHeuristic(nextState.puzzle);

                if (!visited[vector<int>(nextState.puzzle, nextState.puzzle + PUZZLE_SIZE)]) {
                    pq.push(nextState);
                }
            }
        }
    }

    cout << "Goal state not reachable!" << endl;
}

int main() {
    int initialState[PUZZLE_SIZE] = {8, 0, 6, 5, 4, 7, 2, 3, 1};
    cout<<"Initial state \n";
    printPuzzle(initialState);
    solvePuzzle(initialState);

    return 0;
}
