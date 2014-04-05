#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_STR 256

void initrand(void) {
  srand(time(0));
}

float float_rand(void) {
  return rand() / (float)RAND_MAX;
}

float calc_pi(unsigned long points) {
  unsigned long int z = 0, inside = 0;
  float x, y, rootxy, calculated_pi;

  while(z < points) {
    x = float_rand();
    y = float_rand();

    rootxy = sqrt(pow(x, 2) + pow(y, 2));

    if (rootxy <= 1.0) inside++;
    z++;
  }

  calculated_pi = 4 * (float)inside / points;
  return calculated_pi;
}

int main(int argc, char** argv) {
  size_t size = MAX_STR;
  unsigned long int n = 0;
  char *str;
  float calculated_pi;

  str = (char *)malloc(size);
  if(!str) {
    fprintf(stderr, "malloc() failed. exiting\n");
    exit(EXIT_FAILURE);
  }

  printf("Enter number of points to check> ");
  getline(&str, &size, stdin);
  sscanf(str, "%lu", &n);

  if(n == 0) {
    fprintf(stderr, "Please Enter a number greater than zero.\n");
    exit(EXIT_FAILURE);
  }

  initrand();
  calculated_pi = calc_pi(n);

  printf("PI calculated using the Monte Carlo method with %lu points: %f\n", n, calculated_pi);

  return 0;
}
