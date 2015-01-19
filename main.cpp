#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Agent.h"
//#include "Prey.h"
//#include "Predator.h"
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
    double v4_x_temp;              // temporary stockage value for v4_x
    double v4_y_temp;              // temporary stockage value for v4_y
    double vp_x_temp;              // temporary stockage value for vp_x
    double vp_y_temp;              // temporary stockage value for vp_y

    int easiestprey_id;                  // temporary stockage value of the id of the nearest prey for the predator to eat
    double prey_distance;                // temporary stockage value of the distance prey-predator
    Agent* easiestprey = new Agent();    // temporary stockage value of the nearest prey


    double k;                      // number of near (perceived) agents                   
    double kk;                     // number of really (too) near agents

    int Flock_size;

    


    /**************************************         Parameters' Initialization          **************************************/

    width = 800;
    height = 800;

    step = 0.6;

    gamma1 = 5;
    gamma2 = 7;
    gamma3 = 20;

    Flock_size = 200;




    /********************************************          Flock Creation          *******************************************/

    // type_id = 0 <=> Agent is a prey
    // type_id = 1 <=> Agent is a predator 

    Agent* A = new Agent (700,700,0);
    /*Prey* B = new Prey (720,720);
    Prey* C = new Prey (740,740);
    Prey* D = new Prey (200,400);
    Prey* E = new Prey (300,350);
    Prey* F = new Prey (100,300);
    Prey* G = new Prey (250,150);
    Prey* H = new Prey (450,450);
    Prey* I = new Prey (600,741);
    Prey* J = new Prey (703,120);
    Prey* K = new Prey (708,354);*/

    Agent* Marc_Yves = new Agent (500,500,1);

    Boid* Flock = new Boid (A);                           // group of preys
    /*Flock->append(B);
    Flock->append(C);
    Flock->append(D);
    Flock->append(E);
    Flock->append(F);
    Flock->append(G);
    Flock->append(H);
    Flock->append(I);
    Flock->append(J);
    Flock->append(K);*/
    srand(42);
    double j;
    for (j=0; j<Flock_size; j++)
    {
        Flock->append(new Agent (800*(((double)rand())/RAND_MAX), 800*(((double)rand())/RAND_MAX), 0));
    }

    Boid* Enemies = new Boid (Marc_Yves);                 // group of predators



    Agent* W1 = new Agent();           // the Wanderers Wi will browse through the flock
    Agent* W2 = new Agent();           // W1 is the current Agent, W2 is a fellow of W1
    Agent* WP = new Agent();           // Wanderer of the predators

    v1_x_temp = 0;
    v1_y_temp = 0;
    v2_x_temp = 0;
    v2_y_temp = 0;
    v3_x_temp = 0;
    v3_y_temp = 0;
    v4_x_temp = 0;
    v4_y_temp = 0;

    easiestprey_id = -1;
    prey_distance = 1000;

    k = 0;
    kk = 0;


    // Test Loop
    for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
    {
        W1->showAll();
    }



    /********************************************          Window Creation          *******************************************/ 

    bwindow win(width,height);
    printf("%d\n",win.init());
    win.map();

    //sleep(1);            // attempt to add a delay in order to wait until the window is ready before drawing sthg in it



    /***************************************************************************************************************************
    ************************************************          Main Loop         ************************************************
    ***************************************************************************************************************************/



    for (;;)                        // infinite loop
    //double i;
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


        


        /**********************************************         Prey Loop           *********************************************/

        for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
        {


            // re-initialization of stockage variables
            v1_x_temp = 0;
            v1_y_temp = 0;
            v2_x_temp = 0;
            v2_y_temp = 0;
            v3_x_temp = 0;
            v3_y_temp = 0;
            v4_x_temp = 0;
            v4_y_temp = 0;

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

                        v3_x_temp += (W1->get_x()) - (W2->get_x());                    // taking into account W2's influence on W1's v3
                        v3_y_temp += (W1->get_y()) - (W2->get_y());
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


            // predator's influence on preys
            for (WP=Enemies->get_head(); WP != NULL; WP=WP->get_next())
            {
                
            }




            // calculation and storage of the new velocity and position of W1
            W1 -> set_new_x_vel (W1->get_x_velocity() + step * (gamma1*v1_x_temp + gamma2*v2_x_temp + gamma3*v3_x_temp));
            W1 -> set_new_y_vel (W1->get_y_velocity() + step * (gamma1*v1_y_temp + gamma2*v2_y_temp + gamma3*v3_y_temp));

            W1 -> set_new_x (W1->get_x() + step * W1->get_new_x_vel());
            W1 -> set_new_y (W1->get_y() + step * W1->get_new_y_vel());

           
            // Wind Effect
            W1 -> applyWind(height,width,step);
        }





        /*********************************************         Predator Loop           ********************************************/

        for (WP=Enemies->get_head(); WP != NULL; WP=WP->get_next())
        {

            // re-initialization of stockage variables
            vp_x_temp = 0;
            vp_y_temp = 0;
            easiestprey_id = -1;
            prey_distance = 1000;
            easiestprey = NULL;

            for (W2=Flock->get_head(); W2 != NULL; W2=W2->get_next())
            {
                
                // getting which prey is the nearest one
                if ((WP->distance(W2) < WP->get_perception_radius()) && (WP->distance(W2) < prey_distance))
                {
                    prey_distance = WP->distance(W2);
                    easiestprey_id = W2->get_id(); 
                }
            }

            // if one prey has been noticed by the predator
            if (easiestprey_id != -1)
            {
                easiestprey = Flock->select(easiestprey_id);
                WP -> huntPrey(easiestprey);                 // setting predator velocity according to the location of the easiest prey
                printf("%d\n",easiestprey_id);
            }

            // else the predator moves randomly across the world
            else
            {
                //WP -> set_new_x_vel ((2*(((double)rand())/(RAND_MAX)))-1);
                //WP -> set_new_y_vel ((2*(((double)rand())/(RAND_MAX)))-1);
                WP -> set_new_x_vel (0);  
                WP -> set_new_y_vel (0);
            }

            // calculation and storage of the new position of WP
            WP -> set_new_x (WP->get_x() + step * WP->get_new_x_vel());
            WP -> set_new_y (WP->get_y() + step * WP->get_new_y_vel());

            WP -> applyWind(height,width,step);

        }




        /**********************************************         Update Loops           *********************************************/

        for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
        {
            W1->updateAll();
        }

        for (WP=Enemies->get_head(); WP != NULL; WP=WP->get_next())
        {
            WP->updateAll();
        }

    
        


        /***********************************************         Paint Loops           **********************************************/

        win.draw_fsquare(0,0,width,height,0xFFFFFF);      // refreshing the window

        for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
        {
            win.draw_fsquare(W1->get_x()-2, W1->get_y()-2, W1->get_x()+2, W1->get_y()+2, 0x228B22);
        }

        for (WP=Enemies->get_head(); WP != NULL; WP=WP->get_next())
        {
            win.draw_fsquare(WP->get_x()-2, WP->get_y()-2, WP->get_x()+2, WP->get_y()+2, 0xFF0000);
        }

        //sleep(0.1); 

        // Test Loop
        /*for ((W1=Flock->get_head())->get_next(); W1 != NULL; W1=W1->get_next())
        {
            W1->showAll();
        }*/ 

    }

    /***************************************************************************************************************************
    *********************************************          End Of Main Loop         ********************************************
    ***************************************************************************************************************************/



    // Test Loop
    /*for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
    {
        W1->showAll();
    }

	return 0;*/
}