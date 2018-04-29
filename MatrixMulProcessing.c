#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#define max 10


void multi(int **matA,int **matB,int **matC,int *dividing_variable,pid_t pid)
{
    printf("%d",*dividing_variable);
    int core = *dividing_variable++;
 
    printf("\nMatrixMulProcessing [INFO] PID: %d performing calculations..",pid);
    for (int i = core * max / 4; i < (core + 1) * max / 4; i++) 
        for (int j = 0; j < max; j++) 
            for (int k = 0; k < max; k++) 
                matC[i][j] += matA[i][k] * matB[k][j];
}


int main(){
   pid_t pid;
   clock_t start, end;
   double cpu_time_used;
   
    int shmid,shmid2,shmid3,divid;
    int *shm_array[max],*shm_array2[max],*shm_array3[max],*div;
    if((shmid = shmget(IPC_PRIVATE,sizeof(int[max][max]),IPC_CREAT | 0666))<0){
        perror("shmget");
        _exit(-1);
    }
    if((shm_array[max] = shmat(shmid,NULL,0)) == (int *)-1){
        perror("shmat");
        _exit(-1);
    }
    if((shmid2 = shmget(IPC_PRIVATE,sizeof(int[max][max]),IPC_CREAT | 0666))<0){
        perror("shmget");
        _exit(-1);
    }
    if((shm_array2[max] = shmat(shmid2,NULL,0)) == (int *)-1){
        perror("shmat");
        _exit(-1);
    }
    if((shmid3 = shmget(IPC_PRIVATE,sizeof(int[max][max]),IPC_CREAT | 0666))<0){
        perror("shmget");
        _exit(-1);
    }
    if((shm_array3[max] = shmat(shmid3,NULL,0)) == (int *)-1){
        perror("shmat");
        _exit(-1);
    }
 if((divid = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | 0666))<0){
        perror("shmget");
        _exit(-1);
    }
    if((*div = shmat(divid,NULL,0)) == (int *)-1){
        perror("shmat");
        _exit(-1);
    }
     *div=0;
     for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            shm_array[i][j] = rand() % 10;
            shm_array2[i][j] = rand() % 10;
        }
    }
     start=clock();
     pid= fork();
     if(pid==0){
        multi(shm_array,shm_array2,shm_array3,div,pid);
     }
     if(pid>0){
       wait(NULL);
       multi(shm_array,shm_array2,shm_array3,div,pid);
       if(shmdt(shm_array)==-1){
        perror("shmdt");
        _exit(-1);
        }
      if(shmctl(shmid,IPC_RMID,NULL)==-1){
        perror("shmctl");
        _exit(-1);
       }
       if(shmdt(shm_array2)==-1){
        perror("shmdt");
        _exit(-1);
        }
      if(shmctl(shmid2,IPC_RMID,NULL)==-1){
        perror("shmctl");
        _exit(-1);
       }
       if(shmdt(shm_array3)==-1){
        perror("shmdt");
        _exit(-1);
        }
      if(shmctl(shmid3,IPC_RMID,NULL)==-1){
        perror("shmctl");
        _exit(-1);
       }
    // printf("\n %d",dividing_variable); 
     end=clock();
     printf("\n");
         printf("mul of Matrix A and B\n");
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) 
            printf("%d  ", shm_array3[i][j]);       
        printf("\n");
    }

    cpu_time_used = (double)( (end - start))/ CLOCKS_PER_SEC; 
		printf("\ncpu time => %f",cpu_time_used); 
    }
    return 0;





}


