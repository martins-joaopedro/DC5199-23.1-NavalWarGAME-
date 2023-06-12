#include <bits/stdc++.h>

using namespace std;
#define MAX 15

int GAME_MODE = 0;
int DIFFICULT = 0;
int NUMBER_OF_SHIPS = 0;
int SHIPS_PLAYER1 = 0;
int SHIPS_PLAYER2 = 0;
int GRID_SIZE = 0;

const int EMPTY = 0;
const int SHIP = 1;
const int EXPLOSION = 2;
const int SEA = 3;

const int SINGLE_PLAYER = 1;
const int MULTIPLAYER = 2;

set<pair<int, int>>  S;

void printLine() {
    int N = 40;
    cout << ">=";
    for(int i=0; i<N; i++)
        cout << "-";
    cout << "=<" << endl;
}

void initGame() {
    bool START = false;
    int op = 0;
    while(!DIFFICULT or !START or !GAME_MODE) {
        system("cls");
    
        if(!DIFFICULT) {
            printLine();
            cout << "BEM VINDO AO JOGO BATALHA NAVAL " << endl;
            cout << "-> ESCOLHA O SEU MODO DE JOGO " << endl;
            cout << "[1] - FACIL " << endl << "[2] - MEDIO " << endl << "[3] - DIFICIL " << endl << "[4] - TESTE " << endl;
            cin >> op;
            switch (op) {
                case 1:
                    cout << "MODO DE JOGO FACIL ESCOLHIDO " << endl;
                    DIFFICULT = 1;                                    
                break;

                case 2:
                    cout << "MODO DE JOGO MEDIO ESCOLHIDO " << endl;
                    DIFFICULT = 2;                                 
                break;

                case 3:
                    cout << "MODO DE JOGO DIFICIL ESCOLHIDO " << endl;
                    DIFFICULT = 3;                                   
                break;

                case 4:
                    cout << "MODO DE TESTE ESCOLHIDO " << endl;
                    DIFFICULT = 4;
                    GRID_SIZE = 5;
                    NUMBER_OF_SHIPS = 4;
                    SHIPS_PLAYER1 = NUMBER_OF_SHIPS;
                    SHIPS_PLAYER2 = NUMBER_OF_SHIPS;

                    START = true;
                break;

                default:
                    cout << "VALOR INVALIDO - DIGITE NOVAMENTE " << endl;
                    system("pause");
                break;  
            }

            if(DIFFICULT != 4) {
                GRID_SIZE = DIFFICULT*5;
                NUMBER_OF_SHIPS = DIFFICULT*3+1;
                SHIPS_PLAYER1 = NUMBER_OF_SHIPS;
                SHIPS_PLAYER2 = NUMBER_OF_SHIPS;
            }
            

        } else if(!GAME_MODE) { 
            cout << "DEFINA COMO IRA JOGAR" << endl;
            cout << endl << "[1] - UM JOGADOR " << endl << "[2] - DOIS JOGADORES " << endl << "[0] - RETORNAR" << endl;
            cin >> op;

            switch (op) {
                case 1:
                    GAME_MODE = 1;                      
                break;

                case 2:
                    GAME_MODE = 2;
                break;

                case 0:
                    DIFFICULT = 0;                                 
                break;

                default:
                    cout << "VALOR INVALIDO - DIGITE NOVAMENTE " << endl;
                    system("pause");
                break;  
            } 

        } else if(!START) { 
            printLine();
            cout << "SEU MODO DE JOGO FOI ESCOLHIDO: " << endl;
            if(GAME_MODE == SINGLE_PLAYER)
                cout << "JOGADOR 1 vs COMPUTADOR" << endl;
            else if(GAME_MODE == MULTIPLAYER) 
                cout << "JOGADOR 1 vs JOGADOR 2" << endl;

            cout << "-> NUMERO DE CELULAS DO TABULEIRO: " << GRID_SIZE*GRID_SIZE << endl;
            cout << "-> NUMERO DE NAVIOS DO TABULEIRO: " << NUMBER_OF_SHIPS << endl;
            printLine();

            cout << endl << "[1] - PARA INICAR O JOGO " << endl << "[0] - PARA RETORNAR " << endl;
            cin >> op;

            switch (op) {
                case 1:
                    system("cls");   
                    cout << "BOA DIVERSAO! " << endl;
                    printLine();
                    system("pause");                 
                    system("cls");
                    START = true;                      
                break;

                case 0:
                    GAME_MODE = 0;                                 
                break;

                default:
                    cout << "VALOR INVALIDO - DIGITE NOVAMENTE " << endl;
                    system("pause");
                break;  
            } 
        }
    }
}

