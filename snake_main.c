#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
//include your customer header:
#include "snake_functions.h"

int main(){
    printf("welcome to the SNAKE GAME. if you want to start the game, press \"1\" or not press \"0\" : ");
    scanf("%d",&game_begin);
    while(game_begin){
        system("cls");
        srand(time(0));        //to use the random numbers
        choose_board();        //ask us in the beginning of the program
        //calculate the time:
        start_game = clock();
        start_time = clock();
        //
        setup();
        display();
        while(game_over == 0){
            end_time = clock();
            if((double) (end_time - start_time) / (double) CLOCKS_PER_SEC >= 0.2){      //the sleep time:
                input();
                movement();
                accident();
                display();
                start_time = clock();
            }
        }
        end_game = clock();
        double time_taken;
        time_taken = (double) (end_game - start_game) / (double) CLOCKS_PER_SEC;
        printf("your survival time : %.3lf\n\n",time_taken);
        printf("-----> if you want to restart the game, press \"1\" or not press \"0\" : ");
        scanf("%d",&game_begin);
    }
}

