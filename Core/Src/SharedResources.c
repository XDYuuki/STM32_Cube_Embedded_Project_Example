/*
 * SharedResources.c
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */

#include "cmsis_os.h"
#include "SharedResources.h"


struct ThreadCommunication SharedData = {0};
osMutexId_t ThreadCommunication_mutex;

void initCommunicationMutex(void)
{
	ThreadCommunication_mutex = osMutexNew(NULL);
}
