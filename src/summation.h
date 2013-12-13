//SingleGeneControlled project
//Gene Soudlenkov 2013
#ifndef SUMMATION_H
#define SUMMATION_H
//Summation class represents the rule to sum up two genotypes
//Abstraction is based on the protected sum() method
#include "genotype.h"


class Summation
{
public:
    Summation() {}
    virtual ~Summation() {}
    GENOTYPE operator()(const GENOTYPE& c1,const GENOTYPE& c2) { return sum(c1,c2); }
    
protected:
    virtual GENOTYPE sum(const GENOTYPE& c1,const GENOTYPE& c2)=0; //abstracted summation rule
};


#endif


