// Name:   Andrew Tuma                                                                                                                                  
// UserId: alt3zq                                                                                                                                       
// Homework #: 12                                                                                                                                       
// Problem #: 1                                                                                                                                         
// Program Name: alt3zq_bite.cpp                                                                                                                        
// Pledge Signature: I did not give or receive unauthorized aid on this assignment. -Andrew Tuma                                                        

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random.hpp"
#include "hist.hpp"
const int TRIALS = 500;

int randui();

int main(int argc, char *argv[]) {

  int METERS = atoi(argv[1]);
  int bites=0;
  int safe=0;
  h1 trials1;
  h1 trials2;
  h1init(&trials1, 100, 0., 3000., "trials1");
  h1labels(&trials1, "X (trials)", "Y (bites)", "2500M Walk");
  h1init(&trials2, 100, 0., 300., "trials2");
  h1labels(&trials2, "X (trials)", "Y (bites)", "200M Walk");

  if (argc < 2) {
    printf("Please enter a distance in meters.\n");
    return 1;
  } else {
  for (int j = 0; j < TRIALS; j++) {
    bites = 0;
    for (int m = 0; m < METERS; m++) {
      for (int t = 0; t < 100; t++) {
        if (randui(0, 10000) < 100) {
         bites++;
        } else if (randui(0,10000) < 10000) {
          safe++;
        }
      }
   }
    if (METERS > 200) {
    h1fill(&trials1, bites);
    } else if (METERS <= 200) {
      h1fill(&trials2, bites);
    }
  }

  if (METERS > 200) {
  h1plot(&trials1);
  } else if (METERS <= 200) {
    h1plot(&trials2);
  }
  }
  return 0;
}
