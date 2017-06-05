/* This is my own version of tic tac toe. First functional, then smart.
 */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
// The 'board' will be divided into 9 'boxes' that have individual properties.

//THE BOX WILL TELL US WHETHER A COMPARTMENT IS OCCUPIED AND WHO IS OCCUPYING IT
class Box{
private:
    int occupied;

public:
    //make box
    Box () {
        occupied = 0;
    };

    //x occupy
    void x_occupy() {
        occupied += 1;
    }

    // y occupy     NOTE: y is just a sudo for 'o'
    void y_occupy() {
        occupied -= 1;
    }

    //is the box occupied?
    int return_occupied () {
        return occupied;
    }

};

//The BOARD will contain 9 boxes
class Board{
private:
    //declaring total counts for checking game progress
    int r1;
    int r2;
    int r3;
    int d1;
    int d2;
    int c1;
    int c2;
    int c3;

    //declaring boxes of the board
    Box b1;
    Box b2;
    Box b3;
    Box b4;
    Box b5;
    Box b6;
    Box b7;
    Box b8;
    Box b9;


public:
    //to keep all the boxes
    vector<Box> boxes;

    //to check whether a box has been occupied
    vector<int> b_occupied;

    //make board and initialize total values.
    Board () {
        r1 = 0;
        r2 = 0;
        r3 = 0;
        d1 = 0;
        d2 = 0;
        c1 = 0;
        c2 = 0;
        c3 = 0;

        boxes.push_back(b1);
        boxes.push_back(b2);
        boxes.push_back(b3);
        boxes.push_back(b4);
        boxes.push_back(b5);
        boxes.push_back(b6);
        boxes.push_back(b7);
        boxes.push_back(b8);
        boxes.push_back(b9);

        for (int i = 0; i < 9; i++) {
            b_occupied.push_back(i);
        }
    }

    //update the values
    void update() {
        r1 = boxes[0].return_occupied() + boxes[1].return_occupied() + boxes[2].return_occupied();
        r2 = boxes[3].return_occupied() + boxes[4].return_occupied() + boxes[5].return_occupied();
        r3 = boxes[6].return_occupied() + boxes[7].return_occupied() + boxes[8].return_occupied();
        d1 = boxes[0].return_occupied() + boxes[4].return_occupied() + boxes[8].return_occupied();
        d2 = boxes[2].return_occupied() + boxes[4].return_occupied() + boxes[6].return_occupied();
        c1 = boxes[0].return_occupied() + boxes[3].return_occupied() + boxes[6].return_occupied();
        c2 = boxes[1].return_occupied() + boxes[4].return_occupied() + boxes[7].return_occupied();
        c3 = boxes[2].return_occupied() + boxes[5].return_occupied() + boxes[8].return_occupied();
    }

    //for checking row, column and diagonal totals in troubleshooting
    void values() {
        cout << r1 << endl << r2 << endl << r3 << endl << endl;
        cout << d1 << endl << d2 << endl << endl;
        cout << c1 << endl << c2 << endl << c3 << endl << endl;
    }

    //check the values
    bool check() {
        //if any of the rows, columns or diagonals adds up to 3, X wins
        if (r1 == 3 || r2 == 3 || r3 == 3 || d1 == 3 || d2 == 3 || c1 == 3 || c2 == 3 || c3 == 3) {
            cout << "X WINS!" << endl;
            return true;
        }
            //if they add up to -3, Y wins
        else if (r1 == -3 || r2 == -3 || r3 == -3 || d1 == -3 || d2 == -3 || c1 == -3 || c2 == -3 || c3 == -3) {
            cout << "Y WINS!" << endl;
            return true;
        }

        //if all boxes are occupies, its a draw
        if (boxes[0].return_occupied() != 0 && boxes[1].return_occupied() != 0 && boxes[2].return_occupied() != 0 &&
            boxes[3].return_occupied() != 0 && boxes[4].return_occupied() != 0 && boxes[5].return_occupied() != 0 &&
            boxes[6].return_occupied() != 0 && boxes[7].return_occupied() != 0 && boxes[8].return_occupied() != 0) {
            cout << "Shame, its a draw" << endl;
            return true;
        }

        return false;
    }

    //making a move
    void i_play(int n) {

            boxes[n - 1].x_occupy();
            b_occupied.erase(remove(b_occupied.begin(), b_occupied.end(), n - 1), b_occupied.end());
            //removing occupied boxes makes random moves much easier to handle
    }

    //random move from computer(not strategic in any way, yet)
    void c_play() {
        int guess;
        srand (time(NULL));
        guess =  rand() % b_occupied.size();

        int selected = b_occupied[guess];


        boxes[selected].y_occupy();
        b_occupied.erase(remove(b_occupied.begin(), b_occupied.end(), selected), b_occupied.end());
    }

    //print the board to see the state of the game
    void print() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << "|";
                if (boxes[3 * i + j].return_occupied() < 0) {
                    cout << " O " << "|";
                }
                else if (boxes[3 * i + j].return_occupied() > 0) {
                    cout << " X " << "|";
                }
                else {
                    cout << "   " << "|";
                }
            }
            cout << endl;
        }
    }
};



int main() {
    Board board;

    int n;
    cout << "Pick a number to play" << endl;
    while (!board.check()) {
        cout << ">>";
        cin >> n;

        while (n < 1 || n > 9 || board.boxes[n - 1].return_occupied() != 0) {
            cout << "Please enter a valid number in the range 1-9 that is not occupied" << endl;
            cin >> n;
        }

        board.i_play(n);
        board.update();
        if(board.check()) {
            board.print();
            break;
        }

        board.c_play();
        board.update();
        board.print();
        if(board.check())
            break;

    }

    return 0;
}
