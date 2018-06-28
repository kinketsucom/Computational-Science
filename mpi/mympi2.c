nclude<stdio.h>
#include<mpi.h>

#define L 1000LL
#define R 2000000LL

int main(int argc, char **argv){
  int my_rank, num_proc;
  long long n, i, j, t;
  long long myL, myR;
  long long answer=0;
  long long sum=0;
  long long tmp=0;
  double t1, t2;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  MPI_Barrier(MPI_COMM_WORLD);
  t1 = MPI_Wtime();

  tmp = (R-L+1) % num_proc;

  myL = (R-L+1) / num_proc * my_rank + L;
  myL += (tmp > my_rank ? my_rank : tmp);

  myR = (R-L+1) / num_proc * (my_rank + 1) + L;
  myR += (tmp > my_rank+1 ? my_rank+1 : tmp);

  sum = 0;
  for(i=myL; i<myR; i++){
    t = i;
    for(j=2; j*j<=i; j++){
      if(i%j==0){
        t = j;
        break;
      }
    }
    sum += t;
  }
  MPI_Reduce(&sum,&answer,1,MPI_LONG_LONG,MPI_SUM,0,MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);
  t2 = MPI_Wtime();


  if(my_rank==0){
    printf("answer %lld\n", answer);
    printf("time %f\n", t2-t1);
  }

  MPI_Finalize();
  return 0;
}
