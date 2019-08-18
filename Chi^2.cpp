// Name:   Andrew Tuma                                                                                                                                  
// UserId: alt3zq                                                                                                                                       
// Homework #: 13                                                                                                                                       
// Problem #: 1                                                                                                                                         
// Program Name: alt3zq_chi2fit.cpp                                                                                                                     
// Pledge Signature: I have not given or received unauthorized aid on this assingment.                                                                  

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hist.hpp"



int main () {

  FILE *input = fopen("data.dat", "r");
  FILE *inptr = fopen("bkgd_templates.dat", "r");
  FILE *inpur = fopen("signal_templates.dat", "r");

  int i=0;
  double a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,k=0;
  char buf[500];
  h1 A;
  h1 B;
  h1 C;
  h1 D;
  h1 E;
  h1 F;
  h1 G;
  h1 H;
  h1 K;

  h1 A1;
  h1 B1;
  h1 C1;
  h1 D1;
  h1 E1;
  h1 F1;
  h1 G1;
  h1 H1;
  h1 K1;

  h1 A2;
  h1 B2;
  h1 C2;
  h1 D2;
  h1 E2;
  h1 F2;
  h1 G2;
  h1 H2;
  h1 K2
;
  h1init(&A, 60, 0., 200., "Et jet 1");
  h1init(&B, 60, 0., 120., "Et jet 2");
  h1init(&C, 60, 0., 80., "Et jet 3");
  h1init(&D, 40, -5., 5., "Eta 1");
  h1init(&E, 40, -5., 5., "Eta 2");
  h1init(&F, 40, -5., 5., "Eta 3");
  h1init(&G, 48, 0., 120., "Met");
  h1init(&H, 50, 0., 1000., "Ht");
  h1init(&K, 100, 0., 10., "Njet");

  h1init(&A1, 60, 0., 200., "Et jet 1.1");
  h1init(&B1, 60, 0., 120., "Et jet 2.1");
  h1init(&C1, 60, 0., 80., "Et jet 3.1");
  h1init(&D1, 40, -5., 5., "Eta 1.1");
  h1init(&E1, 40, -5., 5., "Eta 2.1");
  h1init(&F1, 40, -5., 5., "Eta 3.1");
  h1init(&G1, 48, 0., 120., "Met.1");
  h1init(&H1, 50, 0., 1000., "Ht.1");
  h1init(&K1, 100, 0., 10., "Njet.1");

  h1init(&A2, 60, 0., 200., "Et jet 1.2");
  h1init(&B2, 60, 0., 120., "Et jet 2.2");
  h1init(&C2, 60, 0., 80., "Et jet 3.2");
  h1init(&D2, 40, -5., 5., "Eta 1.2");
  h1init(&E2, 40, -5., 5., "Eta 2.2");
  h1init(&F2, 40, -5., 5., "Eta 3.2");
  h1init(&G2, 48, 0., 120., "Met.2");
  h1init(&H2, 50, 0., 1000., "Ht.2");
  h1init(&K2, 100, 0., 10., "Njet.2");


  for (int j=0; j<9; j++) {
    while(i<9) {
      fgets(buf, 10, input);
      i++;
    }
  }

  for (int j=0; j<9; j++) {
    while(i<9) {
      fgets(buf, 10, inptr);
      i++;
    }
      }
  for (int j=0; j<9; j++) {
    while(i<9) {
      fgets(buf, 10, inpur);
      i++;
    }
  }

  int stuff = 0;
  while(stuff != EOF) {


    stuff = fscanf(input, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f, &g, &h, &k);
    h1fill(&A, a);
    h1fill(&B, b);
    h1fill(&C, c);
    h1fill(&D, d);
    h1fill(&E, e);
    h1fill(&F, f);
    h1fill(&G, g);
    h1fill(&H, h);
    h1fill(&K, k);

    if (stuff == EOF) break;
  }
  int stuff1 = 0;
  while(stuff1 != EOF) {


    stuff1 = fscanf(inptr, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &a1, &b1, &c1, &d1, &e1, &f1, &g1, &h1, &k1);
    h1fill(&A1, a1);
    h1fill(&B1, b1);
    h1fill(&C1, c1);
    h1fill(&D1, d1);
    h1fill(&E1, e1);
    h1fill(&F1, f1);
    h1fill(&G1, g1);
    h1fill(&H1, h1);
    h1fill(&K1, k1);

    if (stuff1 == EOF) break;
  }
  int stuff2 =0;
  while(stuff2 != EOF) {


    stuff2 = fscanf(inpur, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &a2, &b2, &c2, &d2, &e2, &f2, &g2, &h2, &k2);
    h1fill(&A2, a2);
    h1fill(&B2, b2);
    h1fill(&C2, c2);
    h1fill(&D2, d2);
    h1fill(&E2, e2);
    h1fill(&F2, f2);
    h1fill(&G2, g2);
    h1fill(&H2, h2);
    h1fill(&K2, k2);

    if (stuff2 == EOF) break;
  }

  h1plot(&A);
  h1plot(&B);
  h1plot(&C);
  h1plot(&D);
  h1plot(&E);
  h1plot(&F);
  h1plot(&G);
  h1plot(&H);
  h1plot(&K);

  h1dump_entries(&A, "a.dat");
  h1dump_entries(&B, "b.dat");
  h1dump_entries(&C, "c.dat");
  h1dump_entries(&D, "d.dat");
  h1dump_entries(&E, "e.dat");
  h1dump_entries(&F, "f.dat");
  h1dump_entries(&G, "g.dat");
  h1dump_entries(&H, "h.dat");
  h1dump_entries(&K, "k.dat");
  fclose(input);
  return 0;

}
