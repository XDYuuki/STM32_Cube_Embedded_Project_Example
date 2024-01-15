/*
 * LTECommunicationThread.c
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */

#include <string.h>
#include "cmsis_os.h"
#include "main.h"
#include "LTECommunicationThread.h"
#include "SharedResources.h"

void LTECommunicationThreadRoutine(void *argument)
{
	TickType_t nextCheck = xTaskGetTickCount() + MINUTE_MS;

	// Module Startup
	if(StartupBG95() != MODULE_START_OK)
	{
		//Handle Restart of the module
	}


	while(1)
	{
		//Checks every minute
		if(xTaskGetTickCount()>= nextCheck)
		{

		}
	}
}



ModuleStartup StartupBG95(void)
{
	uint8_t ATCommand [] = "AT/r/n";
	uint8_t ResponseBuffer [100];

	char OKCheck[] = "OK";
	HAL_StatusTypeDef Anstatus;

	HAL_GPIO_WritePin(BG95_RESET_N_GPIO_Port, BG95_RESET_N_Pin, GPIO_PIN_RESET);

	//Driving PWRKEY LOW for 500-1000ms (Considering that the circuit reverses the signal)
	HAL_GPIO_WritePin(BG95_PWRKEY_GPIO_Port, ACTUATOR_Pin, GPIO_PIN_SET);
	HAL_Delay(900);
	HAL_GPIO_WritePin(BG95_PWRKEY_GPIO_Port, ACTUATOR_Pin, GPIO_PIN_RESET);

	//Delay to guarantee that the UART is already active to receive commands
	HAL_Delay(2500);

	HAL_UART_Transmit(&huart2, ATCommand, sizeof(ATCommand), 300);
	Anstatus = HAL_UART_Receive(&huart2, ResponseBuffer, sizeof(ResponseBuffer), 300);

	if(Anstatus == HAL_OK)
	{
		//Checks if there is an "OK" as answer for the AT command
		if(strstr((char*)ResponseBuffer,OKCheck) != NULL)
		{
			return MODULE_START_OK;
		}
	}
	return MODULE_START_FAIL;
}

void SendCommandToActuator(void)
{
    osMutexAcquire(ThreadCommunication_mutex, osWaitForever);


    osMutexRelease(ThreadCommunication_mutex);
}
