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

char str[200];

void main(void)
{
	PORT_voidInti();
	Uart_voidInti();
	GIE_voidEnable();
	MQTT_connect("Client1", "MoTSensorKitv2.0_Menya", "MoTSensorKitv2.0_Menya_pass");
	_delay_ms(2000);
	MQTT_Subscribe("Phone/Ms/Blink_Led");
	//Uart_u8recive_StringA(str, copy_u8size, copy_Pvnotif)
	while(1)
	{

	}
}
