// your C program without sse instructions

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Compile with: gcc -O2 -Wall image.c -o image -DN=.. -DR=..

// use -DN=.. and -DR=... at compilation
#define N 100
#define R 10

void get_walltime(double *wct) {
	struct timeval tp;
	gettimeofday(&tp,NULL);
	*wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}

int main() {
float *p[R],*newP[R];
int i,j;
double ts,te,mflops;
float k = 5.0;
float k1 = 0.5;

  // allocate test arrays
for(i=0;i<R;i++){
	p[i] = (float *)malloc(N*sizeof(float));
    newP[i] = (float *)malloc(N*sizeof(float));
}
  
	if (p==NULL) exit(1);
	if (newP==NULL)	exit(1);
 
  
  //initialize all arrays - cache warm-up
	for (i=0;i<R;i++) {
		for(j=0; j<N; j++){
			p[i][j]=(float)rand()/RAND_MAX;
            newP[i][j] = 0;
			printf("%f\n", p[i][j]);
		}
   
	}
 
  // get starting time (double, seconds) 
	get_walltime(&ts);
  
  // do triad artificial work
	for (i=1;i < R - 1; i++) {
		for (j=1; j < N - 1; j++) {
			newP[i][j] =p[i][j] * k + (p[i-1][j] + p[i-1][j-1] + p[i][j-1] + p[i+1][j] + p[i+1][j+1] + p[i][j+1] + p[i-1][j+1] + p[i+1][j-1]) * k1 ;
		}
	}
 
  // get ending time
	get_walltime(&te);
  
  // compute mflops/sec (2 operations per R*N passes)
	mflops = (R*N*2.0)/((te-ts)*1e6);
  
	printf("MFLOPS/sec = %f\n",mflops);

	return 0;
}
