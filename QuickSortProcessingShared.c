#include<stdio.h>
#include<sys/wait.h> 
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
void swap(int *x,int *y){
   int temp=*x;
   *x=*y;
   *y=temp;
}

int partition(int array[], int start, int end){
    int pivot = array[end];
    int index = (start - 1);	//done according to our logic
 
    for (int i = start; i <= end - 1; i++){
        if (array[i] <= pivot){
            index++;
            swap(&array[index], &array[i]);
        }
    }
    swap(&array[index + 1], &array[end]);
    return (index + 1);
}

void quickSort(int array[], int start, int end){
    int leftPid,rightPid;
    if (start < end){
        int partIndex = partition(array, start, end);
        leftPid=fork();
        if(leftPid<0){
		perror("QuickSortProcessing [ERROR] Left Child Process not Created!");
		_exit(-1);
        }
        else  if(leftPid==0){
	        quickSort(array, start, partIndex - 1);
        }
	else{
		rightPid=fork();
		if(rightPid<0){
		    perror("QuickSortProcessing [ERROR] Right Child Process not Created!");
		    _exit(-1);
                }		
		else if(rightPid==0)
		    quickSort(array, partIndex + 1, end);
        }
   	int returnStatus=0;
        waitpid(leftPid,&returnStatus,0);
        waitpid(rightPid,&returnStatus,0);
    }
}
 
void display(int array[], int size){
    for (int i=0; i < size; i++)
        printf("%d ", array[i]);
}
 
// Driver program to test above functions
int main(){
    int shmid, size=6;
    int *shm_array;
    size_t shm_size = sizeof(int)*size;
    if((shmid = shmget(IPC_PRIVATE,shm_size,IPC_CREAT | 0666))<0){
        perror("shmget");
        _exit(-1);
    }
    if((shm_array = shmat(shmid,NULL,0)) == (int *)-1){
        perror("shmat");
        _exit(-1);
    }
    for (int i=0;i<size;i++) scanf("%d",&shm_array[i]);
    quickSort(shm_array, 0, size-1);
    printf("\nQuickSortProcessing [INFO] CurrentPid: %d , Sorted array: ",getpid());
    display(shm_array, size);
    if(shmdt(shm_array)==-1){
        perror("shmdt");
        _exit(-1);
    }
    if(shmctl(shmid,IPC_RMID,NULL)==-1){
        perror("shmctl");
        _exit(-1);
    }
    return 0;
}
