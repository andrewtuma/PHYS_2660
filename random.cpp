// File: random.hpp                                                                                                                                     
// implementation file for random number tools                                                                                                          

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "random.hpp"

// return a uniformly distributed random number                                                                                                         
// in the range min <= num <= max                                                                                                                       
double randu(double min, double max){
  static int first = 1;          // preserve value between calls                                                                                        
  if (first) {                   // initialize generator on 1st call                                                                                    
    first = 0;
    srand(time((time_t)NULL));
  }
  return (double)rand()/RAND_MAX * (max-min) + min;
}

// return a normally distributed number                                                                                                                 
double randn(double mean, double sigma){
  static int get_u = 1;  // flag to generate 2 uniform values                                                                                           
  static double u1;
  static double u2;
  double n;
  if (get_u) {
    do { u1 = randu(0.,1.0); } while ( !u1 );
    u2 = randu(0.,1.0);
    get_u = 0;
    n = sqrt(-2*log(u1))*cos(2*M_PI*u2);
  }
  else {
    get_u = 1;
    n = sqrt(-2*log(u1))*sin(2*M_PI*u2);
  }
  return n * sigma + mean;
}

int randbin(int n, double p){
  int pass=0;
  for (int i=1; i<=n; i++){
    if ( randu(0.,1.) < p ) pass++;
  }
  return pass;
}


// return a uniformly distributed integer in the given range                                                                                            
int randui(int min, int max){
  double range = max-min + 1.0;
  return (int) (range*rand()/(RAND_MAX+1.0)) + min;
}

