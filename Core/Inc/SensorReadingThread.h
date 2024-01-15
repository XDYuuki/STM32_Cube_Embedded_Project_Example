/*
 * SensorReadingThread.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */

#ifndef INC_SENSORREADINGTHREAD_H_
#define INC_SENSORREADINGTHREAD_H_

#define FIVE_SECONDS_MS 5000UL

typedef enum{
	TURN_ON,
	TURN_OFF
}ActuatorCommand;

void SensorReadingThreadRoutine(void *argument);
GPIO_PinState Sensor2Reading(void);
void UpdateReadings(uint16_t Sensor1AnalogValue, GPIO_PinState Sensor2StateValue);
uint8_t CheckPendingCommand(void);
uint16_t Sensor1AnalogReading(void);

#endif /* INC_SENSORREADINGTHREAD_H_ */
