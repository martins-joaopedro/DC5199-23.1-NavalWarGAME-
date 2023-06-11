#include <bits/stdc++.h>

using namespace std;
#define MAX 15

int GAME_MODE = 0;
int DIFFICULT = 0;
int NUMBER_OF_SHIPS = 0;
int SHIPS_PLAYER1 = 0;
int SHIPS_PLAYER2 = 0;
int GRID_SIZE = 0;

const int SHIP = 1;
const int EXPLOSION = 2;
const int SEA = 3;

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
    while(!DIFFICULT or !START) {
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
            

        } else if(!START) { 
            printLine();
            cout << "SEU MODO DE JOGO FOI ESCOLHIDO! " << endl;
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
                    DIFFICULT = 0;                                 
                break;

                default:
                    cout << "VALOR INVALIDO - DIGITE NOVAMENTE " << endl;
                    system("pause");
                break;  
            } 
        }
    }
}

bool verifyEmptyPlace(int M[MAX][MAX], int i, int j) {
    if(i >= GRID_SIZE or j >= GRID_SIZE or i<0 or j<0)
        return false;
    return !M[i][j];
}

bool theresAShip(int M[MAX][MAX], int i, int j) {
    return M[i][j] == SHIP;
}

void placeShips(int M[MAX][MAX]) {
    int x, y;
    for(int i=0; i<NUMBER_OF_SHIPS; i++) {
        cout << "DIGITE AS COORDENADAS PRA POSICIONAR SEU BARCO " << i+1 << endl;
        cin >> x >> y;
        while(!verifyEmptyPlace(M, x, y)) {
            cout << "POSICAO INVALIDA - DIGITE NOVAMENTE" << endl;
            cin >> x >> y;
        }
        M[x][y] = SHIP;
    }
}

void printGrid(bool debug, int M[MAX][MAX]) {
    for(int i=0; i<GRID_SIZE; i++) {   
        for(int j=0; j<GRID_SIZE; j++)  {
            if(debug) {
                if(M[i][j] == SHIP)
                    cout << "[ <()> ] ";
                else cout << "[      ] ";
            }else {
                if(M[i][j] == EXPLOSION )
                    cout <<  "[ x# ~ ] ";
                else if(M[i][j] == SEA )
                    cout <<  "[ ~~~~ ] ";
                else cout << "[      ] ";
            }
        }
        cout << endl;
    }     
}

bool randomStarter() {
    unsigned seed = time(0);
    srand(seed);
    int N = rand()%5;

    return N%2 == 0;
}

bool sendBomb(int M[MAX][MAX], bool hitted, int score) {
    if(hitted) 
        cout << "PARABENS! VOCE ACERTOU UM NAVIO NA ULTIMA RODADA, ACUMULANDO " << score << " PONTOS! " << endl;

    int x, y;
    cout << "DIGITE AS COORDENADAS PRA ENVIAR UMA BOMBA ";
    cin >> x >> y;

    while((x<0 or x>GRID_SIZE) or (y<0 or y>GRID_SIZE)) {
        cin >> x >> y;
    }

    if(theresAShip(M, x, y)) {
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
    
    return false;
}

void printScore(int score, int player) {
    system("Color 1F");
    printLine();
    cout << "RECORDE DE PONTUACOES: " << score << endl;
    cout << "JOGADOR 1: " << SHIPS_PLAYER1 << " NAVIOS RESTANTES" << endl;
    cout << "JOGADOR 2: " << SHIPS_PLAYER2 << " NAVIOS RESTANTES" << endl;
    if(score) {
        cout << "MELHOR JOGADOR: ";
        if(player)
            cout << "JOGADOR 1" << endl;
        else cout << "JOGADOR 2" << endl;
    }
    system("pause");
    printLine();
    system("Color 0F");
}

bool verifyEndGame() {
    return SHIPS_PLAYER1 and SHIPS_PLAYER2;
}

int main() {

    initGame();
    int GRID1[MAX][MAX] = {{0}};
    int GRID2[MAX][MAX] = {{0}};

    if(DIFFICULT != 4) {
        cout << "JOGADOR 1" << endl;
        placeShips(GRID1);
        cout << "JOGADOR 2" << endl;
        placeShips(GRID2);
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
    
    bool PLAYER1 = randomStarter();
    bool hitted = false;
    int score = 0;
    int bestPlayerScore = 0;
    bool bestPlayer = 0;

    system("cls");
    do {
        // true => jogador 1 - false => jogador 2        
        if(PLAYER1) {
            cout << "JOGADOR 1" << endl;
            printLine();
            printGrid(false, GRID2);
            system("pause");
            hitted = sendBomb(GRID2, hitted, score);
            if(hitted) {
                SHIPS_PLAYER2--;
                score++;
            }
        } else {
            //so its player 2...
            cout << "JOGADOR 2" << endl;
            printLine();
            printGrid(false, GRID1);
            system("pause");
            hitted = sendBomb(GRID1, hitted, score);
            if(hitted) {
                SHIPS_PLAYER1--;
                score++;
            }
        }

        if(!hitted) {
            PLAYER1 = !PLAYER1;
            score = 0;
        }

        if(score >= bestPlayerScore) {
            bestPlayerScore = score;
            bestPlayer = PLAYER1;
        }
                
        system("cls");  
        printScore(bestPlayerScore, bestPlayer);

    } while(verifyEndGame());

    return 0;
}