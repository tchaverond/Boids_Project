#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Agent.h"
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
    int nmax;
    double death_rate;             // predators' death rate
    double devour_delay;           // time that a predator spend to eat a prey

    double v1_x_temp;              // temporary stockage value for v1_x
    double v1_y_temp;              // temporary stockage value for v1_y
    double v2_x_temp;              // temporary stockage value for v2_x
    double v2_y_temp;              // temporary stockage value for v2_y
    double v3_x_temp;              // temporary stockage value for v3_x
    double v3_y_temp;              // temporary stockage value for v3_y
    double v3o_x_temp;             // temporary stockage value for v3_x_o (part of obstacles, used for both preys and predators)
    double v3o_y_temp;             // temporary stockage value for v3_y_o (part of obstacles, used for both preys and predators)
    double v4_x_temp;              // temporary stockage value for v4_x
    double v4_y_temp;              // temporary stockage value for v4_y

    int easiestprey_id;                  // temporary stockage value of the id of the nearest prey for the predator to eat
    double prey_distance;                // temporary stockage value of the distance prey-predator
    Agent* easiestprey = new Agent();    // temporary stockage value of the nearest prey


    double k;                      // number of near (perceived) agents                   
    double kk;                     // number of really (too) near agents
    double o;                      // number of near obstacles

    int Flock_size;                // size of the initial flock
    int Obstacle_number;           // number of obstacles on screen

    int j;

    int blessing;            // used to know whenever a prey is born
    int demise;              // used to know whenever a predator dies

    


    /**************************************         Parameters' Initialization          **************************************/

    width = 1100;
    height = 900;

    step = 0.2;

    gamma1 = 0.0006;
    gamma2 = 0.0005;
    gamma3 = 0.004;
    gamma4 = 2;
    mu = 0.0001;
    nmax = 400;
    death_rate = 0.0003;

    blessing = 0;
    demise = 0;

    devour_delay = 2000;

    Flock_size = 10;
    Obstacle_number = 10;




    /********************************************          Flock Creation          *******************************************/

    // type_id = 1  <=> Agent is a prey
    // type_id = 2  <=> Agent is a predator 

    Agent* A = new Agent (700,700,1);

    Agent* Marc_Yves = new Agent (500,500,2);


    Boid* Flock = new Boid (A);                           // group of preys

    srand(42);

    for (j=0; j<Flock_size; j++)
    {
        Flock->append(new Agent (width*(((double)rand())/RAND_MAX), height*(((double)rand())/RAND_MAX), 1));
    }

    Boid* Enemies = new Boid (Marc_Yves);                 // group of predators


    Agent* Eiffel_Tower = new Agent (550,450,5,5);
    Boid* Obstacles = new Boid (Eiffel_Tower);
    for (j=0; j<Obstacle_number; j++)
    {
        Obstacles->append(new Agent (width*(((double)rand())/RAND_MAX), height*(((double)rand())/RAND_MAX), 5+15*(((double)rand())/RAND_MAX), 5+15*(((double)rand())/RAND_MAX)));
    }



    /*******************************************          Other Initialization         ******************************************/



    Agent* W1 = new Agent();           // the Wanderers Wi will browse through the flock
    Agent* W2 = new Agent();           // W1 is the current Agent, W2 is a fellow of W1
    Agent* WP = new Agent();           // Wanderer of the predators
    Agent* WO = new Agent();           // Wanderer of the obstacles

    v1_x_temp = 0;
    v1_y_temp = 0;
    v2_x_temp = 0;
    v2_y_temp = 0;
    v3_x_temp = 0;
    v3_y_temp = 0;
    v3o_x_temp = 0;
    v3o_y_temp = 0;
    v4_x_temp = 0;
    v4_y_temp = 0;

    easiestprey_id = -1;
    prey_distance = 1000;

    k = 0;
    kk = 0;
    o = 0;


    // Test Loop
    for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
    {
        W1->showAll();
    }
    // Test Loop
    for (W1=Obstacles->get_head(); W1 != NULL; W1=W1->get_next())
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

        /********** Natural birth of preys **********/

        if (blessing == (int) (1/(mu * Flock->getnb_elts() * (1-(Flock->getnb_elts()/nmax)))))
        {
            Flock -> append(new Agent (width*(((double)rand())/RAND_MAX), height*(((double)rand())/RAND_MAX), 1));
            blessing = 0;
        } else {
            blessing++;
            //printf("%d\n",demise);
        }

        // preventing mistakes due to death of a prey with a 'bad' timing
        if (blessing > 2/(mu * Flock->getnb_elts() * (1-(Flock->getnb_elts()/nmax))))
        {
            blessing = 0;
        }


        /**********     **********/


        for (W1=Flock->get_head(); W1 != NULL; W1=W1->get_next())
        {

            // re-initialization of stockage variables
            v1_x_temp = 0;
            v1_y_temp = 0;
            v2_x_temp = 0;
            v2_y_temp = 0;
            v3_x_temp = 0;
            v3_y_temp = 0;
            v3o_x_temp = 0;
            v3o_y_temp = 0;
            v4_x_temp = 0;
            v4_y_temp = 0;
            k = 0;
            kk = 0;
            o = 0;

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

            // obstacles' influence on preys
            for (WO=Obstacles->get_head(); WO != NULL; WO=WO->get_next())
            {
                if (W1->distanceObs(WO) < W1->get_contact_radius())
                {
                    o++;

                    v3o_x_temp += (W1->get_x() - WO->get_x());
                    v3o_y_temp += (W1->get_y() - WO->get_y());
                }
            }

            if (o!=0)
            {
                v3o_x_temp /= o;
                v3o_y_temp /= o;
            }

            v3_x_temp += 10*v3o_x_temp;
            v3_y_temp += 10*v3o_y_temp;


            // predators' influence on preys
            for (WP=Enemies->get_head(); WP != NULL; WP=WP->get_next())
            {
                if (W1->distance(WP) < W1->get_perception_radius())
                {
                    v4_x_temp -= ((WP->get_x()-W1->get_x()) / (sqrt(((WP->get_x()-W1->get_x()) * (WP->get_x()-W1->get_x())) + ((WP->get_y()-W1->get_y()) * (WP->get_y()-W1->get_y())))));
                    v4_y_temp -= ((WP->get_y()-W1->get_y()) / (sqrt(((WP->get_x()-W1->get_x()) * (WP->get_x()-W1->get_x())) + ((WP->get_y()-W1->get_y()) * (WP->get_y()-W1->get_y())))));
                }
            }




            // calculation and storage of the new velocity and position of W1
            W1 -> set_new_x_vel (W1->get_x_velocity() + step * (gamma1*v1_x_temp + gamma2*v2_x_temp + gamma3*v3_x_temp + gamma4*v4_x_temp));
            W1 -> set_new_y_vel (W1->get_y_velocity() + step * (gamma1*v1_y_temp + gamma2*v2_y_temp + gamma3*v3_y_temp + gamma4*v4_y_temp));

            W1 -> set_new_x (W1->get_x() + step * W1->get_new_x_vel());
            W1 -> set_new_y (W1->get_y() + step * W1->get_new_y_vel());

           
            // Wind Effect
            W1 -> applyWind(height,width,step);
        }





        /*********************************************         Predator Loop           ********************************************/

        
        /********** Natural death of predators **********/
        
        if (demise == (int) (1/(death_rate*Enemies->getnb_elts())))
        {
            if (Enemies->getnb_elts() > 1)
            {
                Enemies -> remove(Enemies->get_head()->get_next());
            }
            demise = 0;
        } else {
            demise ++;
            //printf("%d\n",demise);
        }

        // preventing mistakes due to creation of a new predator with a 'bad' timing
        if (demise > 2/(death_rate*Enemies->getnb_elts()))
        {
            demise = 0;
        }

        /**********     **********/


        for (WP=Enemies->get_head(); WP != NULL; WP=WP->get_next())
        {

            // re-initialization of stockage variables
            easiestprey_id = -1;
            prey_distance = 1000;
            easiestprey = NULL;


            // providing the predator isn't currently eating a prey
            if (WP->get_devour_time() > devour_delay)
            {

                for (W2=Flock->get_head(); W2 != NULL; W2=W2->get_next())
                {
                    
                    // getting which prey is the nearest one
                    if ((WP->distance(W2) < WP->get_perception_radius()) && (WP->distance(W2) < prey_distance))
                    {
                        prey_distance = WP->distance(W2);
                        easiestprey_id = W2->get_id(); 
                    }
                }

                // if the prey is near enough to be eaten
                if (prey_distance < WP->get_devour_radius())
                {
                    // death of the prey
                    Flock -> remove(Flock->select(easiestprey_id));
                    WP -> lunchTime();
                    // creation of a new predator at a random position
                    Enemies -> append(new Agent (width*(((double)rand())/RAND_MAX), height*(((double)rand())/RAND_MAX), 2));
                } 
                else 
                {
                    // if one prey has been noticed by the predator
                    if (easiestprey_id != -1)
                    {
                        easiestprey = Flock->select(easiestprey_id);
                        WP -> huntPrey(easiestprey);                 // setting predator velocity according to the location of the easiest prey
                        //printf("%d\n",easiestprey_id);
                    }

                    else
                    {
                        WP -> set_new_x_vel (WP->get_x_velocity() + 0.5*step*((2*(((double)rand())/(RAND_MAX)))-1));
                        WP -> set_new_y_vel (WP->get_y_velocity() + 0.5*step*((2*(((double)rand())/(RAND_MAX)))-1));
                    }

                }

                // obstacles' influence on predators
                v3o_x_temp = 0;
                v3o_y_temp = 0;
                o = 0;
                for (WO=Obstacles->get_head(); WO != NULL; WO=WO->get_next())
                {
                    if (WP->distanceObs(WO) < WP->get_contact_radius())
                    {
                        o++;
                        v3o_x_temp += (WP->get_x() - WO->get_x());
                        v3o_y_temp += (WP->get_y() - WO->get_y());
                    }
                }

                if (o!=0)
                {
                    v3o_x_temp /= o;
                    v3o_y_temp /= o;
                }

                WP -> set_new_x_vel (WP->get_new_x_vel() + step*v3o_x_temp);
                WP -> set_new_y_vel (WP->get_new_y_vel() + step*v3o_y_temp);


                // calculation and storage of the new position of WP
                WP -> set_new_x (WP->get_x() + step * WP->get_new_x_vel());
                WP -> set_new_y (WP->get_y() + step * WP->get_new_y_vel());

                WP -> applyWind(height,width,step);

            }
            // if this predator is busy eating a prey
            else
            {
                WP -> lunchProgress();      // it carries on eating it
            }
            

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
        for (WO=Obstacles->get_head(); WO != NULL; WO=WO->get_next())
        {
            win.draw_fsquare(WO->get_x(), WO->get_y(), WO->get_x()+WO->get_size_x(), WO->get_y()+WO->get_size_y(), 0x000000);
        }

        win.change_title(Flock->getnb_elts(), Enemies->getnb_elts());

        usleep(1500); 

    }

    /***************************************************************************************************************************
    *********************************************          End Of Main Loop         ********************************************
    ***************************************************************************************************************************/

}