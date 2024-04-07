/*
 program : game number 2   -> 2 players, The first player writes an odd number in one of the spaces.
 The second player then plays an even number in an attempt to get three numbers in a row
 that equals 15. The rows may be vertical, horizontal, or diagonal.
 Each number can only be played once.
 Author : mohamed mokhtar ibrahim
 section: S20
 ID : 20230605
 Version: 2
 Date: 1 - 3 - 2024
 File name :CS112_A1_T6_20230605.cpp
*/
#include<iostream>
#include<string>
#include<algorithm>
#include <cctype>
#include <set>
using namespace std;
// function check if current player won the game
bool check_if_a_player_won(int arr[3][3], int row, int column) {
    int sum_row = 0, sum_column = 0, sum_diagonal_1 = 0, sum_diagonal_2 = 0;
    sum_row = arr[row][0] + arr[row][1] + arr[row][2];
    sum_column += arr[0][column] + arr[1][column] + arr[2][column];
    sum_diagonal_1 = arr[0][0] + arr[1][1] + arr[2][2];
    sum_diagonal_2 = arr[0][2] + arr[1][1] + arr[2][0];
    return (sum_column == 15 || sum_row == 15 || sum_diagonal_1 == 15 || sum_diagonal_2 == 15);

}
// function takes number of the column from the user and validate it
int take_colmun_from_player(const string& current) {
    cout << current << ",select the colmun ( 1 or 2 or 3  ) you want to put the number in: ";
    string colmun; cin >> colmun;
    cout << endl;
    while (colmun != "1" && colmun != "2" && colmun != "3") {
        cout << "please select the row number just from 1 to 3: ";
        cin >> colmun;
    }
    return stoi(colmun);
}
// convert capital characters of a string to small characters
string convert_tolower(string s) {
    for (int i = 0; i < 3; ++i)
        s[i] = tolower(s[i]);
    return s;
}
// function print numbers of a set
void print_numbers(set<int>& numbers) {
    for (auto num : numbers)
        cout << num << " ";
    cout << endl;
}
//function check if input contain digits only not characters
bool check_if_string_is_numeric(const string& s) {
    for (auto ch : s)
        if (!isdigit(ch))
            return false;
    return true;
}
//function prints current board 3 X 3
void print_currrent_board(int arr[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "__" << (arr[i][j] != -10 ? to_string(arr[i][j]) : "_") << "__";
            cout << "|";
        }
        cout << "\n";
    }
    cout << "\n";
}
// function takes number of the row from the user and validate it
int take_row_from_player(const string& current) {
    cout << current << ",select the row ( 1 or 2 or 3  ) you want to put the number in: ";
    string row; cin >> row;
    cout << endl;
    while (row != "1" && row != "2" && row != "3") {
        cout << "please select the row number just from 1 to 3: ";
        cin >> row;
    }
    return stoi(row);
}
// main function of the game
void game() {
    set <int>valid_odd_numbers, valid_even_numbers;
    for (int i = 0; i < 10; ++i) {
        if (i & 1)
            valid_odd_numbers.insert(i);
        else
            valid_even_numbers.insert(i);
    }
    int board[3][3];
    for (auto& row : board)
        for (auto& element : row)
            element = -10;
    string current_player;
    for (int i = 1; i < 10; ++i) {
        set<int>current_valid_numbers;
        print_currrent_board(board);
        // this block makes us know who should choose a number now
        if (i & 1) {
            current_player = "first player";
            current_valid_numbers = valid_odd_numbers;
        }
        else {
            current_player = "second player";
            current_valid_numbers = valid_even_numbers;
        }
        cout << current_player << "'s turn. Available numbers: ";
        print_numbers(current_valid_numbers);
        cout << "choose a number : ";
        string input;
        cin >> input;
        int chosen_number;
        set<int>::iterator found;
        // Validate if the chosen number is in the valid numbers
        while (true) {
            while (!check_if_string_is_numeric(input)) {
                cout << "please choose an integer number from : ";
                print_numbers(current_valid_numbers);
                cin >> input;
            }
            chosen_number = stoi(input);
            found = current_valid_numbers.find(chosen_number);
            if (found != current_valid_numbers.end())
                break;
            cout << "please choose an integer number from : ";
            print_numbers(current_valid_numbers);
            cin >> input;
        }
        // delete the number user selected from valid numbers so user can't choose it again
        if (i & 1)
            valid_odd_numbers.erase(chosen_number);
        else
            valid_even_numbers.erase(chosen_number);
        int Row = take_row_from_player(current_player);
        int Colmun = take_colmun_from_player(current_player);
        //check the position user selected is selected before or not
        while (board[Row - 1][Colmun - 1] != -10) {
            cout << "This position is not free please choose another position " << endl;
            Row = take_row_from_player(current_player);
            Colmun = take_colmun_from_player(current_player);
        }
        //put the selected number in the board
        board[Row - 1][Colmun - 1] = chosen_number;

        if (check_if_a_player_won(board, Row - 1, Colmun - 1)) {
            print_currrent_board(board);
            cout << current_player << " won the game " << endl;
            return;
        }
    }
    cout << " it is a draw, no player won the game " << endl;
}

int main() {
    game();
    // Play again loop
    while (true) {
        cout << "Do you want to play again? (yes/no): " << endl;
        string answer; cin >> answer;
        answer = convert_tolower(answer);
        // Answer validation loop
        while (answer != "yes" && answer != "no") {
            cout << "please select only yes or no " << endl;
            cin >> answer;
            answer = convert_tolower(answer);
        }
        // Break the loop( terminate the game ) if the answer is 'no'
        if (answer == "no")
            break;
        // Play another round if answer is yes
        game();
    }

    return 0;
}
