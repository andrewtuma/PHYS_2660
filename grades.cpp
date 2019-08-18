#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
  double homework[15];
  double lab[15];
  double midterm;
  double final;
  char compid[8], first[30], last[30];
} Student;

double points(Student *s) {
  double sum = 0, actfinal, acthw, actmid, actlab;

  for (int i =0; i<15; i++) {
    actlab = s->lab[i];
    acthw = s->homework[i];
    if (actlab == -1) actlab = 10;
    if (acthw == -1) acthw = 100;
    sum = sum + actlab + acthw;
  }
  actmid = s->midterm;
  actfinal = s->final;
  if (actmid == -1) actmid = 100;
  if (actfinal == -1) actfinal = 100;
  sum = sum + actmid + actfinal;
  printf("Student %s %s (%s) has %lf points so far\n", s->first, s->last, s->compid, sum);
  return sum;
}

double percent(Student *s) {
  double perc = 0, labperc =0, hwperc =0;
  double mid, final;

  for (int i = 0; i<15; i++) {
    if (s->lab[i] == -1) {labperc += 100;} else labperc += s->lab[i];
    if (s->homework[i] == -1) {hwperc += 100;} else hwperc += s->homework[i];
  }
  if (s->midterm == -1) {mid = 100;} else mid =  s->midterm;
  if (s->final == -1) {final = 100;} else final = s->final;

  perc = labperc/150*15 + hwperc/552*40 + mid*0.2 + final*0.25;
  printf("Student %s %s (%s) has a %lf%% in the class.\n", s->first, s->last, s->compid, perc);
  return perc;
}



int main(int argc, char *argv[]) {
  FILE *grades = fopen(argv[1], "r");

  if(grades == NULL)
    printf("Error: no gradebook could be found.\n");
  else {

    char firstline[1000];
    fgets(firstline, 1000,grades);

    int status = 0;
    while(status != EOF){
      Student s;

      status = fscanf(grades, "%[^,],\"%[^,],%[^\"]\",", s.compid, s.last, s.first);
      if (status == EOF) break;

      for (int i=0; i<32; i++) {
      char var[15];
      if (i<15) {
        fscanf(grades, "%[^,],", var);
      if (var[0] == '-'){ s.homework[i] = -1;} else s.homework[i] = atof(var);
      } else if (i<30) {
        fscanf(grades, "%[^,],", var);
        if (var[0] == '-'){ s.lab[i-15] = -1;} else s.lab[i-15] = atof(var);
      } else if (i == 30) {
        fscanf(grades, "%[^,],", var);
        if (var[0] == '-')  {s.midterm = -1;} else s.midterm = atof(var);
      } else if (i == 31) {
        fscanf(grades, "%[^,],", var);
        if (var[0] == '-')  {s.final = -1;} else s.final = atof(var);
      }
    }
    points(&s);
    percent(&s);
    printf("\n");
  }

  }
  fclose(grades);
  return 0;
}
