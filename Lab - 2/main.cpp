#include <iostream>
using namespace std;

bool is_prime(int x)
{
    if(x<2)
        return false;
    if(x!=2 && x%2==0)
        return false;
    for(int d=3;d*d<=x;d+=2)
        if(x%d==0)
            return false;
    return true;
}

int main()
{

    /** Functionality for a) **/
    int n=0;
    cout << "Enter your number:\n>";
    cin >> n;
    for(int i=1;i<n;i++)
        if(is_prime(i))
            cout<<i<<' ';

    /** Functionality for b) **/
    int v[100], size_v=0, x=-1;

    // Reading the vector of numbers up to apperance of 0
    cout << "\nEnter a list of numbers (Enter 0 to terminate)\n";
    while(x!=0)
    {
        cin>>x;
        v[size_v] = x;
        size_v ++;
    }

    // Finding the LCS with the property that the sum of the number and its successor is prime
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
    cout<<"\nThe LCS with the given property is:\n";
    for(int i=max_st;i<=dr;i++)
        cout<<lcs[i]<< ' ';
    return 0;
    
}