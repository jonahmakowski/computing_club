#include<stdio.h>

#define BLANK_REPRESENT '.'
#define RED 1
#define BLACK 0

struct Piece {
    bool empty = true;
    char represent = BLANK_REPRESENT; // The character printed out when displaying the board
    int value;
    int side;
    bool backwards = false; // Represents if the piece can move backwards
};

struct Position {
    int x;
    int y;
};

Piece board[8][8];

Piece new_black_piece() {
    Piece n;
    n.empty = false;
    n.represent = '1';
    n.value = 1;
    n.side = BLACK;
    return n;
}

Piece new_red_piece() {
    Piece n;
    n.empty = false;
    n.represent = '2';
    n.value = 1;
    n.side = RED;
    return n;
}

Piece new_black_king() {
    Piece n;
    n.empty = false;
    n.represent = '3';
    n.value = 2;
    n.side = BLACK;
    n.backwards = true;
    return n;
}

Piece new_red_king() {
    Piece n;
    n.empty = false;
    n.represent = '4';
    n.value = 2;
    n.side = RED;
    n.backwards = true;
    return n;
}

Piece new_blank_piece() {
    Piece n;
    n.empty = true;
    n.represent = BLANK_REPRESENT;
    n.value = 0;
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

int calculate_points(int side) {
    int points = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].side == side) {
                points += board[i][j].value;
            }
        }
    }
    
    return points;
}

void move_piece(Position from, Position to) {
    board[to.x][to.y] = board[from.x][from.y];
    board[from.x][from.y] = new_blank_piece();
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

    printf("Red has %d points, Black has %d points\n", calculate_points(1), calculate_points(0));
}

int main() {
    generate_board();
    while (true) {
        display_board();
        printf("Move a piece by entering coordinates in the following pattern: x_from y_from x_to y_to: ");
        Position from;
        Position to;
        scanf("%d %d %d %d", &from.x, &from.y, &to.x, &to.y);
        move_piece(from, to);
    }
}
