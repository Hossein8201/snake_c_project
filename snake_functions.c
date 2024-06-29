#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
//include your customer header:
#include "snake_functions.h"

//define your global variable:
int game_begin;
int snake_head[2];
int snake_length;
int snake_body[200][2];
int food_position[2];
int present_direct;
int score;
int game_over;
char game_board[30][40];
//calculate the time of servival and time of sleep
clock_t start_game, end_game, start_time, end_time;    

//define the fuctions:

//this down group create the game board:
void unbound_field(){
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<LENGTH;j++){
            if(i==0 || i== WIDTH-1)      game_board[i][j] = '-';
            else if(j==0 || j== LENGTH-1)    game_board[i][j] = '|';
            else    game_board[i][j] = ' ';
        }
    }
}

void closed_field(){
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<LENGTH;j++){
            if(i==0 || i== WIDTH-1 || j==0 || j== LENGTH-1)    game_board[i][j] = '#';
            else    game_board[i][j] = ' ';
        }
    }
}

void forest_field(){
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<LENGTH;j++){
            if(i==0 || i== WIDTH-1 || j==0 || j== LENGTH-1)    game_board[i][j] = '+';
            else    game_board[i][j] = ' ';
        }
    }
    int number=0;
    while(number != 7){
        int a, b, n;
        a = rand()%7+1;     b = rand()%7+1;     n = rand()%22;
        if(n <= WIDTH/2-9 || n >= WIDTH/2){
            for(int j=0;j<a;j++)    for(int k=0;k<b;k++)    game_board[n+j][n+k] = '+';
            number++;
        }
    }
}

void choose_board(){       
    printf("Choose your game field you want to play in there : \n");
    printf("1) unbound field\n");
    printf("2) closed field\n");
    printf("3) forest field\n");
    printf("your choose : ");       int board_number;      scanf("%d",&board_number);
    switch(board_number){
        case 1 :    unbound_field();    break;
        case 2 :    closed_field();     break;
        case 3 :    forest_field();     break;
        default:    unbound_field();    break;
    }
}
//this up group create the game board:

void setup(){
    //initialized the snake in start of program:
    snake_head[0] = WIDTH/2-1;         snake_head[1] = LENGTH/2;
    snake_length = 3;
    snake_body[0][0] = WIDTH/2-1;      snake_body[0][1] = LENGTH/2;
    snake_body[1][0] = WIDTH/2-1;      snake_body[1][1] = LENGTH/2-1;
    snake_body[2][0] = WIDTH/2-1;      snake_body[2][1] = LENGTH/2-2;
    //initialized the position of the food in start of game:
    food_position[0] = 1;        food_position[1] = LENGTH/2-1;
    //initialized the score of player:
    score = 0;
    //the direct of moving snake in the beginning:
    present_direct = RIGHT;
    //the end condition of game:
    game_over = 0;
}

void movement(){
    //moving the snake in expected direct:
    switch(present_direct){
        case RIGHT :    snake_head[1]++;    break;
        case LEFT  :    snake_head[1]--;    break;
        case UP    :    snake_head[0]--;    break;
        case DOWN  :    snake_head[0]++;    break;
    }
    //the snake shoud be inside of the board:
    snake_head[0] = (snake_head[0] >= WIDTH-1 && game_board[WIDTH-1][0] == '-') ? 1 : (snake_head[0] <= 0 && game_board[0][0] == '-') ? WIDTH-2 : snake_head[0];  
    snake_head[1] = (snake_head[1] >= LENGTH-1 && game_board[1][LENGTH-1] == '|') ? 1 : (snake_head[1] <= 0 && game_board[1][0] == '|') ? LENGTH-2 : snake_head[1];
    //if the snake eat the food, give it +10 point and create a food again:
    if(snake_head[0] == food_position[0] && snake_head[1] == food_position[1]){
        score += 10;    snake_length++;     food_generation();      //and increase the length of the snake:
    }  
    //moving the body of the snake following by it head:
    for(int i=snake_length-1;i>0;i--){
        snake_body[i][0] = snake_body[i-1][0];      snake_body[i][1] = snake_body[i-1][1];
    }
    snake_body[0][0] = snake_head[0];       snake_body[0][1] = snake_head[1];
}

void food_generation(){
    //generating randomically the position of food:
    food_position[0] = rand()%WIDTH;
    food_position[1] = rand()%LENGTH;
    //check the position of food be in suitable plece:
    if(game_board[food_position[0]][food_position[1]] != ' ')  
        food_generation();
    else{
        int hit_body = 0;
        for(int i=0;i<snake_length;i++)     
            if(snake_body[i][0] == food_position[0] && snake_body[i][1] == food_position[1]){   
                hit_body = 1;   break;
            } 
        if(hit_body)    food_generation();   
    }
}

void accident(){
    //check the collide the head of snake with own body:
    for(int i=1;i<snake_length;i++){
        if(snake_head[0] == snake_body[i][0] && snake_head[1] == snake_body[i][1]){
            game_over = 1;      break;
        }
    }
    //check the collide the head of snake with the board of game:
    if(game_board[snake_head[0]][snake_head[1]] != ' ')     game_over = 1;  
}

void input(){
    if(_kbhit()){
        switch(_getch()){       //get the input character and apply the changes:
            case 'w' :      if(present_direct != DOWN)   present_direct = UP;       break;
            case 's' :      if(present_direct != UP)     present_direct = DOWN;     break;
            case 'a' :      if(present_direct != RIGHT)  present_direct = LEFT;     break;
            case 'd' :      if(present_direct != LEFT)   present_direct = RIGHT;    break;
            case '0' :      game_over = 1;     break;
            default  :      ;
        }
    }
}

void display(){
    system("cls");
    printf("-----> if you want to quit the game, press \"0\". <-----\n");
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<LENGTH;j++){
            if(game_board[i][j] == ' '){
                if(i==food_position[0] && j==food_position[1])      printf("%c",'$');   //print the food
                else{
                    int replace = 0;
                    for(int k=0;k<snake_length;k++){
                        if(snake_body[k][0] == i && snake_body[k][1] == j){
                            if(k==0 && game_over == 1)    printf("%c",'X');       //print the accident place
                            else if(k==0)      printf("%c",'@');        //print the head of snake
                            else        printf("%c",'O');       //print the body of snake
                            replace = 1;    break;
                        }
                    }
                    if(replace == 0)    printf("%c",' ');       //this is empty
                }  
            }
            else if(game_over == 1 && snake_head[0] == i && snake_head[1] == j)       //check the situation of collide
                printf("%c",'X'); 
            else        printf("%c",game_board[i][j]);
        }
        printf("\n");
    }
    printf("your score : %d\n",score);
}
