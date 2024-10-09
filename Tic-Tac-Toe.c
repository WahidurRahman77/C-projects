#include <stdio.h>
#include <windows.h>
#define SIZE 3
#define ROUNDS 3

// Structure to store player information and their wins
typedef struct
{
    char player;
    int wins;
}   HighScore;

// Function prototypes
void printBoard(char board[SIZE][SIZE]);
int checkWin(char board[SIZE][SIZE], char player);
int isBoardFull(char board[SIZE][SIZE]);
void getPlayerMove(char board[SIZE][SIZE], char player);
void resetBoard(char board[SIZE][SIZE]);
char playRound();
void saveHighScores(HighScore xScore, HighScore oScore, HighScore tieScore);
void loadHighScores(HighScore *xScore, HighScore *oScore, HighScore *tieScore);
void playTournament();
void gotoxy(int x, int y);
void setTextColor(int color);
void resetTextColor();
int getConsoleWidth();
int getConsoleHeight();
void printframe();
void Usermanual();

int main()
{
   int n, consoleWidth, consoleHeight;
   consoleWidth = getConsoleWidth();
   consoleHeight = getConsoleHeight();
   int menuStartY = consoleHeight / 2 - 2;

   while (1)
   {
       printframe();
       gotoxy(consoleWidth / 2 - 4, menuStartY-1);
       setTextColor(14);
       printf("Menu\n");
       gotoxy(consoleWidth / 2 - 10, menuStartY + 1);
       setTextColor(6);
       printf("1. Play Tournament\n");
       gotoxy(consoleWidth / 2 - 10, menuStartY + 2);
       setTextColor(15);
       printf("2. User Manual\n");
       gotoxy(consoleWidth / 2 - 10, menuStartY + 3);
       setTextColor(4);
       printf("3. Exit\n");
       resetTextColor();
       gotoxy(consoleWidth / 2 - 10, menuStartY + 5);
       printf("Choose Option: ");
       scanf("%d", &n);
       if (n == 1)
       {
          system("cls");
          gotoxy(consoleWidth / 2 - 10, menuStartY);
          playTournament();
       }
       else if (n == 2)
       {
           system("cls");
           printframe();
           Usermanual();

       }
       else if (n == 3)
       {
           system("cls");
           printframe();
           gotoxy(consoleWidth / 2 - 10, menuStartY + 1);
           setTextColor(15);
           printf("Thanks for playing our game\n");
           resetTextColor();
           break;

       }
       gotoxy(consoleWidth / 2 - 15, menuStartY + 11);
       setTextColor(14);
       const char *message = "Press Enter to return to the menu...";
       int i = 0;
       while (message[i] != '\0')
       {
           printf("%c", message[i]);
           fflush(stdout);
           Sleep(50);
           i++;
       }
       getchar();
       getchar();
       system("cls");
       printframe();
   }
   return 0;
}

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if (!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h, c);
}

void printBoard(char board[SIZE][SIZE])
{
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int startX = consoleWidth / 2 - 5;
    int startY = consoleHeight / 2 - 2;
    setTextColor(2);
    for (int i = 0; i < SIZE; i++)
    {
        gotoxy(startX, startY + i * 2);
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 'X')
            {
                setTextColor(4);
                printf(" %c ", board[i][j]);
                resetTextColor();
            }
            else if (board[i][j] == 'O')
            {
                setTextColor(1);
                printf(" %c ", board[i][j]);
                resetTextColor();
            }
            else
            {
                printf(" %c ", board[i][j]);
            }
            setTextColor(2);
            if (j < SIZE - 1)
            {
                printf("|");
            }
        }
        if (i < SIZE - 1)
        {
            gotoxy(startX, startY + i * 2 + 1);
            printf("-----------");
        }
    }
    resetTextColor();
    printf("\n");

}

int checkWin(char board[SIZE][SIZE], char player)
{
    for (int i = 0; i < SIZE; i++)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        {
            return 1;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return 1;
    }

    return 0;
}

int isBoardFull(char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}

void getPlayerMove(char board[SIZE][SIZE], char player)
{
    int row, col;
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int promptY = consoleHeight / 2 + SIZE + 2;

    while (1)
    {
        gotoxy(consoleWidth / 2 - 23, promptY);
        printf("Player %c, enter your move (row and column, e.g., 1 1): ", player);
        if (scanf("%d %d", &row, &col) != 2 || row < 1 || row > SIZE || col < 1 || col > SIZE ||
            board[row - 1][col - 1] != ' ')
        {
            while (getchar() != '\n');
            gotoxy(consoleWidth / 2 - 10, promptY + 1);
            printf("Invalid move. Please try again.\n");
        }
        else
        {
            board[row - 1][col - 1] = player;
            gotoxy(consoleWidth / 2 - 10, promptY+1);
            printf("                                \n");
            break;
        }
    }
}

