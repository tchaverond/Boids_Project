//****************************************************************************
//
//
//
//****************************************************************************


 
 
// ===========================================================================
//                                   Libraries
// ===========================================================================
#include <cmath>


// ===========================================================================
//                                 Project Files
// ===========================================================================
#include "Agent.h"




//############################################################################
//                                                                           #
//                           Class Agent                            #
//                                                                           #
//############################################################################

// ===========================================================================
//                         Definition of static attributes
// ===========================================================================

  int Agent::total_headcount = 0;

// ===========================================================================
//                                  Constructors
// ===========================================================================

Agent::Agent(void)             // should only be used as a fictitious Agent to browse through the boid (seen as a Linked List)
{
	id = 0;
	x = 0;
	new_x = 0;
	y = 0;
	new_y = 0;
	x_velocity = 0;
	y_velocity = 0;
	perception_radius = 0;
	contact_radius = 0;
	next = NULL;
}



Agent::Agent(double init_x, double init_y)
{
    
	total_headcount ++;
    id = total_headcount;
    x = init_x;
    new_x = init_x;
    y = init_y;
    new_y = init_y;
    x_velocity = 0;
    y_velocity = 0;
    perception_radius = 50;
    contact_radius = 5;
    next = NULL;

	// !!! addition to the output window still to be implemented  !!!

	printf("Agent created succesfully !\n");
}

// ===========================================================================
//                                  Destructor
// ===========================================================================

Agent::~Agent(void)
{
	// !!! unfinished !!!
	total_headcount --;
}

// ===========================================================================
//                                 Public Methods
// ===========================================================================

double Agent::distance(Agent* Fellow)
{
	double result = ((Fellow->x)-(this->x)) * ((Fellow->x)-(this->x))  +  ((Fellow->y)-(this->y)) * ((Fellow->y)-(this->y));
	return (sqrt(result));
}

void Agent::updateAll(void)
{
	x = new_x;
	y = new_y;
	x_velocity = new_x_vel;
	y_velocity = new_y_vel;
}

void Agent::showAll(void)
{
	printf("Position : %lg %lg\n Velocity : %lg %lg\n", x, y, x_velocity, y_velocity);
}

// ===========================================================================
//                                Protected Methods
// ===========================================================================

// ===========================================================================
//                               Non inline accessors
// ===========================================================================
