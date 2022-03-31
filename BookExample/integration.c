//
//  integration.c
//  BookExample
//
//  Created by Judah Small on 3/16/22.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_FUNC_SIZE 100

const int xBound[] ={ 0, 0};
const int yBound[] ={ 0, 0};

const long double N = 10000000000;

char useFunc[MAX_FUNC_SIZE](long double delta, char respectTo);

int main(void)
{
    
    
}

void integrateX(char *function)
{
    //read each line of function seperate out numerics symbols spaces
    long double x = 0.0;
    long double sum = 0.0;
    
    for (long double i = 0; i<=N ; i=i+(1/N))
    {
        x=i;
        //func translated into arithmatic
        sum+= (useFunc(i, 'X'));
        
    }
}

void integrateY(char *function)
{
    
}

void enterFunc(void)
{
    
    char funcArray[MAX_FUNC_SIZE] = { };
    for (int i=0; i < MAX_FUNC_SIZE; i ++)
    {
        funcArray[i] = getchar();
    }
    
}

char useFunc[MAX_FUNC_SIZE](long double delta, char respectTo)
{
    char calc[]= {0};
    
    //delta*constants squared etc
    
    return calc[];
}
    
