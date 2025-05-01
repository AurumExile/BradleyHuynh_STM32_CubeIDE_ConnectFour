/*
 * ConnectFour.c
 *
 *  Created on: Apr 22, 2025
 *      Author: Bradley
 */


 #include "ConnectFour.h"

 extern TIM_HandleTypeDef htim2;
 
  uint8_t grid[BOARD_ROWS][BOARD_COLUMNS];
  uint8_t selectSpot;
 uint8_t turn;
 uint8_t playMode;
 int8_t win;
 uint8_t turnNum;
 uint8_t redWins;
 uint8_t yellowWins;
 uint32_t roundTime;
 
 void gameInit(uint8_t modeSelect) {
 
     resetTimer();
     playMode = modeSelect;
     clearBoard();
     selectSpot = 3;
     turn = RED;
     turnNum = 1;
     startTimer();
 
 
 }
 
 void changePlayer() {
 
     if(turn == RED) {
         turn = YELLOW;
         return;
     }
 
     turn = RED;
     return;
 
 }
 
 void placeChip() {
 
     int8_t y = getNextOpenSpot(selectSpot);
     if(y == COLUMN_FULL) return;
     setSpaceColor(y, selectSpot, turn);
     win = checkWin();
     if(win != GAME_ACTIVE) {
 
         winScenario();
         return;
 
     }
     changePlayer();
     turnNum++;
     if(playMode == ONE_PLAYER && turn == YELLOW) {
         runAITurn();
         turnNum++;
     }
 
 }
 
 void winScenario() {
 
     stopTimer();
     if(win == YELLOW) yellowWins++;
     if(win == RED) redWins++;
 
 }
 
 void runAITurn() {
 
     uint8_t gridBackup[BOARD_ROWS][BOARD_COLUMNS];
 
     for (uint8_t row = 0; row < BOARD_ROWS; row++) {
         for (uint8_t col = 0; col < BOARD_COLUMNS; col++) {
             gridBackup[row][col] = grid[row][col];
         }
     }
 
     selectSpot = getBestAIMove();
 
     for (uint8_t row = 0; row < BOARD_ROWS; row++) {
         for (uint8_t col = 0; col < BOARD_COLUMNS; col++) {
             grid[row][col] = gridBackup[row][col];
         }
     }
 
     int8_t check = getNextOpenSpot(selectSpot);
 
     while(check == COLUMN_FULL) {
         selectSpot++;
             if(selectSpot > 6) {
             selectSpot = 0;
         }
         check = getNextOpenSpot(selectSpot);
     }
 
     //probably uneeded now?
    while(grid[5][3] != EMPTY && selectSpot == 3) {
        selectSpot++;
        if(selectSpot > 6) {
            selectSpot = 0;
        }
    }
 
 
 
 
     placeChip();
 }
 void moveLeft() {
 
     if(selectSpot == 0) return;
     selectSpot--;
 
 }
 
 void moveRight() {
 
     if(selectSpot == 6) return;
     selectSpot++;
 
 }
 
 
 
 void clearBoard() {
 
     for(int i = 0; i < BOARD_ROWS; i++) {
 
         for(int j = 0; j < BOARD_COLUMNS; j++) {
 
             grid[i][j] = EMPTY;
 
         }
 
     }
 
 }
 
 void setSpaceColor(uint8_t row, uint8_t column, uint8_t color) {
 
     grid[row][column] = color;
 
 }
 
 uint8_t checkWin() {
     uint8_t i, j;
 
     // vertical
     for (i = 0; i < BOARD_ROWS - 3; i++) {
 
         for (j = 0; j < BOARD_COLUMNS; j++) {
 
             if (grid[i][j] != EMPTY &&
                 grid[i][j] == grid[i+1][j] &&
                 grid[i][j] == grid[i+2][j] &&
                 grid[i][j] == grid[i+3][j]) {
 
                 return grid[i][j];
 
             }
         }
     }
 
     // horizontal
     for (i = 0; i < BOARD_ROWS; i++) {
 
         for (j = 0; j < BOARD_COLUMNS - 3; j++) {
 
             if (grid[i][j] != EMPTY &&
                 grid[i][j] == grid[i][j+1] &&
                 grid[i][j] == grid[i][j+2] &&
                 grid[i][j] == grid[i][j+3]) {
 
                 return grid[i][j];
 
             }
         }
     }
 
     // right
     for (i = 0; i < BOARD_ROWS - 3; i++) {
 
         for (j = 0; j < BOARD_COLUMNS - 3; j++) {
 
             if (grid[i][j] != EMPTY &&
                 grid[i][j] == grid[i+1][j+1] &&
                 grid[i][j] == grid[i+2][j+2] &&
                 grid[i][j] == grid[i+3][j+3]) {
 
                 return grid[i][j];
 
             }
         }
     }
 
     // left
     for (i = 0; i < BOARD_ROWS - 3; i++) {
         for (j = 3; j < BOARD_COLUMNS; j++) {
             if (grid[i][j] != EMPTY &&
                 grid[i][j] == grid[i+1][j-1] &&
                 grid[i][j] == grid[i+2][j-2] &&
                 grid[i][j] == grid[i+3][j-3]) {
                 return grid[i][j];
             }
         }
     }
 
     // tie
     for (i = 0; i < BOARD_ROWS; i++) {
 
         for (j = 0; j < BOARD_COLUMNS; j++) {
 
             if (grid[i][j] == EMPTY) {
                 return GAME_ACTIVE;
             }
 
         }
     }
 
     return TIE;
 }
 
 
 uint8_t getNextOpenSpot(uint8_t column) {
 
     for(int i = 0; i < BOARD_ROWS; i++) {
 
         if(grid[i][column] == EMPTY) return i;
 
     }
 
     return COLUMN_FULL;
 
 }
 
 uint8_t getSpaceColor(uint8_t x, uint8_t y) {
 
     return grid[y][x];
 
 }
 
 uint8_t getTurn() {
 
     return turn;
 
 }
 
 uint8_t getActiveSpot() {
 
     return selectSpot;
 
 }
 
 void makeAIMove(uint8_t col, uint8_t player) {
     for (uint8_t row = 0; row < BOARD_ROWS; row++) {
         if (grid[row][col] == EMPTY) {
             grid[row][col] = player;
             break;
         }
     }
 }
 
 void undoAIMove(uint8_t col) {
     for (int8_t row = BOARD_ROWS - 1; row >= 0; row--) {
         if (grid[row][col] != EMPTY) {
             grid[row][col] = EMPTY;
             break;
         }
     }
 }
 
 
 int16_t evaluateBoard() {
     int16_t score = 0;
 
     for (uint8_t row = 0; row < BOARD_ROWS; row++) {
         if (grid[row][BOARD_COLUMNS / 2] == YELLOW) score += 3;
         if (grid[row][BOARD_COLUMNS / 2] == RED) score -= 3;
     }
 
     for (uint8_t row = 0; row < BOARD_ROWS; row++) {
         for (uint8_t col = 0; col < BOARD_COLUMNS - 3; col++) {
             uint8_t red = 0, yellow = 0;
             for (uint8_t i = 0; i < 4; i++) {
                 if (grid[row][col + i] == RED) red++;
                 if (grid[row][col + i] == YELLOW) yellow++;
             }
 
             if (yellow == 4) return 1000;
             if (red == 4) return -1000;
             if (yellow == 3 && red == 0) score += 10;
             else if (yellow == 2 && red == 0) score += 5;
             else if (red == 3 && yellow == 0) score -= 100;
             else if (red == 2 && yellow == 0) score -= 5;
         }
     }
 
     for (uint8_t col = 0; col < BOARD_COLUMNS; col++) {
         for (uint8_t row = 0; row < BOARD_ROWS - 3; row++) {
             uint8_t red = 0, yellow = 0;
             for (uint8_t i = 0; i < 4; i++) {
                 if (grid[row + i][col] == RED) red++;
                 if (grid[row + i][col] == YELLOW) yellow++;
             }
             if (yellow == 4) return 1000;
             if (red == 4) return -1000;
             if (yellow == 3 && red == 0) score += 10;
             else if (yellow == 2 && red == 0) score += 5;
             else if (red == 3 && yellow == 0) score -= 100;
             else if (red == 2 && yellow == 0) score -= 5;
         }
     }
 
     for (uint8_t row = 0; row < BOARD_ROWS - 3; row++) {
         for (uint8_t col = 0; col < BOARD_COLUMNS - 3; col++) {
             uint8_t red = 0, yellow = 0;
             for (uint8_t i = 0; i < 4; i++) {
                 if (grid[row + i][col + i] == RED) red++;
                 if (grid[row + i][col + i] == YELLOW) yellow++;
             }
             if (yellow == 4) return 1000;
             if (red == 4) return -1000;
             if (yellow == 3 && red == 0) score += 10;
             else if (yellow == 2 && red == 0) score += 5;
             else if (red == 3 && yellow == 0) score -= 100;
             else if (red == 2 && yellow == 0) score -= 5;
         }
     }
 
     for (uint8_t row = 3; row < BOARD_ROWS; row++) {
         for (uint8_t col = 0; col < BOARD_COLUMNS - 3; col++) {
                 uint8_t red = 0, yellow = 0;
            for (uint8_t i = 0; i < 4; i++) {
                if (grid[row - i][col + i] == RED) red++;
                if (grid[row - i][col + i] == YELLOW) yellow++;
            }
            if (yellow == 4) return 1000;
            if (red == 4) return -1000;
            if (yellow == 3 && red == 0) score += 10;
            else if (yellow == 2 && red == 0) score += 5;
            else if (red == 3 && yellow == 0) score -= 100;
            else if (red == 2 && yellow == 0) score -= 5;
         }
     }
 
     return score;
 }
 int16_t minimax(uint8_t depth, uint8_t maximizingPlayer) {
     if (depth == 0 || checkWin() != GAME_ACTIVE)
         return evaluateBoard();
 
     if (maximizingPlayer) {
         int16_t maxEval = -2000;
         for (uint8_t col = 0; col < BOARD_COLUMNS; col++) {
             if (getNextOpenSpot(col) != COLUMN_FULL) {
                 makeAIMove(col, YELLOW);
                 int16_t eval = minimax(depth - 1, 0);
                 undoAIMove(col);
                 if (eval > maxEval) maxEval = eval;
             }
         }
         return maxEval;
     } else {
         int16_t minEval = 2000;
         for (uint8_t col = 0; col < BOARD_COLUMNS; col++) {
             if (getNextOpenSpot(col) != COLUMN_FULL) {
                 makeAIMove(col, RED);
                 int16_t eval = minimax(depth - 1, 1);
                 undoAIMove(col);
                 if (eval < minEval) minEval = eval;
             }
         }
         return minEval;
     }
 }
 
 uint8_t getBestAIMove() {
     int16_t bestScore = -2000;
     uint8_t bestCol = 0;
 
     if(turnNum == 5 && grid[0][3] == RED && grid[0][2] == RED) return 1;
 
     for (uint8_t col = 0; col < BOARD_COLUMNS; col++) {
         if (getNextOpenSpot(col) != COLUMN_FULL) {
             makeAIMove(col, YELLOW);
             int16_t score = minimax(MAX_DEPTH - 1, 0);
             undoAIMove(col);
 
             if (score > bestScore) {
                 bestScore = score;
                 bestCol = col;
             }
         }
     }
 
     return bestCol;
 }
 
 int8_t getWin() {
 
     return win;
 
 }
 
 uint8_t getRedWins() {
     return redWins;
 }
 uint8_t getYellowWins() {
 
     return yellowWins;
 
 }
 
 void clearWins() {
 
     redWins = 0;
     yellowWins = 0;
 
 }
 
 
 void TIM2_IRQHandler(void)
 {
     HAL_TIM_IRQHandler(&htim2);
 
     HAL_NVIC_DisableIRQ(TIM2_IRQn);
 
     HAL_NVIC_EnableIRQ(EXTI0_IRQn);
 
     __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
     __NVIC_ClearPendingIRQ(TIM2_IRQn);
 
     roundTime++;
 
     HAL_NVIC_EnableIRQ(TIM2_IRQn);
 }
 
 void startTimer()
 {
     HAL_NVIC_EnableIRQ(TIM2_IRQn);
     roundTime = 0;
     HAL_TIM_Base_Start_IT(&htim2);
 }
 
 void stopTimer()
 {
     HAL_NVIC_DisableIRQ(TIM2_IRQn);
     HAL_TIM_Base_Stop_IT(&htim2);
 }
 
 void resetTimer()
 {
     roundTime = 0;
     __HAL_TIM_SET_COUNTER(&htim2, 0);
 }
 
 uint32_t getTimer()
 {
     return roundTime;
 }
 
 
 