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

u8 Topic[] ="Phone/Blink_Led";
u8 Client_id[]="Client1";
u8 username[]="MoTSensorKitv2.0_Menya";
u8 password[]="MoTSensorKitv2.0_Menya_pass";
u8 payload =0;
u8 fixed_header;


void main(void)
{
	PORT_voidInti();
	Uart_voidInti();
	GIE_voidEnable();
	MQTT_connect(Client_id, username, password);
	MQTT_recive_message(&payload, &fixed_header);
	_delay_ms(2000);
	MQTT_Subscribe(Topic);
	MQTT_recive_message(&payload, &fixed_header);
	_delay_ms(5000);


	while(1)
	{
		MQTT_recive_message(&payload, &fixed_header);
		if(payload=='1')
		{
			DIO_u8SetPin(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_HIGH);
		}else if(payload =='0'){
			DIO_u8SetPin(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);
		}
		_delay_ms(100);
//		else{
//			UART_u8SendString("undifed payload\n\r");
//		}

	}
}

