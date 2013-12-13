#ifndef MENDEL_H
#define MENDEL_H
#include <time.h>
#include <stdlib.h>
#include "summation.h"
#include "SimpleRNG.h"

extern SimpleRNG randomizer;

class Mendel:public Summation
{
public:
    Mendel() { srand(time(NULL)); }
    virtual ~Mendel() {}
    
protected:
    virtual GENOTYPE sum(const GENOTYPE& c1,const GENOTYPE& c2)
    {
        GENOTYPE res=POSITIVE;
        //Run Mendel summation scheme
	if(c1==c2)
	{
	    if(c1) //c1==c2==-1 => -1; c1==c2==1 => 1
	        res=c1;
	    else
	    {
	        int tmp=randomizer.GetUniform();
	        res=(tmp<0.25?NEGATIVE:(tmp>0.75?NEUTRAL:POSITIVE));
	    }
	}
	else if(c1==NEGATIVE)
	{
	    res=(c2==NEUTRAL?((randomizer.GetUniform()>0.50?NEUTRAL:NEGATIVE)):NEUTRAL);
	}
	else if(c1==NEUTRAL)
	{
	    res=(c2==POSITIVE?((randomizer.GetUniform()>0.50?NEUTRAL:POSITIVE)):NEUTRAL);
	}
	else //c1==1
	{
	    res=(c2==NEUTRAL?((randomizer.GetUniform()>0.50?NEUTRAL:NEGATIVE)):NEUTRAL);
	}
	return res;
    }
};


#endif


