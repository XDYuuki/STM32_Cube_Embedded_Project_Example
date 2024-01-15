/*
 * SharedResources.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */

#ifndef INC_SHAREDRESOURCES_H_
#define INC_SHAREDRESOURCES_H_

struct ThreadCommunication
{
	int Sensor1Reading;
	unsigned char Sensor2Reading;
	unsigned char CommandReady;
	uint8_t ActuatorCommand [32];
};

extern struct ThreadCommunication SharedData;
extern osMutexId_t ThreadCommunication_mutex;

void initCommunicationMutex(void);

#endif /* INC_SHAREDRESOURCES_H_ */
