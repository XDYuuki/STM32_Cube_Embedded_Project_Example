/*
 * LTECommunicationThread.c
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */
#include "cmsis_os.h"
#include "LTECommunicationThread.h"
#include "SharedResources.h"

void LTECommunicationThreadRoutine(void *argument)
{
	while(1)
	{

	}
}

void SendCommandToActuator(void)
{
    osMutexAcquire(ThreadCommunication_mutex, osWaitForever);


    osMutexRelease(ThreadCommunication_mutex);
}
