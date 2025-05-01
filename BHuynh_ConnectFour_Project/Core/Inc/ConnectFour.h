/*
 * ConnectFour.h
 *
 *  Created on: Apr 22, 2025
 *      Author: Bradley
 */

#ifndef INC_CONNECTFOUR_H_
#define INC_CONNECTFOUR_H_

#include "stm32f4xx_hal.h"

#define BOARD_ROWS 6
#define BOARD_COLUMNS 7

#define EMPTY 0
#define RED 1
#define YELLOW 2

#define NOT_ACTIVE 0
#define RED_TURN 1
#define YELLOW_TURN 2

#define ONE_PLAYER 0
#define TWO_PLAYER 1

#define GAME_ACTIVE -1
#define TIE 0
#define RED_WIN 1
#define YELLOW_WIN 2
#define COLUMN_FULL -1
#define MAX_DEPTH 5

void clearBoard();

void setSpaceColor(uint8_t row, uint8_t column, uint8_t color);

uint8_t checkWin();

uint8_t getNextOpenSpot(uint8_t column);

uint8_t getSpaceColor(uint8_t x, uint8_t y);
uint8_t getTurn();
uint8_t getActiveSpot();
int8_t getWin();


void gameInit(uint8_t modeSelect);
void placeChip();
void moveLeft();
void moveRight();
void changePlayer();
void winScenario();
void runAITurn();

uint8_t getBestAIMove();
int16_t minimax(uint8_t depth, uint8_t maximizingPlayer);
int16_t evaluateBoard();
void undoAIMove(uint8_t col);
void makeAIMove(uint8_t col, uint8_t player);

uint8_t getRedWins();
uint8_t getYellowWins();


void startTimer();

void stopTimer();

void resetTimer();

uint32_t getTimer();

#endif /* INC_CONNECTFOUR_H_ */
