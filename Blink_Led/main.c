/*
 * main.c
 *
 *  Created on: Sep 8, 2024
 *      Author: ms305
 */
#include "libr/STD_types.h"
#include "libr/BIT_math.h"
#include "libr/MQTT.h"

#include "1-DIO/DIO_interface.h"
#include "2-PORT/PORT_interface.h"
#include "3-GIE/GIE_interface.h"
#include "7-USART/Uasrt_inteface.h"

#include "util/delay.h"
#include <string.h>

u8 str[200];
int  led_flag=0;
u8 on_Topic[] ="Phone/Ms/Blink_Led/on";
u8 off_Topic[] ="Phone/Ms/Blink_Led/off";


void main(void)
{
	PORT_voidInti();
	Uart_voidInti();
	GIE_voidEnable();
	MQTT_connect("Client1", "MoTSensorKitv2.0_Menya", "MoTSensorKitv2.0_Menya_pass");
	_delay_ms(2000);
	MQTT_Subscribe(on_Topic);
	_delay_ms(2000);
	//MQTT_Subscribe(off_Topic);
	_delay_ms(2000);
	//Uart_u8recive_StringA(str, 20, &uart_notif);
	while(1)
	{
		MQTT_recive_message(str);
		if(str== on_Topic)
		{
			DIO_u8SetPin(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_HIGH);
		}
		else if(str == off_Topic)
		{
			DIO_u8SetPin(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);
		}
		else{
			UART_u8SendString("undefined Topic\n\r");
		}
//		_delay_ms(500);
	}
}

