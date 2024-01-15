/*
 * LTECommunicationThread.c
 *
 *  Created on: Jan 14, 2024
 *      Author: Gabriel Rocha
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_os.h"
#include "utils.h"
#include "main.h"
#include "LTECommunicationThread.h"
#include "SharedResources.h"

void LTECommunicationThreadRoutine(void *argument)
{
	TickType_t nextCheck = xTaskGetTickCount() + MINUTE_MS;

	// Module Startup
	if(StartupBG95() != MODULE_ANS_OK)
	{
		//Handle Restart of the module
	}

	// Activating Context for the connection
	if(ActivateContext() != MODULE_ANS_OK)
	{
		//Handle Activate context error
	}


	while(1)
	{
		//Checks every minute
		if(xTaskGetTickCount()>= nextCheck)
		{
			//Handle sending and receiving messages
			//Handle sending command to the actuator using the shared struct
		}
	}
}

ModuleStartup StartupBG95(void)
{
	uint8_t ATCommand [] = "AT/r/n";
	uint8_t ResponseBuffer [100];

	char OKCheck[] = "OK";
	HAL_StatusTypeDef Anstatus;

	HAL_GPIO_WritePin(BG95_RESET_N_GPIO_Port, BG95_RESET_N_Pin, GPIO_PIN_RESET);

	//Driving PWRKEY LOW for 500-1000ms (Considering that the circuit reverses the signal)
	HAL_GPIO_WritePin(BG95_PWRKEY_GPIO_Port, ACTUATOR_Pin, GPIO_PIN_SET);
	HAL_Delay(900);
	HAL_GPIO_WritePin(BG95_PWRKEY_GPIO_Port, ACTUATOR_Pin, GPIO_PIN_RESET);

	//Delay to guarantee that the UART is already active to receive commands
	HAL_Delay(2500);

	HAL_UART_Transmit(&huart2, ATCommand, sizeof(ATCommand), 300);
	Anstatus = HAL_UART_Receive(&huart2, ResponseBuffer, sizeof(ResponseBuffer), 300);

	if(Anstatus == HAL_OK)
	{
		//Checks if there is an "OK" as answer for the AT command
		if(strstr((char*)ResponseBuffer,OKCheck) != NULL)
		{
			return MODULE_ANS_OK;
		}
	}
	return MODULE_ANS_FAIL;
}


uint16_t HTTPGetRequest(char * GetResponse, uint32_t BufferSize)
{
	/*
	 * //Example of how to send an HTTP GET response.
AT+QHTTPCFG="contextid",1 //Configure the PDP context ID as 1.
OK
AT+QHTTPCFG="responseheader",1 //Allow the output of HTTP response header.
OK
AT+QIACT? //Query the list of currently activated contexts and their IP
addresses.
OK //No context activated currently.
AT+QICSGP=1,1,"UNINET","","",1 //Configure PDP context 1. Protocol type: IPv4. China
Unicom APN: UNINET. Authentication method: PAP.
OK
AT+QIACT=1 //Activate context 1.
OK //Activated successfully.
AT+QIACT? //Query the list of currently activated contexts and their IP
addresses.
+QIACT: 1,1,1,"10.7.157.1"
OK
AT+QHTTPURL=23,80 //Set the URL of the HTTP server that will be accessed.
CONNECT
http://www.sina.com.cn/ //Input the URL whose length should be 23 bytes. (This URL
is only an example. Input the correct URL in a practical
test.)
OK
AT+QHTTPGET=80 //Send the HTTP GET request with the maximum response
time of 80 s.
OK
LPWA Module Series
BG95&BG77&BG600L_Series_HTTP(S)_Application_Note 28 / 52
+QHTTPGET: 0,200,547256 //If the HTTP response header contains “Content-Length”
information, then the <content_length> (547256) will be
reported.
//Example of how to read an HTTP response.
//Solution 1: Read the HTTP response information and output it via the UART port.
AT+QHTTPREAD=80 //Read the HTTP response information and output it via a
UART. The maximum time to wait for an HTTP session to be
closed is 80 s.
CONNECT
HTTP/1.1 200 OK <CR><LF> //HTTP response header and body.
Content-Type: text/html<CR><LF>
Vary: Accept-Encoding<CR><LF>
X-Powered-By: shci_v1.03<CR><LF>
Server: nginx<CR><LF>
Date: Fri, 27 Dec 2013 02:21:43 GMT<CR><LF>
Last-Modified: Fri, 27 Dec 2013 02:20:01 GMT<CR><LF>
Expires: Fri, 27 Dec 2013 02:22:43 GMT<CR><LF>
Cache-Control: max-age=60<CR><LF>
Age: 1<CR><LF>
Content-Length: 547256<CR><LF>
X-Cache: HIT from xd33-85.sina.com.cn<CR><LF>
<CR><LF>
<body>
OK
+QHTTPREAD: 0 //
	*/

	return 0;
}

ModuleStartup ActivateContext(void)
{
	uint8_t CommandToSend[100];
	uint8_t ResponseBuffer[100];
	char OKCheck[] = "OK";
	uint16_t StringSize;

	HAL_StatusTypeDef AnStatus;


	//Configure context 1. APN is "CMNBIOT" for China Mobile as it is in the application document example
	strcpy((char*)CommandToSend, "AT+QICSGP=1,1,\"CMNBIOT\",\"\",\"\",1");
	StringSize = strlen((char*)CommandToSend);
	HAL_UART_Transmit(&huart2, CommandToSend, StringSize, 300);
	AnStatus = HAL_UART_Receive(&huart2, ResponseBuffer, sizeof(ResponseBuffer), 300);

	if(AnStatus == HAL_OK)
	{
		//Checks if there is an "OK" as answer for the AT command
		if(strstr((char*)ResponseBuffer, OKCheck) == NULL)
		{
			return MODULE_ANS_FAIL;
		}
		return MODULE_ANS_FAIL;
	}

	//Activating the context
	strcpy((char*)CommandToSend, "AT+QIACT=1");
	StringSize = strlen((char*)CommandToSend);
	HAL_UART_Transmit(&huart2, CommandToSend, StringSize, 300);
	AnStatus = HAL_UART_Receive(&huart2, ResponseBuffer, sizeof(ResponseBuffer), 300);

	if(AnStatus == HAL_OK)
	{
		//Checks if there is an "OK" as answer for the AT command
		if(strstr((char*)ResponseBuffer, OKCheck) == NULL)
		{
			return MODULE_ANS_FAIL;
		}
		return MODULE_ANS_FAIL;
	}

	return MODULE_ANS_OK;
}

void SendCommandToActuator(uint8_t * Command, uint16_t Size)
{
    osMutexAcquire(ThreadCommunication_mutex, osWaitForever);

    uint16_t CRC16 = calculateCRC16(Command, sizeof(SharedData.ActuatorCommand));
    Command[sizeof(SharedData.ActuatorCommand) - 2] = (uint8_t)(CRC16>>8);
    Command[sizeof(SharedData.ActuatorCommand) - 1] = (uint8_t)(CRC16 & 0xFF);

    memcpy(SharedData.ActuatorCommand, Command, Size);
    SharedData.CommandReady = true;

    osMutexRelease(ThreadCommunication_mutex);
}
