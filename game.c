#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define HIGH_SCORE_FILE "highscores.txt"
#define LEADERBOARD_SIZE 3

void playGame(int maxRange, int maxAttempts, int *leaderboard, int *totalGames, int *totalGuesses);
int promptReplay();
void clearInputBuffer();
void displayWelcomeMessage();
void displayInstructions();
void displayRules();
void displayDateTime();
void displayFarewellMessage();
int chooseDifficulty();
void loadHighScores(int leaderboards[][LEADERBOARD_SIZE]);
void saveHighScores(int leaderboards[][LEADERBOARD_SIZE]);
void displayHighScores(int leaderboards[][LEADERBOARD_SIZE]);
void updateLeaderboard(int *leaderboard, int score);
void displayPerformanceSummary(int totalGames, int totalGuesses);

int main() {
    srand(time(0));
    int leaderboards[3][LEADERBOARD_SIZE];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < LEADERBOARD_SIZE; j++)
            leaderboards[i][j] = -1;
    loadHighScores(leaderboards);

    displayWelcomeMessage();
    displayDateTime();
    displayInstructions();
    displayRules();
    displayHighScores(leaderboards);

    int totalGames = 0;
    int totalGuesses = 0;

    do {
        int difficulty = chooseDifficulty();
        int maxRange, maxAttempts;

        switch (difficulty) {
            case 1: maxRange = 50; maxAttempts = 10; break;
            case 2: maxRange = 100; maxAttempts = 7; break;
            case 3: maxRange = 200; maxAttempts = 5; break;
            default: maxRange = 100; maxAttempts = 7;
        }

        playGame(maxRange, maxAttempts, leaderboards[difficulty - 1], &totalGames, &totalGuesses);
        saveHighScores(leaderboards);
    } while (promptReplay());

    displayPerformanceSummary(totalGames, totalGuesses);
    displayFarewellMessage();
    return 0;
}

void playGame(int maxRange, int maxAttempts, int *leaderboard, int *totalGames, int *totalGuesses) {
    int numberToGuess = rand() % maxRange + 1;
    int userGuess = 0, guessCount = 0, isValidInput;
    time_t startTime, endTime;

    printf("I have selected a number between 1 and %d. Can you guess it?\n", maxRange);

    time(&startTime);

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
            time(&endTime);
            double timeTaken = difftime(endTime, startTime);
            printf("Congratulations! You guessed the number in %d attempts and %.2f seconds.\n", guessCount, timeTaken);
            updateLeaderboard(leaderboard, guessCount);
            break;
        }

        if (guessCount == maxAttempts && userGuess != numberToGuess)
            printf("Sorry, you've reached the maximum number of attempts. The correct number was %d.\n", numberToGuess);
    }

    (*totalGames)++;
    (*totalGuesses) += guessCount;
}

void updateLeaderboard(int *leaderboard, int score) {
    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        if (leaderboard[i] == -1 || score < leaderboard[i]) {
            for (int j = LEADERBOARD_SIZE - 1; j > i; j--)
                leaderboard[j] = leaderboard[j - 1];
            leaderboard[i] = score;
            break;
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

void displayDateTime() {
    time_t currentTime;
    time(&currentTime);
    printf("Current Date and Time: %s", ctime(&currentTime));
}

void displayInstructions() {
    printf("\nInstructions:\n");
    printf("1. I will think of a number within a range based on the difficulty level.\n");
    printf("2. Your task is to guess the number.\n");
    printf("3. After each guess, I will tell you if your guess is too high, too low, or correct.\n");
    printf("4. Keep guessing until you find the correct number or run out of attempts.\n");
    printf("5. You can choose to play again after each game.\n\n");
}

void displayRules() {
    printf("Game Rules:\n");
    printf("1. You have a limited number of attempts based on the difficulty level.\n");
    printf("2. Guess the correct number within the specified range.\n");
    printf("3. Your best scores will be recorded in the high score list.\n");
    printf("4. Have fun!\n\n");
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

void loadHighScores(int leaderboards[][LEADERBOARD_SIZE]) {
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    if (file != NULL) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < LEADERBOARD_SIZE; j++)
                fscanf(file, "%d", &leaderboards[i][j]);
        fclose(file);
    }
}

void saveHighScores(int leaderboards[][LEADERBOARD_SIZE]) {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (file != NULL) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < LEADERBOARD_SIZE; j++)
                fprintf(file, "%d ", leaderboards[i][j]);
        fclose(file);
    }
}

void displayHighScores(int leaderboards[][LEADERBOARD_SIZE]) {
    const char *levels[] = {"Easy", "Medium", "Hard"};
    printf("\nHigh Scores:\n");
    for (int i = 0; i < 3; i++) {
        printf("%s: ", levels[i]);
        for (int j = 0; j < LEADERBOARD_SIZE; j++) {
            if (leaderboards[i][j] != -1)
                printf("%d attempts ", leaderboards[i][j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("\n");
}

void displayPerformanceSummary(int totalGames, int totalGuesses) {
    printf("\nPerformance Summary:\n");
    printf("Total Games Played: %d\n", totalGames);
    printf("Total Guesses Made: %d\n", totalGuesses);
    printf("Average Guesses per Game: %.2f\n\n", (double)totalGuesses / totalGames);
}
