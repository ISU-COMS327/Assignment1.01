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
#define MAX_ROOM_WIDTH 19
#define MIN_ROOM_HEIGHT 5
#define MAX_ROOM_HEIGHT 11 
int board[HEIGHT][WIDTH] = {{ROCK}};

struct Room {
    int start_x;
    int end_x;
    int start_y;
    int end_y;
    int is_connected;
};

int random_int(int min_num, int max_num, int add_to_seed);
void initialize_immutable_rock();
void print_board();
void print_cell();
void dig_rooms(int number_of_rooms_to_dig);
void dig_room(int index);
int room_is_valid_at_index(int index);
void add_rooms_to_board();
void dig_cooridors();
void connect_rooms_at_indexes(int index1, int index2);
struct Room rooms[MIN_NUMBER_OF_ROOMS];

int main(int argc, char *args[]) {
    printf("Generating dungeon. Random number: %d\n", random_int(0, 50, 0));
    initialize_immutable_rock();
    dig_rooms(MIN_NUMBER_OF_ROOMS);
    dig_cooridors();
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
    if (cell == ROCK || cell == IMMUTABLE_ROCK) {
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
    for (int i = 0; i < number_of_rooms_to_dig; i++) {
        dig_room(i);
    }
    add_rooms_to_board();
}

void dig_room(int index) {
    int start_x = random_int(0, WIDTH, index);
    int start_y = random_int(0, HEIGHT, index);
    int room_height = random_int(MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT, index);
    int room_width = random_int(MIN_ROOM_WIDTH, MAX_ROOM_WIDTH, index);
    int end_y = start_y + room_height;
    if (end_y >= HEIGHT - 1) {
        end_y = HEIGHT - 2;
    }
    int end_x = start_x + room_width;
    if (end_x >= WIDTH - 1) {
        end_x = WIDTH - 2;
    }
    rooms[index].start_x = start_x;
    rooms[index].start_y = start_y;
    rooms[index].end_x = end_x;
    rooms[index].end_y = end_y;
    printf("ROOM DATA -- sX: %d, sY: %d, eX: %d, eY: %d, diffX: %d, diffY: %d\n", start_x, start_y, end_x, end_y, (end_x - start_x), (end_y - start_y));
    if (!room_is_valid_at_index(index)) {
        dig_room(index);
    }
}

int room_is_valid_at_index(int index) {
    struct Room room = rooms[index];
    for (int i = 0; i < index; i++) {
        struct Room current_room = rooms[i];
        int start_x = current_room.start_x + 1;
        int start_y = current_room.start_y + 1;
        int end_x = current_room.end_x + 1;
        int end_y = current_room.end_y + 1;
        if ((room.start_x >= start_x  && room.start_x <= end_x) ||
                (room.end_x >= start_x && room.end_x <= end_x)) {
            if ((room.start_y >= start_y && room.start_y <= end_y) ||
                    (room.end_y >= start_y && room.end_y <= end_y)) {
                return 0;
            }
        }
    }
    return 1;
}

void add_rooms_to_board() {
    for(int i = 0; i < MIN_NUMBER_OF_ROOMS; i++) {
        struct Room room = rooms[i];
        for (int y = room.start_y; y <= room.end_y; y++) {
            for(int x = room.start_x; x <= room.end_x; x++) {
                board[y][x] = ROOM;
            }
        }
    } 
}

void dig_cooridors() {
    printf("I don't like cooridors\n");
    int number_of_connected_rooms = 0;
    while (number_of_connected_rooms < MIN_NUMBER_OF_ROOMS) {
        int room_index = random_int(0, MIN_NUMBER_OF_ROOMS - 1, 0);
        int other_room_index = MIN_NUMBER_OF_ROOMS - 1 - room_index;
        if (other_room_index == room_index) {
            other_room_index ++;   
        }
        struct Room room = rooms[room_index];
        struct Room other_room = rooms[other_room_index];
        connect_rooms_at_indexes(room_index, other_room_index);
        if (!room.is_connected) {
            number_of_connected_rooms ++;
        }
        if (!other_room.is_connected) {
            number_of_connected_rooms ++;
        }
        number_of_connected_rooms = MIN_NUMBER_OF_ROOMS;
    }
}

void connect_rooms_at_indexes(int index1, int index2) {
    printf("Connecting rooms at %d -> %d\n", index1, index2);
}
