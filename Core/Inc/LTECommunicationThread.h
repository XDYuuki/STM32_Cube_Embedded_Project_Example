/*
 * LTECommunicationThread.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */

#ifndef INC_LTECOMMUNICATIONTHREAD_H_
#define INC_LTECOMMUNICATIONTHREAD_H_

#define MINUTE_MS 60000UL

typedef enum
{
	MODULE_ANS_OK = 0,
	MODULE_ANS_FAIL = 1
}ModuleStartup;

void LTECommunicationThreadRoutine(void *argument);
ModuleStartup StartupBG95(void);
ModuleStartup NetWorkConnection(void);
ModuleStartup ActivateContext(void);

#endif /* INC_LTECOMMUNICATIONTHREAD_H_ */
