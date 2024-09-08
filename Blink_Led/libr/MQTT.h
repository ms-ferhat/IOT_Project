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

void MQTT_connect(u8* Client_ID);
void MQTT_Publish(u8* topic,u8* mes,u32 len,u8 QoS);
void MQTT_Subscribe(u8* Topic);



#endif /* INC_MQTT_H_ */
