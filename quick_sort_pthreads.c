
#include<stdio.h>
#include<stdio.h>
#include<time.h> 
#include<pthread.h>
 
void swap(int* a, int* b);
void * quickSort(void *vptr);
int partition (int arr[], int low, int high);
void printArray(int arr[], int size);

pthread_t thread1,thread2;
struct parameter
{
         int high;
	long arr[100000];
	int low;
};
 

int main()
{
    int j;  
  pthread_t thread3;
  struct parameter data1;

double cpu_time_used;
	clock_t start, end;
        int arr_size = sizeof(data1.arr)/sizeof(data1.arr[0]);

    for(j=0;j<100000;j++)
	{
		data1.arr[j]=(rand()/1000000);
		
	}

start=clock();
     pthread_create(&thread3,0, quickSort,&data1);
     pthread_join(thread3,NULL);
		
end=clock();
cpu_time_used = (double)( (end - start))/ CLOCKS_PER_SEC; 
		printf("\nTime Taken => %f",cpu_time_used); 
    
          
	printf("\n");


    return 0;
}
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void * quickSort(void *vptr /*int arr[], int low, int high*/)
{
    struct parameter data;
	  data = *(struct parameter*)vptr;

	  struct parameter data2;
	  data2 = *(struct parameter*)vptr;

   	 struct parameter data3;
	  data3 = *(struct parameter*)vptr;
       

    if (data.low < data.high)
    {
       
        int pi = partition(data.arr, data.low, data.high);
 
        
        data2.low=data.low;
        data2.high=pi-1;
         
        data3.low=pi+1;
        data3.high=data.high;

        pthread_create(&thread1,0, quickSort,&data2);
	pthread_create(&thread2,0, quickSort,&data3);

        pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
    }
}
 


int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    
    int i = (low - 1);  
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;   
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

