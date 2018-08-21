/* Computes the subset sums of for all possible cardinalities.
   Modified from http://ranger.uta.edu/~weems/NOTES2320/subsetSum.c
   compiled using gcc 1001149004.c
   executed with a.out
*/

#include <stdio.h>
#include <stdlib.h>

void readInput(int* n, int* m, int** S, int** C);
void subsetSum(int n, int m, int* S, int* C, int Cost[n][m], int Cardinality[n][m]);
void writeOutput(int n,int m,int* S,int* C, int Cost[n][m], int Cardinality[n][m]);

int main()
{
    int n;    /* Size of input set */
    int m;    /*   Target value */
    int *S;   /*   Input set  */
    int *C;   /*   Cost table */

    readInput(&n,&m,&S,&C); /*Read input from the user and allocate memory */
    free(S);
    free(C);  /*Free the allocated memory after processing */
    return 0;
}

void readInput(int* n, int* m, int** S, int** C)  /* Loads all input and allocates space */
{
    int i;

    printf("Enter the N0 of values in the sequence followed by the target value.\n"); /*Prompt User For Inputs */

    scanf("%d",n);   /*read inputs using scanf */
    scanf("%d",m);

    *S =(int*) malloc((*n+1)*sizeof(int)); /*Allocate Dynamic Memory Using malloc */
    *C =(int*) malloc((*m+1)*sizeof(int));

    int Cost[*n][*m]; /* A 2D array to store the cost */

    int Cardinality[*n][*m]; /*A 2D array to store the Cardinalities of the subsets */

    if (!(*S) || !(*C))
   {
      printf("Malloc failed %d\n",__LINE__); /*In case memory isn't allocated, inform the user and exit program */
      exit(0);
   }

   (*S)[0] = 0; /* Sentinel zero */

   for( i = 1; i <= *n; i++)
   {
      scanf("%d",*S+i);
   }

   subsetSum(*n,*m,*S,*C,Cost,Cardinality);
   writeOutput(*n,*m,*S,*C,Cost,Cardinality);

}

void subsetSum(int n, int m, int* S, int* C, int Cost[n][m], int Cardinality[n][m])
{
    int a,b, j, potentialSum, leftover;  /* Initialize table for DP */

       C[0] = 0;  /* DP base case */

       for( a = 0; a < n; a++)       /*Initialize all the element of both array to zero */
       {
            for (b = 0; b < m; b++)
            {
                Cost[a][b] = 0;
                Cardinality[a][b] = 0;
            }

       }

  /* For each potential sum, determine the smallest index such
     that its input value is in a subset to achieve that sum. */

    for ( potentialSum = 1; potentialSum <= m; potentialSum++ )
    {
        for (j = 1; j <= n; j++)
        {
            leftover = potentialSum-S[j];  /* To be achieved with other values */

              for( a = 0; a < n; a++)
              {
                    for (b = 0; b < m; b++)
                    {

                          if (leftover >= 0 && Cost[a][leftover] < j) /*Possible to have a solution Indices are included in ascending order */
                          {
                                  Cost[a][potentialSum] = j;
                                  Cardinality[a][b]++;
                          }
                    }
              }
        }

    }

}

void writeOutput(int n,int m,int* S,int* C, int Cost[n][m], int Cardinality[n][m])
{
    int i,a,b;

    printf("  i   S\n");
    printf("-------\n");

    for( i = 0; i <= n; i++)
    {
       printf("%3d %3d\n",i,S[i]);
    }

    if ( m <= 50)                     /* output of the DB */
    {
       printf("\n  i  card  C\n");
       printf("--------------\n");

         for (a = 0; a <= m; a++)
        {
	      for (b = 1; b <= n; b++)
	      {
                   printf("%3d %3d %3d \n",a,b,Cost[a][b]); /* print index, cardinality and cost for every case */
              }
        }
    }

          for (b = 1; b <= n; b++)
          {

             if ( Cost[b][m] == n+1 )  /* output of the backtrace */
             {
                 printf("No solution\n");
             }
             else
             {
                 printf("\nSolution with %d elements\n", b);
                 printf("  i   S\n");
                 printf("-------\n");

                 for ( i = m; i > 0; i -= S[Cost[i][b]] )  /* backtrace the 2D cost array and print the cost for each cardinality */
                {
                     break;
                     printf("%3d %3d\n",Cost[i][b],S[Cost[i][b]]);
                }
            }
        }

}

