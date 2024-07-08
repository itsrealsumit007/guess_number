#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HIGH_SCORE_FILE "highscores.txt"

void playGame(int maxRange, int maxAttempts);
int promptReplay();
void clearInputBuffer();
void displayWelcomeMessage();
void displayInstructions();
void displayFarewellMessage();
int chooseDifficulty();
void loadHighScores(int *easyScore, int *mediumScore, int *hardScore);
void saveHighScores(int easyScore, int mediumScore, int hardScore);
void displayHighScores(int easyScore, int mediumScore, int hardScore);

int main() {
    srand(time(0));
    int easyScore = -1, mediumScore = -1, hardScore = -1;
    loadHighScores(&easyScore, &mediumScore, &hardScore);

    displayWelcomeMessage();
    displayInstructions();
    displayHighScores(easyScore, mediumScore, hardScore);

    do {
        int difficulty = chooseDifficulty();
        int maxRange, maxAttempts;

        switch (difficulty) {
            case 1: maxRange = 50; maxAttempts = 10; break;
            case 2: maxRange = 100; maxAttempts = 7; break;
            case 3: maxRange = 200; maxAttempts = 5; break;
            default: maxRange = 100; maxAttempts = 7;
        }

        int attempts = playGame(maxRange, maxAttempts);

        if (attempts != -1) {
            if (difficulty == 1 && (easyScore == -1 || attempts < easyScore)) easyScore = attempts;
            else if (difficulty == 2 && (mediumScore == -1 || attempts < mediumScore)) mediumScore = attempts;
            else if (difficulty == 3 && (hardScore == -1 || attempts < hardScore)) hardScore = attempts;
            saveHighScores(easyScore, mediumScore, hardScore);
        }
    } while (promptReplay());

    displayFarewellMessage();
    return 0;
}

int playGame(int maxRange, int maxAttempts) {
    int numberToGuess = rand() % maxRange + 1;
    int userGuess = 0, guessCount = 0, isValidInput;

    printf("I have selected a number between 1 and %d. Can you guess it?\n", maxRange);

    while (userGuess != numberToGuess && guessCount < maxAttempts) {
        printf("Enter your guess: ");
        isValidInput = scanf("%d", &userGuess);

        if (!isValidInput) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        guessCount++;

        if (userGuess < numberToGuess) printf("Too low! Try again.\n");
        else if (userGuess > numberToGuess) printf("Too high! Try again.\n");
        else {
            printf("Congratulations! You guessed the number in %d attempts.\n", guessCount);
            return guessCount;
        }

        if (guessCount == maxAttempts && userGuess != numberToGuess)
            printf("Sorry, you've reached the maximum number of attempts. The correct number was %d.\n", numberToGuess);
    }
    return -1;
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
    printf("1. I will think of a number within a range based on the difficulty level.\n");
    printf("2. Your task is to guess the number.\n");
    printf("3. After each guess, I will tell you if your guess is too high, too low, or correct.\n");
    printf("4. Keep guessing until you find the correct number or run out of attempts.\n");
    printf("5. You can choose to play again after each game.\n\n");
}

void displayFarewellMessage() {
    printf("Thanks for playing Guess the Number! Goodbye!\n");
}

int chooseDifficulty() {
    int difficulty;
    printf("Choose a difficulty level:\n");
    printf("1. Easy (Range: 1-50, Max Attempts: 10)\n");
    printf("2. Medium (Range: 1-100, Max Attempts: 7)\n");
    printf("3. Hard (Range: 1-200, Max Attempts: 5)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &difficulty);
    clearInputBuffer();

    while (difficulty < 1 || difficulty > 3) {
        printf("Invalid choice. Please enter a number between 1 and 3: ");
        scanf("%d", &difficulty);
        clearInputBuffer();
    }

    return difficulty;
}

void loadHighScores(int *easyScore, int *mediumScore, int *hardScore) {
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    if (file != NULL) {
        fscanf(file, "%d %d %d", easyScore, mediumScore, hardScore);
        fclose(file);
    }
}

void saveHighScores(int easyScore, int mediumScore, int hardScore) {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%d %d %d", easyScore, mediumScore, hardScore);
        fclose(file);
    }
}

void displayHighScores(int easyScore, int mediumScore, int hardScore) {
    printf("\nHigh Scores:\n");
    printf("Easy: %d attempts\n", (easyScore == -1) ? 0 : easyScore);
    printf("Medium: %d attempts\n", (mediumScore == -1) ? 0 : mediumScore);
    printf("Hard: %d attempts\n\n", (hardScore == -1) ? 0 : hardScore);
}
