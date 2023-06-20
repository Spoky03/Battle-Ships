#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

const int windowsScale=90;
const int n=10; //board size n*n
const int sizeWindow = n*windowsScale;
const int divround_n = n / 2 + (n % 2); //used to determine amount of ships
//statek
class Statek {
    public:
        tuple <int, int> pos;
        int direction;
        int size;
        //end position (0 - poziomo, 1 - pionowo)
        tuple <int, int> getEndPos() {
            if (direction == 0) {
                return make_tuple(get<0>(pos), get<1>(pos) + size-1);
            }
            else {
                return make_tuple(get<0>(pos) + size-1, get<1>(pos));
            }
        }
    void randomPos() {
        pos = make_tuple(rand() % n, rand() % n);
        direction = rand() % 2;
    }
};


//plansza
class Plansza {
    public:
        int tab[n][n];
        int round;
        Plansza (int n) {
            setup(tab, n); //not needed because empty array elements are 0
        }
        void setup(int tab[n][n], int n) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    tab[i][j] = 0;
                }
            }
        }
        //adding ship to board
        void addShip(int tab[n][n], int n, Statek statek) {
            if (statek.direction==1) {
                for (int i = get<0>(statek.pos); i <= get<0>(statek.getEndPos()); i++) {
                    tab[i][get<1>(statek.pos)] = 1;
                }
            }
            else if (statek.direction==0) {
                for (int i = get<1>(statek.pos); i <= get<1>(statek.getEndPos()); i++) {
                    tab[get<0>(statek.pos)][i] = 1;
                }
            }
        }
        int shoot(int tab[n][n], int n, tuple <int, int> pos) {
            vector <tuple <int, int>> shooted;    
            if (tab[get<0>(pos)][get<1>(pos)] == 1) {
                tab[get<0>(pos)][get<1>(pos)] = 2;
                shooted.push_back(pos);
                return 1;

            }
            else if (tab[get<0>(pos)][get<1>(pos)] == 0) {
                tab[get<0>(pos)][get<1>(pos)] = 3;
                shooted.push_back(pos);
                return 0;
            }
            else if (tab[get<0>(pos)][get<1>(pos)] == 2) {
                return 2;
            }
            else {
                return 2;
            }
        }
        //direction detection from shooting ai pov
        int direction(int tab[n][n], int n, int x1, int y1, int x2, int y2) {
            if (x1 == x2) {
                return 0;
                // 0 - pionowo
            }
            else if (y1 == y2) {
                return 1;
                // 1 - poziomo
            }
            else {
                return 2;
            }
        }
        //checking if there are 1 on board
        int checkEnd(int tab[n][n], int n) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (tab[i][j] == 1) {
                        return 0;
                    }
                }
            }
            return 1;
        }
        //marking every square around ship as 3
        void markAround(int tab[n][n], int n, int x, int y, int dir) {
            int Tx=x;
            int Ty=y;
            if (dir==1){//poziom
                while (tab[x][y] == 2) {
                    if (y == 0) {
                        tab[x][y + 1] = 3;
                    }
                    else if (y == n - 1) {
                        tab[x][y - 1] = 3;
                    }
                    else {
                        tab[x][y - 1] = 3; tab[x][y + 1] = 3;
                    }
                    x--;
                }
                x = Tx+1;
                while (tab[x][y] == 2) {
                    if (y == 0) {
                        tab[x][y + 1] = 3;
                    }
                    else if (y == n - 1) {
                        tab[x][y - 1] = 3;
                    }
                    else {
                        tab[x][y - 1] = 3; tab[x][y + 1] = 3;
                    }
                    x++;
                }
            }
            else if (dir==0){//pion
                while (tab[x][y] == 2) {
                    if (x == 0) {
                        tab[x+1][y] = 3;
                    }
                    else if (x == n - 1) {
                        tab[x - 1][y] = 3;
                    }
                    else {
                        tab[x - 1][y] = 3; tab[x + 1][y] = 3;
                    }
                    y--;
                }
                y = Ty+1;
                while (tab[x][y] == 2) {
                    if (x == 0) {
                        tab[x + 1][y] = 3;
                    }
                    else if (x == n - 1) {
                        tab[x - 1][y] = 3;
                    }
                    else {
                        tab[x - 1][y] = 3; tab[x + 1][y] = 3;
                    }
                    y++;

                }
            }
        }
        bool nested1(int tab[n][n], int n, Statek statek){
            for (int i = get<0>(statek.pos); i <= get<0>(statek.getEndPos()); i++) {
                            if (tab[i][get<1>(statek.pos)] == 1 or tab[i][get<1>(statek.pos)] == 2) {
                                return false;
                            }
                        }
            return true;
        }
        bool nested2(int tab[n][n], int n, Statek statek){
            for (int i = get<1>(statek.pos); i <= get<1>(statek.getEndPos()); i++) {
                            if (tab[get<0>(statek.pos)][i] == 1 or tab[get<0>(statek.pos)][i] == 2) {
                                return false;
                            }
                        }
            return true;
        }
        bool nested3(int tab[n][n], int n, Statek statek){
            for (int i = get<0>(statek.pos); i <= get<0>(statek.getEndPos()); i++) {
                            if (tab[i][get<1>(statek.pos)+1] == 1 or tab[i][get<1>(statek.pos)-1] == 1) {
                                return false;
                            }
                            if (tab[i+1][get<1>(statek.pos)] == 1 or tab[i-1][get<1>(statek.pos)] == 1) {
                                return false;
                            }
                        }
            return true;
        }
        bool nested4(int tab[n][n], int n, Statek statek){
            for (int i = get<1>(statek.pos); i <= get<1>(statek.getEndPos()); i++) {
                            if (tab[get<0>(statek.pos)+1][i] == 1 or tab[get<0>(statek.pos)-1][i] == 1) {
                                return false;
                            }
                            if (tab[get<0>(statek.pos)][i+1] == 1 or tab[get<0>(statek.pos)][i-1] == 1) {
                                return false;
                            }
                        }
            return true;
        }

        //nested loop 
        //set up ships on board
        //random ships
        void setUpShips(int tab[n][n], int n) {
            int shipCount = 0;
            srand(time(NULL));
            while (shipCount < divround_n) {
                int validPosition = 0;
                Statek statek;  
                statek.size = shipCount+2; //smallest size is 2
                wrong: 
                while (validPosition==0) {

                    //random position
                    statek.randomPos();
                    //checking if ship is not bigger than board
                    if (get<0>(statek.getEndPos()) >= n or get<1>(statek.getEndPos()) >= n) {
                        continue;
                    }
                    //collision
                    if (statek.direction == 1 and nested1(tab, n, statek)==false) { //poziomo
                        break;
                    }
                    else if (statek.direction == 0 and nested2(tab, n, statek)==false) { //pionowo
                        break;
                    }
                    //proximity
                    if (statek.direction == 1 and nested3(tab,n,statek)==false) { //poziomo
                        break;
                    }
                    else if (statek.direction == 0 and nested4(tab,n,statek)==false) { //pionowo
                        break;
                    }
                    //adding
                    //Tabstatek[shipCount] = statek;
                    validPosition = 1;
                    shipCount++;
                    addShip(tab, n, statek); 
                    //another ship               
                }
            }
        }
        
};
//compare if two boards are the same (operator overloading)
    bool operator == (const Plansza& lhs, const Plansza& rhs)
    {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (lhs.tab[i][j] != rhs.tab[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

Plansza plansza(n);
//dynamic board state
vector <Plansza>* boardState = new vector <Plansza>;
int statki()
    {
        //set up ships
        plansza.setUpShips(plansza.tab, n);
        boardState->push_back(plansza); //first board state
        //random game
        while (plansza.checkEnd(plansza.tab, n) == 0) {
            
            //random shoot
            int x = 0, y = 0;
            int Rx = 0, Ry = 0;
            int shipDetectedDirection = -1;
            int shipDetected = 0;  
            while (plansza.tab[x][y] == 2 or plansza.tab[x][y] == 3){
                x = rand() % n;
                y = rand() % n;
            }
            if (plansza.shoot(plansza.tab, n, make_tuple(x, y)) == 1) {
                shipDetected = 1;
                Rx = x;
                Ry = y;
            }
            else if (plansza.shoot(plansza.tab, n, make_tuple(x, y)) == 0) {
                plansza.round++;
            }
            plansza.round++;
            boardState->push_back(plansza);
            while (shipDetected == 1){
                //detecting direction
                while (shipDetectedDirection == -1){
                    if (plansza.tab[x+1][y]==1 and x+1<n){
                        shipDetectedDirection = 1;
                        break;
                    }
                    else if (plansza.tab[x+1][y]==0 and x+1<n){
                        plansza.shoot(plansza.tab, n, make_tuple(x+1, y));
                        plansza.round++;
                        boardState->push_back(plansza);
                    }
                    if (plansza.tab[x-1][y]==1 and x-1>=0){
                        shipDetectedDirection = 1;
                        break;
                    }
                    else if (plansza.tab[x-1][y]==0 and x-1>=0){
                        plansza.shoot(plansza.tab, n, make_tuple(x-1, y));
                        plansza.round++;
                        boardState->push_back(plansza);
                    }
                    shipDetectedDirection = 0;            
                }
                //shooting
                if (shipDetectedDirection == 1) { //poziom
                    while (plansza.shoot(plansza.tab, n, make_tuple(x+1, y)) == 1) {
                        x++;
                        boardState->push_back(plansza);
                    }
                    plansza.round++;
                    x=Rx;
                    while (plansza.shoot(plansza.tab, n, make_tuple(x-1, y)) == 1) {
                        x--;
                        boardState->push_back(plansza);
                    }
                    plansza.round++;
                    x=Rx;
                }
                else if (shipDetectedDirection == 0) { //pion
                    while (plansza.shoot(plansza.tab, n, make_tuple(x, y+1)) == 1) {
                        y++;
                        boardState->push_back(plansza);
                    }
                    plansza.round++;
                    y=Ry;
                    while (plansza.shoot(plansza.tab, n, make_tuple(x, y-1)) == 1) {
                        y--;
                        boardState->push_back(plansza);
                    }
                    //plansza.round++;
                    y=Ry;
                }
                    plansza.markAround(plansza.tab, n, Rx, Ry, shipDetectedDirection);
                    shipDetected = 0;
                    shipDetectedDirection = -1;
        
            }
            //adding board state to vector
            boardState->push_back(plansza);
            
        }
        //end of game
        //removing duplicates from vector (comparation using operator== operator overloaing)
        boardState->erase(unique(boardState->begin(), boardState->end()), boardState->end());
        return plansza.round;
    }

//Stefan Grzelec 2023

