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

    double step;
    double gamma1;
    double gamma2;
    double gamma3;
    double gamma4;
    double mu;
    double nmax;

    double v1_x_temp;              // temporary stockage value for v1_x
    double v1_y_temp;              // temporary stockage value for v1_y
    double v2_x_temp;              // temporary stockage value for v2_x
    double v2_y_temp;              // temporary stockage value for v2_y
    double v3_x_temp;              // temporary stockage value for v3_x
    double v3_y_temp;              // temporary stockage value for v3_y

    double k;                      // number of near (perceived) agents                   
    double kk;                     // number of really (too) near agents



    Boid* Flock = new Boid ();                   // group of preys
    Boid* Enemies = new Boid ();                 // group of predators



    /**************************************         Parameters' Initialization          **************************************/

    step = 0.1;

    gamma1 = 5;
    gamma2 = 2;
    gamma3 = 3;



    /********************************************          Flock Creation          *******************************************/ 

    double a = 100;
    double b = 100;
    Prey* Jean_Eudes = new Prey (a,b);
    Predator* Marc_Yves = new Predator (150,150);

    Flock->append(Jean_Eudes);
    Flock->append(Jean_Eudes);
    Enemies->append(Marc_Yves);




    /***************************************************************************************************************************
    ************************************************          Main Loop         ************************************************
    ***************************************************************************************************************************/


    Agent* W1 = new Agent();       // the Wanderers Wi will browse through the flock
    Agent* W2 = new Agent();       // W1 is the current Agent, W2 is a fellow of W1

    v1_x_temp = 0;
    v1_y_temp = 0;
    v2_x_temp = 0;
    v2_y_temp = 0;
    v3_x_temp = 0;
    v3_y_temp = 0;

    k = 0;
    kk = 0;


    // epic loop begins here !
    for (W1=Flock->get_head(); W1->get_next() != NULL; W1=W1->get_next())
    {

        for (W2=Flock->get_head(); W2->get_next() != NULL; W2=W2->get_next())
        {
            if ((W1 != W2) && ((W1->distance(W2)) < W1->get_perception_radius()))  // condition for v1 & v2
            {
                k++;                                                               // one more nearby fellow has been found

                v1_x_temp += (W2->get_x_velocity()) - (W1->get_x_velocity());      // taking into account W2's influence on W1's v1
                v1_y_temp += (W2->get_y_velocity()) - (W1->get_y_velocity());

                v2_x_temp += (W2->get_x()) - (W1->get_x());                        // taking into account W2's influence on W1's v2
                v2_y_temp += (W2->get_y()) - (W1->get_y());



                if ((W1->distance(W2)) < W1->get_contact_radius())                 // condition for v3 (OBSTACLES STILL TO BE DONE)
                {
                    kk++;                                                          // one more really near fellow has been found

                    v3_x_temp -= (W2->get_x()) - (W1->get_x());                    // taking into account W2's influence on W1's v3
                    v3_y_temp += (W2->get_y()) - (W1->get_y());
                }
            }
        }


        if (k!=0)
        {
            v1_x_temp /= k;
            v1_y_temp /= k;
            v2_x_temp /= k;
            v2_y_temp /= k;
        }

        if (kk!=0)
        {
            v3_x_temp /= kk;
            v3_y_temp /= kk;
        }


        // calculation and storage of the new velocity and position of W1
        W1 -> set_new_x_vel (W1->get_x_velocity() + step * (gamma1*v1_x_temp + gamma2*v2_x_temp + gamma3*v3_x_temp));
        W1 -> set_new_y_vel (W2->get_y_velocity() + step * (gamma1*v1_y_temp + gamma2*v2_y_temp + gamma3*v3_y_temp));

        W1 -> set_new_x (W1->get_x() + step * W1->get_new_x_vel());
        W1 -> set_new_y (W1->get_y() + step * W1->get_new_y_vel());

        
    }


    // Update Loop : used to update position and velocity values, once they've been calculated for each prey
    for (W1=Flock->get_head(); W1->get_next() != NULL; W1=W1->get_next())
    {
        W1->updateAll();
    }
    


	return 0;
}