void resetBoard(char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }
}

char playRound()
{
    char board[SIZE][SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char currentPlayer = 'X';
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int startY = consoleHeight / 2 - 5;
    while (1)
    {
        gotoxy(consoleWidth / 2 - 6, startY);
        printf("Player %c's turn:\n", currentPlayer);
        printBoard(board);
        getPlayerMove(board, currentPlayer);
        gotoxy(consoleWidth / 2 - 10, startY+9);
        printf("                            \n");
        if (checkWin(board, currentPlayer))
        {
            printBoard(board);
            gotoxy(consoleWidth / 2 - 10, startY+9);
            setTextColor(13);
            char buffer[30];
            sprintf(buffer, "Player %c wins this round!\n", currentPlayer);

            int i = 0;
            gotoxy(consoleWidth / 2 - 10, startY + 9);
            while (buffer[i] != '\0')
            {
                printf("%c", buffer[i]);
                fflush(stdout);
                Sleep(70);
                i++;
            }
            usleep(10000);
            gotoxy(consoleWidth / 2 - 10, startY + 9);
            printf("                          \n", currentPlayer);
            resetTextColor();
            system("cls");
            return currentPlayer;
        }

        if (isBoardFull(board))
        {
            printBoard(board);
            gotoxy(consoleWidth / 2 - 10, startY+9);
            setTextColor(12);
            char buffer[30];
            sprintf(buffer, "The round is a tie!\n");

            int i = 0;
            gotoxy(consoleWidth / 2 - 10, startY + 9);
            while (buffer[i] != '\0')
            {
                printf("%c", buffer[i]);
                fflush(stdout);
                Sleep(70);
                i++;
            }
            usleep(100);
            system("cls");
            resetTextColor();
            return ' ';
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

void saveHighScores(HighScore xScore, HighScore oScore, HighScore tieScore)
{
    FILE *file = fopen("Score.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "X %d\n", xScore.wins);
        fprintf(file, "O %d\n", oScore.wins);
        fprintf(file, "Tie %d\n", tieScore.wins);
        fclose(file);
    }
    else
    {
        printf("Error: Could not open the file for saving high scores.\n");
    }
}

void loadHighScores(HighScore *xScore, HighScore *oScore, HighScore *tieScore)
{
    FILE *file = fopen("Score.txt", "r");
    if (file != NULL)
    {
        fscanf(file, "X %d", &xScore->wins);
        fscanf(file, "O %d", &oScore->wins);
        fscanf(file, "Tie %d", &tieScore->wins);
        fclose(file);
    }
    else
    {
        printf("Error: Could not open the file for loading high scores.\n");
    }
}

void playTournament()
{
    HighScore xScore = {'X', 0};
    HighScore oScore = {'O', 0};
    HighScore tieScore = {'T', 0};
    loadHighScores(&xScore, &oScore, &tieScore);

    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int startY = consoleHeight / 2 - 5;
    printframe();
    gotoxy(consoleWidth / 2 - 15, startY);
    setTextColor(7);
    printf("*****************************************\n");
    gotoxy(consoleWidth / 2 - 14, startY-1);
    setTextColor(9);

    const char *message = "Welcome to the Tic-Tac-Toe Tournament!";
    int i = 0;
    while (message[i] != '\0')
    {
        if(i > 14 && 26 > i)
        {
            setTextColor(4);
        }
        else
        {
            setTextColor(9);
        }
        printf("%c", message[i]);
        fflush(stdout);
        Sleep(50);
        i++;
    }
    resetTextColor();
    usleep(900000);
    system("cls");
    printframe();
    for (int round = 1; round <= ROUNDS; round++)
    {
        printframe();
        gotoxy(consoleWidth / 2 - 3, startY -1);
        setTextColor(14);
        char buffer[20];
        sprintf(buffer, "Round %d\n", round);

        int i = 0;
        gotoxy(consoleWidth / 2 - 3, startY - 1);
        while (buffer[i] != '\0')
        {
            printf("%c", buffer[i]);
            fflush(stdout);
            Sleep(100);
            i++;
        }

        char result = playRound();


        if (result == 'X')
        {
            xScore.wins++;
        }
        else if (result == 'O')
        {
            oScore.wins++;
        }
        else
        {
            tieScore.wins++;
        }
    }

    system("cls");
    printframe();
    setTextColor(15);
    gotoxy(consoleWidth / 2 - 10, startY + 1);
    printf("Tournament Results:\n");
    gotoxy(consoleWidth / 2 - 10, startY + 2);
    printf("Player X wins: %d\n", xScore.wins);
    gotoxy(consoleWidth / 2 - 10, startY + 3);
    printf("Player O wins: %d\n", oScore.wins);
    gotoxy(consoleWidth / 2 - 10, startY + 4);
    printf("Ties: %d\n", tieScore.wins);
    resetTextColor();

    if (xScore.wins > oScore.wins)
    {
        gotoxy(consoleWidth / 2 - 11, startY + 8);
        setTextColor(2);
        const char *message = "Player X is the overall winner!";
        int i = 0;
        while (message[i] != '\0')
        {
            printf("%c", message[i]);
            fflush(stdout);
            Sleep(50);
            i++;
        }
        usleep(50);
        resetTextColor();
    }
    else if (oScore.wins > xScore.wins)
    {
        gotoxy(consoleWidth / 2 - 11, startY + 8);
        setTextColor(2);
        const char *message = "Player O is the overall winner!";
        int i = 0;
        while (message[i] != '\0')
        {
            printf("%c", message[i]);
            fflush(stdout);
            Sleep(50);
            i++;
        }
        usleep(50);
        resetTextColor();
    }
    else
    {
        gotoxy(consoleWidth / 2 - 8, startY + 8);
        setTextColor(9);
        const char *message = "The tournament is a tie!";
        int i = 0;
        while (message[i] != '\0')
        {
            printf("%c", message[i]);
            fflush(stdout);
            Sleep(50);
            i++;
        }
        usleep(50);
        resetTextColor();
    }

    saveHighScores(xScore, oScore, tieScore);
}

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

int getConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return rows;
}

void setTextColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void resetTextColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
}

void printframe()
{
   int consoleWidth = getConsoleWidth();
   int consoleHeight = getConsoleHeight();
   int menuStartY = consoleHeight / 2 - 2;
   setTextColor(3);
   for(int i=0; i<25;i++)
   {
       gotoxy(consoleWidth / 2 - 40, (menuStartY - 10) + i);
       printf("****");
   }
   for(int i=0; i<80;i++)
   {
       gotoxy((consoleWidth / 2 - 40) + i, menuStartY - 10);
       printf("*");
       gotoxy((consoleWidth / 2 - 40) + i, menuStartY - 9);
       printf("*");
   }
   for(int i=0; i<25;i++)
   {
       gotoxy(consoleWidth / 2 + 40, (menuStartY - 10) + i);
       printf("****");
   }
   for(int i=0; i<80;i++)
   {
       gotoxy((consoleWidth / 2 - 40) + i, menuStartY + 13);
       printf("*");
       gotoxy((consoleWidth / 2 - 40) + i, menuStartY + 14);
       printf("*");
   }
   resetTextColor();
}

void Usermanual()
{
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int startY = consoleHeight / 2 - 8;

    setTextColor(14);
    gotoxy(consoleWidth / 2 - 17, startY-1);
    printf("Instructions: How to Play ");
    setTextColor(4);
    gotoxy(consoleWidth / 2 + 9, startY-1);
    printf("Tic-Tac-Toe\n");
    setTextColor(15);
    gotoxy(consoleWidth / 2 - 35, startY + 1);
    printf("1. Get three of your marks (X or O) in a row, column, or diagonal.\n");
    gotoxy(consoleWidth / 2 - 35, startY + 3);
    printf("2. Gameplay: Two players take turns to place their marks on the 3x3 grid.\n");
    gotoxy(consoleWidth / 2 - 22, startY + 4);
    printf("Players must enter the row and column (e.g., '1 1') to place\n");
    gotoxy(consoleWidth / 2 - 22, startY + 5);
    printf("their mark.\n");
    gotoxy(consoleWidth / 2 - 35, startY + 6);
    printf("3. Winning: A player wins by placing three of their marks in a row, column,\n");
    gotoxy(consoleWidth / 2 - 23, startY + 7);
    printf("or diagonal.\n");
    gotoxy(consoleWidth / 2 - 35, startY + 8);
    printf("4. Tie: If all nine squares are filled and no player has won, the game is\n");
    gotoxy(consoleWidth / 2 - 27, startY + 9);
    printf("a tie.\n");
    gotoxy(consoleWidth / 2 - 35, startY + 10);
    printf("5. Rounds: In tournament mode, the game consists of multiple rounds. The\n");
    gotoxy(consoleWidth / 2 - 24, startY + 11);
    printf("player  with the most wins at the end  of  all  rounds is the\n");
    gotoxy(consoleWidth / 2 - 24, startY + 12);
    printf("overall winner.\n");
    gotoxy(consoleWidth / 2 - 35, startY + 14);
    printf("6. Controls: Use numbers to input your move(e.g., 1 2 for row 1, column 2).\n");
    resetTextColor();
}


