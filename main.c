/****************************************************/
/******** Author     : Shadi Bahaa   ****************/
/******** File name  : main.c        ****************/
/******** Date       : 14/10/2022    ****************/
/******** Version    : V1            ****************/
/******** Desc       : ...           ****************/
/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LCD_INTERFACE.h"
#include "KPD_INTERFACE.h"
#include "KEYS.h"
#include "STACK_CHAR.h"
#include "STACK_D.h"
/* Array that hold the complete mathematical expression as infix formula*/
u8 infix[105];
/* length of mathematical expression */
u8 len;
/* the start index of mathematical expression show on the screen */
u8 start;
/* zeroDivision flag */
u8 zeroDiv;
/* overFlow flag */
u8 overFlow;
/* underFlow flag */
u8 underFlow;
/* functions prototypes */
void Data_Initialize();
u8 checkExp();
f64 calcPostfix();
void infixToPostfix(u8 arr[]);
void addInfix(u8 key);
u8 precedence(u8 op);
f64 stringToDouble(u8 arr[]);
f64 calc(f64 operandOne, u8 operation, f64 operandTwo);
/* Driving function */
void main(void) {
	/* Initializing LCD, Keypad and variables */
	Data_Initialize();
	LCD_VidInitialize();
	KPD_VidInit();
	while (1) {
		volatile u8 key = KPD_VidGetPressedKey();
		/* Checking the value of pressed key */
		if (key == EQUAL) {
			infix[len] = '\0';
			u8 flag = checkExp();
			/* Invalid expression */
			if (flag == 0) {
				LCD_VidMoveTo(2, 10);
				LCD_VidSendString("INVALID");
			} else {
				f64 res = calcPostfix();
				/* Division by zero expression */
				if (zeroDiv) {
					LCD_VidMoveTo(2, 4);
					LCD_VidSendString("Zero Division");
				/* overflow of the expression */
				} else if (overFlow) {
					LCD_VidMoveTo(2, 9);
					LCD_VidSendString("Overflow");
				/* underfow of the expression */
				} else if (underFlow) {
					LCD_VidMoveTo(2, 8);
					LCD_VidSendString("Underflow");
				/* printing the result */
				} else {
					LCD_VidMoveTo(2, 1);
					LCD_VidSendFloatingNumber(res);
				}
			}
			break;
		/* A key from the calculator is pressed */
		} else if (key != ':') {
			/* moving the expression on the screen if it is longer than 16 characters */
			if (len >= 16) {
				start++;
				LCD_VidClearLCD();
				for (u8 ind = start; ind < len; ++ind) {
					LCD_VidSendData(infix[ind]);
				}
			}
			/* Adding the new key value to the expression */
			addInfix(key);
			_delay_ms(200);
		}
	}
}
/* Adding the key to the infix expression
 * options:
 * key: range[0-15] (represents the pressed key on the keypad)
 * */
void addInfix(u8 key) {
	if (key >= ONE && key <= THREE) {
		LCD_VidSendIntNumber(key + 1);
		infix[len] = (key + 1) + '0';
	} else if (key >= FOUR && key <= SIX) {
		LCD_VidSendIntNumber(key);
		infix[len] = (key) + '0';
	} else if (key >= SEVEN && key <= NINE) {
		LCD_VidSendIntNumber(key - 1);
		infix[len] = (key - 1) + '0';
	} else if (key == ZERO) {
		LCD_VidSendIntNumber(0);
		infix[len] = '0';
	} else if (key == DOT) {
		LCD_VidSendData('.');
		infix[len] = '.';
	} else if (key == PLUS) {
		LCD_VidSendData('+');
		if (len == 0) {
			infix[0] = '0';
			len++;
		} else {
			if (infix[len - 1] == '+' || infix[len - 1] == '-') {
				return;
			}
		}
		infix[len] = '+';
	} else if (key == MINUS) {
		LCD_VidSendData('-');
		if (len == 0) {
			infix[0] = '0';
			len++;
		} else {
			if (infix[len - 1] == '-') {
				infix[len - 1] = '+';
				return;
			}
			if (infix[len - 1] == '+') {
				infix[len - 1] = '-';
				return;
			}
		}
		infix[len] = '-';
	} else if (key == MUL) {
		LCD_VidSendData('x');
		infix[len] = 'x';
	} else if (key == DIV) {
		LCD_VidSendData('/');
		infix[len] = '/';
	}
	len++;
}
/* Checking if the infix expression is valid or not
 * output:
 * 0 -> invalid expression
 * 1 -> valid expression
 * */
