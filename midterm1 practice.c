/*****************************************************************************************************************
ROBT1270 - C Programming
MIDTERM #1 Practice Programming Problem

Author: Leland, Dean

Declaration: I, Leland Dean, declare that the following program was written by me and I
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
void printPoints(double*, double*, bool*, const size_t);
bool inverseKinematics(double x, double y, double* r, double* theta);
bool adjustPoints(double* x, double* y, bool* bAdjusted, const size_t NPTS);
void printCommands(double* x, double* y, int* penPos, const size_t NPTS);
void printSingleCommand(double x, double y, int penPos, int n);
//----------------------------------------------------------------------------------------------------------------
// demonstrates basic control of the robot simulator
int main()
{
   double x[] = {234.0, -214.7,  89.9,   891.4, -37.1, 191.7, -22.2}; // x coordinates
   double y[] = {847.7,   70.4, -11.1, -1118.2,  97.7, 104.0, -55.5}; // y coordinates
   int penPos[] = {PEN_UP, PEN_DOWN, PEN_DOWN, PEN_DOWN, PEN_DOWN, PEN_DOWN, PEN_UP}; // pen position
   bool bAdjusted[] = {false, false, false, false, false, false, false}; // set true if x,y outside range
   size_t NPTS = 0;  // number of points in the arrays (ASSUME ALL SAME NUMBER OF ELEMENTS)

   NPTS = sizeof(x) / sizeof(x[0]);

   printPoints(x, y, bAdjusted, NPTS);
   if (adjustPoints(x, y, bAdjusted, NPTS))
   {
      printPoints(x, y, bAdjusted, NPTS);
      printCommands(x, y, penPos, NPTS);

   }

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

void printPoints(double *x, double *y, bool *bAdjusted, const size_t NPTS)
{
   int pfw = PRINT_FIELD_WIDTH, pm = PRINT_MARGIN;
   double r = 0;
   for (size_t index = 0; index < NPTS; ++index)
   {
      if (index == 0)
      {
         printHLine(60);
         printf("%*c%*c%*c%*s\n", pfw - pm, 'x', pfw, 'y', pfw, 'r', pfw + pm, "Adjusted");
         printHLine(60);
      }
      r = sqrt(pow(x[index], 2) + pow(y[index], 2));

      printf("%+*.*lf%+*.*lf%+*.*lf%*.*s\n", pfw, PRINT_PRECISION, x[index], pfw, PRINT_PRECISION, y[index], pfw, PRINT_PRECISION, r, pfw, PRINT_PRECISION, bAdjusted[index] ? "yes" : "no");

   }
}

bool inverseKinematics(double x, double y, double* r, double* theta)
{
   *theta = atan2(y, x);
   *r = sqrt((x*x) + (y*y));

   if (*r < RMIN || *r >RMAX)
   {
      return false;
   }
   else
   {
      return true;
   }
}

bool adjustPoints(double* x, double* y, bool* bAdjusted, const size_t NPTS)
{
   size_t n;
   int selection = 0;
   bool bHasGarbage = false;
   int count = 0;
   double r = 0;
   double theta = 0;
   int iret;

   for (n = 0; n < NPTS; ++n)
   {
      if (!inverseKinematics(x[n], y[n], &r, &theta))
      {
         count++;
         bAdjusted[n] = true;
      }
   }

   /*
   for (int index = 0; index < NPTS; ++index)
   {
      r = sqrt(pow(x[index], 2) + pow(y[index], 2));
      if (r <= RMIN || r <= RMAX)
      {
         count++;
         bAdjusted[index] = true;
      }

   }
   */

   if (count == 0) return false;

   printf("%d points(s) are outside the robot range and need adjustment.\n", count);

   while (true)
   {
      printf("Press 1 to adjust the %d coordinate(s), 2 to abort the adjustment: ", count);
      iret = scanf_s("%d", &selection);
      bHasGarbage = flushInputBuffer();

      if (iret == 1 && !bHasGarbage && (selection == 1 || selection == 2)) break;
   }

   if (selection == 2)
   {
      printf("\n");
      return false;
   }

   for (int index = 0; index < NPTS; ++index)
   {
      if (!bAdjusted[n]) continue;
      
      r = sqrt(pow(x[index], 2) + pow(y[index], 2));

      if (r < RMIN)
      {
         x[n] *= RMIN / r;
         y[n] *= RMIN / r;
      }
      else if (r > RMAX)
      {
         x[n] *= RMAX / r;
         x[n] *= RMAX / r;
      }
   }

   printf("\n");
   return true;

}

void printCommands(double* x, double* y, int* penPos, const size_t NPTS)
{
   size_t n;
   for (n = 0; n < NPTS; ++n) printSingleCommand(x[n], y[n], penPos[n], (int)(n + 1));
   printf("\n");
}

void printSingleCommand(double x, double y, int penPos, int n)
{
   double r, theta;

   inverseKinematics(x, y, &r, &theta);
   printf("Point #%d string: \"MOVE_ARM R %*.*lf THETA %+*.*lf ", n,
      COMMAND_FIELD_WIDTH, COMMAND_PRECISION, r, COMMAND_FIELD_WIDTH, COMMAND_PRECISION, radToDeg(theta));
   if (penPos == PEN_UP)
      printf("PEN_UP\"\n");
   else
      printf("PEN_DOWN\"\n");
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

