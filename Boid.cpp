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
#include "Boid.h"
#include "Agent.h"




//############################################################################
//                                                                           #
//                           Class Boid                          #
//                                                                           #
//############################################################################

// ===========================================================================
//                         Definition of static attributes
// ===========================================================================


// ===========================================================================
//                                  Constructors
// ===========================================================================

Boid::Boid(Agent* pioneer)
{
  head = pioneer;
  nb_elts = 1;
}

// ===========================================================================
//                                  Destructor
// ===========================================================================

Boid::~Boid(void)
{
  Agent* i = NULL;
  for (i=head; i->get_next()!=NULL; i=i->get_next())
    {
      delete (i);
    }
}

// ===========================================================================
//                                 Public Methods
// ===========================================================================

void Boid::append (Agent* element)
{
  Agent* i = NULL;
  for (i=head; i->get_next()!=NULL; i=i->get_next())
    {}
  i->set_next(element);
  element->set_next(NULL);
  nb_elts++;
  //printf("%d\n",nb_elts);
}

void Boid::remove (Agent* element)
{
  Agent* i = head;
  while ((i->get_next()!=element) && (i->get_next()!=NULL))
    {
      i = i->get_next();
    }
  if (i->get_next()==element)
    {
      i->set_next(element->get_next());
      delete(element);
      nb_elts--;
      //printf("%d\n",nb_elts);
    }
}

Agent* Boid::select (int id)
{
  Agent* i = NULL;
  for (i=head; i->get_id() != id; i=i->get_next())
    {}
  return i;
}

// ===========================================================================
//                                Protected Methods
// ===========================================================================

// ===========================================================================
//                               Non inline accessors
// ===========================================================================
