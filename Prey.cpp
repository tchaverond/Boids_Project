//****************************************************************************
//
//
//
//****************************************************************************


 
 
// ===========================================================================
//                                   Libraries
// ===========================================================================



// ===========================================================================
//                                 Project Files
// ===========================================================================
#include "Prey.h"




//############################################################################
//                                                                           #
//                           Class Prey                            #
//                                                                           #
//############################################################################

// ===========================================================================
//                         Definition of static attributes
// ===========================================================================

int Prey::headcount = 0;

// ===========================================================================
//                                  Constructors
// ===========================================================================
Prey::Prey(double init_x, double init_y) : Agent (init_x, init_y)
{

	headcount ++;
	printf("Prey created succesfully !\n");
}

// ===========================================================================
//                                  Destructor
// ===========================================================================
Prey::~Prey(void)
{
}

// ===========================================================================
//                                 Public Methods
// ===========================================================================

// ===========================================================================
//                                Protected Methods
// ===========================================================================

// ===========================================================================
//                               Non inline accessors
// ===========================================================================
