#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include<windows.h>                                             //library to use textcolors

#define MAX 255

struct highscore_user
{
    char username[255];
    int score;
};

void print_hangman(int failed)                                  //shows hangman in ASCII in the console using counter "failed"
{

    switch(failed)                                              //switch between the failed-points
    {
    case 1:
        for(int i = 0; i < 7; i++)
        {
            printf(" \n");
        }
        printf("=========\n");
        break;
    case 2:
        printf(" \n");
        for(int i = 0; i < 6; i++)
        {
            printf("      |\n");
        }
        printf("=========\n");
        break;
    case 3:
        printf(" \n");
        printf("  +---+\n");
        for(int i = 0; i < 6; i++)
        {
            printf("      |\n");
        }
        printf("=========\n");
        break;
    case 4:
        printf(" \n");
        printf("  +---+\n");
        printf("  |   |\n");
        for(int i = 0; i < 5; i++)
        {
            printf("      |\n");
        }
        printf("=========\n");
        break;
    case 5:
        printf(" \n");
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        for(int i = 0; i < 4; i++)
        {
            printf("      |\n");
        }
        printf("=========\n");
        break;
    case 6:
        printf(" \n");
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf("  |   |\n");
        for(int i = 0; i < 3; i++)
        {
            printf("      |\n");
        }
        printf("=========\n");
        break;
    case 7:
        printf(" \n");
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|   |\n");
        for(int i = 0; i < 2; i++)
        {
            printf("      |\n");
        }
        printf("=========\n");
        break;
    case 8:
        printf(" \n");
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        for(int i = 0; i < 2; i++)
        {
            printf("      |\n");
        }
        printf("=========\n");
        break;
    case 9:
        printf(" \n");
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" /    |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    case 10:
        printf(" \n");
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf("      |\n");
        printf("=========\n");
        break;

    default:
        printf(" ");
        break;
    }
}

void create_highscore_in_list(char *username, int tries, int time, char *word)  //writes highscore in highscorelist.csv
{

    FILE *the_file = fopen("highscorelist.csv", "a");

    fprintf(the_file, "%s ; %i ; %i ; %s ;\n", username, tries, time, word);

    fclose(the_file);

}

void create_highscore(char *username, int tries, int time)      //writes highscores in the highscores.txt
{

    FILE *the_file = fopen("highscores.txt", "a");

    if(tries < 10)
    {
        fprintf(the_file, "%i  %s", tries, username);
    }
    else
    {
        fprintf(the_file, "%i %s", tries, username);
    }
    fprintf(the_file, "\n");

    fclose(the_file);
}

