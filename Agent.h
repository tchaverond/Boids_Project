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

    Agent(double, double);

    // =======================================================================
    //                                Destructor
    // =======================================================================
    virtual ~Agent(void);

    // =======================================================================
    //                            Accessors: getters
    // =======================================================================

    inline Agent* get_next(void) const;

    inline double get_perception_radius(void) const;

    inline double get_contact_radius(void) const;

    inline double get_x(void) const;

    inline double get_y(void) const;

    inline double get_x_velocity(void) const;

    inline double get_y_velocity(void) const;

    inline double get_new_x_vel(void) const;

    inline double get_new_y_vel(void) const;

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

    Agent* next;                    // for Linked List purposes

};


// ===========================================================================
//                              Getters' definitions
// ===========================================================================

Agent* Agent::get_next(void) const 
{
    return next;
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

