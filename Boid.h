#ifndef __Boid_H__
#define __Boid_H__

#include "Agent.h"


class Boid
{
 protected :
  Agent* head;
  int nb_elts;
  ;

 public :
  Boid(void);
  //Boid(const Boid&);
  ~Boid(void);
  int getnb_elts(void);
  void append (Agent*);
  void remove (Agent*);

};

#endif