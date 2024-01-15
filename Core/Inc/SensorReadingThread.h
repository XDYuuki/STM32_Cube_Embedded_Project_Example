/*
 * SensorReadingThread.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */

#ifndef INC_SENSORREADINGTHREAD_H_
#define INC_SENSORREADINGTHREAD_H_

enum ActuatorCommand{
	TURN_ON,
	TURN_OFF
};

void SensorReadingThreadRoutine(void *argument);
GPIO_PinState Sensor1Reading();
void UpdateReadings(GPIO_PinState Sensor1StateValue);
uint8_t CheckPendingCommand();

#endif /* INC_SENSORREADINGTHREAD_H_ */
