//
// Created by GEORGE-pc on 2020/3/17.
//

#ifndef CHAPTER_09_REFINING_ABSTRACTIONS_SNAKEGAME_H
#define CHAPTER_09_REFINING_ABSTRACTIONS_SNAKEGAME_H

#include <string>
#include <vector>
#include <deque>
#include "PointTale.h"

using namespace std;

/* Exercise 21. */

class SnakeGame {
public:
    SnakeGame();
private:
    /* activity of range for the snake. */
    vector<string> world;

    /* height and width of the world. */
    int num_rows, num_cols;

    /* the snake implemented based on deque. */
    deque<PointTale> snake;

    /* number of points being eaten currently by the snake. */
    int num_eaten;

    /* The current direction of snake. (1,0), (0,1), (-1,0), (0,-1). */
    int dx, dy;
public:
    static const int kMaxFood = 20;
    static const int kWaitInterval = 0.1;
    static const string kClearCommand = "CLS";
    static const char kEmptyTile = ' ';
    static const char kWallTile = '#';
    static const char kFoodTile = '$';
    static const char kSnakeTile = '*';

public:
    void InitializeGame();
    void RunSimulation();

private:
    void OpenFile(fstream &input) const ;
    void LoadGame(fstream &input);
    void PrintWorld() const ;
    void PerformAI();
    const PointTale GetNextPosition(const int &dx, const int &dy) const ;
    bool Crashed(const PointTale &head) const ;
    bool TurnDirectionRandom(const double &probability) const ;
    bool MoveSnake();
    void PlaceFood();
    void Pause() const ;
    void DisplayResult() const ;
};

#endif //CHAPTER_09_REFINING_ABSTRACTIONS_SNAKEGAME_H