void show_highscores()                                          //shows last six highscores in the win / loss screen
{

    struct highscore_user highscore_struct[255];

    char tempstr[255];

    int temp, i, j, k;

    char highscoreline[20][255];


    FILE *the_file_to_read = fopen("highscores.txt", "r");

    for(i = 0; i < 255; i++)
    {
        fgets(highscoreline[i], 255, the_file_to_read);

        strcpy(highscore_struct[i].username, highscoreline[i]+2);
        highscore_struct[i].score = atoi(highscoreline[i]);

    }

    for (j = 0; j < strlen(highscoreline); j++)
    {
        for (k = j + 1; k < strlen(highscoreline); k++)
        {
            if (highscore_struct[j].score > highscore_struct[k].score)
            {
                temp = highscore_struct[j].score;
                highscore_struct[j].score= highscore_struct[k].score;
                highscore_struct[k].score = temp;

                strcpy(tempstr, highscore_struct[j].username);
                strcpy(highscore_struct[j].username, highscore_struct[k].username);
                strcpy(highscore_struct[k].username, tempstr);
            }
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    printf("===- HIGHSCORES -===\n");
    for (i = 0; i < 6; ++i) {
        printf("%i. [%i] %s", i+1, highscore_struct[i].score, highscore_struct[i].username);
    }

}

void create_user(char *username)                                //creates a new user if needed
{

    FILE *the_file = fopen("users.txt", "a");

    fprintf(the_file, "%s\n", username);

    fclose(the_file);

}

void get_user(int input_user, char user[])                      //chooses a existing user from file
{

    int i = 0;

    FILE *the_file = fopen("users.txt", "r");                // declares which file to read
    if(the_file == NULL)                                     //if the file can't be opened print out an error message
    {
        printf("Unable to open the file");
    }

    char userline[20][255];


    while(fgets(userline[i], 255, the_file))                     //read from the text document and store in array
    {
        userline[i][strcspn(userline[i], "\n")] = 0;

        strcpy(user, userline[input_user - 1]);
        i++;
    }
}

void show_users()                                               //shows all known users at the beginning
{

    int i = 0;

    FILE *the_file = fopen("users.txt", "r");                // declares which file to read
    if(the_file == NULL)                                     //if the file can't be opened print out an error message
    {
        printf("Unable to open the file");
    }

    char line[20][200];

    printf("0. Create new user \n\n");

    while(fgets(line[i], 200, the_file))                     //read from the text document and store in array
    {
        line[i][strcspn(line[i], "\n")] = 0;
        printf("%i. %s \n", i+1, line[i]);
        i++;
    }

}

void pick_solution(char* solution)                           //takes the pointer "solution" as parameter and picks a random word from a file and copies it into solution
{

    int i = 0;                                               //variable i is declared to later assign its value to the variable line_number to get the number of lines read
    int line_number;
    int random_number;


    FILE *the_file = fopen("words.txt", "r");                // declares which file to read
    if(the_file == NULL)                                     //if the file can't be opened print out an error message
    {
        printf("Unable to open the file");
    }
    char line[20][200];                                      //declare array to store the words
    while(fgets(line[i], 200, the_file))                     //read from the text document and store in array
    {
        line[i][strcspn(line[i], "\n")] = 0;
        i++;
    }
    line_number = i;

    srand(time(NULL));                                      //initialize the random number generator

    random_number = rand() % line_number;                   //assigns a random number from 0 to the value of variable line_number to random_number

    strcpy(solution, line[random_number]);                  //copies a random word in the string solution
}

void show_used_chars_and_attempts(char usedChars[], int attempts)       //function to show used chars and the number of attempts made
{
    char tmp;
    int i, j;
    for(i = 0; i < strlen(usedChars); i++)                              //bubble sort to sort used chars
    {
        for(j = 0; j < strlen(usedChars)-1; j++)
        {

            if(usedChars[j] > usedChars[j+1])
            {

                tmp = usedChars[j];
                usedChars[j] = usedChars[j+1];
                usedChars[j+1] = tmp;

            }
        }

    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    printf("\n\nYou already used the following chars:\n");
    for(i = 0; i < strlen(usedChars); i++)
    {
        printf("%c ",usedChars[i]);
    }
    printf("\n");
    printf("You already guessed %i times!\n\n",attempts);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void convert_to_upper(char solution[])                                  //function to convert a string to uppercase
{
    int i = 0;
    char chr;

    while (solution[i])
    {
        chr = solution[i];
        solution[i] = toupper(chr);
        i++;
    }
}

char input(char usedChars[])                                            //function for input and input validation
{

    char input;

    while(1)
    {
        printf("Guess a letter: \n");
        scanf("%c",&input);
        input = toupper(input);
        fflush(stdin);
        if(input >= 'A' && input <= 'Z')
        {
            if(strchr(usedChars, input))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);    //change the textcolor
                printf("The char %c was already used in a previous guess please try again:\n", input);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    //reset the textcolor
            }
            else
            {
                return input;
            }

        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);    //change the textcolor
            printf("Invalid input try again:\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    //reset the textcolor
        }

    }

}

void show_win_loss_screen(char username[], char usedChars[], int attempts, int failed, int correct,char hiddenWord[], char solution[], long time_limit, unsigned long seconds) //function to show the end screen of the game. See if you lost or won and displays statistics
{

    int i;
    char close;

    system("cls");                                                          //clear the console

    if(strchr(hiddenWord, '_')|| seconds > time_limit)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);        //change the textcolor in to grey
        printf("\n____________________________________\n\n");

        printf("%s:\n\n", username);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);        //change the textcolor in to dark red
        printf("You lost\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);        //change the textcolor in to grey

        print_hangman(failed);

        if(seconds > time_limit)
        {
            printf("You exceeded the time limit!\nTime Limit: %li minutes and %li seconds\nYour Time: %li minutes and %li seconds",time_limit/60,time_limit%60,seconds/60,seconds%60);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);        //change the textcolor in to white
        printf("\n\nThe word was: ");
        for(int i = 0; i<strlen(solution); i++)
        {
            printf("%c",solution[i]);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);        //change the textcolor in to white
        printf("\n\nYour used chars: ");
        for(i = 0; i < strlen(usedChars); i++)
        {
            printf("%c ",usedChars[i]);
        }
        printf("\n\nYour total guesses: %i", attempts);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);        //change the textcolor in to green
        printf("\n\nYour correct guesses: %i",correct);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);        //change the textcolor in to purple

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);        //change the textcolor in to dark red
        printf("\nYour failed guesses: %i\n",failed);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);        //change the textcolor in to white


        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);        //change the textcolor in to grey
        printf("\n\n____________________________________\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);        //change the textcolor in to white

    }
    else
    {

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);        //change the textcolor in to grey
        printf("\n____________________________________\n\n");

        printf("%s:\n\n", username);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);        //change the textcolor in to green
        printf("You have figured out the word\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);        //change the textcolor in to grey

        print_hangman(failed);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);        //change the textcolor in to purple
        printf("\n\nThe word was: ");
        for(int i = 0; i<strlen(solution); i++)
        {
            printf("%c",solution[i]);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);        //change the textcolor in to white
        printf("\n\nYour used chars: ");
        for(i = 0; i < strlen(usedChars); i++)
        {
            printf("%c ",usedChars[i]);
        }
        printf("\n\nYour total guesses: %i", attempts);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);        //change the textcolor in to green
        printf("\n\nYour correct guesses: %i",correct);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);        //change the textcolor in to purple

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);        //change the textcolor in to dark red
        printf("\nYour failed guesses: %i\n",failed);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);        //change the textcolor in to white

        printf("\nYour Time: %li minutes and %li seconds",seconds/60,seconds%60);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);        //change the textcolor in to grey
        printf("\n\n____________________________________\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);        //change the textcolor in to white
    }

    show_highscores();

    printf("\nPress a button to close!");
    scanf("%c", &close);
}
