nclude <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#define N 2048
#define ZERO (double)(0.0)
#define THREE (double)(3.0)

double getrusage_sec(){

  struct rusage t;
  struct timeval tv;
  getrusage(RUSAGE_SELF, &t);
  tv = t.ru_utime;
  return tv.tv_sec + (double)tv.tv_usec*1e-6;

}
void dgemm_(char *transa, char *transb, int *m, int *n, int *k,
double *alpha, double *A, int *ldA, double *B, int *ldB,
double *beta , double *C, int *ldC);//プロトタイプ宣言
int main(){

  static int i,j,k;
  static double a[N][N],b[N][N],c[N][N],s;
　static double a1[N*N],b1[N*N],c1[N*N];
  static double t1,t2;

  srand(1);

  for(i=0;i<N;i++){
        for(j=0;j<N;j++){
      a1[i*N+j]=rand()/(double)RAND_MAX;//一次元
      b1[i*N+j]=rand()/(double)RAND_MAX;//一次元
      c1[i*N+j]=0;//一次元
        }
  }

  t1 = getrusage_sec();



  void dgemm_('N', 'N', &N,&N,&N, 1, a1,&N, b1, &N, 0, c1,&N);

  t2 = getrusage_sec();

  printf("time = %10.5f\n", t2 - t1);

  s=ZERO;

  for(i=0;i<N;i+=10){
    for(j=0;j<N;j+=10){
      if(a[i*N+j]>s){
        s=a1[i*N+j];
      }
      if(b[i*N+j]>s){
        s=b1[i*N+j];
      }
      if(c[i*N+j]>s){
        s=c1[i*N+j];
      }
    }
  }

  printf("%f\n",s);

  return 0;
}
