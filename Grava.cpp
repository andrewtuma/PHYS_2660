// Name:   Andrew Tuma
// UserId: alt3zq
// Homework #: 9
// Problem #: 1
// Program Name: alt3zq_grava.cpp
// Pledge Signature: I did not receive help on this assignment. Andrew Tuma


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


//- a position coordinate (x,y,z) (stored as a 3 component array)
//- a velocity vector (vx,vy,vz) (stored as a 3 component array)
//- a force vector (fx,fy,fz) (stored as a 3 component array)
//- a mass, m [kg]
typedef struct{
  double s_vec[3];  // space(position) vector
  double v_vec[3];  // velocity vector
  double f_vec[3];  // force vector
  double com[3];    //c.o.m
  double dist[3];   // vec difference between each comp and com
  double mag;       // mag difference between objects
  double mass;
} body;

const int MAX_BODIES = 100;
body bodies[MAX_BODIES]; //array of bodies




const double G = 6.67*pow(10,-11);

void COM(body *bodies, int count) {

  double M=0, R[3]={0,0,0};
  for (int i = 0; i<count; i++){
    R[0] += bodies[i].s_vec[0] * bodies[i].mass;
    R[1] += bodies[i].s_vec[1] * bodies[i].mass;
    R[2] += bodies[i].s_vec[2] * bodies[i].mass;
    M += bodies[i].mass;
  }
  bodies[0].com[0] = R[0]/M;
  bodies[0].com[1] = R[1]/M;
  bodies[0].com[2] = R[2]/M;

}

void dist(body *bodies, int count) {

  for (int i=0; i<count; i++) {
    bodies[i].mag=sqrt(pow(bodies[i].s_vec[0] - bodies[0].com[0],2)+pow(bodies[i].s_vec[1] - bodies[0].com[1],2)+pow(bodies[i].s_vec[2] - bodies[0].com$

 bodies[i].dist[0] = bodies[i].s_vec[0] - bodies[0].com[0];
 bodies[i].dist[1] = bodies[i].s_vec[1] - bodies[0].com[1];
 bodies[i].dist[2] = bodies[i].s_vec[2] - bodies[0].com[2];
  }
}

void Fgrav(body *bodies, int count ) {

  for (int i=0; i<count; i++) {
    for ( int j=0; j<count; j++) {
      if (i==j) continue;
      bodies[i].f_vec[0] += G*bodies[i].mass*bodies[j].mass*(bodies[i].s_vec[0]-bodies[j].s_vec[0])/pow(sqrt(pow(bodies[i].s_vec[0]-bodies[j].s_vec[0],$
      bodies[i].f_vec[1] += G*bodies[i].mass*bodies[j].mass*(bodies[i].s_vec[1]-bodies[j].s_vec[1])/pow(sqrt(pow(bodies[i].s_vec[0]-bodies[j].s_vec[0],$
      bodies[i].f_vec[2] += G*bodies[i].mass*bodies[j].mass*(bodies[i].s_vec[2]-bodies[j].s_vec[2])/pow(sqrt(pow(bodies[i].s_vec[0]-bodies[j].s_vec[0],$
    }
  }
}

int read_data(char* file, body *bodies){
  int num =0; //number of entries read from file
  int status;
  FILE *file_p = fopen(file, "r");
  if (file_p==NULL) {
    printf("Error: File not found!\n");
    return -1;
  }

  while(num < MAX_BODIES) {
    status = fscanf(file_p, "%lf %lf %lf %lf %lf %lf %lf",
                    &bodies[num].s_vec[0],
                    &bodies[num].s_vec[1],
                    &bodies[num].s_vec[2],
                    &bodies[num].v_vec[0],
                    &bodies[num].v_vec[1],
                    &bodies[num].v_vec[2],
                    &bodies[num].mass);
    if (status == EOF) break;
    num++;
  }
  return num;
}

int main (int argc, char *argv[]) {

   int count = read_data(argv[1], bodies);
   Fgrav(bodies, count);
   dist(bodies,count);
   COM(bodies, count);


   printf("COM\t%8.2lg\t%8.2lg\t%8.2lg\n", bodies[0].com[0], bodies[0].com[1], bodies[0].com[2]);

   for (int i=0; i<count; i++) {
     printf("Force\t%8.2lg\t%8.2lg\t%8.2lg\n", bodies[i].f_vec[0], bodies[i].f_vec[1], bodies[i].f_vec[2]);
   }

  return 0;
}

