/**
 ******************************************************************************
 * @file           : MQTT.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention

 ******************************************************************************
 */
/*
 *  file name :	MQTT.c
 *  Created on: Nov 19, 2023
 *  Author    : Mohamed Shaban
 */

#include "STD_types.h"
#include "BIT_math.h"

#include "MQTT.h"
#include "../1-DIO/DIO_interface.h"
#include "../2-PORT/PORT_interface.h"
#include "../7-USART/Uasrt_inteface.h"

u8 Packet_buffer[200]={0};
u8 packetInd=0;
u8 packetID=1;


void MQTT_connect(uint8_t* Client_ID, uint8_t* username, uint8_t* password) {
    uint8_t username_len = strlen(username);
    uint8_t password_len = strlen(password);
    uint8_t client_id_len = strlen(Client_ID);

    uint8_t remlen = 12 + client_id_len + 2 + username_len + 2 + password_len;  // Adjust remaining length to include username and password

    // Encode packet
    packetInd = 0;
    Packet_buffer[packetInd++] = CONNECT_PACKET;  // Packet type 0x10 for connect packet
    Packet_buffer[packetInd++] = remlen;

    // Protocol Name
    Packet_buffer[packetInd++] = 0x00;
    Packet_buffer[packetInd++] = 0x04;
    strcpy(Packet_buffer + packetInd, "MQTT");
    packetInd += 4;

    // Protocol Level
    Packet_buffer[packetInd++] = 0x04;  // Protocol level 4 for MQTT 3.1.1

    // Connect Flags (username and password flags set)
    Packet_buffer[packetInd++] = 0xC2;  // Flags: 0xC2 (Clean Session, Username, Password)

    // Keep Alive
    Packet_buffer[packetInd++] = 0x00;
    Packet_buffer[packetInd++] = 0xFF;

    // Client ID
    Packet_buffer[packetInd++] = 0x00;
    Packet_buffer[packetInd++] = client_id_len;
    strcpy(Packet_buffer + packetInd, Client_ID);
    packetInd += client_id_len;

    // Username
    Packet_buffer[packetInd++] = 0x00;
    Packet_buffer[packetInd++] = username_len;
    strcpy(Packet_buffer + packetInd, username);
    packetInd += username_len;

    // Password
    Packet_buffer[packetInd++] = 0x00;
    Packet_buffer[packetInd++] = password_len;
    strcpy(Packet_buffer + packetInd, password);
    packetInd += password_len;

    // Send packet
    Uart_u8SendBuffer(Packet_buffer, packetInd);
}

void MQTT_Publish(uint8_t* topic,uint8_t* mes,uint32_t len,uint8_t QoS)
{
	uint8_t mesInd=0;
	uint8_t remlen=(2 + strlen(topic) + len);


	//encode packet
	packetInd=0;
	if(QoS>0)
	{
		remlen+=2;
		Packet_buffer[packetInd++]=0x32;	//packet type
	}else
	{
		Packet_buffer[packetInd++]=0x30;
	}
	Packet_buffer[packetInd++]=remlen;

	/* topics */
	Packet_buffer[packetInd++]=0x00;
	Packet_buffer[packetInd++]=strlen(topic);
	// name
	strcpy(Packet_buffer+packetInd,topic);
	packetInd +=strlen(topic);

	/* packet ID if Qos > 0 */
	if(QoS>0)
	{
		Packet_buffer[packetInd++]=(uint8_t)(packetID>>8);
		Packet_buffer[packetInd++]=(uint8_t)(packetID);
		packetID++;
	}
	else
	{
		//nothing to do now!
	}
	// write mes
	for(mesInd=0;mesInd<len;mesInd++)
	{
		Packet_buffer[packetInd++]=mes[mesInd];
	}

	//send packet
	Uart_u8SendBuffer(Packet_buffer, packetInd);

}

void MQTT_Subscribe(uint8_t* Topic)
{
	uint8_t remlen=(5+strlen(Topic));
	//encode packet
	packetInd=0;
	Packet_buffer[packetInd++]=0x82;		// b0 packet type 0x10 for connect packet
	Packet_buffer[packetInd++]=remlen;

	//packet ID
	Packet_buffer[packetInd++]=(uint8_t)(packetID>>8);
	Packet_buffer[packetInd++]=(uint8_t)(packetID);
	packetID++;

	/* topics */
	Packet_buffer[packetInd++]=0x00;
	Packet_buffer[packetInd++]=strlen(Topic);
	// name
	strcpy(Packet_buffer+packetInd,Topic);
	packetInd +=strlen(Topic);

	//Subscription Options
	Packet_buffer[packetInd++]=0x01;

	/* send the packet*/
	//send packet
	Uart_u8SendBuffer(Packet_buffer, packetInd);

}

