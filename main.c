#include<stdio.h>
void displayBoard(char board[3][3]){
    int i,j;
    printf("The Current Board State.\n*-----*-----*-----*\n");
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(j==0) printf("|");
            printf("  %c  |",board[i][j]);
        }
        printf("\n*-----*-----*-----*\n");
    }
}
int winner(char board[3][3], int i, int j) {
    if(
    (board[i][j] == board[(i+1)%3][(j+1)%3] && board[(i+2)%3][(j+2)%3] == board[(i+1)%3][(j+1)%3]) || //leading diagonal
    (board[i][j] == board[(i+1)%3][(j-1)%3] && board[(i+1)%3][(j-1)%3] == board[(i+2)%3][(j-2)%3]) || //trailing diagonal
    (board[i][j] == board[i][(j+1)%3] && board[i][(j+1)%3] == board[i][(j+2)%3]) || //row
    (board[i][j] == board[(i+1)%3][j] && board[(i+1)%3][j] == board[(i+2)%3][j]) //column
    ) { 
        return 1;
    }
    else{
        return 0;
    }
}
int validMoves(char board[3][3], int i, int j) {
    if(i<0 || j<0 || i>2 || j>2 || board[i][j] != ' ') 
        return 0;
    return 1;
}
int game(char board[3][3]) {
    displayBoard(board);
    char player[] = {'X','O'};
    int i, j, moves = 0;
    do {
        printf("Player %c, enter your move: ",player[moves%2]);
        scanf("%d %d",&i,&j);
        // printf("\n%d %d %d %d",i,j, validMoves(board,i,j), (board[i][j]!=' '));
        if(validMoves(board,i,j)){
            board[i][j] = player[moves%2];
            moves++;
            printf("%d %d",moves, winner(board,i,j));
            displayBoard(board);
            if(winner(board,i,j)) return moves-1;
        }
        else{
            printf("Invalid move.\nEnter a valid move.\n");
        }
    }while(moves < 9);
    return 0;
}
int minimax(char board[3][3], char player) {
    int move = -1;
    int score = -2;
    int i, j;
    for(i = 0; i < 3; ++i) {
        for(j = 0; j<3; j++) {
            if(board[i][j] == ' ') {//If legal,
                board[i][j] = player;//Try the move
                if(player == 'X') player = 'O';
                else player = 'X';
                int thisScore = -minimax(board, player);
                if(thisScore > score) {
                    score = thisScore;
                    move = i;
                }
                board[i][j] = ' ';
            }
        }
    }
    if(move == -1) return 0;
    return score;
}
void ai_play(char board[3][3]){
    int i,j, score=-2, temp_score,x,y;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(board[i][j] == ' '){
                temp_score = -minimax(board, 'X');
                board[i][j] = 'O';
                if(temp_score > score) {
                    score = temp_score;
                    x = i;
                    y = j;
                }
                board[i][j] = ' ';
            }
        }
    }
    board[x][y] = 'O';
}
int ai_game(char board[3][3]){
    int i,j, moves=0;
    do {
        printf("Player X, enter your move: ");
        scanf("%d %d",&i,&j);
        if(validMoves(board,i,j)){
            board[i][j] = 'X';
            moves++;
            displayBoard(board);
            if(winner(board,i,j)) return moves-1;
            ai_play(board);
            moves++;
             displayBoard(board);
            if(winner(board,i,j)) return moves-1;
        }
        else{
            printf("Invalid move.\nEnter a valid move.\n");
        }
    }while(moves<9);
}
int main() {
    int choice, win;
    printf("Welcome to Tic Tac Toe!!!\n Enter 1 for 2 player mode.\n Enter 2 for single player mode.\n Enter choice \t");
    scanf("%d",&choice);
    do {
        char board[3][3]={{' ',' ',' '},
                          {' ',' ',' '},
                          {' ',' ',' '}};
        switch(choice) {
            case 1:
                printf("2 player mode selected.\n");
                win = game(board);
                if(win > 0) 
                    printf("The winner is Player %d.\n",((win%2)+1));
                else 
                    printf("The game is a draw.\n");
                break;
            case 2:
                printf("Single player mode selected.\n");
                win = ai_game(board);
                if(win > 0)
                   printf("The winner is Player %d.\n",((win%2)));
                else
                   printf("The game is a draw against the AI.\n");
                break;
            default:
                printf("You entered %d. Which is an invalid choice.\n Please Enter a valid choice. \n Enter 0 to exit.",choice);
        }
        printf("\n Enter 1 for 2 player mode.\n Enter 2 for single player mode.\n Enter choice \t\n");
        scanf("%d",&choice);
    }while(choice!=0); //choice==0 for exit
    return 0;    
}
