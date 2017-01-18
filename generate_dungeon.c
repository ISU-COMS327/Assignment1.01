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

int main(int argc, char *args[]) {
    printf("Generating dungeon. Random number: %d\n", random_int(0, 50));
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

