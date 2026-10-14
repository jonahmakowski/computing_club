#include<stdio.h>

#define BLANK_REPRESENT '.'
#define RED 1
#define BLACK 0
#define BLACK_KING_ROW 0
#define RED_KING_ROW 7

struct Piece {
    char represent = BLANK_REPRESENT; // The character printed out when displaying the board
    int side;
};

Piece board[8][8];

Piece new_black_piece() {
    Piece n;
    n.represent = '1';
    n.side = BLACK;
    return n;
}

Piece new_red_piece() {
    Piece n;
    n.represent = '2';
    n.side = RED;
    return n;
}

Piece new_black_king() {
    Piece n;
    n.represent = '3';
    n.side = BLACK;
    return n;
}

Piece new_red_king() {
    Piece n;
    n.represent = '4';
    n.side = RED;
    return n;
}

Piece new_blank_piece() {
    Piece n;
    n.represent = BLANK_REPRESENT;
    return n;
}

void generate_board() {
    for (int i = 0; i < 8*3; i++) {
        int x = i%8;
        int y = i / 8;

        if ((x + y) % 2 == 0) {
            board[x][y] = new_red_piece();
        }
    }

    for (int i = 63; i >= 64 - 8*3; i--) {
        int x = i%8;
        int y = i / 8;

        if ((x + y) % 2 == 0) {
            board[x][y] = new_black_piece();
        }
    }
}

void move_piece(int from_x, int from_y, int to_x, int to_y) {
    board[to_x][to_y] = board[from_x][from_y];

    if (to_y == BLACK_KING_ROW && board[to_x][to_y].side == BLACK) {
        board[to_x][to_y] = new_black_king();
    } else if (to_y == RED_KING_ROW && board[to_x][to_y].side == RED) {
        board[to_x][to_y] = new_red_king();
    }

    board[from_x][from_y] = new_blank_piece();
}

void display_board() {
    for (int y = 7; y >= 0; y--) {
        printf("%d ", y);

        for (int x = 0; x < 8; x++) {
            printf("%c ", board[x][y].represent);
        }

        printf("\n");
    }

    printf("  0 1 2 3 4 5 6 7\n\n");
}

int main() {
    generate_board();
    while (true) {
        display_board();
        printf("Move a piece by entering coordinates in the following pattern: x_from y_from x_to y_to: ");
        int from_x, from_y, to_x, to_y;
        scanf("%d %d %d %d", &from_x, &from_y, &to_x, &to_y);
        move_piece(from_x, from_y, to_x, to_y);
    }
}
