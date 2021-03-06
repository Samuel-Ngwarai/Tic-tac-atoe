#include <iostream>
#include <vector>
#include <map>
using namespace std;

//Creates tic-tac-a-go game

class TicTacToe {
    int boardSize;  // size of board to play on
    int degree;     // minimum win condition
    vector<vector<int> > board;

public:
    // Visited places
    map<pair<int, int>, bool> visited;

    TicTacToe(int n, int d) {
        board.resize(n, vector<int>(n, 0));
        boardSize = n;
        degree = d;
    }

    // Check whether a point is valid
    bool invalid(pair<int, int> point) {
        if (visited[point]) {
            cout << "This point has been visited before." << endl;
            return true;
        }

        if (point.first < 0 || point.second < 0 || point.first >= boardSize || point.second >= boardSize) {
            cout << "This point is invalid." << endl;
            return true;
        }
        return false;
    }

    // Check whether given a starting point, and a token (x  or o), there exists
    // a win condition. This uses a breadth first search-like algorithm.
    int checkBoard(pair<int, int> point, int pToken) {
        if (visited.size() == boardSize * boardSize) return -1;

        //check Vertical
        int vertical = 1;
        for (int i = point.first - 1; i >= 0; i--) {
            if (board[i][point.second] != pToken) break;
            vertical++;
        }
        for (int i = point.first + 1; i < boardSize; i++) {
            if (board[i][point.second] != pToken) break;
            vertical++;
        }

        if (vertical >= degree) return 1;

        //check Horizontal
        int horizontal = 1;
        for (int i = point.second - 1; i >= 0; i--) {
            if (board[point.first][i] != pToken) break;
            horizontal++;
        }
        for (int i = point.second + 1; i < boardSize; i++) {
            if (board[point.first][i] != pToken) break;
            horizontal++;
        }
        if (horizontal >= degree) return 1;

        //check Fdiagonal
        int fDiagonal = 1;
        int r = point.first - 1, c = point.second - 1;
        while(r >= 0 && c >= 0) {
            if (board[r][c] != pToken) break;
            r--;
            c--;
            fDiagonal++;
        }
        r = point.first + 1, c = point.second + 1;
        while(r < boardSize && c < boardSize) {
            if (board[r][c] != pToken) break;
            r++;
            c++;
            fDiagonal++;
        }

        if (fDiagonal >= degree) return 1;
        
        //check Ndiagonal
        int nDiagonal = 1;
        r = point.first - 1, c = point.second + 1;
        while(r >= 0 && c < boardSize) {
            if (board[r][c] != pToken) break;
            r--;
            c++;
            nDiagonal++;
        }
        r = point.first + 1, c = point.second - 1;
        while(r < boardSize && c >= 0) {
            if (board[r][c] != pToken) break;
            r++;
            c--;
            nDiagonal++;
        }

        if (nDiagonal >= degree) return 1;
        
        return 0;

    }

    // add token for certain player to a given position.
    int move(int row, int col, int player) {
        int diff;
        if (player == 1) diff = 1;
        else diff = -1;
        
        pair<int, int> point = make_pair(row, col);
        
        //check point validity
        while (invalid(point)) {
            cout << "Please pick a new valid point" << endl;
            cin >> row >> col;
            point = make_pair(row, col);
        }
        
        //add point to board
        board[row][col] = diff;
        visited[point] = true;

        return checkBoard(point, diff);
    }

    // Show what the board looks like after each play including numbers for positioning
    void visualize() {
        cout << "  ";
        for (int i = 0; i < boardSize; i++) cout << i << " ";
        cout << endl;

        for (int r = 0; r < boardSize; r++) {
            cout << r << " ";
            for (int c = 0; c < boardSize; c++) {
                if (board[r][c] == 1) cout << "X ";
                else if (board[r][c] == -1) cout << "O ";
                else cout << "- ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "Let's play tic-tac-toe" << endl << "First to move is 'X', followed by 'O'" << endl;
    cout << "Pick the boardSize of tic-tac-toe you want to play: ";

    int boardSize;
    
    vector<vector<int> > board(3, vector<int>(3));
    cin >> boardSize;

    // boardSize validation
    while (boardSize < 3 && boardSize > 50) {
        cout << "Enter a number '2 < x < 50' please" << endl;
        cin >> boardSize;
    }
   
    cout << "Pick the degree of the tic-tac-go-ing (number of X's/O'sin a line for win condition)" << endl;

    int degree;
    cin >> degree;

    while (degree < 3 || degree > 10) {
        cout << "Make sure your degree is larger than 2 and smaller than 10" << endl;
        cin >> degree;
    }
    
    // Initialize game
    TicTacToe game(boardSize, degree);

    cout << "Here is the board" << endl;
    game.visualize();
    cout << endl;

    int r, c, moveResponse;
    while (1) {
        cout << endl << "X to play" << endl;
        cout << "Pick a place on the board (row first)" << endl;
        cin >> r >> c;
        
        moveResponse = game.move(r, c, 1);
        if (moveResponse == 1) {
            cout << "X wins!" << endl;
            break;
        } else if (moveResponse == -1) {
            cout << "--- DRAW ---" << endl;
            break;
        }

        game.visualize();

        cout << endl << "Y to play" << endl;
        cout << "Pick a place on the board (row first)" << endl;
        cin >> r >> c;
        moveResponse = game.move(r, c, 2);

        if (moveResponse == 1) {
            cout << "Y wins!" << endl;
            break;
        } else if (moveResponse == -1) {
            cout << "--- DRAW ---" << endl;
            break;
        }
        game.visualize();
    }
    game.visualize();
    return 0;
}
