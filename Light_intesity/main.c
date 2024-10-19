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
#include "5-ADC/ADC_interface.h"
#include "7-USART/Uasrt_inteface.h"

#include "util/delay.h"

/***********   MQTT vars  *****************/
#define Publish_Topic	"Phone/Monitor/Lux"
#define Subscr_Topic	"Phone"
#define Client_id		"Client3"
#define username		"MoTSensorKitv2.0_Menya"
#define password		"MoTSensorKitv2.0_Menya_pass"
#define Qos				0
u8 payload ;
u8 fixed_header;
/************  general vars **************/
u16 Lux;
/***********  funcation  ******************/
u16 LDR_read(u8 ADC_Channel)
{
	u16 ADC_reading;
	u16 Vol,Res;
	ADC_u8startconversionsync(ADC_Channel,&ADC_reading);
	Vol = (ADC_reading * 5000)/1024;
	Res = 10000/(5000/Vol -1);


	return Res; //(u16)((Res * 18)/100000);
}


void main(void)
{

	PORT_voidInti();
	ADC_voidinti();
	Uart_voidInti();
	GIE_voidEnable();
	// connect to MQTT broker and than recive ConACK packet
	MQTT_connect(Client_id, username, password);
	MQTT_Recive_Packet(&payload, &fixed_header);
	// sub
//	MQTT_Subscribe(Subscr_Topic);
//	MQTT_Recive_Packet(&payload, &fixed_header);



	while(1)
	{
		Lux = LDR_read(ADC0);


	}

}


