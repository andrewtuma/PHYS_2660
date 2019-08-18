// program grav1                                                                                                                                        
//   read in a file (filename given on the command line)                                                                                                
//   file format is: x y z vx vy vz m r                                                                                                                 
//   place data into an array of structures, calculate the C.O.M. of the system                                                                         
//   calculate the force experienced by each object due to all others                                                                                   

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
  double s_vec[3];  // space(position) vector                                                                                                           
  double v_vec[3];  // velocity vector                                                                                                                  
  double f_vec[3];  // force vector                                                                                                                     
  double mass;
} body;

const int MAX_BODIES = 100;

//function to read in data file                                                                                                                         
int read_data(char* file, body *bodies);

// function to calculate the center of mass                                                                                                             
void center_of_mass(body *bodies, int nbodies, double *cmass);

// calc. distance^2 between two bodies                                                                                                                  
double distance2(double *svec1, double *svec2);
// calculate vector = v1 - v2                                                                                                                           
void vsub(double *v1, double *v2, double *v1m2);

// calc. forces on each body                                                                                                                            
void forces(body *bodies, int nbodies);




// The main program is very simple, it directs the work to our functions                                                                                
// and prints the final answer to the screen                                                                                                            
int main(int argc, char *argv[]){

  FILE *output = fopen("location.dat", "w");
  body bodies[MAX_BODIES];
  int nbodies;
  double timesim, timestep;
  double cmass[3];
  if (argc < 4) {
    printf("Please enter the data file name, total time, and time step into the command line.\n");
    return 1;
  }
  nbodies = read_data(argv[1],bodies);
  timesim = atof(argv[2]);
  timestep = atof(argv[3]);

  for(int i =0; i<3; i++) {
    double a;
    for(int t =0; t < timesim; t++) {
      t = (double)t + timestep;
        for(int n=0; n<3; n++) {
          a = bodies[i].f_vec[n] / bodies[i].mass;
          bodies[i].s_vec[n] +=  bodies[i].v_vec[n]*t + .5*a*t*t;
        }
     fprintf(output,"%lg %lg %lg \n", bodies[i].s_vec[0], bodies[i].s_vec[1], bodies[i].s_vec[2]);
    }
  }

  if (!nbodies) {
    printf("No data read\n");
    return 1;
  }
  center_of_mass(bodies,nbodies,cmass);  // calc center of mass                                                                                         
  printf("Center of Mass (x,y,z): ( %f, %f, %f )\n",cmass[0],cmass[1],cmass[2]);

  forces(bodies, nbodies);
  printf("\n Gravitational forces acting on bodies\n");
  printf("          X          Y          Z     (Newtons)\n");
  for (int i=0; i<nbodies; i++)
    printf("%3i: %10.2g %10.2g %10.2g\n",i,
           bodies[i].f_vec[0],bodies[i].f_vec[1],bodies[i].f_vec[2]);

  return 0;
}



int read_data(char* file, body *bodies){
  int num=0; /* number of entries read from file */
  int status;
  FILE *file_p = fopen(file,"r");

  if (!file_p) {
    printf("File error\n");
    return 0;
  }
  while(num<MAX_BODIES) {
    status=fscanf(file_p,"%lf %lf %lf %lf %lf %lf %lf",
                  &bodies[num].s_vec[0], &bodies[num].s_vec[1], &bodies[num].s_vec[2],
                  &bodies[num].v_vec[0], &bodies[num].v_vec[1], &bodies[num].v_vec[2],
                  &bodies[num].mass);
    if (status==EOF || status!= 7) break;
    num++;
  }
  printf("Read %d bodies from input file\n",num);
  return num;
}

void center_of_mass(body *bodies, int nbodies, double *cmass){
  int i,j;
  double sum_mass=0;
  for (i=0 ; i<3 ; i++) cmass[i] = 0;
  for (j=0 ; j<nbodies ; j++){
    sum_mass += bodies[j].mass;
    for (i=0 ; i<3 ; i++)
      cmass[i] += bodies[j].s_vec[i]*bodies[j].mass;
  }
  for (i=0 ; i<3 ; i++) cmass[i] /= sum_mass;
}

double distance2(double *svec1, double *svec2){
  double dist2=0;
  int i;
  for (i=0; i<3; i++)
    dist2 += (svec1[i]-svec2[i])*(svec1[i]-svec2[i]);
  return dist2;
}

void vsub(double *v1, double *v2, double *v1m2){
  int i;
  for (i=0; i<3; i++) v1m2[i] = v1[i]-v2[i];
}

void forces(body *bodies, int nbodies){
  double dist, dist2, force;
  double dirvec[3];
  const double G = 6.67e-11;
  for(int i=0; i<nbodies; i++) {  // init all forces to 0                                                                                               
    bodies[i].f_vec[0]=0;
    bodies[i].f_vec[1]=0;
    bodies[i].f_vec[2]=0;
  }
  // loop over all bodies and calculate force on body[i] from body[j] & visa versa                                                                      
  for(int i=0; i<nbodies; i++){
    for(int j=i+1; j<nbodies; j++){
      dist2 = distance2(bodies[i].s_vec,bodies[j].s_vec);  // distance^2 from [j] to [i]                                                                
      dist = sqrt(dist2);
      vsub(bodies[i].s_vec,bodies[j].s_vec,dirvec);  // vector from [j] -> [i]                                                                          
      dirvec[0] /= dist;
      dirvec[1] /= dist; // dirvec = unit vector pointing from body[j] -> body[i]                                                                       
      dirvec[2] /= dist;
      force = bodies[i].mass*bodies[j].mass*G/dist2;  // m_i*m_j*G/R^2                                                                                  
      for(int k=0; k<3; k++) {
        bodies[i].f_vec[k] += -force*dirvec[k];  // force of j acting on i                                                                              
        bodies[j].f_vec[k] +=  force*dirvec[k];  // force of i acting on j                                                                              
      }
    }
  }
}
