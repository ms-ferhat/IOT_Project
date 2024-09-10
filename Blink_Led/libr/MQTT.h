/*
 * MQTT.h
 *
 *  Created on: Nov 19, 2023
 *      Author: MS
 */

#ifndef INC_MQTT_H_
#define INC_MQTT_H_

#include "stdint.h"
#include "string.h"

#define CONNECT_PACKET		0x10;

void MQTT_connect(uint8_t* Client_ID, uint8_t* username, uint8_t* password);
void MQTT_conAck(u8 *stues);
void MQTT_Publish(u8* topic,u8* mes,u32 len,u8 QoS);
void MQTT_Subscribe(u8* Topic);
void MQTT_recive_message(u8 *Payload,u8 *header);




#endif /* INC_MQTT_H_ */
