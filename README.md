# Assignment 1.01: Dungeon Generation

## Description

This assignment deals with generating a dungeon. A dungeon
contains rooms, corridors, and rock. Eventually, an adventurer will
travel via cooridors to various rooms in the dungeon.

## Usage

To run this program, perform the following series of commands in your shell:

`make`
`./generate_dungeon`

Upon running `./generate_dungeon`, a dungeon will be generated and printed
to your shell.

The `generate_dungeon` program accepts two parameters: `-n <number of rooms>` and
`-h`. The `-h` flag will print usage information, and the `-n` parameter, followed
by a number, will set the number of rooms to be generated. The minimum
number of rooms is 10, and the maximum number of rooms is 25. At this point,
the number 25 is arbitrary, and can be adjusted.
