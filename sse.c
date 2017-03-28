// your C program using sse instructions

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Compile with: gcc -O2 -Wall float-triad-normal.c -o float-triad-normal -DN=.. -DR=..

// use -DN=.. and -DR=... at compilation
#define N 10
#define R 10

void get_walltime(double *wct) {
	struct timeval tp;
	gettimeofday(&tp,NULL);
	*wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}

int main() {
float *p,*newP;
int i,j;
double ts,te,mflops;
float k = 5.0;
float k1 = 0.5;
__m128 *vp, *vnewP

  // allocate test arrays
i=posix_memalign((void**)&p,16,P*N*sizeof(float));
	if(i!=0){printf("Wrong");
			exit(1);}

i=posix_memalign((void**)&newP,16,P*N*sizeof(float));
	if(i!=0){printf("Wrong");
			exit(1);}
 
  
  //initialize all arrays - cache warm-up
	for (i=0;i<R;i++) {
		for(j=0; j<N; j++){
			p[(i * N) + j]=(float)rand()/RAND_MAX;
			newP[(i * N) + j]=0;
			printf("%f\n", p[i][j]);
		}
   
	}
 
  // get starting time (double, seconds) 
	get_walltime(&ts);
	vp=(__m128 *)p;
	vnewP=(__m128 *)newP;
	
  // do triad artificial work
	for (i=1;i < R - 1; i++) {
		for (j=1; j < N - 1; j++) {
			*vnewP=_mm_add_ps(_mm_mul_ps(5.0,*vp),_mm_mul_ps (0.5,*vp[i-1]));
    		vp++; vnewP++;
	}
 
  // get ending time
	get_walltime(&te);
  
  // compute mflops/sec (2 operations per R*N passes)
	mflops = (R*N*2.0)/((te-ts)*1e6);
  
	printf("MFLOPS/sec = %f\n",mflops);

	return 0;
}
