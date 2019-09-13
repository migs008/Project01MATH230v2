// Your Name:  Miguel Aquino
// Your email: ma1070652@swccd.edu
// Your ID: 1070652

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
   //int startingElevation;
   int nextElevationTile;
   int firstSum, secondSum, thirdSum;
   int tileMoveNum[3]; //remove?
   int totalMoveCost;
   int shortestPathSum[5]; //change to ROWS? check if correct if changed
   srand(time(NULL));
   int randomIndex;
   int count = 0;


   for( r=0; r<ROWS; r++)
    {
        for (c=0; c<COLS; c++)
        {
            //calculates absolute sum for next elevation change
            //change r and c values to something else to move tile pointers properly?
            if (r == 0 && c != 5)
            {
                firstSum = abs(topog[r][c] - topog[r][c + 1]);
                secondSum = abs(topog[r][c] - topog[r + 1][c + 1]);
                if (firstSum < secondSum)
                {
                    nextElevationTile = topog[r][c + 1];
                    c = c + 1;
                    totalMoveCost += firstSum;
                }
                else if (secondSum < firstSum)
                {
                    nextElevationTile = topog[r + 1][c + 1]; //correctly identified elevation in next tile, needs to move actually move pointer to tile
                    r = r + 1;
                    totalMoveCost += secondSum;
                }
                else
                {
                    tileMoveNum[0] = firstSum;
                    tileMoveNum[1] = secondSum;
                    randomIndex = rand() % 2;
                    nextElevationTile = tileMoveNum[randomIndex];
                }

            }
            else if (r == 4 && c != 5)
            {
                firstSum = abs(topog[r][c] - topog[r - 1][c + 1]);
                secondSum = abs(topog[r][c] - topog[r][c + 1]);
                if (firstSum < secondSum)
                {
                    nextElevationTile = topog[r - 1][c + 1];
                    r = r - 1;
                    totalMoveCost += firstSum;
                }
                else if (secondSum < firstSum)
                {
                    nextElevationTile = topog[r][c + 1];
                    totalMoveCost += secondSum;
                }
                else
                {
                    tileMoveNum[0] = topog[r - 1][c + 1];
                    tileMoveNum[1] = topog[r][c + 1];
                    randomIndex = rand() % 2;
                    nextElevationTile = tileMoveNum[randomIndex];
                }
            }
            else if (c !=5)
            {
                firstSum = abs(topog[r][c] - topog[r - 1][c + 1]);
                secondSum = abs(topog[r][c] - topog[r][c + 1]);
                thirdSum = abs(topog[r][c] - topog[r + 1][c + 1]);
                if ((firstSum < secondSum) && (firstSum < thirdSum)) //check if it works
                {
                    nextElevationTile = topog[r - 1][c + 1];
                    totalMoveCost += firstSum;
                }
                else if ((secondSum < firstSum) && (secondSum < thirdSum))
                {
                    nextElevationTile = topog[r][c + 1];
                    totalMoveCost += secondSum;
                }
                else if ((thirdSum < firstSum) && (thirdSum < secondSum))
                {
                    nextElevationTile = topog[r + 1][c + 1];
                    r = r + 1;
                    totalMoveCost += thirdSum;
                }
                else
                {
                    tileMoveNum[0] = firstSum;
                    tileMoveNum[1] = secondSum;
                    randomIndex = rand() % 2;
                    nextElevationTile = tileMoveNum[randomIndex];
                }
            }
            else if ((r != 4) && (c == 5))
            {
                r = 0;
                c = 0;
                sums[count] = totalMoveCost;
                count++;

            }
            else
            {
                sums[count] = totalMoveCost;
            }



        }
		//placeholder. Calculate correct sums
		sums[r] = totalMoveCost;  //place sums in this array. One sum per row
	}

}


