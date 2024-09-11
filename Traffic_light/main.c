/*
 * main.c
 *
 *  	Created on: Sep 11, 2024
 *      Author: Mohamed Shaban Elsayed
 */
/************* Includes **************/
#include "libr/STD_types.h"
#include "libr/BIT_math.h"
#include "libr/MQTT.h"

#include "1-DIO/DIO_interface.h"
#include "2-PORT/PORT_interface.h"
#include "3-GIE/GIE_interface.h"
#include "7-USART/Uasrt_inteface.h"

#include "util/delay.h"

/***********   MQTT vars  *****************/
#define Publish_Topic	"Phone/Traffic/Color"
#define Subscr_Topic	"Phone/Traffic/Control"
#define Client_id		"Client2"
#define username		"MoTSensorKitv2.0_Menya"
#define password		"MoTSensorKitv2.0_Menya_pass"
#define Qos				0
u8 payload =0;
u8 fixed_header;
/************  general vars **************/
u8 counter=0;
#define red			1
#define yellow 		2
#define	green		4

#define red_c		"red"
#define yellow_c	"yellow"
#define green_c		"green"
/***********  funcation  ******************/
void mqtt_notify(void);


void main(void)
{

	PORT_voidInti();
	Uart_voidInti();
	GIE_voidEnable();
	MQTT_connect(Client_id, username, password);
	MQTT_Recive_Packet(&payload, &fixed_header);

	MQTT_Subscribe(Subscr_Topic);
	MQTT_Recive_Packet(&payload, &fixed_header);
	Uart_u8recive_Asyn(&fixed_header);
	uart_u8setcallback(&mqtt_notify);


	while(1)
	{
		if(counter >= 0 && counter <15)
		{
			DIO_u8SetPort(DIO_u8PORTA, red);				//turn red led on
			MQTT_Publish(Publish_Topic, red_c, 3, Qos);		//publish MOT platform
			counter++;										//increase counter
		}
		else if(counter >= 15 && counter <20)
		{
			DIO_u8SetPort(DIO_u8PORTA, yellow);
			MQTT_Publish(Publish_Topic, yellow_c, 6, Qos);

			counter++;
		}
		else if(counter >= 20 && counter < 30)
		{
			DIO_u8SetPort(DIO_u8PORTA, green);
			MQTT_Publish(Publish_Topic, green_c, 5, Qos);
			counter++;
		}else
		{
			counter=0;
		}
		_delay_ms(1000);
	}
}
void mqtt_notify(void)
{
	Uart_u8recive(&fixed_header);
	for(u8 i=0;i<fixed_header;i++)
	{
		Uart_u8recive(&payload);
	}
	if(payload == '1')
	{
		counter=20;
	}
	Uart_u8recive_Asyn(&fixed_header);
}

