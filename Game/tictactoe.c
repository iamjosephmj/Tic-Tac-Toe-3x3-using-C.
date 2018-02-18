#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define  PROFILE1 1
#define  PROFILE2 2

int match_moves_left = 0;

struct xo_board {
    char rows[3][3];

} board;

/*
 * this function places the item inside the board.
 * */
bool make_move(int r, int c, int mode) {
    match_moves_left -= 1;
    switch (mode) {
        case PROFILE1:

            if (board.rows[r][c] == '-') {
                board.rows[r][c] = '0';
                return true;
            } else {
                match_moves_left += 1;
                printf("\n Invalid move.... \n");
                return false;
            }

        case PROFILE2:

            if (board.rows[r][c] == '-') {
                board.rows[r][c] = 'X';
                return true;
            } else {
                match_moves_left += 1;
                printf("\n Invalid move.... \n");
                return false;
            }


        default:
            break;
    }
}

/*
 * prints out the Tic Tac Toe board
 * */
bool print_board() {
    printf("\n-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("|");
        for (int j = 0; j < 3; j++) {
            printf(" %c |", board.rows[i][j]);
        }
        printf("\n-------------\n");
    }
}

/*
 * this maps the mode into make_move()'s 3 parameter.
 * also dependent on the 1st parameter, if it is 0 then no change else it inverts the item received by the mode parameter.
 * */

int mode_value_finder(int function, char mode) {
    if (function == 1 && mode == 'X') {
        return PROFILE1;
    } else if (function == 1 && mode == '0') {
        return PROFILE2;
    } else if (mode == 'X') {
        return PROFILE2;
    } else {
        return PROFILE1;
    }
}

/*
 * this function first checks if there is any chance of victory, And next it checks the measures to counter the opponent's victory.
 * returns boolean value false if all the steps fails.
 * */

bool counter_move(char mode, int function) {
    int temp, irri = 0, irry = 0, i, j;

    for (i = 0; i < 3; i++) {
        temp = 0;
        for (j = 0; j < 3; j++) {
            if (board.rows[i][j] == mode) {
                temp += 1;
            } else {
                irri = i;
                irry = j;
            }
        }
        if (temp == 2) {
            if (board.rows[irri][irry] == '-') {
                make_move(irri, irry, mode_value_finder(function, mode));
                return true;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        temp = 0;
        for (j = 0; j < 3; j++) {
            if (board.rows[j][i] == mode) {
                temp += 1;
            } else {

                irri = j;
                irry = i;
            }
        }
        if (temp == 2) {
            if (board.rows[irri][irry] == '-') {
                make_move(irri, irry, mode_value_finder(function, mode));
                return true;
            }
        }
    }
    temp = 0;
    for (i = 0; i < 3; i++) {

        if (board.rows[i][i] == mode) {
            temp++;
        } else {
            irri = i;
            irry = irri;
        }
        if (temp == 2) {
            if (board.rows[irri][irry] == '-') {
                make_move(irri, irry, mode_value_finder(function, mode));
                return true;
            }
        }
    }
    temp = 0;
    for (i = 0; i < 3; i++) {

        if (board.rows[i][2 - i] == mode) {
            temp++;
        } else {
            irri = i;
            irry = 2 - irri;
        }
    }
    if (temp == 2) {
        if (board.rows[irri][irry] == '-') {
            make_move(irri, irry, mode_value_finder(function, mode));
            return true;
        }
    }
    return false;
}
/*
 * response for wise move in the board game
 * */
bool move_on_wise(int mode, int function) {
    int i, j, irri = 0, irry = 0, temp;
    for (i = 0; i < 3; i++) {
        temp = 0;
        for (j = 2; j >= 0; j--) {
            if (board.rows[i][j] == '-') {
                irri = i;
                irry = j;
                temp += 1;
            }
        }
        if (temp == 2) {
            make_move(irri, irry, mode_value_finder(function, (char) mode));
            return true;
        }
    }
    for (i = 0; i < 3; i++) {
        temp = 0;
        for (j = 2; j >= 0; j--) {
            if (board.rows[j][i] == '-') {
                temp += 1;
                irri = j;
                irry = i;
            }
        }
        if (temp == 2) {
            make_move(irri, irry, mode_value_finder(function, (char) mode));
            return true;
        }
    }
    return false;
}
/*
 * making draw in the board, most probably the last move before draw.
 * */
bool make_it_draw(int mode) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board.rows[i][j] == '-') {
                make_move(i, j, mode);
                return true;
            }
        }
    }
    return false;
}

