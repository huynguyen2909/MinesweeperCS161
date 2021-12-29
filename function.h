#pragma once
struct top //lưu thông tin bang xếp hạng theo từng chế độ
{             
    int modenum;
    double ranki[6];
    bool check_exist ;
};
int board[1000][1000]; //khai báo bảng (sử dụng mảng)
bool check_opened[1000][1000]; //mảng này dùng để lưu trạng thái ô đã mở hay chưa (đã mở -> true; chưa mở -> false)
bool check_flagged[1000][1000]; //mảng này dùng để lưu trạng thái ô đã được cắm cờ hay chưa (đã cắm -> true; chưa cắm: -> false)
void tutorial(); //giới thiệu và hướng dẫn 
void chooseMode(int& row, int& column, int& number_of_mines, int& choose_mode); //chọn chế độ
void prepare_board(int& row, int& column); //khởi tạo các giá trị thô sơ cho bảng
void calculate_hints(int& tempr, int& tempc); //tính số mìn xung quanh ô
void spread(int& therownum, int& thecolnum); //mở ô ko còn mìn xung quanh -> đệ quy để mở tiếp các ô tương tự
int number_of_opened_boxes(int& row, int& column); //hàm kiểm tra số ô đã mở
void draw_board(int& row, int& column); //vẽ bảng (cập nhật sau mỗi lần chọn ô)
void game_over(int x, double& y, int& row, int& column, int& choose_mode);//display khi thắng hoặc thua
bool check_condition(int& therownum,int& thecolnum, int& row, int& column); //kiểm tra tọa độ ô mà người chơi nhập vào có hợp lệ hay không