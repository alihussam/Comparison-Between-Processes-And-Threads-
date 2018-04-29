# Comparison Between Processes and Threads
## Idea:
The main idea of the project is comparision between Process and Threads when parallel programming is used.

## Advantages of Using Threads:
On a multiprocessor system, multiple threads can concurrently run on multiple CPUs. Therefore, multithreaded programs can run much faster than a program running on a uniprocessor system. They can also be faster than a program using multiple processes, because threads require fewer resources and generate less overhead.

## Advantages of Using Multiprocesses:
The advantages of the multiprocessing system are:
### Increased Throughput:
By increasing the number of processors, more work can be completed in a unit time.
### Cost Saving
Parallel system shares the memory, buses, peripherals etc. Multiprocessor system thus saves money as compared to multiple single systems.
## Technologies Used:
1. Pthreads
2. Process creation using fork() system call.
3. Shared memory
4. Ubuntu

## Implementaion:
The following programs are implimented using pthreads and by making processes using fork() and their time of execution is calculated. Shared memory segments are created between programs using multiple processes because processes have their own individual memory unlike threads, they need implimentaion of shared memory as they use shared memory space.
## Project Result
The processes and threads are independent sequences of execution, the typical difference is that threads run in a shared memory space, while processes run in separate memory spaces. ... Threads exist within a process and every process has at least one thread. 
Threads have direct access to the data segment of its process but a processes have their own copy of the data segment of the parent process. For most problems, multithreading is probably significantly faster than using multiple processes.
## Important Points
In multiprocessing programmer is forced to impliment a program keeping in mind that what is beging shared between processes.
Thread share every thing this adds the overhead of protecting everything which will be shared between threads.




