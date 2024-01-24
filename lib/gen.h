#ifndef GEN_H
#define GEN_H

void gen_init();
double gen_rand(double);
int gen_int(int, int);
void gen_vector(double *, double, double, int);
void gen_vector_zto(double *, int);
void gen_vector_int(int *, int, int, int);
void statistic_log(double, double, int);

#endif
