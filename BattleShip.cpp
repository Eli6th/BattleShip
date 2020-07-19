#include <iostream>

using namespace std;

void createShipPos (int shipPos [4][2], int positions[8][8]);
void showBoard (int positions[8][8]);
void fire (int positions[8][8], int fireX, int fireY, int &torpedoes);

int main()
{
    srand (time(NULL));
    
    int width = 10, length = 10;
    
    int torpedoes = 15;
    int positions[8][8] = {};
    int subPos [4][2] = {};
    int subHit = 0;
    int fireX, fireY;
    
    bool win = false, loss = false;
    
    
    for (int i = 0; i < 8; i++) {
        for (int a = 0; a < 8; a++) {
         positions[i][a] = 0;
        }
    }
    
    createShipPos(subPos, positions);
    
    while (torpedoes != 0 && win == false && loss == false) {
        showBoard(positions);
        cout << endl << torpedoes << " torpedoes remain. Fire where?";
        cin >> fireX >> fireY;
        fire(positions, fireX, fireY, torpedoes);
        for (int i = 0; i < 4; i++) {
            if (positions[subPos[i][0]][subPos[i][1]] == 3) {
                subHit++;
            }
        }
        if (subHit >= 4) {
            cout << "Submarine sunk!" << endl;
            win = true;
        } else {
            subHit = 0;
        }
        if (torpedoes <= 0 && win != true) {
            loss = true;
        }
    }
    
    if (loss == true) {
        cout << "Not all ships have sunk! Out of torpedoes! You lose ;(" << endl;
    } else if (win == true) {
        cout << "All ships have sunk! You win :)" << endl;
    }
    
    return 0;
}

void createShipPos (int shipPos [4][2], int positions[8][8]) {
    bool directionPicked = false;
    int directionTry = 0;
    shipPos [0] [0] = {rand() % 8};
    shipPos [0] [1] = {rand() % 8};
    
    int direction = rand() % 4 + 1;
    
    while (directionPicked == false && directionTry < 4) {
        if (direction == 1) {
            if (shipPos[0][1] >= 3) {
                for (int i = 1; i < 4; i++) {
                    shipPos[i][0] = shipPos[0][0];
                    shipPos[i][1] = shipPos[0][1] - i;
                }
                
                directionPicked = true;
            } else {
                directionTry++;
                direction = 2;
            }
        }
        
        if (direction == 2) {
            if (shipPos[0][0] <= 4) {
                for (int i = 1; i < 4; i++) {
                    shipPos[i][0] = shipPos[0][0] + i;
                    shipPos[i][1] = shipPos[0][1];
                }
                
                directionPicked = true;
            } else {
                directionTry++;
                direction = 3;
            }
        }
        
        if (direction == 3) {
            if (shipPos[0][1] <= 4) {
                for (int i = 1; i < 4; i++) {
                    shipPos[i][0] = shipPos[0][0];
                    shipPos[i][1] = shipPos[0][1] + i;
                }
                
                directionPicked = true;
            } else {
                directionTry++;
                direction = 4;
            }
        }
        
        if (direction == 4) {
            if (shipPos[0][0] >= 3) {
                for (int i = 1; i < 4; i++) {
                    shipPos[i][0] = shipPos[0][0] - i;
                    shipPos[i][1] = shipPos[0][1];
                }
                
                directionPicked = true;
            } else {
                directionTry++;
                direction = 1;
            }
        }
    }
    
    if (directionTry >= 4) {
       createShipPos (shipPos, positions);
    }
    
    for (int i = 0; i < 4; i++) {
        positions [shipPos[i][0]] [shipPos[i][1]] = 1;
    }
}

void showBoard (int positions[8][8]) {
    
    cout << endl << " ";
    
    for (int i = 0; i < 8; i++) {
        cout << " " << i << " ";
    }
    
    for (int i = 0; i < 8; i++) {
        cout << endl;
        cout << i;
        for (int a = 0; a < 8; a++) {
            if (positions[i][a] == 0) {
                cout << " . ";
            } else if (positions[i][a] == 1) {
                cout << " . ";
            } else if (positions[i][a] == 2) {
                cout << " O ";
            } else if (positions[i][a] == 3) {
                cout << " X ";
            }
        }
    }
}

void fire (int positions[8][8], int fireX, int fireY, int &torpedoes) {
    if (positions [fireX] [fireY] == 0) {
        positions [fireX] [fireY] = 2;
        torpedoes--;
        cout << "Miss!" << endl;
    } else if (positions [fireX] [fireY] == 1) {
        positions [fireX] [fireY] = 3;
        torpedoes--;
        cout << "Hit!" << endl;
    } else if (positions [fireX] [fireY] == 2 || positions [fireX] [fireY] == 3) {
        cout << endl << "You've already shot there. " << torpedoes << " torpedoes remain. Fire where?";
        cin >> fireX >> fireY;
        fire(positions, fireX, fireY, torpedoes);
    }
}