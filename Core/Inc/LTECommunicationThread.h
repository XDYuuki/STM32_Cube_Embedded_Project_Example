/*
 * LTECommunicationThread.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */

#ifndef INC_LTECOMMUNICATIONTHREAD_H_
#define INC_LTECOMMUNICATIONTHREAD_H_

enum
{
	MODULE_START_OK = 0,
	MODULE_START_FAIL = 1
};

void LTECommunicationThreadRoutine(void *argument);

#endif /* INC_LTECOMMUNICATIONTHREAD_H_ */
