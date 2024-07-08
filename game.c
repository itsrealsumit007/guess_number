#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void playGame();
int promptReplay();

int main() {
    srand(time(0));
    printf("Welcome to Guess the Number!\n");

    do {
        playGame();
    } while (promptReplay());

    printf("Thanks for playing!\n");
    return 0;
}

void playGame() {
    int numberToGuess = rand() % 100 + 1;
    int userGuess = 0;
    int guessCount = 0;
    int isValidInput;

    printf("I have selected a number between 1 and 100. Can you guess it?\n");

    while (userGuess != numberToGuess) {
        printf("Enter your guess: ");
        isValidInput = scanf("%d", &userGuess);

        if (!isValidInput) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        guessCount++;

        if (userGuess < numberToGuess) {
            printf("Too low! Try again.\n");
        } else if (userGuess > numberToGuess) {
            printf("Too high! Try again.\n");
        } else {
            printf("Congratulations! You guessed the number in %d attempts.\n", guessCount);
        }
    }
}

int promptReplay() {
    char response;
    printf("Do you want to play again? (y/n): ");
    scanf(" %c", &response);

    while (getchar() != '\n');

    if (response == 'y' || response == 'Y') {
        return 1;
    } else {
        return 0;
    }
}
