
#include <stdlib.h>		// For: exit, drand48, malloc, free, NULL, EXIT_FAILURE
#include <stdio.h>		// For: perror
#include <string.h>		// For: memset

#include <float.h>		// For: DBL_EPSILON
#include <math.h>		// For: fabs

#include <sys/time.h>		// For struct timeval, gettimeofday
#include <unistd.h>
double wall_time()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	printf()
	return 1. * t.tv_sec + 1.e-6 * t.tv_usec;
}


int main(void){
	double seconds=0.1;
	 seconds=wall_time();
	printf("time is %lf",seconds);
	//return 0;
}
