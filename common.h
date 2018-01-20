#ifndef COMMON_H
#define COMMON_H

// #include "stdafx.h"
#include <iostream>
#include "time.h"
#include <math.h>


static double in_bound = 10.0;
static double out_bound = 20.0;

enum Status{idle, candiate, inBound, outBound, clusterHead};

// Calculate Eclidean Distance to the power 2 , //NOTE no sqrt cause it is expensive!!
static double euclidean_dist2(double x1, double y1, double x2, double y2)
{
	return ((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

static void counter(int seconds)
{
	clock_t endTurn = clock() + seconds * CLOCKS_PER_SEC;
	while(clock() < endTurn){}
}

struct candidacy_msg
{
	double x;
	double y;
	uint32_t id;
	candidacy_msg(double xx,double yy,uint32_t ii){x = xx; y = yy; id = ii;}
};

class draw_object
{
public:
	draw_object(double xx, double yy, uint32_t ii)
	{x = xx; y= yy; cluster_id = ii;}
	double x;
	double y;
	uint32_t cluster_id;
};

static int poisson ( double lambda )
{
  double u = drand48();
  int k = 0;
  double sum = exp(-lambda);

  double sidste = sum;

  while ( true )
    {
      if ( u < sum ) { return k; }
      else 
	{
	  k++;
	  sidste *= lambda/k;
	  sum += sidste;
	}
    }
}
#endif // COMMON_H
