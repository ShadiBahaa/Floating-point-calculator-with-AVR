/****************************************************/
/******** Author     : Shadi Bahaa   ****************/
/******** File name  : KPD_PRG.c     ****************/
/******** Date       : 10/10/2022    ****************/
/******** Version    : V1            ****************/
/******** Desc       : ...           ****************/
/****************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "KPD_CFG.h"
#include <util/delay.h>
#include "DIO_INTERFACE.h"
/* Initializing the Keypad port */
void KPD_VidInit(){
    DIO_VidSetPortDirection(KPD_PORT,0b11110000);
    DIO_VidSetPortValue(KPD_PORT,0b11111111);
}
/* Getting the value of the pressed key
 * Result:
 * range[0-15] (a number representing the  pressed key) - ':' (no key is pressed)
 * */
u8 KPD_VidGetPressedKey(){
    u8 key = ':';
    for (u8 col = 0; col<4; col++){
        DIO_VidSetPinValue(KPD_PORT,col+4,0);
        for (u8 row = 0; row<4; ++row){
            u8 x = DIO_U8GetPinValue(KPD_PORT,row);
            if (x==0){
                key = (row*4)+col;
                while (DIO_U8GetPinValue(KPD_PORT,row)!=0);
                _delay_ms(2);
            }
        }
        DIO_VidSetPinValue(KPD_PORT,col+4,1);
    }
    return key;
}
