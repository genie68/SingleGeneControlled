//SingleGeneControlled project
//Gene Soudlenkov 2013
#include "herd.h"
#include "SimpleRNG.h"


using namespace std;


extern SimpleRNG randomizer;

Herd::Herd(Summation& sum):m_Summation(sum),m_bNeedSubst(false),m_Lambda(1.0/17.0)
{
}

Herd::~Herd()
{
}

void Herd::Initialise(int initialSize,bool bNeedSubst)
{
    m_bNeedSubst=bNeedSubst;
    if(!initialSize)
        return;
    m_Dames.resize(initialSize);
    for(int i=0;i<initialSize;i++)
    {
        m_Dames[i].genotype()=(GENOTYPE)((int)(randomizer.GetUniform()*100)%3-1);
	m_Dames[i].age()=randomizer.GetUniform()*10+1;
    }
    PeriodStats ps={m_Dames.size(),mean_genotype(),mean_age(),0,0};
    m_Stats.push_back(ps);
}

void Herd::AddSires(int sires)
{
    m_Sires.resize(sires);
    for(int i=0;i<sires;i++)
    {
        m_Sires[i].genotype()=(GENOTYPE)((int)(randomizer.GetUniform()*100)%3-1);
	m_Sires[i].age()=randomizer.GetUniform()*10+1;
    }
}

void Herd::PulloutDames(int number,ANIMALS& dames)
{
    for(int i=0;i<number && m_Dames.size();i++)
    {
        //make random selection from the dames
        int index= m_Dames.size()*randomizer.GetUniform();
	dames.push_back(m_Dames[index]);
	m_Dames.erase(m_Dames.begin()+index);
    }
}

void Herd::AddDames(const ANIMALS& dames)
{
    for(ANIMALS::const_iterator it=dames.begin();it!=dames.end();++it)
    {
        m_Dames.push_back(*it);
    }
}

void Herd::Advance()
{
    for(ANIMALS::iterator it=m_Dames.begin();it!=m_Dames.end();++it)
        it->age()++;
    for(ANIMALS::iterator it=m_Subst.begin();it!=m_Subst.end();++it)
        it->age()++;
    for(ANIMALS::iterator it=m_Sires.begin();it!=m_Sires.end();++it)
        it->age()++;
}

void Herd::Breed()
{
    int substThresh=m_Subst.size();
    int deaths=0;
    int births=0;

    if(!m_Sires.size() || !m_Dames.size())
        return;
    for(int i=0;i<m_Dames.size();i++)
    {
        if(m_Dames[i].age()>2 && randomizer.GetUniform()>0.5)
	{
	    //Age and nature are for breeding!
	    int sire=rand()%m_Sires.size();
	    births++;
	    if(m_bNeedSubst)
	        m_Subst.push_back(Animal(m_Summation(m_Sires[sire].genotype(),m_Dames[i].genotype()),0));
            else
	        m_Dames.push_back(Animal(m_Summation(m_Sires[sire].genotype(),m_Dames[i].genotype()),0));
	}
    }
    //retire some of the dames
    for(int i=0;i<m_Dames.size();)
    {
        //int v=randomizer.GetPoisson(m_Lambda);
	//printf("V=%d\n",v);
	//break;
        if(randomizer.GetUniform()<=m_Lambda*m_Dames[i].age())
	{
	    //Well, RIP, cow!
	    m_Dames.erase(m_Dames.begin()+i);
	    deaths++;
	}
	else
	{
	    i++;
	}
    }
    //Check if any of the dames are to vacate
    if(m_bNeedSubst)
    {
        //Check if substitute herd need to feed the main herd 
	for(int i=0;i<m_Subst.size();)
	{
            if(randomizer.GetUniform()<=m_Lambda)
	    {
	        //RIP, baby cow
	        m_Subst.erase(m_Subst.begin()+i);
		deaths++;
	    }
	    else if(m_Subst[i].age()>=2)
	    {
	        //Only those older than 2 should be moved
		m_Dames.push_back(m_Subst[i]);
		m_Subst.erase(m_Subst.begin()+i);
	    }
	    else
	    {
	        i++;
	    }
	}
    }
    PeriodStats ps={m_Dames.size(),mean_genotype(),mean_age(),births,deaths};
    m_Stats.push_back(ps);
}

int Herd::Size(unsigned short what)
{
    int res=0;

    if(what&MAIN_HERD)
        res+=m_Dames.size();
    if(what&SUBST_HERD)
        res+=m_Subst.size();
    return res;
}

double Herd::mean_genotype()
{
    double sum=0.0;

    for(ANIMALS::iterator it=m_Dames.begin();it!=m_Dames.end();++it)
    {
        sum+=(int)it->genotype();
    }
    return sum/m_Dames.size();
}

double Herd::mean_age()
{
    double sum=0.0;

    for(ANIMALS::iterator it=m_Dames.begin();it!=m_Dames.end();++it)
    {
        sum+=it->age();
    }
    return sum/m_Dames.size();
}

void Herd::print()
{
    printf("Main herd:\n");
    for(int i=0;i<m_Dames.size();i++)
        printf("Age=%d, genotype=%d\n",m_Dames[i].age(),m_Dames[i].genotype());
    printf("Substitute herd:\n");
    for(int i=0;i<m_Subst.size();i++)
        printf("Age=%d, genotype=%d\n",m_Subst[i].age(),m_Subst[i].genotype());
}

void Herd::stats()
{
    for(int i=0;i<m_Stats.size();i++)
    {
        printf("%d. Main herd size: %d, mean genotype: %.2lf, mean age: %.2lf, births: %d, deaths: %d\n",i,m_Stats[i].MainHerdSize,m_Stats[i].MeanGenotype,
	       m_Stats[i].MeanMainHerdAge,m_Stats[i].Births,m_Stats[i].Deaths);
    }
}

void Herd::Clear(unsigned short what)
{
    if(what&MAIN_HERD)
        m_Dames.clear();
    if(what&SUBST_HERD)
        m_Subst.clear();
}
