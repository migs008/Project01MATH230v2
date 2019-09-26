// Your Name:  Miguel Aquino
// Your email: ma1070652@swccd.edu
// Your ID: 1070652

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ROWS  3
#define COLS  5
#include<string.h>
#define MAXN 100L

void calcSums(int topog[ROWS][COLS], int sumList[ROWS] );

int main(int argc, char* argv[]) //char** argv also ok
{
    char lineRead[MAXN];
    int readIntegers[10000]; //memory allocation error? <<<<<<<<<<<
    int i = 0;
    int num;
    int topography[ROWS][COLS];
    int ivalRead;
    double dvalRead;

    FILE* inFile = fopen("1topo983by450.txt", "r"); //open a file from user for reading

    if( inFile == NULL)
    {
        exit(1);
        printf("There was an error opening with opening the file.");
    }

/************ READ:  NCOLS  and   983 *************************/
    fscanf(inFile,"%s",lineRead);
    printf("I just read:  %s \n", lineRead);
    system("pause");

    fscanf(inFile,"%d",&ivalRead);
    printf("I just read:  %d \n", ivalRead);
    system("pause");
/************* READ:  NROWS  and  450 ************************/
    fscanf(inFile,"%s",lineRead);
    printf("I just read:  %s \n", lineRead);
    system("pause");

    fscanf(inFile,"%d",&ivalRead);
    printf("I just read:  %d \n", ivalRead);
    system("pause");
/************** READ:  xllcorner  and  -123.9417****************/
    fscanf(inFile,"%s",lineRead);
    printf("I just read:  %s \n", lineRead);
    system("pause");

    fscanf(inFile,"%lf",&dvalRead);
    printf("I just read:  %lf \n", dvalRead);
    system("pause");
/************** READ:  yllcorner  and  32.991666666667 ***********/
    fscanf(inFile,"%s",lineRead);
    printf("I just read:  %s \n", lineRead);
    system("pause");

    fscanf(inFile,"%lf",&dvalRead);
    printf("I just read:  %lf \n", dvalRead);
    system("pause");
/************** READ:  cellsize  and   0.016666666667***********/
    fscanf(inFile,"%s",lineRead);
    printf("I just read:  %s \n", lineRead);
    system("pause");

    fscanf(inFile,"%lf",&dvalRead);
    printf("I just read:  %lf \n", dvalRead);
    system("pause");


    while(fscanf(inFile, "%d", &num) > 0)
    {
        readIntegers[i] = num;
        i++;
        printf("Integer: %d \n", readIntegers); //works with displaying num, but unable to display correct value from readIntegers <<<<<<<<<
        system("pause");
    }


    int count = 0;

    for (int r=0; r<ROWS; r++) //converting the 1D array to 2D array
    {
        for (int c=0; c<COLS; c++)
        {
            topography[r][c] = readIntegers[count];
            count++;
        }
    }

    int sumList[ROWS] = {0};
    calcSums(topography, sumList ); //pass in topography, get back list of elevation sums

    for(int r=0; r < ROWS; r++)
    {
        printf("%8d %8d \n",r, sumList[r]);  //should display calculated sums
    }

    fclose(inFile);

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
