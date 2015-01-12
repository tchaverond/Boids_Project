#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Agent.h"
#include "Prey.h"
#include "Predator.h"
#include "Boid.h"
#include "bwindow.h"


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
    double vw_x_temp;              // temporary stockage value for vw_x
    double vw_y_temp;              // temporary stockage value for vw_y
    double v_angle_temp;           // temporary stockage value for angle of velocity

    double wind_force;

    double k;                      // number of near (perceived) agents                   
    double kk;                     // number of really (too) near agents



    Boid* Flock = new Boid ();                   // group of preys
    Boid* Enemies = new Boid ();                 // group of predators



    /**************************************         Parameters' Initialization          **************************************/

    width = 1000;
    height = 1000;

    step = 0.01;

    gamma1 = 1;
    gamma2 = 1;
    gamma3 = 3;



    /********************************************          Flock Creation          *******************************************/ 

    Prey* A = new Prey (100,100);
    Prey* B = new Prey (150,150);
    Prey* C = new Prey (180,170);
    Prey* D = new Prey (200,400);
    Prey* E = new Prey (300,350);
    Prey* F = new Prey (100,300);
    Prey* G = new Prey (250,150);
    Prey* H = new Prey (450,450);

    Predator* Marc_Yves = new Predator (150,150);

    Flock->append(A);
    Flock->append(B);
    Flock->append(C);
    Flock->append(D);
    Flock->append(E);
    Flock->append(F);
    Flock->append(G);
    Flock->append(H);


    Enemies->append(Marc_Yves);



    Agent* W1 = new Agent();       // the Wanderers Wi will browse through the flock
    Agent* W2 = new Agent();       // W1 is the current Agent, W2 is a fellow of W1

    v1_x_temp = 0;
    v1_y_temp = 0;
    v2_x_temp = 0;
    v2_y_temp = 0;
    v3_x_temp = 0;
    v3_y_temp = 0;
    vw_x_temp = 0;
    vw_y_temp = 0;
    v_angle_temp = 0;

    wind_force = 0;

    k = 0;
    kk = 0;


    // Test Loop
    for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
    {
        W1->showAll();
    }



    /********************************************          Window Creation          *******************************************/ 

    bwindow win(1000,1000);
    printf("%d\n",win.init());
    win.map();

    sleep(1);            // attempt to add a delay in order to wait until the window is ready before drawing sthg in it



    /***************************************************************************************************************************
    ************************************************          Main Loop         ************************************************
    ***************************************************************************************************************************/



    double i;
    for (;;)                        // infinite loop
    //for (i=0; i<100; i+=step)       // non-infinite (aka standard) loop
    {

        int ev = win.parse_event();
        switch(ev)
        {
            case BKPRESS :
            printf("keypressed\n"); 
            printf("key : %s\n",win.get_lastkey());
            break;
            case BBPRESS:
            printf("buttonpressed\n"); break;
            case BEXPOSE:
            printf("expose\n"); break;
            case BCONFIGURE:
            printf("configure\n"); break;
        }


        //win.draw_fsquare(0,0,1000,1000,0xFFFFFF);      // refreshing the window


        // epic loop begins here !
        for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
        {


            // re-initialization of stockage variables
            v1_x_temp = 0;
            v1_y_temp = 0;
            v2_x_temp = 0;
            v2_y_temp = 0;
            v3_x_temp = 0;
            v3_y_temp = 0;
            vw_x_temp = 0;
            vw_y_temp = 0;
            v_angle_temp = 0;
            wind_force = 0;

            for (W2=Flock->get_head(); W2 != NULL; W2=W2->get_next())
            {


                if ((W1->get_id() != W2->get_id()) && ((W1->distance(W2)) < W1->get_perception_radius()))  // condition for v1 & v2
                {
                    k++;                                                               // one more nearby fellow has been found

                    v1_x_temp += (W2->get_x_velocity()) - (W1->get_x_velocity());      // taking into account W2's influence on W1's v1
                    v1_y_temp += (W2->get_y_velocity()) - (W1->get_y_velocity());

                    v2_x_temp += (W2->get_x()) - (W1->get_x());                        // taking into account W2's influence on W1's v2
                    v2_y_temp += (W2->get_y()) - (W1->get_y());



                    if ((W1->distance(W2)) < W1->get_contact_radius())                 // condition for v3 (OBSTACLES STILL TO BE DONE)
                    {
                        kk++;                                                          // one more really near fellow has been found

                        v3_x_temp += (W2->get_x()) - (W1->get_x());                    // taking into account W2's influence on W1's v3
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


            // !!! wind effects yet to be applied !!!
            // calculation of the angle value
            /*v_angle_temp = 180/M_PI * atan(W1->get_y()-W1->get_x());
            // correction
            if (W1->get_x() < 0)
            {
                v_angle_temp += 180;
            }

            // upper frontier
            if (W1->get_y() < 50)
            {
                wind_force = 50/W1->get_y();
                if (v_angle_temp < 90)
                {
                    vw_y_temp = wind_force + cos(-45+v_angle_temp);
                    vw_y_temp = wind_force + cos(-45+v_angle_temp);
                }
                else
                {
                    vw_y_temp = wind_force + cos(45+v_angle_temp);
                    vw_y_temp = wind_force + cos(-45+v_angle_temp);
                }

            }
            // lower frontier
            if (W1->get_y() < height-50)
            {
                wind_force = 50/(height-W1->get_y());
                if (v_angle_temp < 90)
                {
                    vw_y_temp = wind_force + cos(-45+v_angle_temp);
                    vw_y_temp = wind_force + cos(-45+v_angle_temp);
                }
                else
                {
                    vw_y_temp = wind_force + cos(45+v_angle_temp);
                    vw_y_temp = wind_force + cos(-45+v_angle_temp);
                }

            }
            // left frontier
            if (W1->get_x() < 50)
            {

            }
            // right frontier
            if (W1->get_x() < width-50)
            {

            }*/



            // calculation and storage of the new velocity and position of W1
            W1 -> set_new_x_vel (W1->get_x_velocity() + step * (gamma1*v1_x_temp + gamma2*v2_x_temp + gamma3*v3_x_temp + vw_x_temp));
            W1 -> set_new_y_vel (W1->get_y_velocity() + step * (gamma1*v1_y_temp + gamma2*v2_y_temp + gamma3*v3_y_temp + vw_y_temp));

            W1 -> set_new_x (W1->get_x() + step * W1->get_new_x_vel());
            W1 -> set_new_y (W1->get_y() + step * W1->get_new_y_vel());

            
        }


        // Update Loop : used to update position and velocity values, once they've been calculated for each prey
        for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
        {
            W1->updateAll();
        }


        // Paint Loop : used to draw (the position of) each prey
        for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
        {
            win.draw_fsquare(W1->get_x()-2, W1->get_y()-2, W1->get_x()+2, W1->get_y()+2, 0xFF00000);
        }

        sleep(0.1); 

    }

    /********************************************          End of Main Loop         *******************************************/ 



    // Test Loop
    for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
    {
        W1->showAll();
    }

	return 0;
}