#include <stdio.h>
#include <limits.h>



int equals(int a,int b,int c){
    return a==b && a==c && a!=0;
}


int checkWin(int board[9]){
    //calculate this function if a player has won
    int wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    //horizontal:{0,1,2},{3,4,5},{6,7,8}
    //vertical:{0,3,6},{1,4,7},{2,5,8}
    //diagonal:{0,4,8},{2,4,6}
    for(int i = 0; i < 8; ++i) {
        int a=board[wins[i][0]];
        int b=board[wins[i][1]];
        int c=board[wins[i][2]];
        if(equals(a,b,c)){
            return c;
        }
    }
    return 0;
}

char boardTable(int point){
    switch (point) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}
void BoardDraw(int table[9]){
    printf("  (0) %c  |  (1) %c  |  (2)%c  \n",boardTable(table[0]),boardTable(table[1]),boardTable(table[2]));
    printf("---------+--------+---------\n");
    printf("  (3) %c  |  (4) %c  |  (5)%c  \n",boardTable(table[3]),boardTable(table[4]),boardTable(table[5]));
    printf("---------+--------+---------\n");
    printf("  (6) %c  |  (7) %c  |  (8)%c  \n",boardTable(table[6]),boardTable(table[7]),boardTable(table[8]));
}

int minimax(int board[9], int player) {

    int winner = checkWin(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = INT_MIN;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            board[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;

}

void computerMove(int boardTable[9]){
    int move[9]={0};
    int bestScore=INT_MIN;
    for (int i = 0; i < 9; ++i) {
            if (boardTable[i] == 0){
                boardTable[i] = 1;
                int tempScore= -minimax(boardTable,-1);
                boardTable[i] = 0;
                if (tempScore>bestScore){
                    bestScore=tempScore;
                    move[0]=i;
                }
            }
        }
    boardTable[move[0]] = 1;
}

void playerMove(int board[9]){
    int i=0;
    do {
        printf("\n Input move [0,1,2,3,4,5,6,7,8]:");
        scanf("%d",&i);
    } while (i >= 9 || i < 0 && board[i]!=0);
        board[i] = -1;
}

int main() {
    int board[9]={0,0,0,0,0,0,0,0,0};
    printf("Welcome to the Tic Tac Toe games\n");
    printf("Computer:O , You:X\nPlay 1st or 2st:");
    int player=0;
    scanf("%d",&player);
    for (int i = 0; i <9 && checkWin(board) == 0; i++) {
        if ((i+player) % 2 == 0)
            computerMove(board);
        else{
            BoardDraw(board);
            playerMove(board);
        }
    }
    switch (checkWin(board)) {
        case 0:
            BoardDraw(board);
            printf("A draw\n");
            break;
        case 1:
            BoardDraw(board);
            printf("You Lose\n");
            break;
        case -1:
            BoardDraw(board);
            printf("you win");
            break;

    }
    return 0;
}
