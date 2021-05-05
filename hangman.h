#ifndef HANGMAN_H_INCLUDED
#define HANGMAN_H_INCLUDED


void print_hangman(int failed);
void pick_solution(char* solution);
void show_used_chars_and_attempts(char usedChars[], int attempts);
void convert_to_upper(char solution[]);
char input(char usedChars[]);
void show_win_loss_screen(char username[], char usedChars[], int attempts, int failed, int correct,char hiddenWord[], char solution[], long time_limit, unsigned long seconds);
void get_user(int input_user, char user[]);
void show_users();
void create_user(char username[]);
void create_highscore(char *username, int tries);
void show_highscores();
void create_highscore_in_list(char *username, int tries, int time, char *word);

#endif // HANGMAN_H_INCLUDED

