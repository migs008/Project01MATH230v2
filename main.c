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

   void calcPath(int top, int mid, int bot) //calculates totalMoveCost if proceeding top, middle, or bottom tiles
   {
       int randomTileBox[2]; //holds selected variables to draw
       int randomIndex; //random draw
       bool noNegative = true;

       if (top < 0 || bot < 0)//determines if there is a negative value present
       {
           noNegative = false;
       }


       if (noNegative == false) //adds totalMoveCost with least elevation change and moves to that tile if noNegative is false
       {
           if ((top < 0) && (mid < bot) || (mid == bot))
           {
                totalMoveCost += mid;
                currentCol++;
           }
           else if ((top < 0) && (bot < mid))
           {
                totalMoveCost += bot;
                currentRow++;
                currentCol++;
           }
           else if ((bot < 0) && (top < mid))
           {
                totalMoveCost += top;
                currentRow--;
                currentCol++;
           }
           else
           {
                totalMoveCost += mid;
                currentCol++;
           }
       }
       else //when noNegative is true, adds totalMoveCost with the least elevation change and moves to that tile
       {
           if ((top < mid) && (top < bot))
           {
               totalMoveCost += top;
               currentRow--;
               currentCol++;
           }
           else if ((mid < top) && (mid < bot))
           {
               totalMoveCost += mid;
               currentCol++;
           }
           else if ((bot < top) && (bot < mid))
           {
               totalMoveCost += bot;
               currentRow++;
               currentCol++;
           }
           else if (top == bot) //when top is equal to bot, do random selection of path
           {
                randomTileBox[0] = top;
                randomTileBox[1] = bot;
                randomIndex = rand() % 2;
                totalMoveCost += randomTileBox[randomIndex];
                if (randomIndex == 0)
                {
                    currentRow--;
                }
                else
                {
                    currentRow++;
                    currentCol++;
                }
           }
           else //when all is equal then proceed through mid
           {
               totalMoveCost += mid;
               currentCol++;
           }
       }
   }

   for(r=0; r<ROWS; r++)
    {
        totalMoveCost = 0;
        currentRow = r;

        for(c=0; c<COLS - 1; c++)
        {
            if (currentCol == COLS - 1) //resets column and row selection and moves to next row
            {
                currentCol = 0;
                currentRow = 0;
                currentRow = r;
            }

            if (currentRow != 0 && currentRow != (ROWS - 1)) //for when three paths are available
            {
                sum1 = abs(topog[currentRow][currentCol] - topog[currentRow - 1][currentCol + 1]);
                sum2 = abs(topog[currentRow][currentCol] - topog[currentRow][currentCol + 1]);
                sum3 = abs(topog[currentRow][currentCol] - topog[currentRow + 1][currentCol+ 1]);
                calcPath(sum1, sum2, sum3);
            }
            else if(currentRow == 0) //when top path is unavailable
            {
                sum1 = -1;
                sum2 = abs(topog[currentRow][currentCol] - topog[currentRow][currentCol + 1]);
                sum3 = abs(topog[currentRow][currentCol] - topog[currentRow + 1][currentCol + 1]);
                calcPath(sum1, sum2, sum3);
            }
            else //when bottom path is unavailable
            {
                sum1 = abs(topog[currentRow][currentCol] - topog[currentRow - 1][currentCol + 1]);
                sum2 = abs(topog[currentRow][currentCol] - topog[currentRow][currentCol + 1]);
                sum3 = -1;
                calcPath(sum1, sum2, sum3);
            }

            sums[r] = totalMoveCost; //place sums in this array. One sum per row


        }
	}


}
