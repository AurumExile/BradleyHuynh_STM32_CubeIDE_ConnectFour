/*
 * SceneDriver.h
 *
 *  Created on: Apr 23, 2025
 *      Author: Bradley
 */

#ifndef INC_SCENEDRIVER_H_
#define INC_SCENEDRIVER_H_

#include "LCD_Driver.h"
#include <stdio.h>
#include "ConnectFour.h"

#define STARTMENU 0
#define PLAY 1
#define END 2

void sceneInit();

void drawScene();

void sceneDelay(uint32_t time);

void drawStartMenu();

void drawGame();

void drawEnd();

void changeScene(uint8_t newScene);

void touchHandler(uint8_t x, uint8_t y);

void convertTimeToString(uint32_t time, char *str);
void convertScoreToString(char * str);

#endif /* INC_SCENEDRIVER_H_ */
