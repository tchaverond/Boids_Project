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
    new_x_vel = 0;
    new_y_vel = 0;
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
    new_x_vel = 0;
    new_y_vel = 0;
    perception_radius = 150;
    contact_radius = 10;
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

void Agent::applyWind(double height, double width, double step)
{

	double wind_x = 0;
	double wind_y = 0;
    double max_speed = 0.2;
    double speed;
    double wind_force = 0.005;

	/****************************************        First Approach       **************************************************/

	/*double v_angle_temp;
	double wind_force;

	// calculation of the angle value of the current velocity, to obtain the direction of the prey
    v_angle_temp = 180/M_PI * atan(new_y_vel/new_x_vel);

    // angle correction : necessary because atan returns a value between -PI/2 & PI/2
    // but if the prey goes to the left, the return value must be between PI/2 and 3PI/2
    if (new_x_vel < 0)
    {
        v_angle_temp += 180;
    }

    // little test
    if ((v_angle_temp < -90) || (v_angle_temp > 270))
    {
        printf("Wrong angle !");
    }


    // upper frontier
    if (y < 10)
    {
        wind_force = 10/y;       // wind force is inversely proportional to the prey's distance to the border
        // if the prey goes right, it has to keep going right, hence we add -PI/4 to obtain the desired angle
        if (v_angle_temp < 90)             
        {
            wind_x += wind_force * cos(v_angle_temp - 45);
            wind_y += wind_force * sin(v_angle_temp - 45);
        }
        // if the prey goes left, it has to keep going left, hence we add PI/4 to obtain the desired angle
        else
        {
            wind_x += wind_force * cos(v_angle_temp + 45);
            wind_y += wind_force * sin(v_angle_temp + 45);
        }

    }
    // lower frontier
    if (y > height-10)
    {
        wind_force = 10/(height-y);
        if (v_angle_temp < 90)   
        {
            wind_x += wind_force * cos(v_angle_temp + 45);
            wind_y += wind_force * sin(v_angle_temp + 45);
        }
        else
        {
            wind_x += wind_force * cos(v_angle_temp - 45);
            wind_y += wind_force * sin(v_angle_temp - 45);
        }

    }
    // left frontier
    if (x < 10)
    {
        wind_force = 10/x; 
        // if the prey goes up
        if ((v_angle_temp > 0) && (v_angle_temp < 180))
                 
        {
            wind_x += wind_force * cos(v_angle_temp - 45);
            wind_y += wind_force * sin(v_angle_temp - 45);
        }
        else
        {
            wind_x += wind_force * cos(v_angle_temp + 45);
            wind_y += wind_force * sin(v_angle_temp + 45);
        }

    }
    // right frontier
    if (x > width-10)
    {
        wind_force = 10/(width-x); 
        if ((v_angle_temp > 0) && (v_angle_temp < 180))
                 
        {
            wind_x += wind_force * cos(v_angle_temp + 45);
            wind_y += wind_force * sin(v_angle_temp + 45);
        }
        else
        {
            wind_x += wind_force * cos(v_angle_temp - 45);
            wind_y += wind_force * sin(v_angle_temp - 45);
        }

    }

    new_x_vel += wind_x;
    new_y_vel += wind_y;

    new_x += step * new_x_vel;
    new_y += step * new_y_vel;*/

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
    if (x > height-50)
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

}

void huntPrey(Agent* victim)
{
    printf("This shouldn't be printed ");
}

// ===========================================================================
//                                Protected Methods
// ===========================================================================

// ===========================================================================
//                               Non inline accessors
// ===========================================================================
