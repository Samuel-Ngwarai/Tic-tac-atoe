#include <iostream>
#include <vector>
#include <map>
using namespace std;

//create a tic tac toe game

class TicTacToe {
    vector<vector<int> > board;
public:
    //vector<vector<int>> board;
    map<int, int> rowsP;
    map<int, int> colsP;
    map<int, int> forwardP;
    map<int, int> backwardsP;
    map<int, int> rowsN;
    map<int, int> colsN;
    map<int, int> forwardN;
    map<int, int> backwardsN;
    map<pair<int, int>, bool> visited;
    
    int boardSize;
    int degree;

    TicTacToe(int n) {
        board.resize(n, vector<int>(n, 0));
        boardSize = n;
        degree = 3;
    }

    bool invalid(pair<int, int> point) {
        if (visited[point]) {
            cout << "This point has been visited before." << endl;
            return true;
        }
        
        //cout << endl << "First: " << point.first << " - Second: " << point.second << endl;

        if (point.first < 0 || point.second < 0 || point.first >= boardSize || point.second >= boardSize) {
            cout << "This point is invalid." << endl;
            return true;
        }
        return false;
    }

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

        if (diff == 1) {
            forwardP[row + col] += diff;
            backwardsP[row - col + boardSize] += diff;
            rowsP[row] += diff;
            colsP[col] += diff;
        } else {
            forwardN[row + col] += diff;
            backwardsN[row - col + boardSize] += diff;
            rowsN[row] += diff;
            colsN[col] += diff;
        }

        if (rowsP[row] == degree || colsP[col] == degree || forwardP[row + col] == degree || backwardsP[row - col + boardSize] == degree) return 1;
        if (rowsN[row] == 0 - degree || colsN[col] == 0 - degree || forwardN[row + col] == 0 - degree || backwardsN[row - col + boardSize] == 0 - degree) return 2;

        if (visited.size() == boardSize * boardSize) return -1;

        return 0;
    }

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

    while (boardSize < 2) {
        cout << "Enter a number larger than 1 please" << endl;
        cin >> boardSize;
    }
   
    TicTacToe game(boardSize);

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

        if (moveResponse == 2) {
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