void printGrid(bool debug, int M[MAX][MAX]) {

    for(int i=0; i<=GRID_SIZE; i++) {
        if(i)
            cout << "[  " << i << "  ] ";
        else cout << "[     ] ";
    } 

    cout << endl;

    for(int i=0; i<GRID_SIZE; i++) {   
        cout << "[  " << i+1 << "  ] ";
        for(int j=0; j<GRID_SIZE; j++)  {
            if(debug) {
                if(M[i][j] == SHIP)
                    cout << "[ <#> ] ";
                else cout << "[     ] ";
            }else {
                if(M[i][j] == EXPLOSION )
                    cout <<  "[ < ~#] ";
                else if(M[i][j] == SEA )
                    cout <<  "[ ~~~ ] ";
                else cout << "[     ] ";
            }
        }
        cout << endl;
    }     
}

bool isAEmptyPlace(int M[MAX][MAX], int i, int j) {
    return M[i][j] == EMPTY;
}

bool isAShip(int M[MAX][MAX], int i, int j) {
    return M[i][j] == SHIP;
}

bool isSea(int M[MAX][MAX], int i, int j) {
    return M[i][j] == SEA;
}

bool isValid(int i, int j) {
    if((i>=0 and i<GRID_SIZE) and (j>=0 and j<GRID_SIZE))
        return true;
    else {
        cout << "[ POSICAO INVALIDA ] - NOVAMENTE, ";
        return false;
    }
}

void placeShips(int M[MAX][MAX]) {
    int x, y;
    for(int i=0; i<NUMBER_OF_SHIPS; i++) {     
        do {
            system("cls");
            printGrid(true, M);
            cout << "DIGITE AS COORDENADAS PRA POSICIONAR SEU BARCO " << i+1 << endl;
            cin >> x >> y;
            x--; y--;
        } while(!isAEmptyPlace(M, x, y) or !isValid(x, y));
        M[x][y] = SHIP;
    }
}

pair<int, int> generatePosition() {
    unsigned seed = time(0);
    srand(seed);
    
    pair<int, int> P;

    int x = rand()%GRID_SIZE;
    int y = rand()%GRID_SIZE;

    return make_pair(x,y);
}

void placeShipsMachine(int M[MAX][MAX]) {
    for(int i=0; i<NUMBER_OF_SHIPS; i++) {
        pair<int, int> coordinates = generatePosition();

        while(!isAEmptyPlace(M, coordinates.first, coordinates.second)) {
            coordinates = generatePosition();
        }
        M[coordinates.first][coordinates.second] = SHIP;
    }
}

bool randomStarter() {
    unsigned seed = time(0);
    srand(seed);
    int N = rand()%5;

    return N%2 == 0;
}

bool sendBomb(int M[MAX][MAX], bool MODE, int X, int Y) {
    if(MODE) {
        if(isAShip(M, X, Y)) {
            M[X][Y] = EXPLOSION;
            system("cls");
            system("Color 64");
            cout << "BOO@@@@@@@@@OOOOOOMMMM!!!!!!!" << endl;
            printGrid(false, M);
            system("pause");
            system("Color 0F"); 
            return true;
        }else {
            M[X][Y] = SEA;
        }
    } else {
        int x, y;

        printLine();
        cout << endl << "-> TABULEIRO DO SEU INIMIGO: " << endl;
        printGrid(false, M);
        system("pause");

        do {
            cout << "DIGITE AS COORDENADAS PRA ENVIAR UMA BOMBA ";
            cin >> x >> y;
            x--; y--;

        } while(!isValid(x, y) or isSea(M, x, y));

        if(isAShip(M, x, y)) {
            M[x][y] = EXPLOSION;
            system("cls");
            system("Color 64");
            cout << "BOO@@@@@@@@@OOOOOOMMMM!!!!!!!" << endl;
            printGrid(false, M);
            system("pause");
            system("Color 0F"); 
            return true;
        }else {
            M[x][y] = SEA;
        }
    }

    return false;
}

