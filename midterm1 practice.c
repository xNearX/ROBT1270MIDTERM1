/*****************************************************************************************************************
ROBT1270 - C Programming
MIDTERM #1 Practice Programming Problem

Author: <Firstname, Lastname>

Declaration: I, <Firstname, Lastname>, declare that the following program was written by me and I
             didn't get any help from anyone.

Date Created: February 22 2023
*****************************************************************************************************************/

//-------------------------- Standard library prototypes ---------------------------------------------------------
#include <stdlib.h>  // standard functions and constant
#include <stdio.h>   // i/o functions
#include <math.h>    // math functions
#include <string.h>  // string functions
#include <ctype.h>   // character functions
#include <stdbool.h> // bool definitions

//------------------------------------- GLOBAL CONSTANTS ---------------------------------------------------------
const unsigned char HL = 196;                // horizontal border line

const int PRINT_FIELD_WIDTH = 12;            // field width for numbers printed in table
const int PRINT_PRECISION = 1;               // precision for numbers printed in table
const int PRINT_MARGIN = 2;                  // margin used in table
const int COMMAND_FIELD_WIDTH = 10;          // field width for numbers printed in robot command string
const int COMMAND_PRECISION = 5;             // precision for numbers printed in robot command string

const double PI = 3.14159265358979323846;    // the one and only
const double RMIN = 100.0;                   // minimum length of telescoping arm
const double RMAX = 1000.0;                  // maximum length of telescoping arm
const int PEN_UP = 0;                        // used to set the pen position to up
const int PEN_DOWN = 1;                      // used to set the pen position to down

//----------------------------- Function Prototypes --------------------------------------------------------------
bool flushInputBuffer();   // flushes any characters left in the standard input buffer
void waitForEnterKey();    // waits for the Enter key to be pressed
double degToRad(double);   // returns angle in radians from input angle in degrees
double radToDeg(double);   // returns angle in degrees from input angle in radians
void printHLine(int);      // print a solid line

//----------------------------------------------------------------------------------------------------------------
// demonstrates basic control of the robot simulator
int main()
{
   double x[] = {234.0, -214.7,  89.9,   891.4, -37.1, 191.7, -22.2}; // x coordinates
   double y[] = {847.7,   70.4, -11.1, -1118.2,  97.7, 104.0, -55.5}; // y coordinates
   int penPos[] = {PEN_UP, PEN_DOWN, PEN_DOWN, PEN_DOWN, PEN_DOWN, PEN_DOWN, PEN_UP}; // pen position
   bool bAdjusted[] = {false, false, false, false, false, false, false}; // set true if x,y outside range
   size_t NPTS = 0;  // number of points in the arrays (ASSUME ALL SAME NUMBER OF ELEMENTS)






   printf("Press ENTER to end the program...");
   waitForEnterKey();
   return EXIT_SUCCESS;
}



//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  Print of a solid line of N characters
// ARGUMENTS:    N:  number of characters in line
// RETURN VALUE: none
void printHLine(int N)
{
   int n;

   for(n = 0; n < N; n++) printf("%c", HL);
   printf("\n");
}

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  Returns angle in degrees from input angle in radian
// ARGUMENTS:    angDeg:  angle in degrees
// RETURN VALUE: angle in radians
double degToRad(double angDeg)
{
   return (PI/180.0)*angDeg;
}

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  Returns angle in radians from input angle in degrees
// ARGUMENTS:    angRad:  angle in radians
// RETURN VALUE: angle in degrees
double radToDeg(double angRad)
{
   return (180.0/PI)*angRad;
}

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  This function flushes the input buffer to avoid scanf issues
// ARGUMENTS:    none
// RETURN VALUE: false if nothing or only '\n' in stdin. true if extra keystrokes precede the '\n'.
//               Good for detecting left over garbage from scanf_s in the input buffer
bool flushInputBuffer()
{
   unsigned char ch; // temp character variable
   bool bHasGarbage = false;

   // exit loop when all characters are flushed
   while((ch = (unsigned char)getchar()) != '\n' && ch != EOF)
   {
      if(!bHasGarbage) bHasGarbage = true;
   }
   return bHasGarbage;
}

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  Waits for user to press enter.  flushes stdin if keystrokes precede enter
// ARGUMENTS:    none
// RETURN VALUE: none
void waitForEnterKey()
{
   unsigned char ch;
   if((ch = (unsigned char)getchar()) != EOF && ch != '\n') flushInputBuffer();
}

