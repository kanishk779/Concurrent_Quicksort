# Concurrent_Quicksort
## Objectives
The Objective of this project is to develop a concurrent quicksort.
1. First, we try to analyze the runtime using the process to handle sub-tasks.
2. Second, we try to analyze the runtime using the normal quicksort program.

## My Implementation
* As the quicksort algorithm is a divide and conquer algorithm it is natural and easy to make it concurrent.
* The program starts with asking the user for input.
* Than concurrent_quicksort is called.
* The method first find the pivot by using randomization and than creates two process to sort the left sub-array and right sub-array.
* Since the processes do not share memory like threads do if they are of the same process, we need to create a shared memory.
* This shared memory stores the array.
* The recursive call ends when the number of elements remaining is less than or equal to five.
* At last the runtime is evaluated by calling both the concurrent quicksort and simple single process quicksort. 
* real time used by NORMAL QUICKSORT is 0.000000
* cpu time used by NORMAL QUICKSORT is 0.001431
* real time used by CONCURRENT QUICKSORT is 0.000000
* cpu time used by CONCURRENT QUICKSORT is 0.000759
