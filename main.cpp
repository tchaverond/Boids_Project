#include <cstdio>
#include <cstdlib>

#include "Agent.h"
#include "Prey.h"
#include "Predator.h"
#include "Boid.h"


int main (int argc, char* argv[])
{
    
    double width;
    double height;

    double gamma1;
    double gamma2;
    double gamma3;
    double gamma4;
    double mu;
    double nmax;

    double perceived_agents;

    Boid* Feather = new Boid ();                 // group of preys
    Boid* Enemies = new Boid ();                 // group of predators

    double a = 100;
    double b = 100;
    Prey* Jean_Eudes = new Prey (a,b);
    Predator* Marc_Yves = new Predator (150,150);

    Feather->append(Jean_Eudes);
    Enemies->append(Marc_Yves);


	return 0;
}