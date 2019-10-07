// Your Name:  Miguel Aquino
// Your email: ma1070652@swccd.edu
// Your ID: 1070652

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <time.h>
#define MAXN 100L

void calcSums(int** topog, int* sumList);
int** malloc2d(int x, int y);

int ROWS, COLS;
int** topography;
int *readIntegers;

int main(int argc, char* argv[]) //char** argv also ok
{
    char lineRead[MAXN];
    int i = 0;
    int num;
    int ivalRead;
    double dvalRead;
    int lowValSum = 0;
    int lowValSumRow = 0;

    FILE* inFile = fopen(argv[1], "r"); //open a file from user for reading, must set project program arguments to file name beforehand

    if(inFile == NULL)
    {
        exit(1);
        printf("There was an error opening with opening the file.");
    }

/************ READ:  NCOLS  value*************************/
    fscanf(inFile,"%s",lineRead);
    printf("%s: ", lineRead);

    fscanf(inFile,"%d",&ivalRead);
    printf("%d \n", ivalRead);
    COLS = ivalRead;
/************* READ:  NROWS  value************************/
    fscanf(inFile,"%s",lineRead);
    printf("%s: ", lineRead);

    fscanf(inFile,"%d",&ivalRead);
    printf("%d \n", ivalRead);
    ROWS = ivalRead;
/************** READ:  xllcorner  value****************/
    fscanf(inFile,"%s",lineRead);
    printf("%s: ", lineRead);

    fscanf(inFile,"%lf",&dvalRead);
    printf("%lf \n", dvalRead);
/************** READ:  yllcorner  value***********/
    fscanf(inFile,"%s",lineRead);
    printf("%s: ", lineRead);

    fscanf(inFile,"%lf",&dvalRead);
    printf("%lf \n", dvalRead);
/************** READ:  cellsize  value**********/
    fscanf(inFile,"%s",lineRead);
    printf("%s: ", lineRead);

    fscanf(inFile,"%lf",&dvalRead);
    printf("%lf \n", dvalRead);

    topography = malloc2d(ROWS, COLS); //calls memory allocation for 2d array

    readIntegers = (int*) malloc((ROWS * COLS) * sizeof(int)); //calls memory allocation for array

    while(fscanf(inFile, "%d", &num) == 1) //assigns integers in file to array
    {
        readIntegers[i] = num;
        i++;
    }

    int count = 0;

    for (int r=0; r<ROWS; r++) //converts the 1D array to 2D array
    {
        for (int c=0; c<COLS; c++)
        {
            topography[r][c] = readIntegers[count];
            count++;
        }
    }

    int sumList[ROWS];
    calcSums(topography, sumList); //pass in topography, get back list of elevation sums

    lowValSum = sumList[0]; //default lowest elevation sum assigned to starting row

    for(int r=0; r < ROWS; r++) //finds the lowest elevation sum and its row
    {
        if(sumList[r] < lowValSum)
        {
            lowValSum = sumList[r];
            lowValSumRow = r;
        }
    }
    printf("Lowest elevation change sum: %d \n", lowValSum);
    printf("Starting row calculated from: %d", lowValSumRow);

    fclose(inFile);

    return 0;
}

int** malloc2d(int x, int y) //dynamically allocates memory to 2d array
{
    int index;
    int** t = malloc(x * sizeof(int*));
    for (index = 0; index < x; index++)
      t[index] = malloc(y * sizeof(int));
    return t;
}


/*
 *  Receives 2d matrix that represents topography
 *  and uses this data to calculate an elevation path sum for each
 *  row.
 *  Input:  topog[][]
 *  Output: sum[]
 *
 */
void calcSums(int** topog, int* sumList )
{
   int r,c;
   int currentRow = 0; // do currentRow++ to cycle through the rows
   int sum1, sum2, sum3;
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
           if (((top < 0) && (mid < bot)) || (mid == bot))
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
                    currentCol++;
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

            sumList[r] = totalMoveCost; //place sums in this array. One sum per row
        }
	}
}
