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

uint8_t Packet_buffer[200]={0};
uint8_t packetInd=0;
uint8_t packetID=1;


void MQTT_connect(uint8_t* Client_ID)
{
	uint8_t remlen=(12+strlen(Client_ID));
	//encode packet
	packetInd=0;
	Packet_buffer[packetInd++]=CONNECT_PACKET;		// b0 packet type 0x10 for connect packet
	Packet_buffer[packetInd++]=remlen;
	/* Pocket name*/
	//name length
	Packet_buffer[packetInd++]=0x00;
	Packet_buffer[packetInd++]=0x04;
	// name
	strcpy(Packet_buffer+packetInd,"MQTT");
	packetInd +=4;

	//packet idnterifer
	Packet_buffer[packetInd++]=0x04;
	Packet_buffer[packetInd++]=0x02;
	Packet_buffer[packetInd++]=0xff;
	Packet_buffer[packetInd++]=0xff;

	/* packet ID */
	//ID length
	Packet_buffer[packetInd++]=0x00;
	Packet_buffer[packetInd++]=strlen(Client_ID);
	// name
	strcpy(Packet_buffer+packetInd,Client_ID);
	packetInd +=strlen(Client_ID);


	//send packet
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

