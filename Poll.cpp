// Name: Andrew Tuma                                                                                                                                    
// UserId: alt3zq                                                                                                                                       
// Homework #: 11                                                                                                                                       
// Problem #: 1                                                                                                                                         
// Program Name: alt3zq_polls.cpp                                                                                                                       
// Pledge Signature: I did not receive unauthorized aid on this assignment. -Andrew Tuma                                                                

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "random.hpp"
#include "hist.hpp"
const int N = 10000;

int main () {
  FILE *output;
  output = fopen("Earthisflat.dat", "w");

  int j = 0;
  int k = 0;
  int p = 0;
  int l = 0;
  h1 Other;
  h1 Flat;
  h1 NotSure;
  h1 Round;
  h1init(&Other, 100, 0., 100., "Other");
  h1init(&Flat, 100, 0., 100., "Flat");
  h1init(&NotSure, 100, 0., 100., "NotSure");
  h1init(&Round, 100, 0., 100., "Round");
  srand(time(NULL));

  for (int a = 0; a<N; a++) {
    for (int c = 0; c<1420; c++) {
      j=0;
      k=0;
      p=0;
      l=0;
      for (int t =0; t<100; t++) {
        double i = (double)rand()/(double)RAND_MAX;
        if (i>0. && i<0.03) {
          j++;
        } else if (i >= 0.03 && i<0.21) {
          k++;
        } else if (i >= 0.21 && i < 0.22) {
          p++;
        } else if (i >=0.22 && i<1.00) {
          l++;
        }
      }
    }
    h1fill(&Other, j);
    h1fill(&Flat, k);
    h1fill(&NotSure, p);
    h1fill(&Round, l);
    fprintf(output,"%d %d %d %d\n", l, k, p, j);
  }
  h1plot(&Other);
  h1plot(&Flat);
  h1plot(&NotSure);
  h1plot(&Round);
  fclose(output);
  return 0;
}


//The distributions appear to be normal, though it is harder to see on the answers that are less than 5% frequency, because you can't have the negative\
 portion of the percentages. However, when looking at the answer choices such as the earth is flat and the earth is round, you can see the full bell cu\
rve. You can see that in most cases the most frequent percentage is the one that was originially found in the study, which is to be expected. The curve\
s also become more easily seen as the number of trials, N, is increased. Eventually, with enough trials, you could probably get a very smooth curve.    


