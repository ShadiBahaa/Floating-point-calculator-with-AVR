/**********************************************************/
/******** Author     : Shadi Bahaa         ****************/
/******** File name  : LCD_INTERFACE.h     ****************/
/******** Date       : 1/10/2022           ****************/
/******** Version    : V5                  ****************/
/******** Desc       : ...                 ****************/
/**********************************************************/
/* header guard */
#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_
/* LCD function prototypes */
void LCD_VidInitialize();
void LCD_VidSendData(u8 value);
void LCD_VidSendCommand(u8 command);
void LCD_VidClearLCD();
void LCD_VidShiftDisplayLeft();
void LCD_VidShiftDisplayRight();
void LCD_VidSendString(u8 arr[]);
void LCD_VidMoveTo(u8 row, u8 column);
void LCD_VidSendIntNumber(s64 num);
void LCD_VidDrawChar(u8 arr[], u8 pos, u8 col, u8 row);
void LCD_VidSendFloatingNumber(f64 num);
#endif
