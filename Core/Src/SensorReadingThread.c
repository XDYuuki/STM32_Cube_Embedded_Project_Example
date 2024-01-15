/*
 * SensorReadingThread.c
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */
#include <stdint.h>
#include <stdbool.h>

#include "cmsis_os.h"
#include "main.h"
#include "SensorReadingThread.h"
#include "SharedResources.h"
#include "utils.h"

void SensorReadingThreadRoutine(void *argument)
{
	  TickType_t currentTicks = xTaskGetTickCount();
	  GPIO_PinState Sensor1StateValue;
	while(1)
	{
		//checks every 5 seconds
		if(currentTicks >= (xTaskGetTickCount() + pdMS_TO_TICKS(5000)))
		{
			Sensor1StateValue = Sensor1Reading();
			UpdateReadings(Sensor1StateValue);
		}
	}
}

GPIO_PinState Sensor1Reading()
{
	GPIO_PinState Sensor2ReadingState;
	Sensor2ReadingState = HAL_GPIO_ReadPin(SENSOR_2_GPIO_Port, SENSOR_2_Pin);

	return Sensor2ReadingState;
}

void UpdateReadings(GPIO_PinState Sensor1StateValue)
{
    osMutexAcquire(ThreadCommunication_mutex, osWaitForever);


    osMutexRelease(ThreadCommunication_mutex);
}

uint8_t CheckPendingCommand()
{
    osMutexAcquire(ThreadCommunication_mutex, osWaitForever);

    if(SharedData.CommandReady)
    {
    	if(checkCRC16(SharedData.ActuatorCommand, sizeof(SharedData.ActuatorCommand)))
    	{

    	}
    }

    osMutexRelease(ThreadCommunication_mutex);

	return 0;
}

void ExecuteActuatorCommand(enum ActuatorCommand Command)
{
	if(Command == TURN_ON)
	{
		//set Actuatior GPIO
		HAL_GPIO_WritePin(ACTUATOR_GPIO_Port, ACTUATOR_Pin, GPIO_PIN_SET);
	}
}
