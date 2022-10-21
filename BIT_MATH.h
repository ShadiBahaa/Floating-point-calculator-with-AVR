/****************************************************/
/******** Author     : Shadi Bahaa   ****************/
/******** File name  : BIT_MATH.h    ****************/
/******** Date       : 17/9/2022     ****************/
/******** Version    : V1            ****************/
/******** Desc       : ...           ****************/
/****************************************************/
/* header guard */
#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_
/* Function-like macro used for setting a bit
*  bit_num: the bit to be set
*  var    : the variable that includes bit_num
*/
#define SET_BIT(var,bit_num) var=var|(1<<bit_num)
/* Function-like macro used for clearing a bit
*  bit_num: the bit to be cleared
*  var    : the variable that includes bit_num
*/
#define CLR_BIT(var,bit_num) var=var&~(1<<bit_num)
/* Function-like macro used for toggling a bit
*  bit_num: the bit to be toggled
*  var    : the variable that includes bit_num
*/
#define TOGGLE_BIT(var,bit_num) var=var^(1<<bit_num)
/* Function-like macro used for getting a bit value
*  bit_num: the bit to get its value
*  var    : the variable that includes bit_num
*/
#define GET_BIT(var,bit_num) (var>>bit_num)&1
#endif // _BIT_MATH_H_
