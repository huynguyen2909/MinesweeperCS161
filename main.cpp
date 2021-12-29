#include <fstream>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include<algorithm>
#include "function.cpp"
using namespace std;

int main()
{
    clock_t start, end;
    double time_use;
    //làm tròn thời gian lấy 2 chữ số thập phân
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "\n";
gameplay:
    int i, j, tempr, tempc, row, column, number_of_mines;
    int behaviour, choose_mode;
    int therownum;
    int thecolnum;
    bool start_time_check = true;

    system("cls");
    tutorial();         //giới thiệu và hướng dẫn 
    chooseMode(row, column, number_of_mines, choose_mode);   //chọn chế độ
    int number_of_safe_boxes = (row - 2) * (column - 2) - number_of_mines;   //ô chưa mở = tổng số ô trừ số bom
    prepare_board(row, column); //khởi tạo các giá trị thô sơ cho bảng

    //tạo mìn ngẫu nhiên, gán giá trị -1 cho ô nào có mìn
    srand(time(NULL));   
    i = 1;
    while (i <= number_of_mines)
    {
        tempr = 1 + rand() % (row - 2) ; //rand()%(max - min + 1) + min để nhận kết quả trong đoạn [min;max] ~ rand()%((row -2) - 1 + 1) + 1
        tempc = 1 + rand() % (column - 2) ;
        if (board[tempr][tempc] != -1) // 
        {
            board[tempr][tempc] = -1; //ô nào có giá trị -1 thì là mìn
            calculate_hints(tempr, tempc);  
            ++i;
        }
    }
    /* GAMEPLAY */
    while (number_of_opened_boxes(row, column) != number_of_safe_boxes && board[therownum][thecolnum] != -1)
    {
        cout << "\n";
    after_flagging:
        system("cls");  //clean màn hình
        cout <<"Number of mines: " << number_of_mines<< endl;
        draw_board(row, column);  //vẽ bảng (cập nhật sau mỗi lần chọn ô)
    coordinate:
        cout << "Enter the coordinate of the box you'd like to play:" << endl;
        cout << "Column: "; cin >> thecolnum;
        cout << "Row   : "; cin >> therownum;
        cout << "Press 1 to open, press 2 to flag/unflag: "; cin >> behaviour;
        if (start_time_check == true) start = clock();    //bắt đầu tính giờ nếu là lần nhập đầu tiên **
        start_time_check = false;
         if (check_condition(therownum, thecolnum, row, column) == false) //tui đã đảo phần này với if (behaviour == 2) để cho chính xác hơn
        {
            system("cls");
            draw_board(row, column);
            cout << "\nInput doesn't match the conditions, try again!\n\n";
            getch();
            system("cls");
            goto after_flagging;
        }
        if (behaviour == 2)
        {
            if (check_flagged[therownum][thecolnum] == false) check_flagged[therownum][thecolnum] = true;
            else check_flagged[therownum][thecolnum] = false;
            goto after_flagging;
        }
        if (check_condition(therownum, thecolnum, row, column) == false)
        {
            draw_board(row, column);
            cout << "\nInput doesn't match the conditions, try again!\n\n";
            goto coordinate;
        }
        if (board[therownum][thecolnum] == 0) spread(therownum, thecolnum); //bấm vào ô rỗng (số 0 hoặc " ") thì mở thêm các ô bên cạnh
        else check_opened[therownum][thecolnum] = true; //set ô vừa mở thành true
        cout << '\n' << endl;
        system("cls");
    }
    end = clock(); //kết thúc tính giờ
    time_use = (double)(end - start) / CLOCKS_PER_SEC; //thời gian chơi
    game_over(board[therownum][thecolnum], time_use, row, column, choose_mode);
    getch();
    goto gameplay;
    return 0;
}

