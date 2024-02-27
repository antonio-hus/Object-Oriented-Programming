#include <stdio.h>

int is_prime(int x)
{
    /* Verifies if a given integer is prime */

    if(x<2)
        return 0;
    if(x!=2 && x%2==0)
        return 0;
    for(int d=3;d*d<=x;d+=2)
        if(x%d==0)
            return 0;
    return 1;
}

void prime_smaller_than(int x)
{
    /* Prints to the console the prime numbers smaller than x (int) */
    for(int i=2; i<x; i++)
        if(is_prime(i))
            printf("%d ", i);
}

void lcs(int v[], int size_v)
{
    /* Prints to the console the LCS of prime sum of consecutive numbers in the list v of length size_v */
    // LCS Vector
    int lcs[100], size_lcs=0;

    // LCS Indices
    int max_size_lcs=0, st=0, max_st=0, dr=-1;

    // Checking the number and succesor. Going through the list in one for loop
    // Best / Worst / Total Case Time Complexity: O(n)
    for(int i=0; i<size_v-1; i++)
    {
        if(v[i+1]==0)
            break;
        if(is_prime(v[i]+v[i+1]))
        {
            if(size_lcs==0)
            {
                lcs[size_lcs] = v[i];
                size_lcs++;
            }
            lcs[size_lcs] = v[i+1];
            size_lcs++;
            if(max_size_lcs < size_lcs)
            {
                max_st = st;
                dr = i+1;
            }
        }
        else
        {
            st=i;
            size_lcs = 0;
        }
    }

    // Printing the LCS
    printf("\nThe LCS with the given property is:\n");
    for(int i=max_st;i<=dr;i++)
        printf("%d ", lcs[i]);
}

int main()
{
    printf("Welcome to my first assignment!\n");
    printf("Made by Antonio Hus, Group 914/1\n\n");

    while(1)
    {
        printf("Test Functionality:\n1. Prime numbers smaller than a given number (task a)\n2. LCS of prime sum of consecutive (task b)\n0. Exit\n>");
        int input;
        scanf("%d", &input);

        if(input==1)
        {
            int number;
            printf("\nEnter your number: ");
            scanf("%d", &number);
            printf("Here is the list of prime numbers smaller than %d: \n", number);
            prime_smaller_than(number);
            break;
        }
        else if(input==2)
        {
            int v[100], size_v=0, x=-1;

            // Reading the vector of numbers up to apperance of 0
            printf("\nEnter a list of numbers (Enter 0 to terminate)\n");
            while(1)
            {
                scanf("%d", &x);
                if (x == 0)
                    break;
                v[size_v] = x;
                size_v++;
            }
            lcs(v, size_v);
            break;
        }
        else if (input==0)
            break;
        else printf("Invalid Option!\n\n\n");
    }
    return 0;
}