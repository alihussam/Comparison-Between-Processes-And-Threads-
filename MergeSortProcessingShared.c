#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h> 
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void merge(int array[], int start, int middle, int end){
    int left  = middle - start + 1;
    int right =  end - middle;
    int leftArr[left], rightArr[right];

    for(int i = 0; i < left; i++)
        leftArr[i] = array[start + i];
    for(int i = 0; i < right; i++)
        rightArr[i] = array[middle + 1+ i];
 
    int i=0,j=0,k=start;
    while(i < left && j < right){
        if (leftArr[i] <= rightArr[j]){
            array[k] = leftArr[i];
            i++;
        }
        else{
            array[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while(i < left){
        array[k] = leftArr[i];
        i++; k++;
    }
    while (j < right){
        array[k] = rightArr[j];
        j++; k++;
    }
}

void mergeSort(int array[], int start, int end){
    if (start < end){
        int leftPid,rightPid;
        int middle = start+(end-start)/2;
        leftPid=fork();
	if(leftPid<0){
		perror("MergeSortProcessing [ERROR] Left Child Process Not Created!");
		_exit(-1);
	}
	else if(leftPid == 0){
		mergeSort(array, start, middle);
	}
        else{
		rightPid=fork();
		if(rightPid < 0){
			perror("MergeSortProcessing [ERROR] Right Child Process Not Created!");
			_exit(-1);
		}
		if(rightPid==0)
        		mergeSort(array, middle+1, end);
 	}
	wait(NULL);
	wait(NULL);
        merge(array, start, middle, end);
    }
}

void display(int array[], int size){
    for(int i=0; i < size; i++)
        printf("%d ", array[i]);
}

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
    mergeSort(shm_array, 0, size-1);
    printf("\nMergeSortProcessing [INFO] CurrentPid: %d , Sorted array: ",getpid());
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
