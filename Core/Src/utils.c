/*
 * utils.c
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */

#include <stdint.h>
#include <stdbool.h>

#include "utils.h"

// Function to calculate CRC-16-CCITT for a given data array
uint16_t calculateCRC16(const uint8_t *data, uint32_t length)
{
    const uint16_t polynomial = 0x1021; // CRC-16-CCITT polynomial
    uint16_t crc = 0xFFFF; // Initial value

    for (uint32_t i = 0; i < length; i++) {
        crc ^= (uint16_t)(data[i] << 8); // XOR with next byte

        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc = crc << 1;
            }
        }
    }

    return crc;
}

// Function to check CRC-16-CCITT for a given data array
bool checkCRC16(const uint8_t *data, uint32_t length)
{
    // The last two bytes in the data array are assumed to be the CRC-16
    uint16_t receivedCRC = (uint16_t)((data[length - 2] << 8) | data[length - 1]);

    // Calculate CRC-16 for the rest of the data
    uint16_t calculatedCRC = calculateCRC16(data, length - 2);

    // Compare calculated CRC with received CRC
    return (receivedCRC == calculatedCRC);
}
