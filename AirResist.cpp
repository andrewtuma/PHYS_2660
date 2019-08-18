/ Name: Andrew Tuma                                                                                                                                    
// UserId: alt3zq                                                                                                                                       
// Homework #: 11                                                                                                                                       
// Problem #: 2                                                                                                                                         
// Program Name: alt3zq_airresist.cpp                                                                                                                   
// Pledge Signature: I did not receive unauthorized aid on this assignment. -Andrew Tuma                                                                


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "random.hpp"
#include "hist.hpp"

const double g = 9.81;
const double time_step = 0.1;
const double koverm = 0.2;
const double pi = 3.14;
const int N = 100;

void position();

void velocity();

void acceleration();

double x,y,t,vx,vy,ax,ay,k_m;
int main (int argc, char *argv[]) {

  FILE *output;
  output = fopen("airresist.dat", "w");

  srand(time(NULL));
  int entries = 0;
  double mean = 0;
  double std_dev = 0;
  double angle;
  double v0;
  h1 ranges;
  h1init(&ranges,100, 0., 1000., "ranges");

  angle = atof(argv[1]);
  v0 = atof(argv[2]);

  for (int i=0; i<N; i++) {
    t = 0;
    x = 0;
    y = 0;
    k_m = koverm + 0.2*((double)rand()/(double)RAND_MAX*2-1);
    vx = v0*cos(angle*(2.*pi/360.));
    vy = v0*sin(angle*(2.*pi/360.));

      while(y>=0) {
        velocity();
        position();
        acceleration();
        t+=time_step;
        fprintf(output,"%lf %lf %lf %lf %lf\n", t, x, y, vx, vy);
      }
    printf("%lf %lf %lf %lf %lf\n", t, x, y, vx, vy);
    h1fill(&ranges, x);
  }
  h1plot(&ranges);
  h1stats(&ranges,&entries, &mean, &std_dev);
  printf("Stats for hist: entries = %d mean = %lf std_dev = %lf\n",entries, mean, std_dev);

  fclose(output);
  return 0;
}


void position() {

  x += vx * time_step;
  y += vy * time_step;

}

void velocity() {

  vy += ay * time_step;
  vx += ax * time_step;
}

void acceleration() {

  ax = -vx*k_m;
  ay = -vy*k_m - g;
}
