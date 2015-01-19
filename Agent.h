//****************************************************************************
//
//
//
//****************************************************************************



#ifndef __Agent_H__
#define __Agent_H__


// ===========================================================================
//                                  Libraries
// ===========================================================================
#include <cstdio>
#include <cstdlib>



// ===========================================================================
//                                Project Files
// ===========================================================================




// ===========================================================================
//                              Class declarations
// ===========================================================================






class Agent
{
  public :
    
    // =======================================================================
    //                                 Enums
    // =======================================================================
    
    // =======================================================================
    //                               Constructors
    // =======================================================================
    
    Agent(void);              // should only be used as a fictitious Agent to browse through the boid (seen as a Linked List)

    Agent(double, double, int);

    // =======================================================================
    //                                Destructor
    // =======================================================================
    ~Agent(void);

    // =======================================================================
    //                            Accessors: getters
    // =======================================================================

    inline Agent* get_next(void) const;

    inline int get_id(void) const;

    inline double get_perception_radius(void) const;

    inline double get_contact_radius(void) const;

    inline double get_x(void) const;

    inline double get_y(void) const;

    inline double get_x_velocity(void) const;

    inline double get_y_velocity(void) const;

    inline double get_new_x_vel(void) const;

    inline double get_new_y_vel(void) const;

    inline double get_devour_radius(void) const;

    inline double get_devour_time(void) const;

    // =======================================================================
    //                            Accessors: setters
    // =======================================================================

    inline void set_next(Agent*);

    inline void set_new_x(double);

    inline void set_new_y(double);

    inline void set_new_x_vel(double);

    inline void set_new_y_vel(double);

    // =======================================================================
    //                                Operators
    // =======================================================================

    // =======================================================================
    //                              Public Methods
    // =======================================================================

    double distance(Agent*);

    void updateAll(void);

    void showAll(void);

    void applyWind(double, double, double);

    void huntPrey(Agent*);

    void lunchTime(void);

    void lunchProgress(void);

    // =======================================================================
    //                             Public Attributes
    // =======================================================================





  protected :

    // =======================================================================
    //                            Forbidden Constructors
    // =======================================================================
    /*Agent(void)
    {
      printf("%s:%d: error: call to forbidden constructor.\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    };*/
    Agent(const Agent &model)
    {
      printf("%s:%d: error: call to forbidden constructor.\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    };


    // =======================================================================
    //                              Protected Methods
    // =======================================================================

    // =======================================================================
    //                             Protected Attributes
    // =======================================================================

    static int total_headcount;

    int id;                        // unique id for each agent, for Linked List purposes 
    int type_id;                   // defines whether the agent is a prey or a predator (0 = prey, 1 = predator)

    double x;
    double new_x;
    double y;
    double new_y;
    double x_velocity;
    double y_velocity;
    double new_x_vel;
    double new_y_vel;

    double perception_radius;       // | static potential |
    double contact_radius;


    // Predator-specific variables
    double devour_radius;
    double devour_time;
    double hunt_speed;

    Agent* next;                    // for Linked List purposes

};


// ===========================================================================
//                              Getters' definitions
// ===========================================================================

Agent* Agent::get_next(void) const 
{
    return next;
}

int Agent::get_id(void) const
{
    return id;
}

double Agent::get_perception_radius(void) const
{
    return perception_radius;
}

double Agent::get_contact_radius(void) const
{
    return contact_radius;
}

double Agent::get_x(void) const
{
    return x;
}

double Agent::get_y(void) const
{
    return y;
}

double Agent::get_x_velocity(void) const
{
    return x_velocity;
}

double Agent::get_y_velocity(void) const
{
    return y_velocity;
}

double Agent::get_new_x_vel(void) const
{
    return new_x_vel;
}

double Agent::get_new_y_vel(void) const
{
    return new_y_vel;
}

double Agent::get_devour_radius(void) const
{
    return devour_radius;
}

double Agent::get_devour_time(void) const
{
    return devour_time;
}


// ===========================================================================
//                              Setters' definitions
// ===========================================================================

void Agent::set_next(Agent* new_next)
{
    this->next = new_next;
}

void Agent::set_new_x(double new_value)
{
    new_x = new_value;
}

void Agent::set_new_y(double new_value)
{
    new_y = new_value;
}

void Agent::set_new_x_vel(double new_value)
{
    new_x_vel = new_value;
}

void Agent::set_new_y_vel(double new_value)
{
    new_y_vel = new_value;
}

// ===========================================================================
//                             Operators' definitions
// ===========================================================================

// ===========================================================================
//                          Inline functions' definition
// ===========================================================================


#endif // __Agent_H__

