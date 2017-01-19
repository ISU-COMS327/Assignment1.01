#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define HEIGHT 105
#define WIDTH 160
#define IMMUTABLE_ROCK -1
#define ROCK 0
#define ROOM 1
#define CORRIDOR 2
#define MIN_NUMBER_OF_ROOMS 10
#define MIN_ROOM_WIDTH 7
#define MAX_ROOM_WIDTH 15
#define MIN_ROOM_HEIGHT 5
#define MAX_ROOM_HEIGHT 15

int board[HEIGHT][WIDTH] = {{ROCK}};

typedef struct {
    int start_x;
    int end_x;
    int start_y;
    int end_y;
} tRoom;

int random_int(int min_num, int max_num);
void initialize_immutable_rock();
void print_board();
void print_cell();
void dig_rooms(int number_of_rooms_to_dig);

int main(int argc, char *args[]) {
    printf("Generating dungeon. Random number: %d\n", random_int(0, 50));
    initialize_immutable_rock();
    print_board();
    return 0;
}

int random_int(int min_num, int max_num) {
    int seed = time(NULL);
    printf("Used seed: %d\n", seed);
    max_num ++;
    int delta = max_num - min_num;
    srand(seed);
    return (rand() % delta) + min_num;
}

void initialize_immutable_rock() {
    int y;
    int x;
    int max_x = WIDTH - 1;
    int max_y = HEIGHT - 1;
    for (y = 0; y < HEIGHT; y++) {
        board[y][0] = IMMUTABLE_ROCK;
        board[y][max_x] = IMMUTABLE_ROCK;
    }
    for (x = 0; x < WIDTH; x++) {
        board[0][x] = IMMUTABLE_ROCK;
        board[max_y][x] = IMMUTABLE_ROCK;
    }
}

void print_board() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            print_cell(board[y][x]);
        }
        printf("\n");
    }
}

void print_cell(int cell) {
    if (cell == IMMUTABLE_ROCK) {
        printf("=");
    }
    else if (cell == ROCK) {
        printf(" ");
    }
    else if (cell == ROOM) {
        printf(".");
    }
    else if (cell == CORRIDOR) {
        printf("#");
    }
    else {
        printf("F");
    }
}
