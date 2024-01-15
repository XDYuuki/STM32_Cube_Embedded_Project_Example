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
	  TickType_t nextCheck = xTaskGetTickCount() + FIVE_SECONDS_MS;
	  GPIO_PinState Sensor2StateValue;
	  uint16_t Sensor1AnalogValue;

	while(1)
	{
		//checks every 5 seconds
		if(xTaskGetTickCount() >= nextCheck)
		{
			Sensor2StateValue = Sensor2Reading();
			Sensor1AnalogValue = Sensor1AnalogReading();
			UpdateReadings(Sensor1AnalogValue, Sensor2StateValue);

			nextCheck = xTaskGetTickCount() + FIVE_SECONDS_MS;
		}
	}
}

uint16_t Sensor1AnalogReading(void)
{
	uint16_t AnalogResponse = 0;

	//Execute the analog value here
	return AnalogResponse;
}

GPIO_PinState Sensor2Reading(void)
{
	GPIO_PinState Sensor2ReadingState;
	Sensor2ReadingState = HAL_GPIO_ReadPin(SENSOR_2_GPIO_Port, SENSOR_2_Pin);

	return Sensor2ReadingState;
}

void UpdateReadings(uint16_t Sensor1AnalogValue, GPIO_PinState Sensor2StateValue)
{
    osMutexAcquire(ThreadCommunication_mutex, osWaitForever);

    SharedData.Sensor1Reading = Sensor1AnalogValue;
    SharedData.Sensor2Reading = Sensor2StateValue;

    osMutexRelease(ThreadCommunication_mutex);
}

uint8_t CheckPendingCommand(void)
{
    osMutexAcquire(ThreadCommunication_mutex, osWaitForever);

    if(SharedData.CommandReady)
    {
    	if(checkCRC16(SharedData.ActuatorCommand, sizeof(SharedData.ActuatorCommand)))
    	{
    		//Handle the command list and execute it
    	}
    }

    SharedData.CommandReady = false;
    osMutexRelease(ThreadCommunication_mutex);

	return 0;
}

void ExecuteActuatorCommand(ActuatorCommand Command)
{
	if(Command == TURN_ON)
	{
		HAL_GPIO_WritePin(ACTUATOR_GPIO_Port, ACTUATOR_Pin, GPIO_PIN_SET);
	}else
	{
		HAL_GPIO_WritePin(ACTUATOR_GPIO_Port, ACTUATOR_Pin, GPIO_PIN_RESET);
	}
}
