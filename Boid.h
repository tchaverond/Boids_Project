//****************************************************************************
//
//
//
//****************************************************************************



#ifndef __Boid_H__
#define __Boid_H__


// ===========================================================================
//                                  Libraries
// ===========================================================================
#include <cstdio>
#include <cstdlib>



// ===========================================================================
//                                Project Files
// ===========================================================================

#include "Agent.h"


// ===========================================================================
//                              Class declarations
// ===========================================================================






class Boid
{
  public :
    
    // =======================================================================
    //                                 Enums
    // =======================================================================
    
    // =======================================================================
    //                               Constructors
    // =======================================================================
    
    Boid (Agent*);

    // =======================================================================
    //                                Destructor
    // =======================================================================
    ~Boid(void);

    // =======================================================================
    //                            Accessors: getters
    // =======================================================================

    inline int getnb_elts(void) const;

    inline Agent* get_head (void) const;

    // =======================================================================
    //                            Accessors: setters
    // =======================================================================

    // =======================================================================
    //                                Operators
    // =======================================================================

    // =======================================================================
    //                              Public Methods
    // =======================================================================

    void append (Agent*);
    void remove (Agent*);
    Agent* select (int);

    // =======================================================================
    //                             Public Attributes
    // =======================================================================





  protected :

    // =======================================================================
    //                            Forbidden Constructors
    // =======================================================================
    Boid(void)
    {
      printf("%s:%d: error: call to forbidden constructor.\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    };
    Boid(const Boid &model)
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

    Agent* head;
    int nb_elts;


};


// ===========================================================================
//                              Getters' definitions
// ===========================================================================

int Boid::getnb_elts (void) const
{
	return nb_elts;
}

Agent* Boid::get_head (void) const
{
    return head; 
}

// ===========================================================================
//                              Setters' definitions
// ===========================================================================

// ===========================================================================
//                             Operators' definitions
// ===========================================================================

// ===========================================================================
//                          Inline functions' definition
// ===========================================================================


#endif // __Boid_H__

