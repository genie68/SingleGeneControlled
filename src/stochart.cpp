#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mendel.h"
#include "herd.h"
#include "SimpleRNG.h"


using namespace std;

SimpleRNG randomizer;


int main(int argc,char *argv[])
{
    int sires[6]={1,0,1,1,-1,-1};
    int dams[6]={0,-1,0,1,1,-1};
    Mendel s;
    Herd h(s);

    h.Initialise(10,true);
    h.AddSires(3);
    for(int i=0;i<5;i++)
    {
        printf("Year %d:\n",i);
        h.print();
        h.Advance();
        h.Breed();
    }
    h.stats();
    return 0;
}