u8 checkExp() {
	if (len == 0)
		return 0;
	if (!(infix[0] == '+' || infix[0] == '-'
			|| (infix[0] >= '0' && infix[0] <= '9') || infix[0] == '.')) {
		return 0;
	}
	if (!(infix[len - 1] == '.'
			|| (infix[len - 1] >= '0' && infix[len - 1] <= '9'))) {
		return 0;
	}
	for (u8 index = 1; index < len; ++index) {
		if (infix[index] == '.' && infix[index - 1] == '.')
			return 0;
		if (infix[index] == '*' && infix[index - 1] == 'x')
			return 0;
		if (infix[index] == 'x' && infix[index - 1] == '/')
			return 0;
		if (infix[index] == '/' && infix[index - 1] == '*')
			return 0;
		if (infix[index] == '/' && infix[index - 1] == '/')
			return 0;
		if (infix[index] == '+' && infix[index - 1] == 'x')
			return 0;
		if (infix[index] == '-' && infix[index - 1] == 'x')
			return 0;
		if (infix[index] == '+' && infix[index - 1] == '/')
			return 0;
		if (infix[index] == '-' && infix[index - 1] == '/')
			return 0;
	}
	return 1;
}
/* Calculating the postfix expression
 * output:
 * valid   -> result of the mathematical expression as double number
 * invalid -> zero and a raisen flag
*/
f64 calcPostfix() {
	/* An array representing the postfix of infix expression */
	u8 postfix[105] = "";
	/* converting the infix to postifx */
	infixToPostfix(postfix);
	u8 ind = 0;
	/* using stack to calculate the whole postfix expression */
	while (postfix[ind] != '\0') {
		u8 cur[105];
		u8 i = 0;
		while (((postfix[ind] >= '0' && postfix[ind] <= '9')
				|| (postfix[ind] == '.'))) {
			cur[i] = postfix[ind];
			i++;
			ind++;
		}
		cur[i] = '\0';
		if (i != 0) {
			f64 res = stringToDouble(cur);
			pushD(res);
		} else if (postfix[ind] == ',') {
			ind++;
			continue;
		} else if (Res) {
			f64 operandOne = topD();
			popD();
			f64 operandTwo = topD();
			popD();
			pushD(calc(operandTwo, postfix[ind], operandOne));
			if (underFlow || overFlow || zeroDiv) {
				return 0;
			}
			ind++;
		}
	}
	return topD();
}
/* converting the infix expression to postfix expression
 * options:
 * postifx : array that will contain the expression after conversion
*/
void infixToPostfix(u8 postfix[]) {
	infix[len] = '-';
	len++;
	push('#');
	u8 ind = 0;
	u8 postInd = 0;
	while (ind < len) {
		u8 cur[105] = "";
		u8 i = 0;
		while (((infix[ind] >= '0' && infix[ind] <= '9') || (infix[ind] == '.'))
				&& ind < len && i < len) {
			cur[i] = infix[ind];
			i++;
			ind++;
		}
		cur[i] = '\0';
		/* An operand */
		if (i != 0) {
			for (u8 j = 0; j < i; ++j) {
				postfix[postInd] = cur[j];
				postInd++;
			}
			postfix[postInd] = ',';
			postInd++;
		/* An operator */
		} else {
			while (head && precedence(top()) >= precedence(infix[ind])) {
				postfix[postInd] = top();
				pop();
				postInd++;
				postfix[postInd] = ',';
				postInd++;
			}
			push(infix[ind]);
			ind++;
		}
	}
	postfix[postInd] = '\0';
}
/* function that returns the precedence of specific operations
 * input options:
 * op : operations (+ , - , * , /)
 * result:
 * 1 -> operator is either + or -
 * 2 -> operator is either x or /
 * 0 -> none of the above
*/
u8 precedence(u8 op) {
	if (op == '+' || op == '-')
		return 1;
	if (op == 'x' || op == '/')
		return 2;
	return 0;
}
/* Performs the necessary calculations (addition, subtraction, multiplication, division)
 * input options:
 * operandOne: range[DBL_MIN - DBL_MAX] the first operand in the expression
 * operandTwo: range[DBL_MIN - DBL_MAX] the second operand in the expression
 * operation : one of the following operations (+ , - , / , x)
 * result:
 * No underflow/ overflow/ zeroDivision -> result of operations as double
 * otherwise                            -> zero with a raised flag
*/
f64 calc(f64 operandOne, u8 operation, f64 operandTwo) {
	switch (operation) {
	/* addition */
	case '+':
		if (operandOne > DBL_MAX - operandTwo) {
			overFlow = 1;
			return 0;
		}
		return operandOne + operandTwo;
	/* subtraction */
	case '-':
		if (operandOne < (-1 * DBL_MAX) - operandTwo) {
			underFlow = 1;
			return 0;
		}
		return operandOne - operandTwo;
	/* multiplication */
	case 'x':
		if (operandOne > DBL_MAX / operandTwo) {
			overFlow = 1;
			return 0;
		}
		return operandOne * operandTwo;
	/* division */
	case '/':
		if (operandTwo == 0) {
			zeroDiv = 1;
			return 0;
		}
		if (operandOne < -1 * DBL_MAX * operandTwo) {
			underFlow = 1;
			return 0;
		}
		return operandOne / operandTwo;
	}
	return 0;
}
/* a function that converts a string to a double number
 * input options:
 * arr    : string as an array of character (each character in range [0-9] or symbols [+,-,x,/,.])
 * result:
 * double number representing the conversion
*/
f64 stringToDouble(u8 arr[]) {
	s8 ind = 0;
	f64 res = 0;
	/* searching for the decimal point */
	while (arr[ind] != '\0' && arr[ind] != '.') {
		ind++;
	}
	f64 fact = 1.0;
	s8 begin = 0;
	if (arr[begin] == '-')
		begin++;
	/* building the integer part */
	for (s8 i = ind - 1; i >= begin; --i) {
		res += ((arr[i] - '0') * fact);
		fact *= 10.0;
	}
	if (arr[ind] == '\0') {
		if (arr[0] == '-')
			res *= -1;
		return res;
	}
	fact = 1 / 10.0;
	/* building the floating part */
	for (s8 i = ind + 1; arr[i] != '\0'; ++i) {
		res += ((arr[i] - '0') * fact);
		fact *= (1 / 10.0);
	}
	if (arr[0] == '-')
		res *= -1;
	return res;
}
/* initializes the program data */
void Data_Initialize(){
	infix[0] = '\0';
	len = 0;
	start = 0;
	zeroDiv = 0;
	underFlow = 0;
}
