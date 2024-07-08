#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void playGame();
int promptReplay();
void clearInputBuffer();
void displayWelcomeMessage();
void displayInstructions();
void displayFarewellMessage();

int main() {
    srand(time(0));
    displayWelcomeMessage();
    displayInstructions();

    do {
        playGame();
    } while (promptReplay());

    displayFarewellMessage();
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
            clearInputBuffer();
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
    clearInputBuffer();

    while (response != 'y' && response != 'Y' && response != 'n' && response != 'N') {
        printf("Invalid response. Please enter 'y' or 'n': ");
        scanf(" %c", &response);
        clearInputBuffer();
    }

    return (response == 'y' || response == 'Y');
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

void displayWelcomeMessage() {
    printf("*****************************\n");
    printf("* Welcome to Guess the Number! *\n");
    printf("*****************************\n");
}

void displayInstructions() {
    printf("\nInstructions:\n");
    printf("1. I will think of a number between 1 and 100.\n");
    printf("2. Your task is to guess the number.\n");
    printf("3. After each guess, I will tell you if your guess is too high, too low, or correct.\n");
    printf("4. Keep guessing until you find the correct number.\n");
    printf("5. You can choose to play again after each game.\n\n");
}

void displayFarewellMessage() {
    printf("Thanks for playing Guess the Number! Goodbye!\n");
}
