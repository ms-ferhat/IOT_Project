/************************************************************************/
/************************************************************************/
/*******************  Author : Mohamed shaban   *************************/
/*******************     layer : mcal           *************************/
/*******************     Version : 1.00         *************************/
/*******************        SWC : DIO           *************************/
/************************************************************************/
/************************************************************************/




#ifndef _DIO_INTERFACE_h
#define _DIO_INTERFACE_h


#define DIO_u8PIN_HIGH      1
#define DIO_u8PIN_LOW       0


#define DIO_u8PORT_HIGH     0xff
#define DIO_u8PORT_LOW      0

#define DIO_u8PORTA         0
#define DIO_u8PORTB         1
#define DIO_u8PORTC         2
#define DIO_u8PORTD         3

#define DIO_u8PIN0          0
#define DIO_u8PIN1          1
#define DIO_u8PIN2          2
#define DIO_u8PIN3          3
#define DIO_u8PIN4          4
#define DIO_u8PIN5          5
#define DIO_u8PIN6          6
#define DIO_u8PIN7          7

#define SOURCE    			1
#define SINK     			0

#define ACTIVE_HIGH 		1
#define ACTIVE_LOW  		0


/***************************************************************************************
*	Function Name: DIO_u8SetPin(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8value)		****
*	description	 : this function used to write value on any pin of dio pins			****
*	parameter	 : 1.Port	2.pin	3.Value(0 or 1)									****
*	return value : return error states												****
***************************************************************************************/
u8 DIO_u8SetPin(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8value);


/***************************************************************************************
*	Function Name: DIO_u8SetPort (u8 copy_u8port,u8 copy_u8value)					****
*	description	 : this function used to write value on any port of DIO Port		****
*	parameter	 : 1.Port	3.Value(0-255)											****
*	return value : return error states												****
***************************************************************************************/
u8 DIO_u8SetPort (u8 copy_u8port,u8 copy_u8value);


/***************************************************************************************
*	Function Name: DIO_u8GetPin (u8 copy_port ,u8 copy_pin,u8* copy_value)			****
*	description	 : this function used to Read value on any port of DIO Port			****
*	parameter	 : 1.Port	2.pin	3.Pointer 										****
*	return value : return error states												****
***************************************************************************************/
u8 DIO_u8GetPin (u8 copy_port ,u8 copy_pin,u8* copy_value);


#endif	/*_DIO_INTERFACE_h*/
