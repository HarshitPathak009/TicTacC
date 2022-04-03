#include<stdio.h>
int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}
int min(int num1, int num2) 
{
    return (num1 > num2 ) ? num2 : num1;
}
void displayBoard(char board[3][3])
{
    int i,j;
    printf("The Current Board State.\n*-----*-----*-----*\n");
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(j==0) printf("|");
            printf("  %c  |",board[i][j]);
        }
        printf("\n*-----*-----*-----*\n");
    }
}
int isMovesLeft(char board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]==' ')
                return 1;
    return 0;
}
 
int winner(char board[3][3], int i, int j) 
{
    if(
    (board[i][j] == board[(i+1)%3][(j+1)%3] && board[(i+2)%3][(j+2)%3] == board[(i+1)%3][(j+1)%3]) || //leading diagonal
    (board[i][j] == board[(i+1)%3][(j-1)%3] && board[(i+1)%3][(j-1)%3] == board[(i+2)%3][(j-2)%3]) || //trailing diagonal
    (board[i][j] == board[i][(j+1)%3] && board[i][(j+1)%3] == board[i][(j+2)%3]) || //row
    (board[i][j] == board[(i+1)%3][j] && board[(i+1)%3][j] == board[(i+2)%3][j]) //column
    ) 
    { 
        if(board[i][j] == 'X')
            return -1;
        else if(board[i][j] == 'O')
            return 1;
    }
    else
    {
        return 0;
    }
}
int validMoves(char board[3][3], int i, int j) 
{
    if(i<0 || j<0 || i>2 || j>2 || board[i][j] != ' ') 
        return 0;
    return 1;
}
int game(char board[3][3]) 
{
    displayBoard(board);
    char player[] = {'X','O'};
    int i, j;
    int moves = 0;
    do 
    {
        printf("Player %c, enter your move: ",player[moves%2]);
        scanf("%d %d",&i,&j);
        if(validMoves(board,i,j))
        {
            board[i][j] = player[moves%2];
            moves++;
            printf("%d %d",moves, winner(board,i,j));
            displayBoard(board);
            if(winner(board,i,j)) return moves-1;
        }
        else
        {
            printf("Invalid move.\nEnter a valid move.\n");
        }
    }while(moves < 9);
    return 0;
}
int minimax(char board[3][3], char player, int MaxPlayer, int x, int y) 
{
    int score = winner(board,x, y);
    if (score == 1)
        return score;
    if (score == -1)
        return score;
    if (isMovesLeft(board)==0)
        return 0;
    if (MaxPlayer)
    {
        int best = -1000;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]==' ')
                {
                    board[i][j] = player;
                    best = max( best, minimax(board, 'O', 0, i, j));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]==' ')
                {
                    board[i][j] = player;
                    best = min(best, minimax(board, 'X', 1, i, j));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}
void ai_play(char board[3][3])
{
    int best_val = -1000;
    int row = -1;
    int column = -1;
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (board[i][j]==' ')
            {
                board[i][j] = 'O';
                int move_val = minimax(board, 'O', 0, i, j);
                board[i][j] = ' ';
                if (move_val > best_val)
                {
                    row = i;
                    column = j;
                    best_val = move_val;
                }
            }
        }
    }
    board[row][column] = 'O';
}
int ai_game(char board[3][3])
{
    int i,j, moves=0;
    do 
    {
        printf("Player X, enter your move: ");
        scanf("%d %d",&i,&j);
        if(validMoves(board,i,j))
        {
            board[i][j] = 'X';
            moves++;
            displayBoard(board);
            if(winner(board,i,j)) return moves-1;
            ai_play(board);
            moves++;
            displayBoard(board);
            if(winner(board,i,j)) return moves-1;
        }
        else
        {
            printf("Invalid move.\nEnter a valid move.\n");
        }
    }while(moves<9);
}
int main() 
{
    int choice, win;
    printf("Welcome to Tic Tac Toe!!!\n Enter 1 for 2 player mode.\n Enter 2 for single player mode.\n Enter choice \t");
    scanf("%d",&choice);
    do 
    {
        char board[3][3]={{' ',' ',' '},
                          {' ',' ',' '},
                          {' ',' ',' '}};
        switch(choice) 
        {
            case 1:
                printf("2 player mode selected.\n");
                win = game(board);
                if(win == -1) 
                    printf("The winner is Player 1.\n");
                else if(win == 1)
                    printf("The winner is Player 2.\n");
                else 
                    printf("The game is a draw.\n");
                displayBoard(board);
                break;
            case 2:
                printf("Single player mode selected.\n");
                win = ai_game(board);
                if(win == -1) 
                    printf("The winner is Player 1.\n");
                else if(win == 1)
                    printf("The winner is Player 2.\n");
                else 
                    printf("The game is a draw.\n");
                displayBoard(board);
                break;
            default:
                printf("You entered %d. Which is an invalid choice.\n Please Enter a valid choice. \n Enter 0 to exit.",choice);
        }
        printf("\n Enter 1 for 2 player mode.\n Enter 2 for single player mode.\n Enter choice \t\n");
        scanf("%d",&choice);
    }while(choice!=0); //choice==0 for exit
    return 0;    
}
