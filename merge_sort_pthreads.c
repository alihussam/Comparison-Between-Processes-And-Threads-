#include<pthread.h>
#include<stdio.h>
#include<time.h> 
#include<stdlib.h>
pthread_t thread1,thread2;
struct parameter{
        long a[100000];
	int mid;
	int right;
	int left;

};

 

void * mergeSort(void *ptr)
{
 	double cpu_time_used;
	struct parameter data;
	  data = *(struct parameter*)ptr;

	  struct parameter data2;
	  data2 = *(struct parameter*)ptr;

   	 struct parameter data3;
	  data3 = *(struct parameter*)ptr;
	clock_t start ;
	
	clock_t end ;
	

    if (data.left < data.right)
    {
	
        data.mid = data.left+(data.right-data.left)/2;
        data2.left=data.left;
        data2.mid=data.mid+1;
	data2.right=data.mid; 
	
        data3.left=data.mid;
	data3.right=data.right;

	
	pthread_create(&thread1,0, mergeSort,&data2);
	pthread_create(&thread2,0, mergeSort,&data3);
       
       
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
        merge(data.a, data.left, data.mid, data.right);
	
	
    }
	
	
}
 
void merge(long a[], int left, int mid, int right);
void printArray(long A[], int size);
 
int main(){	
        int count;  
	pthread_t thread3;
        struct parameter data1;
	double cpu_time_used;
	clock_t start, end;
        int arr_size = sizeof(data1.a)/sizeof(data1.a[0]);
 
	for(count=0;count<100000;count++){
		data1.a[count]=(rand()/1000000);
		
	}

       printf("Given array is \n");  
    // printArray(data1.a, arr_size);	
    	 
	start=clock();
     pthread_create(&thread3,0, mergeSort,&data1);
     pthread_join(thread3,NULL);
		
end=clock();
cpu_time_used = (double)( (end - start))/ CLOCKS_PER_SEC; 
		printf("\ncpu time taken => %f",cpu_time_used); 
    printf("\nArray Becomes Sorted \n");
   
	printf("\n");
    return 0;
}


void merge(long a[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 =  right - mid;
    int LFT[n1], RGT[n2];
 
    
    for (i = 0; i < n1; i++)
        LFT[i] = a[left + i];
    for (j = 0; j < n2; j++)
        RGT[j] = a[mid + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; //  first subarray
    j = 0; // second subarray
    k = left; //  merged subarray
    while (i < n1 && j < n2)
    {
        if (LFT[i] <= RGT[j])
        {
            a[k] = LFT[i];
            i++;
        }
        else
        {
            a[k] = RGT[j];
            j++;
        }
        k++;
    }
 
   while (i < n1)
    {
        a[k] = LFT[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        a[k] = RGT[j];
        j++;
        k++;
    }
	
}
void printArray(long A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%lo ", A[i]);
    printf("\n");
}
