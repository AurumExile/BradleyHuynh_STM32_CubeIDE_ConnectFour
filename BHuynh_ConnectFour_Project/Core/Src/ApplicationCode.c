/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
uint8_t pressed;
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	// This is the orientation for the board to be directly up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;
	InitializeLCDTouch();
	HAL_Delay(500);
	sceneInit();
	#endif // COMPILE_TOUCH_FUNCTIONS

}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
}

void runProgram() {

	if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed && pressed == FALSE) {
		touchHandler(StaticTouchData.x, StaticTouchData.y);
		pressed = TRUE;
		HAL_Delay(250);
	} else {
		pressed = FALSE;
	}

}
#endif // COMPILE_TOUCH_FUNCTIONS

/*void EXTI15_10_IRQHandler(void)
{
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
    HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
    uint8_t intStatus = STMPE811_Read(STMPE811_INT_STA);
    STMPE811_Write(STMPE811_INT_STA, 0xFF);

    if (intStatus & 0x1)
    {
    	DetermineTouchPosition(&StaticTouchData);
    	printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
        touchHandler(StaticTouchData.x, StaticTouchData.y);
    }

} */

