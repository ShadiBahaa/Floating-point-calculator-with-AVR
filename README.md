# Floating-point calculator with AVR
## About
#### A floating-point calculator using 16X2 LMB161A character LCD and 4x4 keypad.
#### The application is run on AVR Atmega32 microcontroller, for any configuration changes to be suitable for another microcontroller you can go to name_CFG.h files and KEYS.h and change whatever you want.
#### The calculator doesn't use any optimal built-in function for converting between strings, doubles and integers, so the calculator results may become less precise as they depend mainly on the double representation in AVR memory.
## Configuration
#### To run the program, you can use any IDE that is suitable for running C applications, in addition to adding AVR c compiler.
## Simulation
#### You can find a simulation right here in the link: https://drive.google.com/file/d/1Fh_ilhVZdcqkvJBCLkPJ1kDBtMTlU1iX/view?usp=sharing
## Features
#### The calculator takes the advantage of stack data structure to hold all calculations in O(1) time complexity with reducing the use of built-in functions designed for different conversions between strings, doubles and integers
#### The calculator handles overflow, underflow and zero division test cases. Overflow and underflow work in calculations part assuming the entered numbers don't exceed the double range.
#### The calculator handles invalid input (like entering * / consequently) and handles consecutive + or - and dot operator without integer and floating parts.
#### The precedence of operations are handled very well using the stack to make sure the results are correct using infix and postfix formula.
#### The calculator accepts doubles and integers, but for more precise results it is preferred to limit usage to doubles with 7 digits in the integer part and 5 digits in the decimal part (As double conversions aren't so accurate in AVR)
#### The screen can accept an expression of length 100 character
