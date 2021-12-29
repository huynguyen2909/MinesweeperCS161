#include <fstream>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include<algorithm>
#include "function.h"
using namespace std;

void tutorial()
{
    cout << "Hello ohayou bonjour ni hao ma choi Minesweeper nha" << endl;
    cout << "Credit: Huu Hao & Trung Huy" << endl;
    cout << "DON'T KNOW HOW TO PLAY? READ THE DESCRIPTION CAREFULLY ^^" << endl;
    cout << "Description:" << endl;
    cout << "#1 Choose the coordinate of the box you want to open" << endl;
    cout << "#2 (?): mystery box" << endl;
    cout << "   (X): box with mine (displayed when the game is over)" << endl;
    cout << "   1-8: the number of mines surrounding that box" << endl;
    cout << "   ( ): empty box or the number of mines surrounding that box is 0" << endl;
    cout << "Let's roll! Good luck :))" << endl;
    cout << "Press any key to begin...";
    getch();
    cout << "\n\n";
}

void chooseMode(int& row, int& column, int& number_of_mines, int& choose_mode) 
{
Choosemode:
    system("cls");
    cout << "Choose mode you want to play:\n";
    cout << "1.Beginner (8x8 and 10 mines)\n";
    cout << "2.Intermediate (16x16 and 40 mines)\n";
    cout << "3.Expert(30x16 and 99 mines!)\n";
    cout << "4.custom\n";
    cout << "you choose: ";
    cin >> choose_mode;
    switch (choose_mode) {
    case 1: {
        row = 8;
        column = 8;
        number_of_mines = 10;
        break;
    }
    case 2: {
        row = 16;
        column = 16;
        number_of_mines = 40;
        break;
    }
    case 3: {
        row = 30;
        column = 16;
        number_of_mines = 99;
        break;
    }
    case 4: {
    Enter:
        cout << "Enter the row: ";
        cin >> row;
        if (row <= 0) {
            cout << "Enter an positive integer number please:((\n\n";
            goto Enter;
        }
        cout << "Enter the column: ";
        cin >> column;
        if (column <= 0) {
            cout << "Enter an positive integer number please:((\n\n";
            goto Enter;
        }
        cout << "Enter the number of mines: ";
        cin >> number_of_mines;
        if (number_of_mines <= 0 || number_of_mines >= row * column) {
            cout << "Enter an positive integer number or make sure that mine<row*column\n\n";
            goto Enter;
        }
        break;
    }
    default: {
        cout << "oh no choose a again\n";
        getch();
        goto Choosemode;
    }
    }
    row += 2;
    column += 2;
}

void prepare_board(int& row, int& column)
{
    int i, j;
    for (i = 0; i < row; ++i)
    {
        for (j = 0; j < column; ++j)
        {
            board[i][j] = 0;  //cho giá trị mỗi ô bằng 0
            check_opened[i][j] = false; //set tất cả các ô chưa mở thành false
            check_flagged[i][j] = false; //set tất cả các ô chưa cắm cờ thành false
        }
    }
    for (i = 0; i < row; ++i)  board[i][0] = board[i][column - 1] = -4;   
    for (i = 0; i < column; ++i) board[0][i] = board[row - 1][i] = -4;   
}

void calculate_hints(int& tempr, int& tempc)
{
    int m, n;
    for (m = tempr - 1; m <= tempr + 1; ++m)
    {
        for (n = tempc - 1; n <= tempc + 1; ++n)
        {
            if (board[m][n] >= 0) ++board[m][n];
        }
    }
}

void spread(int& therownum, int& thecolnum)
{
    int i, j;
    for (i = therownum - 1; i <= therownum + 1; ++i)
    {
        for (j = thecolnum - 1; j <= thecolnum + 1; ++j)
        {
            if (check_opened[i][j] == false)
            {
                check_opened[i][j] = true;
                if (board[i][j] == 0) spread(i, j);
            }
        }
    }
}

int number_of_opened_boxes(int& row, int& column)
{
    int i, j, sum = 0;
    for (i = 1; i < row - 1; ++i) // <= row - 2
    {
        for (j = 1; j < column - 1; ++j) // <= col - 2
        {
            if (check_opened[i][j] == true) sum++;
        }
    }
    return sum;
}

bool check_condition(int& therownum,int& thecolnum, int& row, int& column)
{
    if (therownum < 1 || thecolnum < 1 || therownum > row - 2 || thecolnum > column - 2) return false;
    return true;
}