bool handleRoundAccordingToGamemode(int M[MAX][MAX], bool PLAYER1) {
    //this function also returns if the bomb reached the ship
    bool isBombReachedTheShip = false;

    if(PLAYER1) {
            //its time player1 to play...
            cout << "JOGADOR 1" << endl;
            isBombReachedTheShip = sendBomb(M, false, 0, 0);

    } else {
        if(GAME_MODE == MULTIPLAYER) {
            //so its time to player2 to play
            cout << "JOGADOR 2" << endl;
            isBombReachedTheShip = sendBomb(M, false, 0, 0);

        }else if(GAME_MODE == SINGLE_PLAYER) {
            //so its machine time to play
            pair<int, int> coordinates;
            do {
                coordinates = generatePosition();
            } while(isSea(M, coordinates.first, coordinates.second));

            cout << "SEU OPONENTE ESCOLHEU AS POSICOES: " << "X: " << coordinates.first+1 << " Y: " << coordinates.second+1 << endl;
            system("pause");

            isBombReachedTheShip = sendBomb(M, true, coordinates.first, coordinates.second);
        }
    }

    return isBombReachedTheShip;
}

void printScore(int bestPlayerScore, int bestPlayer, int score, bool isPlayer1) {
    system("Color 1F");

    if(score) {
        if(!isPlayer1 and GAME_MODE == SINGLE_PLAYER)
            cout << "SEU OPONENTE DERRUBOU UM NAVIO SEU NA ULTIMA RODADA E JOGARA NOVAMENTE! " << endl;
        else cout << "PARABENS! VOCE DERRUBOU UM NAVIO ACUMULANDO " << score << " PONTOS! " << endl;
    }

    printLine();
    cout << "RECORDE DE PONTUACOES: " << bestPlayerScore << endl;
    cout << "JOGADOR 1: " << SHIPS_PLAYER1 << " NAVIOS RESTANTES" << endl;
    cout << "JOGADOR 2: " << SHIPS_PLAYER2 << " NAVIOS RESTANTES" << endl;

    if(bestPlayerScore) {
        cout << "MELHOR JOGADOR: ";
        if(bestPlayer)
            cout << "JOGADOR 1" << endl;
        else cout << "JOGADOR 2" << endl;
    }
    system("pause");
    printLine();
    system("Color 0F");
}

bool verifyGameOver() {
    return SHIPS_PLAYER1 and SHIPS_PLAYER2;
}

int main() {

    initGame();
    int GRID1[MAX][MAX] = {{0}};
    int GRID2[MAX][MAX] = {{0}};

    if(DIFFICULT != 4) {
        cout << "JOGADOR 1" << endl;
        placeShips(GRID1);
        system("cls");
        cout << "VISAO GERAL DO SEU TABULEIRO" << endl;
        printGrid(true, GRID1);
        system("pause");
        system("cls");

        if(GAME_MODE == MULTIPLAYER) {
            cout << "JOGADOR 2" << endl;
            placeShips(GRID2);
            system("cls");
            cout << "VISAO GERAL DO SEU TABULEIRO" << endl;
            printGrid(true, GRID2);
        } else {
            cout << "COMPUTADOR esta escolhendo suas posicoes..." << endl;
            placeShipsMachine(GRID2);
        }

    }else {
        GRID1[0][1] = SHIP;
        GRID1[0][2] = SHIP;
        GRID1[0][3] = SHIP;
        GRID1[0][4] = SHIP;
        GRID1[1][4] = SHIP;
        GRID2[0][1] = SHIP;
        GRID2[0][2] = SHIP;
        GRID2[0][3] = SHIP;
        GRID2[0][4] = SHIP;
        GRID2[1][4] = SHIP;
    }
    
    bool isPlayer1 = randomStarter();
    bool isBombReachedTheShip = 0;
    int score = 0;
    int bestPlayerScore = 0;
    bool bestPlayer = 0;

    system("cls");
    do {   
        if(isPlayer1) {
            //player 1 plays against GRID2
            isBombReachedTheShip = handleRoundAccordingToGamemode(GRID2, isPlayer1);
            system("cls");
            printLine();
            cout << endl << "-> TABULEIRO DO SEU INIMIGO: " << endl;
            printGrid(false, GRID2);
            system("pause");
            if(isBombReachedTheShip) {
                SHIPS_PLAYER2--;
                score++;
            }
        } else {
            //so its player 2...
            isBombReachedTheShip = handleRoundAccordingToGamemode(GRID1, isPlayer1);
            system("cls");
            printLine();
            cout << endl << "-> SEU TABULEIRO: " << endl;
            printGrid(false, GRID1);
            system("pause");

            if(isBombReachedTheShip) {
                SHIPS_PLAYER1--;
                score++;
            }
        }

        if(!isBombReachedTheShip) {
            isPlayer1 = !isPlayer1;
            score = 0;
        }

        if(score >= bestPlayerScore) {
            bestPlayerScore = score;
            bestPlayer = isPlayer1;
        }
                
        system("cls");  
        printScore(bestPlayerScore, bestPlayer, score, isPlayer1);

    } while(verifyGameOver());

    return 0;
}