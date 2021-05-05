#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "hangman.h"                                            //library for our local functions

#include<windows.h>                                             //library to use textcolors

#define MAX 255


int main()
{
    int in;
    int t_input;
    char solution[MAX];
    char usedChars[MAX] = {0};
    char hiddenWord[MAX];
    int attempts = 0;
    int failed = 0;
    int correct = 0;
    unsigned long start_time;
    unsigned long end_time;
    unsigned long seconds;
    long time_limit = 10;
    int seconds_formated = 0;
    int minutes = 0;
    int count = 0;
    char username[255];
    int user_input = 0;

    show_users();                                                                  //shows all known users

    printf("\n> ");
    scanf("%i", &user_input);                                                      //get the username from the console input

    if(user_input == 0) {
        printf("Please enter your username: ");
        scanf("%s", username);
        create_user(username);                                                      //creates a new user in a file
    }
    else {
        get_user(user_input, username);                                             //picks a known user from file
    }

    pick_solution(solution);                                                        //get a random word from the words.txt
    convert_to_upper(solution);                                                     //converts the solution to uppercase

    system("cls");                                                                  //clears the console

    do {                                                                            //Loop runs as long as you make invalid inputs
        printf("Do you want to set a time Limit?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        scanf("%i",&in);
        fflush(stdin);

        if(in == 1 || in == 2)                                                      //checks if you want a time limit or not
        {

            if(in == 2)
            {
                time_limit = 99999999;                                              //if N time limit is set to 9999999999999 seconds
                break;
            }
            else
            {
                printf("Enter your time limit in seconds:\n");                      //lets you enter your time limit in seconds
                scanf("%i",&t_input);
                fflush(stdin);
                time_limit = t_input;                                               //sets time limit to your input
                printf("Time Limit of: %li minutes and %li seconds\n\nYour Time starts at your first guess!\n\n",time_limit/60, time_limit%60); //shows your time limit
                break;
            }

        }
        else
        {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);            //chages the console-text-color to red
            printf("You have made a wrong input!\n");
            printf("Try again!\n\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);            //chages the console-text-color to white

        }

    } while (1);

    system("cls");

    for(int i = 0; i<strlen(solution); i++)
    {
        hiddenWord[i] = '_';                                                        //replace the solution with underscores
        printf("%c ",hiddenWord[i]);
    }
    printf("\n");

    while(failed != 10)                                                             //checks the failed count
    {
        in = input(usedChars);
        if(count == 0)                                                              //starts the timer after your first input count makes sure it only happens once
        {
            start_time = (unsigned long)time(NULL);                                 //assigns the epoch time/Unix time to the variable start_time
            count++;
        }
        usedChars[attempts] = in;
        if(strchr(solution, in))                                                    //checks if your input char is in the solution string
        {

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            system("cls");
            printf("You guessed correctly!!\n\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            correct++;
            print_hangman(failed);                                                  //prints the ASCII Hangman in the console

            for(int i=0; i<strlen(hiddenWord); i++)
            {
                if(solution[i] == in)
                {
                    hiddenWord[i] = in;                                             //replaces the "_" in hidden word with your input
                }
            }
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            system("cls");
            printf("Loser\n\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            failed++;
            print_hangman(failed);                                                  //prints the ASCII Hangman in the console
        }
        for(int i = 0; i<strlen(solution); i++)
        {
            printf("%c ",hiddenWord[i]);
        }
        attempts++;
        show_used_chars_and_attempts(usedChars, attempts);                      //shows all already used chars and attempts in the console
        end_time = (unsigned long)time(NULL);                                   //assigns the epoch time/Unix time to the variable end_time
        minutes = (end_time - start_time)/60;                                   //converts epoch time into minutes
        seconds_formated = (end_time - start_time)%60;                          //calculates the remaining seconds after minute conversion
        seconds = end_time - start_time;                                        //calculates time passed in seconds
        if(seconds >= time_limit)                                               //if the time limit is exceeded end the loop
        {
            break;
        }
        if(strchr(hiddenWord, '_') == 0)                                        // if the hidden word string no longer contains "_" end the loop
        {
            break;
        }
    }

    create_highscore(username, attempts);                                       //creates a highscore for the current round for the user
    create_highscore_in_list(username, attempts, seconds, solution);            //creates a highscore in the highscore list (csv)
    show_win_loss_screen(username, usedChars, attempts, failed, correct, hiddenWord, solution, time_limit, seconds);    //shows the win or loss screen

    return 0;
}