/**
1) chữ số thể hiện số bom xung quanh
2) nếu không có bom xung quanh, ô sẽ hiện " "
3) những ô chưa mở sẽ là "(?)"
4) khi đã bấm trúng bom, ô có bom sẽ là "(X)"
**/
void draw_board(int& row, int& column)
{
    int i, j;
    cout << "  ";
    if (column - 2 >= 9)
    {
        for (i = 1; i <= 8; i++)
        {
            cout << "  " << i << "  ";
        }
        cout << "  " << 9 << "    ";
        for (i = 10; i < column - 1; i++)
        {
            cout << i << "   ";
        }
    }
    else
    {
        for (i = 1; i < column - 1; i++)
        {
            cout << "  " << i << "  ";
        }
    }
    cout << "\n\n";
    for (i = 1; i < row - 1; i++) // <= row - 2
    {
        if (i <= 9) cout << i << " ";
        else cout << i;
        for (j = 1; j < column - 1; j++) // <= col - 2
        {
            switch (check_opened[i][j])
            {
            case true:
                switch (board[i][j])
                {
                case 0: cout << "     "; break;
                default: cout << "  " << board[i][j] << "  ";
                }
                break;

            default:
                switch (check_flagged[i][j])
                {
                case true:
                    cout << " *P* "; break;

                default:
                    cout << " (?) "; break;
                }
                // cout << " (?) "; break;
            }
        }
        cout << "\n" << endl;
    }
}


void game_over(int x, double& y, int& row, int& column, int& choose_mode)
{
    int i, j;
    cout << "  ";
    for (i = 1; i < column - 1; i++) // col - 2
    {
        cout << "  " << i << "  ";
    }
    cout << "\n\n";
    for (i = 1; i < row - 1 ; i++) // <= row - 2
    {
        cout << i << " ";
        for (j = 1; j < column - 1 ; j++) // col - 2
        {
            switch (board[i][j])
            {
            case 0: cout << "     "; break;
            case -1: cout << " (X) "; break;
            default: cout << "  " << board[i][j] << "  ";
            }
        }
        cout << "\n" << endl;
    }
    if (x == -1)
    {
        cout << "You were blown off by a mine :(" << endl;
        cout << "GAME OVER!";
        cout << "Press any key to play again" << endl;
    }
    else
    {
        if(choose_mode != 4) {
        top mode[3];
        int check;
        ifstream fin;
        ofstream fout;
        for (int i = 0; i < 3; ++i)  mode[i].check_exist = false;
        fin.open("Top.txt");
        if (fin) {
            fin >> check;
            while (fin && !fin.eof()){
            if (check != -1) {
                fin >> mode[check].modenum;
                for (int i = 0; i < mode[check].modenum; ++i) fin >> mode[check].ranki[i];
                mode[check].check_exist = true;
                if (choose_mode - 1 == check){
                ++mode[check].modenum;
                mode[check].ranki[mode[check].modenum - 1] = y;
                sort(mode[check].ranki, mode[check].ranki + mode[check].modenum);
                mode[check].modenum = min(mode[check].modenum, 5);
                }
            }
            fin >> check;
            }
            }
        fout.open("Top.txt");
        if (mode[choose_mode - 1].check_exist == false) {
            mode[choose_mode - 1].check_exist = true;
            mode[choose_mode - 1].modenum = 1;
            mode[choose_mode - 1].ranki[0] = y;
        }
        for (int i = 0; i < 3; ++i) {
            if (mode[i].check_exist) {
                fout << -1 << endl;
                fout << i << "  ";
                fout << mode[i].modenum << endl; //fout << mode[i].modenum << endl;
                for (int j = 0; j < mode[i].modenum; ++j) {
                    fout << mode[i].ranki[j] << endl;
                }
            }
        }
        
        cout << "You are amazing! :D" << endl;
        cout << "YOU WON THE GAME FOR " << y << " SECONDS " << endl;
        if (choose_mode != 4){
        cout << "TOP 5 PLAYER OF YOUR MODE (NOT INCLUDE CUSTOM): \n";
        for (int i = 0; i < mode[choose_mode - 1].modenum; ++i) cout << mode[choose_mode - 1].ranki[i] << " SECONDS" << endl;
        }
        cout << "Press any key to play again" << endl;
        fin.close(); fout.close();
    }else{
        cout << "You are amazing! :D" << endl;
        cout << "YOU WON THE GAME FOR " << y << " SECONDS " << endl;
        cout << "Press any key to play again" << endl;
    }
    }
}