/*
 * SceneDriver.c
 *
 *  Created on: Apr 23, 2025
 *      Author: Bradley
 */


#include "SceneDriver.h"

uint8_t Scene;

void sceneInit() {

	changeScene(STARTMENU);
	drawScene();

}

void drawScene() {

	if(Scene == STARTMENU) drawStartMenu();
	else if(Scene == PLAY) drawGame();
	else if(Scene == END) drawEnd();

}

void drawStartMenu() {

	LCD_Clear(0, LCD_COLOR_BLACK);
	LCD_DrawRectangle(30, 60, 210, 140, LCD_COLOR_BLUE);
	LCD_DrawRectangle(30, 200, 210, 280, LCD_COLOR_BLUE);

	char msg[] = "1 Player";

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	LCD_DrawString(50,90, msg);

	char msg2[] = "2 Player";

	LCD_DrawString(50, 230, msg2);


}

void drawGame() {


	LCD_Clear(0, LCD_COLOR_BLUE2);
	LCD_DrawRectangle(0, 260, 80, 320, LCD_COLOR_BLACK);
	LCD_DrawRectangle(80, 260, 160, 320, LCD_COLOR_WHITE);
	LCD_DrawRectangle(160, 260, 240, 320, LCD_COLOR_BLACK);

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	LCD_DisplayChar(30, 290,'L');
	LCD_DisplayChar(190, 290,'R');
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayChar(110, 290,'P');

	uint8_t x = 24;
	uint8_t y = 244;
	uint8_t color = EMPTY;

	for(int i = 0; i < BOARD_ROWS; i++) {

		for(int j = 0; j < BOARD_COLUMNS; j++) {

			color = getSpaceColor(j, i);

			if(color == RED) {

				LCD_Draw_Circle_Fill(x, y, 12, LCD_COLOR_RED);

			} else if(color == YELLOW) {

				LCD_Draw_Circle_Fill(x, y, 12, LCD_COLOR_YELLOW);

			} else {

				LCD_Draw_Circle_Fill(x, y, 12, LCD_COLOR_WHITE);

			}

			x += 32;

		}

		x = 24;
		y -= 32;

	}

	x = 24 + (32 * getActiveSpot());
	color = getTurn();

	if(color == RED) {

		LCD_Draw_Circle_Fill(x, 52, 12, LCD_COLOR_RED);

	} else {

		LCD_Draw_Circle_Fill(x, 52, 12, LCD_COLOR_YELLOW);

	}



}

void drawEnd() {

	LCD_Clear(0, LCD_COLOR_BLACK);

	LCD_DrawRectangle(30, 10, 210, 70, LCD_COLOR_BLUE);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	int8_t winState = getWin();

	if (winState == RED) {
	    char msg1[] = "Red Wins";
	    LCD_DrawString(50, 30, msg1);
	} else if (winState == YELLOW) {
	    char msg2[] = "Yellow Wins";
	    LCD_DrawString(35, 30, msg2);
	} else if (1) {
	    char msg3[] = "Tie";
	    LCD_DrawString(100, 30, msg3);
	}

	char msg4[] = "Time:";
	LCD_DrawString(35, 100, msg4);
	char buffer[20];
	convertTimeToString(getTimer(), buffer);
	LCD_DrawString(120, 100, buffer);

	char msg5[] = "R/Y:";
	LCD_DrawString(40, 150, msg5);
	char buffer2[20];
	convertScoreToString(buffer2);
	LCD_DrawString(120, 150, buffer2);

	LCD_DrawRectangle(0, 250, 240, 320, LCD_COLOR_BLUE);
	char msg6[] = "Restart";
	LCD_DrawString(75, 270, msg6);


}

void changeScene(uint8_t newScene) {

	Scene = newScene;

}

void touchHandler(uint8_t x, uint8_t y) {

	if(Scene == STARTMENU) {
			if(y > 60 && y < 140 && x > 30 && x < 210) {
				gameInit(TWO_PLAYER);
				changeScene(PLAY);
				drawScene();
			} else if (y > 200 && y < 280 && x > 30 && x < 210) {
				gameInit(ONE_PLAYER);
				changeScene(PLAY);
				drawScene();
			}

			return;

		}
	else if (Scene == PLAY) {
		if(x == 239) return;
	    if (y >= 0 && y < 60) {
	        if (x >= 0 && x < 80) {
	            moveLeft();
	            drawScene();
	        } else if (x >= 80 && x < 160) {
	            placeChip();
	            drawScene();
	            if(getWin() != GAME_ACTIVE) {
	            	if(getWin() == RED) {
	            		LCD_DrawRectangle(0, 0, 240, 50, LCD_COLOR_RED);
	            	}
	            	if(getWin() == YELLOW) {
	            		LCD_DrawRectangle(0, 0, 240, 50, LCD_COLOR_YELLOW);
	            	}
	            	HAL_Delay(4000);
	            	changeScene(END);
	            	drawScene();
	            }
	        } else if (x >= 160 && x <= 239) {
	            moveRight();
	            drawScene();
	        }
	    }

	    return;
	} else {
		if(y < 70) {
			changeScene(STARTMENU);
			drawScene();
		}
	}

}

void convertTimeToString(uint32_t time, char *str)
{
    uint32_t minutes = time / 60;
    uint32_t seconds = time % 60;

    sprintf(str, "%02lu:%02lu", minutes, seconds);
}

void convertScoreToString(char* str)
{
    uint32_t red = getRedWins();
    uint32_t yellow = getYellowWins();

    sprintf(str, "%02lu/%02lu", red, yellow);
}
