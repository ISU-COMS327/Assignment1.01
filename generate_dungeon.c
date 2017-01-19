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

struct Room {
    int start_x;
    int end_x;
    int start_y;
    int end_y;
};

int random_int(int min_num, int max_num, int add_to_seed);
void initialize_immutable_rock();
void print_board();
void print_cell();
void dig_rooms(int number_of_rooms_to_dig);
void dig_room(int index);
struct Room rooms[MIN_NUMBER_OF_ROOMS];

int main(int argc, char *args[]) {
    printf("Generating dungeon. Random number: %d\n", random_int(0, 50, 0));
    initialize_immutable_rock();
    dig_rooms(MIN_NUMBER_OF_ROOMS);
    print_board();
    return 0;
}

int random_int(int min_num, int max_num, int add_to_seed) {
    int seed = time(NULL);
    if (add_to_seed) {
        seed += add_to_seed;
    }
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

void dig_rooms(int number_of_rooms_to_dig) {
    printf("Digging %d rooms!\n", number_of_rooms_to_dig);
    for (int i = 0; i < number_of_rooms_to_dig; i++) {
        dig_room(i);
    }
}

void dig_room(int index) {
    // TODO write algorithm for determining room spaces
    printf("Digging a room for index %d\n", index);
    int start_x = random_int(0, WIDTH, index);
    int start_y = random_int(0, HEIGHT, index);
    int room_height = random_int(MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT, index);
    int room_width = random_int(MIN_ROOM_WIDTH, MAX_ROOM_WIDTH, index);
    int end_y = start_y + room_height;
    if (end_y >= HEIGHT) {
        end_y = HEIGHT - 1;
    }
    int end_x = start_x + room_width;
    if (end_x >= WIDTH) {
        end_x = WIDTH - 1;
    }
    rooms[index].start_x = start_x;
    rooms[index].start_y = start_y;
    rooms[index].end_x = end_x;
    rooms[index].end_y = end_y;
    printf("ROOM DATA -- sX: %d, sY: %d, eX: %d, eY: %d, diffX: %d, diffY: %d\n", start_x, start_y, end_x, end_y, (end_x - start_x), (end_y - start_y));
}
