# Guess the Number Game

## Overview

"Guess the Number" is a command-line game written in C. The game challenges players to guess a randomly selected number within a specified range and limited number of attempts based on the selected difficulty level. It also features a leaderboard to keep track of top scores for each difficulty level and provides a performance summary at the end of the session.

## Features

- Multiple difficulty levels: Easy, Medium, Hard
- High score leaderboard for each difficulty level
- Real-time performance feedback
- Summary of the player's performance across multiple games
- Option to replay the game

## Game Rules

1. The game will select a number within a range based on the chosen difficulty level.
2. The player must guess the number within a limited number of attempts.
3. After each guess, the game will provide feedback indicating whether the guess was too high, too low, or correct.
4. If the player guesses the correct number within the allotted attempts, their score will be recorded on the leaderboard.
5. The player can choose to play again after each game.

## Difficulty Levels

- **Easy**: Range: 1-50, Max Attempts: 10
- **Medium**: Range: 1-100, Max Attempts: 7
- **Hard**: Range: 1-200, Max Attempts: 5