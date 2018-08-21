/* Computes the Max interleave factor for sequence X
   by using a subsequence of sequence A 

   compiled using gcc hw1.c
   executed with a.out
*/

#include<stdio.h>
#include<stdlib.h>

void sequence_finder(int A_count, int X_count, int *X_array, int *A_array); 
int binary_search(int *A_array,int num,int key);
void print (int low, int mid, int high);
void sequence_finder2(int possible_mid, int A_count, int X_count, int *X_array, int *A_array); 

int main(void)
{
    int i,j;
    int A_num , X_num, A_count = 0, X_count = 0;
    int A_int, X_int, num = -999999999; /* this num ends user input for the sequences */
    int *A_array, *X_array;
    
    printf("Enter the No_ of intergers in sequence A and sequence X space separted: ");
    scanf("%d %d",&A_num,&X_num);
    A_array = malloc(A_num * sizeof(int));
    X_array = malloc(X_num * sizeof(int));
    
    while(A_num+1 != A_count)  /* Takes input from the user for sequence A */
    {
	printf("Enter the integer for Sequence A: ");
	scanf("%d",&A_int);

	if (A_int == num)
	{
	   break;
	} 

	A_array[A_count] = A_int;
        A_count++;	
    }

    while(X_num+1 != X_count) /* Takes input from the user for sequence X */
    {
        printf("Enter the integer for Sequence X: ");
        scanf("%d",&X_int);

        if (X_int == num)
        {
           break;
        }

	X_array[X_count] = X_int;
        X_count++;
    } 
	sequence_finder( A_count, X_count, X_array, A_array); 

}

void sequence_finder(int A_count, int X_count, int *X_array, int *A_array)
{		
  
   int a, b, Sub_array_size, flag, possible_mid, low, high;
   int *Sub_array , j, k = 0, Max_interleave = 0, count = 0;
   Sub_array = malloc(possible_mid * sizeof(int));

   possible_mid = A_count/X_count; /* intial estimated mid */
   low = possible_mid/2; /* initial low and high for the mid */
   high =  possible_mid;
   Sub_array_size = X_count * possible_mid;   

   for(j = 0; j < Sub_array_size; j++) /* creates a subsequent array using interleave factor */
   {
        if (count != possible_mid)
        {
           Sub_array [j] = X_array[k];
	   count++;
        }
        else
        {
           k++;
           Sub_array [j] = X_array[k];
           count = 0; /* Reset counter */
	}
   }

  for(a = 0; a < Sub_array_size; a++) /* nested for loop to check if the new sequence is a subsequence of sequence A */
  {
       for(b = 0; b < A_count; b++)
       {
	   if (Sub_array [a] == A_array[b]) /* finding matching numbers in each sequence index */
	   {
		flag = binary_search(A_array,A_count,Sub_array[a]); /* stores the index of the matching number found */
		Max_interleave++; /* update the Maximum interleave whenever we find matching values in the sequences */	
	   }	   
	   else  /* new sequence isn't subsequence of A */ 
	   {
		flag = -1;  /* means no matching numbers found */	   
           }
       }

   }
	possible_mid = flag; /* new interleave factor is set to create a new subsequence */
	printf("Maximum repeats is %d \n", Max_interleave);
}

void sequence_finder2(int possible_mid, int A_count, int X_count, int *X_array, int *A_array)
{

   int a, b, Sub_array_size, flag,low, high;
   int *Sub_array , j, k = 0, Max_interleave = 0, count = 0;
   Sub_array = malloc(possible_mid * sizeof(int));

   low = possible_mid/2; /* initial low and high for the mid */
   high =  possible_mid;
   Sub_array_size = X_count * possible_mid;

   for(j = 0; j < Sub_array_size; j++) /* creates a subsequent array using interleave factor */
   {
        if (count != possible_mid)
        {
           Sub_array [j] = X_array[k];
           count++;
        }
        else
        {
           k++;
           Sub_array [j] = X_array[k];
           count = 0; /* Reset counter */
        }
   }

     for(a = 0; a < Sub_array_size; a++) /* nested for loop to check if the new sequence is a subsequence of sequence A */
     {
       for(b = 0; b < A_count; b++)
       {
           if (Sub_array [a] == A_array[b]) /* finding matching numbers in each sequence index */
           {
                flag = binary_search(A_array,A_count,Sub_array[a]); /* stores the index of the matching number found */
                Max_interleave++; /* update the Maximum interleave whenever we find matching values in the sequences */
           }
           else  /* new sequence isn't subsequence of A */
           {
                flag = -1;  /* means no matching numbers found */
           }
       }

   }
        possible_mid = flag; /* new interleave factor is set to create a new subsequence */
        printf("Maximum repeats is %d \n", Max_interleave);
        sequence_finder2(possible_mid, A_count,X_count,X_array,A_array); /* construct a new sequnce */

}

int binary_search(int *A_array,int num,int key)
{
   int low = 0, high, mid;
   high = num - 1;
   print(low,mid,high);
   
  while (low <= high)
 {
    mid = (low + high)/2;

    if (A_array[mid]==key)
    {
        return mid; /* value found in sequence A */
    }

    if (A_array[mid] < key)
    {
        low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
 }
    
}

void print (int low, int mid, int high)
{
 
   if (mid != -1) 
   {
      printf("low %d mid %d high %d passed\n",low,mid,high);
   }

   else
   {
      printf("low %d mid %d high %d failed\n",low,mid,high);
   }

}
