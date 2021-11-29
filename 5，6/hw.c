#include<stdio.h>
int A[5][9];
int main()
{
    printf("%d\n",4*(&A[3][2]-&A[0][0]));
}