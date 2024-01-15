/*
 * utils.h
 *
 *  Created on: Jan 14, 2024
 *      Author: gabzy
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

uint16_t calculateCRC16(const uint8_t *data, uint32_t length);
bool checkCRC16(const uint8_t *data, uint32_t length);


#endif /* INC_UTILS_H_ */
