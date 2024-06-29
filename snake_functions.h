#ifndef SNAKE_FUNCTIONS_H
#define SNAKE_FUNCTIONS_H

//the length of board of the game:
#define WIDTH 30
#define LENGTH 40
//define the direction movements signs:
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

//define your global variable:
extern int game_begin;
extern int snake_head[2];
extern int snake_length;
extern int snake_body[200][2];
extern int food_position[2];
extern int present_direct;
extern int score;
extern int game_over;
extern char game_board[30][40];
//calculate the time of servival and time of sleep
extern clock_t start_game, end_game, start_time, end_time; 

//the notification of functions:
void setup();
void choose_board();
void unbound_field();
void closed_field();
void forest_field();
void movement();
void food_generation();
void accident();
void input();
void display();

#endif