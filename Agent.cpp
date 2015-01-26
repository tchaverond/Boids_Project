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

  int Agent::total_headcount = 0;                    // deprecated

// ===========================================================================
//                                  Constructors
// ===========================================================================

/*Agent::Agent(void)             // should only be used as a fictitious Agent to browse through the boid (seen as a Linked List)
{
	id = 0;
	x = 0;
	new_x = 0;
	y = 0;
	new_y = 0;
	x_velocity = 0;
	y_velocity = 0;
    new_x_vel = 0;
    new_y_vel = 0;
    size_x = 0;
    size_y = 0;
	perception_radius = 0;
	contact_radius = 0;
	next = NULL;
    devour_radius = 0;
    devour_time = RAND_MAX;
    hunt_speed = 0;
}*/


Agent::Agent(double init_x, double init_y, int type)
{

    type_id = type;
    total_headcount ++;
    id = total_headcount;
    x = init_x;
    new_x = init_x;
    y = init_y;
    new_y = init_y;

    new_x_vel = 0;
    new_y_vel = 0;
    size_x = 0;
    size_y = 0;
    contact_radius = 12;
    next = NULL;

    // predator case
    if (type == 2)
    {
        x_velocity = 0;
        y_velocity = 0;
        perception_radius = 100;
        devour_radius = 4;
        hunt_speed = 2.7;
        devour_time = 100000;
    } 
    // prey case
    else
    {
        x_velocity = 0.15*(2*(((double)rand())/(RAND_MAX))-1);
        y_velocity = 0.15*(2*(((double)rand())/(RAND_MAX))-1);
        perception_radius = 80;
        devour_radius = -1;
        hunt_speed = -1;
        devour_time = RAND_MAX;  // to make it virtually infinite
    }

    //printf("Agent created succesfully !\n");

}


Agent::Agent(double init_x, double init_y, double init_size_x, double init_size_y)
{

    type_id = 0;
    id = -1;
    x = init_x;
    new_x = init_x;
    y = init_y;
    new_y = init_y;
    x_velocity = 0;
    y_velocity = 0;
    new_x_vel = 0;
    new_y_vel = 0;
    size_x = init_size_x;
    size_y = init_size_y;
    perception_radius = -1;
    contact_radius = -1;
    next = NULL;
    devour_radius = -1;
    hunt_speed = -1;
    devour_time = RAND_MAX;

    //printf("Obstacle created succesfully !\n");

}

// ===========================================================================
//                                  Destructor
// ===========================================================================

Agent::~Agent(void)
{
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

// alternative method for obstacles, to calculate a distance more accurate between a living being and an obstacle (according to which side the living being comes from)
double Agent::distanceObs(Agent* Obstacle)
{
    double result = 0;

    if ((this->x < Obstacle->x) && (this->y < Obstacle->y))
    {
        result = ((Obstacle->x)-(this->x)) * ((Obstacle->x)-(this->x))  +  ((Obstacle->y)-(this->y)) * ((Obstacle->y)-(this->y));
    }

    if ((this->x < Obstacle->x) && (this->y > Obstacle->y))
    {
        result = ((Obstacle->x)-(this->x)) * ((Obstacle->x)-(this->x))  +  ((Obstacle->y+Obstacle->size_y)-(this->y)) * ((Obstacle->y+Obstacle->size_y)-(this->y));
    }

    if ((this->x > Obstacle->x) && (this->y < Obstacle->y))
    {
        result = ((Obstacle->x+Obstacle->size_x)-(this->x)) * ((Obstacle->x+Obstacle->size_x)-(this->x))  +  ((Obstacle->y)-(this->y)) * ((Obstacle->y)-(this->y));
    }

    if ((this->x > Obstacle->x) && (this->y > Obstacle->y))
    {
        result = ((Obstacle->x+Obstacle->size_x)-(this->x)) * ((Obstacle->x+Obstacle->size_x)-(this->x))  +  ((Obstacle->y+Obstacle->size_y)-(this->y)) * ((Obstacle->y+Obstacle->size_y)-(this->y));
    }
    
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
	printf("Position : %lg %lg\n Velocity : %lg %lg\n Size : %lg %lg\n", x, y, x_velocity, y_velocity, size_x, size_y);
}

void Agent::applyWind(double height, double width, double step)
{

	double wind_x = 0;
	double wind_y = 0;
    double max_speed = 1;
    double speed;
    double wind_force = 0.2;

	/****************************************        First Approach       **************************************************/

    // unused


    /****************************************        Second Approach       **************************************************/

    // upper frontier
    if (y < 50)
    {
        wind_y = wind_force/(y+0.1);
    }

    // lower frontier
    if (y > height-50)
    {
        wind_y = -wind_force/(height-y+0.1);
    }

    // left frontier
    if (x < 50)
    {
        wind_x = wind_force/(x+0.1);
    }

    // right frontier
    if (x > width-50)
    {
        wind_x = -wind_force/(width-x+0.1);
    }

    new_x_vel += wind_x;
    new_y_vel += wind_y;

    // preventing excessive speeds
    speed = sqrt((new_x_vel * new_x_vel) + (new_y_vel * new_y_vel));
    if (speed > max_speed)
    {
        new_x_vel /= speed/max_speed;
        new_y_vel /= speed/max_speed;
    }

    new_x += step * new_x_vel;
    new_y += step * new_y_vel;

    // shouldn't be necessary, just one more security
    if (new_x < 0)
    {
        new_x = 5;
    }

    if (new_x > width)
    {
        new_x = width-5;
    }

    if (new_y < 0)
    {
        new_y = 5;
    }

    if (new_y > height)
    {
        new_y = height-5;
    }

}

void Agent::huntPrey(Agent* victim)
{
    if (type_id == 2)
    {
        // getting direction of the nearest prey
        new_x_vel = victim->get_x() - x;
        new_y_vel = victim->get_y() - y;

        // going towards it at the required speed
        double new_vel = sqrt((new_x_vel * new_x_vel) + (new_y_vel * new_y_vel));
        new_x_vel /= new_vel/hunt_speed;
        new_y_vel /= new_vel/hunt_speed;  
    } else {
        printf("Error : Calling huntPrey method on a Prey, not on a Predator !\n");
    }
}

void Agent::lunchTime(void)
{
    if (type_id == 2)
    {
        new_x_vel = 0;
        new_y_vel = 0;
        devour_time = 0;
        //printf("Miam !\n");

    } else {
        printf("Error : Calling lunchTime method on a Prey, not on a Predator !\n");
    }
}

void Agent::lunchProgress(void)
{

    devour_time ++;
}

// ===========================================================================
//                                Protected Methods
// ===========================================================================

// ===========================================================================
//                               Non inline accessors
// ===========================================================================
