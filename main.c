// Your Name:  Miguel Aquino
// Your email: ma1070652@swccd.edu
// Your ID: 1070652

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ROWS  5
#define COLS  6
void calcSums(int topog[ROWS][COLS], int sumList[ROWS] );

int main()
{
    int topography[ROWS][COLS] =
	{
		{ 3011, 2800, 2852, 2808, 2791, 2818 },
		{ 2972, 2937, 2886, 2860, 2830, 2748 },
		{ 2937, 2959, 2913, 2864, 2791, 2742 },
		{ 2999, 2888, 2986, 2910, 2821, 2754 },
		{ 2909, 3816, 2893, 2997, 2962, 2798 }
	};
	int sumList[ROWS] = {0};
	int r,c;


	/*  student to implement calcSums */
	calcSums(topography, sumList ); //pass in topography, get back list of elevation sums



	for(r=0; r < ROWS; r++)
		printf("%8d %8d \n",r, sumList[r]);  //should display calculated sums


    return 0;
}

/*
 *  Receives 2d matrix that represents topography
 *  and uses this data to calculate an elevation path sum for each
 *  row.
 *  Input:  topog[][]
 *  Output: sum[]
 *
 */
void calcSums(int topog[ROWS][COLS], int sums[ROWS] ) {
   int r,c;
   int currentRow = 0; // do currentRow++ to cycle through the rows
   int sum1, sum2, sum3;
   int top, mid, bot;
   int totalMoveCost;
   srand(time(NULL));
   int currentCol = 0;
   int testSums[ROWS];
   int colCal = 0;



   void calcPath(int a, int b, int c) //returns totalMoveCost, choose mid if equal in elevation change
   {
       int randomTileBox[2];
       int randomIndex;
       bool noNegative = true;

       if (a < 0 || c < 0)
       {
           noNegative = false;
       }


       if (noNegative == false)
       {
           if ((a < 0) && (b < c) || (b == c))
           {
                totalMoveCost += b;
                currentCol = colCal - currentCol + 1;
           }
           else if ((a < 0) && (c < b))
           {
                totalMoveCost += c;
                currentRow = currentRow + 1;
                currentCol = currentCol + 1;
           }
           else if ((c < 0) && (a < b))
           {
                totalMoveCost += a;
                currentRow = currentRow - 1;
                currentCol = currentCol + 1;
           }
           else if ((c < 0) && (b < a) || (b == a))
           {
                totalMoveCost += b;
                currentCol = currentCol + 1;
           }
           else //when a is equal to c do random selection of path
           {
                randomTileBox[0] = a;
                randomTileBox[1] = c;
                randomIndex = rand() % 2;
                totalMoveCost += randomTileBox[randomIndex];
                if (randomIndex == 0)
                {
                currentRow = currentRow - 1;
                }
                else
                {
                    currentRow = currentRow + 1;
                    currentCol = currentCol + 1;
                }
           }
       }
       else //when noNegative is true
       {
           if ((a < b) && (a < c))
           {
               totalMoveCost += a;
               currentRow = currentRow - 1;
               currentCol = currentCol + 1;
           }
           else if ((b < a) && (b < c))
           {
               totalMoveCost += b;
               currentCol = currentCol + 1;
           }
           else if ((c < a) && (c < b))
           {
               totalMoveCost += c;
               currentRow = currentRow + 1;
               currentCol = currentCol + 1;
           }
           else //when all equal then proceed mid
           {
               totalMoveCost += b;
               currentCol = currentCol + 1;
           }
       }

        //fix logic
        //replace false logic with bool?
        //seperate the noNegative statements
       //if ((a < b) && (a < c) && (noNegative == true)) //add the current selected tile
       //{
       //    totalMoveCost += a;
       //    currentRow = currentRow - 1;
       //}
       //else if ((b < a) && (b < c) && (noNegative == true))
       //{
       //    totalMoveCost += b;
       //    currentCol = colCal - currentCol + 1;
       //}
       //else if ((c < a) && (c < b) && (noNegative == true))
       //{
       //    totalMoveCost += c;
       //    currentRow = currentRow + 1;
       //    currentCol = currentCol + 1;
       //}
       //else if ((a == b) && (b == c) //chooses middle path if all numbers equal
       //{
       //    totalMoveCost += b;
       //}
       /*
       else if ((b < c) && (noNegative == false)) //if no top and middle sum is lower
       {
           totalMoveCost += b;
           currentCol = colCal - currentCol + 1;
       }
       else if ((c < b) && (noNegative == false)) //if no top and bottom sum is lower
       {
           totalMoveCost += c;
           currentRow = currentRow + 1;
           currentCol = colCal - currentCol + 1;
       }
       else if ((noNegative == false) && (b == c)) // if no top mid and bottom sum are equal then pick mid
       {
           totalMoveCost += b;
           currentCol = colCal - currentCol + 1;
       }
       else if ((noNegative == false) && (a < b)) //if no bottom and top is lower than mid
       {
           totalMoveCost += a;
           currentRow = currentRow - 1;
       }
       else if ((noNegative == false) && (b < a)) //if no bottom and mid is lower than top
       {
           totalMoveCost += b;
           currentCol = colCal - currentCol + 1;
       }
       else if ((noNegative == false) && (a == b)) //if mid and top sum are equal then pick mid
       {
           totalMoveCost += b;
           currentCol = colCal - currentCol + 1;
       }
       else if (a == c) //if top and bottom are equal do random
       {
           randomTileBox[0] = a;
           randomTileBox[1] = c;
           randomIndex = rand() % 2;
           totalMoveCost += randomTileBox[randomIndex];
           if (randomIndex == 0)
           {
               currentRow = currentRow - 1;
           }
           else
           {
               currentRow = currentRow + 1;
               currentCol = colCal - currentCol + 1;
           }
       }
       else //so when everything is equal supposed to be it would pick mid
       {
           totalMoveCost += b;
           currentCol = colCal - currentCol + 1;
       }

       noNegative = true;
*/
   }

   for(r=0; r<ROWS; r++) //build array that takes all starting elevations?
    {
        totalMoveCost = 0;
        currentRow = r;

        //-->added c - currentCol to replace c and added c++
        //-->replaced r with currentRow
        for(c=0; c<COLS - 1; c++)
        {
            if (currentCol == COLS - 1) //causing error for third sum
            {
                currentCol = 0;
                currentRow = 0;
                currentRow = r;
            }

            if (currentRow != 0 && currentRow != (ROWS - 1)) //will do middle path
            {
                sum1 = abs(topog[currentRow][currentCol] - topog[currentRow - 1][currentCol + 1]);
                sum2 = abs(topog[currentRow][currentCol] - topog[currentRow][currentCol + 1]);
                sum3 = abs(topog[currentRow][currentCol] - topog[currentRow + 1][currentCol+ 1]);
                calcPath(sum1, sum2, sum3); //set designated sum to negative value for path determination
            }
            else if(currentRow == 0)
            {
                sum1 = -1;
                sum2 = abs(topog[currentRow][currentCol] - topog[currentRow][currentCol + 1]);
                sum3 = abs(topog[currentRow][currentCol] - topog[currentRow + 1][currentCol + 1]);
                calcPath(sum1, sum2, sum3);
            }
            else
            {
                sum1 = abs(topog[currentRow][currentCol] - topog[currentRow - 1][currentCol + 1]);
                sum2 = abs(topog[currentRow][currentCol] - topog[currentRow][currentCol + 1]);
                sum3 = -1;
                calcPath(sum1, sum2, sum3);
            }

            /*if (currentCol == COLS - 1)
            {
                currentCol = 0;
                currentRow = 0;
                currentRow = r + 1;
            }*/

            sums[r] = totalMoveCost;


        }


		  //place sums in this array. One sum per row
	}


}

//create method that determines path

//add method for determining equals

