#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void playGame();

int main() {
    srand(time(0));
    printf("Welcome to Guess the Number!\n");
    playGame();
    return 0;
}

void playGame() {
    int numberToGuess = rand() % 100 + 1;
    int userGuess = 0;

    printf("I have selected a number between 1 and 100. Can you guess it?\n");

    while (userGuess != numberToGuess) {
        printf("Enter your guess: ");
        scanf("%d", &userGuess);

        if (userGuess < numberToGuess) {
            printf("Too low! Try again.\n");
        } else if (userGuess > numberToGuess) {
            printf("Too high! Try again.\n");
        } else {
            printf("Congratulations! You guessed the number.\n");
        }
    }
}