/*
 * check for the victory in board
 * */
bool check_victory(char mode) {
    int i, j;
    int temp;
    for (i = 0; i < 3; i++) {
        temp = 0;
        for (j = 0; j < 3; j++) {
            if (board.rows[i][j] == mode) {
                temp += 1;
                if (temp == 3) {
                    printf("\n%c wins\n", mode);
                    return true;
                }
            }
        }
    }
    for (i = 0; i < 3; i++) {
        temp = 0;
        for (j = 0; j < 3; j++) {
            if (board.rows[j][i] == mode) {
                temp += 1;
                if (temp == 3) {
                    printf("\n%c wins\n", mode);
                    return true;
                }
            }
        }
    }
    temp = 0;
    for (i = 0; i < 3; i++) {
        if (board.rows[i][i] == mode) {
            temp += 1;
            if (temp == 3) {
                printf("\n%c wins\n", mode);
                return true;
            }
        }
    }
    temp = 0;
    for (i = 0; i < 3; i++) {
        if (board.rows[i][2 - i] == mode) {
            temp += 1;
            if (temp == 3) {
                printf("\n%c wins\n", mode);
                return true;
            }
        }
    }
    return false;
}


/*
 * working in computer start game mode
 * */
void profile_start_computer() {
    int r, c;
    make_move(1, 1, PROFILE2);
    print_board();
    /*
        first move : basic move is fixed (1: on the center ,2: at the adjacent corner if played on a corner)
    */
    printf("----Input your move in the form of r c ----:\n");
    scanf("%d %d", &r, &c);
    make_move(r - 1, c - 1, PROFILE1);
    print_board();
    if (r == 1 && c == 1) {
        make_move(0, 2, PROFILE2);
    } else if (r == 1 && c == 3) {
        make_move(2, 2, PROFILE2);
    } else if (r == 3 && c == 1) {
        make_move(0, 0, PROFILE2);
    } else if (r == 3 && c == 3) {
        make_move(0, 2, PROFILE2);
    } else {
        if (r == 1) {
            make_move(2, 2, PROFILE2);
        } else if (r == 2 && c == 1) {
            make_move(0, 2, PROFILE2);
        } else make_move(0, r == 2 && c == 3 ? 0 : 2, PROFILE2);
    }

    print_board();

    while (match_moves_left > 0) {
        printf("\n----Input your move in the form of r c ----:\n");
        scanf("%d%d", &r, &c);
        if (make_move(r - 1, c - 1, PROFILE1)) {
            if (!counter_move('X', 0)) {
                if (!counter_move('0', 1)) {
                    if (!move_on_wise('X', 0)) {
                        make_it_draw(PROFILE2);
                    }
                }
            }
        }
        print_board();
        if (!check_victory('X')) {
            if (!check_victory('0')) {
                continue;
            } else {
                exit(0);
            }
        } else {
            exit(0);
        }
    }
    printf("----- > Draw :) <------\n");


}

/*
 * working in user start game mode
 * */
void profile_start_user() {
    int r, c;
    printf("\n----Input your move in the form of r c ----:\n");
    scanf("%d %d", &r, &c);
    make_move(r - 1, c - 1, PROFILE2);
    if (r == 2 && c == 2) {
        make_move(0, 0, PROFILE1);
    } else {
        make_move(1, 1, PROFILE1);
    }
    print_board();
    while (match_moves_left > 0) {
        printf("\n----Input your move in the form of r c ----:\n");
        scanf("%d %d", &r, &c);
        if (make_move(r - 1, c - 1, PROFILE2)) {
            if (!counter_move('0', 0)) {
                if (!counter_move('X', 1)) {
                    if (!move_on_wise('0', 0)) {
                        make_it_draw(PROFILE1);
                    }
                }
            }
        }
        print_board();
        if (!check_victory('X')) {
            if (!check_victory('0')) {
                continue;
            } else {
                exit(0);
            }
        } else {
            exit(0);
        }
    }
    printf("----- > Draw :) <------\n");


}

/*
 * setting up initial board elements.
 * */
void setup_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board.rows[i][j] = '-';
        }
    }
    match_moves_left = 9;
}

void main() {
    int i;
    printf("1. user start game \n2. computer start game :\n");
    scanf("%d", &i);
    setup_board();
    switch (i) {
        case PROFILE1:
            profile_start_user();
            break;
        case PROFILE2:
            profile_start_computer();
            break;
        default:
            break;
    }
}
