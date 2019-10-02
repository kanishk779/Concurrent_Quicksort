#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	return ;
}
int * shareMemory_Allocator(size_t size)
{
    key_t mem_key = IPC_PRIVATE;
    int shm_id = shmget(mem_key, size, IPC_CREAT | 0666);
    return (int*)shmat(shm_id, NULL, 0);
}
int partition(int *arr,int left ,int right)
{
	int x = arr[right];
	int key = left - 1;
	for(int i=left;i<right;i++)
	{
		if(arr[i] <= x)
		{
			key++;
			swap(arr+i,arr+key);
		}
	}
	swap(arr+key+1,arr+right);
	return key+1;
}
int randomized_partition(int *arr,int left,int right)
{
	int random = rand()%(right-left+1);
	swap(arr+right,arr+left+random);
	return partition(arr,left,right);
}
void quicksort(int *arr, int left, int right)
{
	if(left < right)
	{
		int pivot = partition(arr,left,right);
		quicksort(arr,left,pivot-1);
		quicksort(arr,pivot+1,right);
	}
}

void concurrent_quicksort(int * arr,int left,int right)
{
	if(left < right)
	{
		/*
		* if(right - left + 1 <= 5)
		* {
		*	insertion sort
		* }
		*/
		int pivot = rand() % (right - left  + 1) + left;
		swap(&arr[right], &arr[pivot]);
		int p = partition(arr, left, right);
		int left_sort_pid = fork();
		if(left_sort_pid == 0)
		{
			concurrent_quicksort(arr,left,p-1);
			exit(0);
		}
		else
		{
			int right_sort_pid = fork();
			if(right_sort_pid == 0)
			{
				concurrent_quicksort(arr,p+1,right);
				exit(0);
			}
			else
			{
				int status_left,status_right;
				waitpid(left_sort_pid, &status_left, 0);
				waitpid(right_sort_pid, &status_right, 0);
			}
    }
  }
}

void randomized_quicksort(int *arr,int left ,int right)
{
	if(left < right)
	{
		int pivot = randomized_partition(arr,left,right);
		randomized_quicksort(arr,left,pivot-1);
		randomized_quicksort(arr,pivot+1,right);
	}
}
int main()
{
	int * arr;
	int n;
	printf("give the size\n");
	scanf("%d",&n);

	arr = (int *)shareMemory_Allocator(n*sizeof(int));
	printf("give the elements\n");
	for(int i=0;i<n;i++)
		scanf("%d",arr+i);
	printf("the array received\n");
	
	for(int i=0;i<n;i++)
		printf("%d\n", arr[i]);
	printf("calling quicksort\n");
	randomized_quicksort(arr,0,n-1);
	printf("quicksort over\n");
	for(int i=0;i<n;i++)
		printf("%d\n", arr[i]);
	return 0;
}