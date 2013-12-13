//SingleGeneControlled project
//Gene Soudlenkov 2013
#ifndef HERD_H
#define HERD_H

#include <vector>
#include "summation.h"

//Single animal class
//Age is used rather than birth time
//in order to save time on further calculations
//Genotype only takes -1,0,1 values
class Animal
{
public:
    Animal():m_Genotype(NEUTRAL),m_Age(0) {}
    Animal(const GENOTYPE& g,int a):m_Genotype(g),m_Age(a) {}
    Animal(const Animal& other):m_Genotype(other.m_Genotype),m_Age(other.m_Age) {}
    ~Animal() {}
    GENOTYPE& genotype() { return m_Genotype; }
    int& age() { return m_Age; }
    Animal& operator=(const Animal& other)
    {
        if(&other!=this)
	{
	    m_Genotype=other.m_Genotype;
	    m_Age=other.m_Age;
	}
	return *this;
    }
protected:
    GENOTYPE m_Genotype;
    int m_Age;
};


//group of animals
typedef std::vector<Animal> ANIMALS;

#define MAIN_HERD 0x0001
#define SUBST_HERD 0x0002
#define BOTH_HERDS MAIN_HERD|SUBST_HERD

//Herd class
//Represents both main and substitute herds if necessary
//Options can control whether substitute herd is to be created
class Herd
{
public:
    Herd(Summation& sum);
    ~Herd();

    void Initialise(int initialSize,bool bNeedSubst);
    void PulloutDames(int number,ANIMALS& dames);
    void AddDames(const ANIMALS& dames);
    void AddSires(int sires);
    void Breed();
    void Advance();
    void Clear(unsigned short what=BOTH_HERDS);
    int Size(unsigned short what=MAIN_HERD);
    void print();
    void stats();

protected:

    double mean_genotype();
    double mean_age();
    struct PeriodStats
    {
        int MainHerdSize;
	double MeanGenotype;
	double MeanMainHerdAge;
	int Births;
	int Deaths;
    };
    
    ANIMALS m_Dames;
    ANIMALS m_Subst;
    ANIMALS m_Sires;
    bool m_bNeedSubst;
    Summation& m_Summation;
    double m_Lambda;
    std::vector<PeriodStats> m_Stats;
};

#endif

