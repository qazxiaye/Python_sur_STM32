#include "builtin.hpp"
#include "time.hpp"
#include "math.hpp"
#include "copy.hpp"
#include "random.hpp"
#include "150.hpp"
extern "C" {
#include "stm32f4xx.h" 
#include "stm32f4_discovery.h" 
#include <stdio.h> 
#include "stm32f4xx_conf.h" 
#include "stm32f4xx.h" 
#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;
}

namespace __150__ {

using __random__::random;
using __random__::randint;
using __random__::choice;
using __math__::sin;
using __copy__::copy;

double infiniteNeg, pi;
SGA *sga;
str *__name__;


double  default_0;

static inline list<__ss_bool> *list_comp_0(__ss_int ngenes);
static inline list<Individual *> *list_comp_2(SGA *self);

static inline list<__ss_bool> *list_comp_0(__ss_int ngenes) {
    __ss_int __0, __1, i;

    list<__ss_bool> *__ss_result = new list<__ss_bool>();

    FAST_FOR(i,0,ngenes,1,0,1)
        __ss_result->append(___bool((random()<0.5)));
    END_FOR

    return __ss_result;
}

static inline list<Individual *> *list_comp_2(SGA *self) {
    __ss_int __8, __9, i;

    list<Individual *> *__ss_result = new list<Individual *>();

    FAST_FOR(i,0,self->popSize,1,8,9)
        __ss_result->append((new Individual(self->genomeSize)));
    END_FOR

    return __ss_result;
}

/**
class Individual
*/

class_ *cl_Individual;

double Individual::fitnessFun(double x) {
    
    return (x+__abs(sin((32*x))));
}

__ss_int Individual::bin2dec(__ss_int inf, __ss_int sup) {
    __ss_int __2, __3, i, result;

    if ((sup==0)) {
        sup = (this->ngenes-1);
    }
    result = 0;

    FAST_FOR(i,inf,(sup+1),1,2,3)
        if ((this->genome)->__getfast__(i)) {
            result = (result+(1<<(i-inf)));
        }
    END_FOR

    return result;
}

double Individual::computeValuesGenome(__ss_int xMin, double xMax) {
    double scaleFactor;

    scaleFactor = ((xMax-xMin)/(1<<this->ngenes));
    return (this->bin2dec(0, 0)*scaleFactor);
}

void *Individual::computeFitness() {
    
    this->fitness = this->fitnessFun(this->computeValuesGenome(0, default_0));
    return NULL;
}

void *Individual::__init__(__ss_int ngenes) {
    
    this->ngenes = ngenes;
    this->genome = list_comp_0(ngenes);
    this->fitness = infiniteNeg;
    return NULL;
}

Individual *Individual::__copy__() {
    Individual *c = new Individual();
    c->ngenes = ngenes;
    c->genome = genome;
    c->fitness = fitness;
    return c;
}

/**
class SGA
*/

class_ *cl_SGA;

void *SGA::mutatePop() {
    list<__ss_bool> *__16;
    __ss_int __14, __15, gene, i, nmutations;
    Individual *individual;

    nmutations = __int(___round(((this->popSize*this->genomeSize)*this->geneMutationProb)));

    FAST_FOR(i,0,nmutations,1,14,15)
        individual = choice(this->population);
        gene = randint(0, (this->genomeSize-1));
        individual->genome->__setitem__(gene, __NOT((individual->genome)->__getfast__(gene)));
    END_FOR

    return NULL;
}

void *SGA::run() {
    __ss_int __31, __32;

    this->generateRandomPop();
    this->bestIndividual = (new Individual(this->genomeSize));

    FAST_FOR(this->generation,1,(this->generationsMax+1),1,31,32)
        this->computeFitnessPop();
        this->showGeneration_bestIndFind();
        this->population = this->tounamentSelectionPop();
        this->mutatePop();
        this->crossingOverPop();
    END_FOR

    return NULL;
}

void *SGA::generateRandomPop() {
    
    this->population = list_comp_2(this);
    return NULL;
}

void *SGA::crossingOverPop() {
    list<__ss_bool> *__23, *__24;
    __ss_bool __25, __26;
    __ss_int __19, __20, __21, __22, crossPosition, i, j, nCrossingOver;
    Individual *ind1, *ind2;

    nCrossingOver = __int(___round((this->popSize*this->crossingOverProb)));

    FAST_FOR(i,0,nCrossingOver,1,19,20)
        ind1 = choice(this->population);
        ind2 = choice(this->population);
        crossPosition = randint(0, (this->genomeSize-1));

        FAST_FOR(j,0,(crossPosition+1),1,21,22)
            __25 = (ind2->genome)->__getfast__(j);
            __26 = (ind1->genome)->__getfast__(j);
            ind1->genome->__setitem__(j, __25);
            ind2->genome->__setitem__(j, __26);
        END_FOR

    END_FOR

    return NULL;
}

void *SGA::showGeneration_bestIndFind() {
    list<Individual *> *__27;
    Individual *bestIndividualGeneration, *individual;
    double fitnessTot;
    __iter<Individual *> *__28;
    __ss_int __29;
    list<Individual *>::for_in_loop __30;

    fitnessTot = 0.0;
    bestIndividualGeneration = (this->population)->__getfast__(0);

    FOR_IN(individual,this->population,27,29,30)
        fitnessTot = (fitnessTot+individual->fitness);
        if ((individual->fitness>bestIndividualGeneration->fitness)) {
            bestIndividualGeneration = individual;
        }
    END_FOR

    if (((this->bestIndividual)->fitness<bestIndividualGeneration->fitness)) {
        this->bestIndividual = copy(bestIndividualGeneration);
    }
    return NULL;
}

void *SGA::computeFitnessPop() {
    list<Individual *>::for_in_loop __13;
    Individual *individual;
    list<Individual *> *__10;
    __ss_int __12;
    __iter<Individual *> *__11;


    FOR_IN(individual,this->population,10,12,13)
        individual->computeFitness();
    END_FOR

    return NULL;
}

list<Individual *> *SGA::tounamentSelectionPop() {
    __ss_int __17, __18, i;
    list<Individual *> *pop2;
    Individual *individual1, *individual2;

    pop2 = (new list<Individual *>());

    FAST_FOR(i,0,this->popSize,1,17,18)
        individual1 = choice(this->population);
        individual2 = choice(this->population);
        if ((random()<this->selectivePressure)) {
            if ((individual1->fitness>individual2->fitness)) {
                pop2->append(individual1);
            }
            else {
                pop2->append(individual2);
            }
        }
        else {
            if ((individual1->fitness>individual2->fitness)) {
                pop2->append(individual2);
            }
            else {
                pop2->append(individual1);
            }
        }
    END_FOR

    return pop2;
}

void *SGA::__init__() {
    
    this->popSize = 200;
    this->genomeSize = 16;
    this->generationsMax = 16;
    this->crossingOverProb = 0.75;
    this->selectivePressure = 0.75;
    this->geneMutationProb = 0.005;
    return NULL;
}

void __init() {
    __name__ = new str("__main__");

    pi = __math__::pi;
    infiniteNeg = (-1e+302);
    default_0 = pi;
    cl_Individual = new class_("Individual");
    cl_SGA = new class_("SGA");
    sga = (new SGA(1));
    sga->generationsMax = 3000;
    sga->genomeSize = 20;
    sga->popSize = 30;
    sga->geneMutationProb = 0.01;
    sga->run();
}

} // module namespace

int main(int, char **) {

    USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
    setbuf(stdout, NULL);
    __shedskin__::__init();
    __math__::__init();
    __time__::__init();
    __random__::__init();
    __copy__::__init();
    __shedskin__::__start(__150__::__init);
}
