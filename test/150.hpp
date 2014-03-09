#ifndef __150_HPP
#define __150_HPP

using namespace __shedskin__;
namespace __150__ {

class Individual;
class SGA;


extern str *__name__;
extern double infiniteNeg, pi;
extern SGA *sga;


extern class_ *cl_Individual;
class Individual : public pyobj {
public:
    __ss_int ngenes;
    list<__ss_bool> *genome;
    double fitness;

    Individual() {}
    Individual(__ss_int ngenes) {
        this->__class__ = cl_Individual;
        __init__(ngenes);
    }
    double fitnessFun(double x);
    __ss_int bin2dec(__ss_int inf, __ss_int sup);
    double computeValuesGenome(__ss_int xMin, double xMax);
    void *computeFitness();
    void *__init__(__ss_int ngenes);
    Individual *__copy__();
};

extern class_ *cl_SGA;
class SGA : public pyobj {
public:
    double geneMutationProb;
    Individual *bestIndividual;
    __ss_int generation;
    double selectivePressure;
    __ss_int popSize;
    __ss_int genomeSize;
    double crossingOverProb;
    list<Individual *> *population;
    __ss_int generationsMax;

    SGA() {}
    SGA(int __ss_init) {
        this->__class__ = cl_SGA;
        __init__();
    }
    void *mutatePop();
    void *run();
    void *generateRandomPop();
    void *crossingOverPop();
    void *showGeneration_bestIndFind();
    void *computeFitnessPop();
    list<Individual *> *tounamentSelectionPop();
    void *__init__();
};

extern double  default_0;


} // module namespace
#endif
